#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(199
200
208
210
200
207
240
269
260
263)" );

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

    getline ( file, line );
    auto v0 = stoull ( line );
    while ( getline ( file, line ) ) {
        auto v1 = stoull ( line );
        ans += v1 > v0;
        v0 = v1;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    getline ( file, line );
    auto v1 = stoull ( line );
    getline ( file, line );
    auto v2 = stoull ( line );
    getline ( file, line );
    auto v3 = stoull ( line );

    while ( getline ( file, line ) ) {
        auto v = stoull ( line );
        ans += v1 < v;
        v1 = v2;
        v2 = v3;
        v3 = v;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
