#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(1000
2000
3000

4000

5000
6000

7000
8000
9000

10000)" );

inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto sum = 0ull;
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    while ( getline ( file, line ) ) {
        sum = line.empty() ? ( ans = std::max ( ans, sum ), 0 ) : sum + stoull ( line );
    }
    ans = std::max ( ans, sum );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto sum = 0ull;
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    std::vector<int> t;
    sum = 0;
    while ( getline ( file, line ) ) {
        sum = !line.empty() ? sum + stoull ( line ) : ( t.push_back ( sum ), 0 );
    }
    t.push_back ( sum );
    //std::ranges::sort ( t, std::ranges::greater() );
    std::sort ( t.begin(), t.end(), std::ranges::greater() );
    ans = std::accumulate ( t.begin(), t.begin() + 3, 0 );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
