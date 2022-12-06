#include "day"
#include <bit>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    "mjqjpqmgbljsphdztnvjfqwrcgsmlb"
);

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    constexpr size_t LEN = 4;
    auto ans = 0l;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    uint32_t sum, i = 0;
    do {
        file >> line;
        // WARNING: 'line[i + ...]' no check out of bound
        sum = ( 1ul << ( line[i + 0] - 'a' ) )
              | ( 1ul << ( line[i + 1] - 'a' ) )
              | ( 1ul << ( line[i + 2] - 'a' ) )
              | ( 1ul << ( line[i + 3] - 'a' ) );
        i++;    // WARNING: loop forever if no LEN distinct characters found
    } while ( std::popcount ( sum ) != LEN );
    ans = --i + LEN;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    constexpr size_t LEN = 14;
    auto ans = 0ul;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    uint sum;
    uint i = 0;
    do {
        file >> line;
        sum = 0;
        for ( size_t j = 0; j < LEN ; j++ ) {
            sum |= 1ul << ( line[i + j] - 'a' );    // WARNING: 'line[i + j]' no error check: out of bound
        }
        i++;    // WARNING: loop forever if no LEN distinct characters found
    } while ( std::popcount ( sum ) != LEN );
    ans = --i + LEN;

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
