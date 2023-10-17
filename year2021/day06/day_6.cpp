#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <ranges>
#include "day"
//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_6 {

//---------------------------------------------------------------------------//
//auto testinput = R"(3,4,3,1,2)";
auto testinput = R"(3)";
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
std::vector<int> load( std::istream& ss) {
    std::vector<int> data;
    std::string dir;
    int value;
    char comma;
    while ( ss.good() ) {
        if ( ss >> value ) {
            ss >> comma;
            data.push_back ( value );
        }
    }
    return data;
}

//---------------------------------------------------------------------------//
uint64_t f ( uint64_t a, uint64_t b ) {
    static std::unordered_map<int, uint64_t> cache;
    if ( a < b ) {
        uint64_t i = ( a << 16 ) | b;
        if ( !cache[i] )
            cache[i] = 1 + f ( 9, b - a ) + f ( 7, b - a );
        return cache[i];
    }
    return 0;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    uint64_t ans = 0;

    //auto& input = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto& input = test_input();
    auto data = load( input );

    ans = data.size();
    for ( auto v : data ) {
        ans += f ( v, 80 );
    }

    OUT(ans);
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    uint64_t ans = 0;

    auto& input = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( input );

    ans = data.size();
    for ( auto v : data ) {
        ans += f ( v, 256 );
    }

    OUT(ans);
}

//---------------------------------------------------------------------------//
}
//---------------------------------------------------------------------------//
