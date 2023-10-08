//---------------------------------------------------------------------------//
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <fstream>
#include <limits>
#include <numeric>
#include <algorithm>

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_7 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

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
void Task_1() {
    auto ans = std::numeric_limits<int64_t>::max();;

    auto data = load ( "../input" );

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
void Task_2() {
    auto ans = std::numeric_limits<int64_t>::max();;

    auto data = load ( "../input" );

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
