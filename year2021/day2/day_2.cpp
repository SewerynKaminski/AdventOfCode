#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(forward 5
down 5
forward 8
up 3
down 8
forward 2)" );

inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    auto depth = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    while ( getline ( file, line ) ) {
        switch ( line[0] ) {
        case 'd':
            depth += stoull ( line.substr ( 5 ) );
            break;
        case 'u':
            depth -= stoull ( line.substr ( 3 ) );
            break;
        case 'f':
            ans += stoull ( line.substr ( 8 ) );
            break;
        }
    }
    ans *= depth;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    auto depth = 0ull;
    auto aim = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    while ( getline ( file, line ) ) {
        switch ( line[0] ) {
        case 'd':
            aim += stoull ( line.substr ( 5 ) );
            break;
        case 'u':
            aim -= stoull ( line.substr ( 3 ) );
            break;
        case 'f':
            auto x = stoull ( line.substr ( 8 ) );
            ans += x;
            depth += aim * x;
            break;
        }
    }
    ans *= depth;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
