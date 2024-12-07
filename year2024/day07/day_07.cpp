#include "day"
#include <cmath>
//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
struct S {
    uint64_t test_value;
    ::std::vector<uint64_t> numbers;
};

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    ::std::vector<S> ret;
    ::std::string line;
    while ( ::std::getline( file, line ) ) {
        std::istringstream l(line);
        uint64_t a,v; char sep;
        l >> a >> sep;
        ret.push_back( { a, ::std::vector<uint64_t>{} } );
        while( !l.eof() ) {
            l >> v;
            ret.back().numbers.push_back(v);
        }
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    for ( auto& d : data ) {
        int operations = d.numbers.size()-1;
        auto len = 1ull << operations;
        for ( uint i=0; i < len; i++ ) {
            uint64_t evaluated = d.numbers[0];
            for ( uint in=1; in < d.numbers.size(); in++ ) {
                uint mask = 1 << (in-1);
                if ( i&mask ) {
                    evaluated += d.numbers[in];
                } else {
                    evaluated *= d.numbers[in];
                };
            }
            if ( d.test_value == evaluated ) {
                ans += d.test_value;
                break;
            }
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
bool can_be_true ( const S& s, uint64_t e, uint i=1 ) {
    if ( s.numbers.size() == i )
        return s.test_value == e;

    uint64_t b = s.numbers[i++];
    uint64_t m = pow ( 10, 1+floor(log10(b)) );
    auto ret = can_be_true ( s, e + b, i )
       || can_be_true ( s, e * b, i )
       || can_be_true ( s, e * m + b, i );

    return ret;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );

    for ( const auto& equation : data )
        if ( can_be_true ( equation, equation.numbers[0] ) )
            ans += equation.test_value;

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
