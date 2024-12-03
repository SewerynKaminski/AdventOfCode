//---------------------------------------------------------------------------//
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <map>
//#include <unordered_map>
//#include <vector>
#include <ranges>
//#include <fstream>
//#include <limits>
//#include <numeric>
//#include <algorithm>
#include "day"
//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
//template<class T>
//constexpr auto Range ( T a, T b ) {
//    return std::views::iota ( a, b );
//}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::vector<int64_t> data;
    std::fstream fs ( file );
    int64_t value;
    char comma;

    while ( fs >> value ) {
        data.push_back ( value );
        fs >> comma;
    }

    return data;
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
void Task_1(std::istream& puzzle_input ) {
    auto ans = std::numeric_limits<int64_t>::max();;

    //auto data = load ( "../input" );
    auto data = load ( puzzle_input );

    auto [min, max] = std::minmax_element ( data.begin(), data.end() );

    for ( auto i : Range ( *min, *max ) ) {
        auto sum = 0l;
        for ( auto v : data ) {
            sum += std::abs ( v - i );
        }
        ans = std::min ( ans, sum );
    }

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
void Task_2( std::istream& puzzle_input ) {
    auto ans = std::numeric_limits<int64_t>::max();;

    //auto data = load ( "../input" );
    auto data = load ( puzzle_input );

    auto [min, max] = std::minmax_element ( data.begin(), data.end() );

    for ( auto i : Range ( *min, *max ) ) {
        auto sum = 0l;
        for ( auto v : data ) {
            auto d = std::abs ( v - i );
            sum += d * ( d + 1 ) / 2;
        }
        ans = std::min ( ans, sum );
    }

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
