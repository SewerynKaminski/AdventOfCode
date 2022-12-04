#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)" );

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    // find doubles
    auto find = [] ( std::string l1,  std::string l2 )->uint64_t{
        for ( auto c1 : l1 ) {
            for ( auto c2 : l2 ) {
                if ( c1 == c2 ) {
                    return c1 += c1 <= 'Z' ? -'A' + 27 : -'a' + 1;
                }
            }
        }
        return 0;
    };

    while ( getline ( file, line ) ) {
        // Split on half
        auto half = line.length() / 2;
        auto left  = line.substr ( 0, half );
        auto right = line.substr ( half );

        ans += find ( left, right );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto find = [] ( std::string l1,  std::string l2, std::string l3 )->uint64_t{
        for ( auto c1 : l1 )
            for ( auto c2 : l2 ) {
                for ( auto c3 : l3 ) {
                    if ( c1 == c2 && c2 == c3 ) {
                        return c1 += c1 <= 'Z' ? -'A' + 27 : -'a' + 1;
                    }
                }
            }
        return 0;
    };

    while ( file ) {
        std::string l1, l2, l3;
        getline ( file, l1 );
        getline ( file, l2 );
        getline ( file, l3 );
        ans += find ( l1, l2, l3 );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
