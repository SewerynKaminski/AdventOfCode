#include "day"
#include <ranges>
#include <iomanip>
#include <unordered_set>
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(1
2
-3
3
-2
0
4)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
struct S{
    int64_t idx,v;
};

std::vector<S> parse( std::istream& s ) {
    std::vector<S> input {};
    int64_t idx=0;
    std::string line;
    while ( getline( s, line ) ) {
        input.push_back ( {idx++, stoll(line)} );
    }
    return input;
}

//---------------------------------------------------------------------------//
auto sum( std::vector<S>& input ) {
    const int64_t T = input.size();
    for( int64_t i=0; i < T;i++) {
        if ( input[i].v==0 ) {
            return input[(i+1000)%T].v + input[(i+2000)%T].v + input[(i+3000)%T].v;
        }
    }
    return (int64_t)0;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    auto input = parse( file );
    const int64_t T = input.size();

    for ( int64_t i = 0; i < T; i++ ) {
        for ( int64_t j = 0; j < T; j++ ) {
            if ( input[j].idx == i ) {
                auto jumps = input[j].v % (T-1);
                jumps = (jumps + T - 1) % (T-1);
                for( int64_t jj = j; jj < j+jumps ; jj++ ) {
                    std::swap ( input[ jj % T ], input[ (jj + 1) % T] );
                }
                break;
            }
        }
    }

    ans = sum ( input );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    auto input = parse( file );
    const int64_t T = input.size();

    constexpr int64_t KEY = 811589153;

    for ( int r = 0 ; r < 10; r++ ) {
        for ( int64_t i = 0; i < T; i++ ) {
            for( int64_t j = 0; j < T; j++ ) {
                if ( input[j].idx == i ) {
                    int64_t jumps = (input[j].v * KEY) % (T-1);
                    jumps = (jumps+T-1) % (T-1);
                    for ( int64_t jj = j; jj < j+jumps ; jj++ ) {
                        std::swap ( input[ jj % T ], input[ (jj + 1) % T] );
                    }
                    break;
                }
            }
        }
    }
    ans = KEY * sum ( input );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
