#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput =
    R"(A Y
B X
C Z)";

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

    std::istream& file = is_test_enabled() ? test_input() : puzzle_input;


    auto score = [] ( auto a, auto b ) {
        return ( ( 4 + b - a ) % 3 ) * 3 + b + 1;
    };

    while ( getline ( file, line ) ) {
        char a = line[0] - 'A', b = line[2] - 'X';
        ans += score ( a, b );
    }
    /*
        0 - rock
        1 - paper
        2 - scissor
        (4 + 2 - 0) % 3 = 0 lost
        (4 + 0 - 0) % 3 = 1 remis
        (4 + 1 - 0) % 3 = 2 win
    */

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    std::istream& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto score = [] ( auto a, auto b ) {
        return ( ( 4 + b - a ) % 3 ) * 3 + b + 1;
    };

    std::string line;
    while ( getline ( file, line ) ) {
        char a = line[0] - 'A', b = line[2] - 'X';
        ans += score ( a, ( 2 + a + b ) % 3 );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
