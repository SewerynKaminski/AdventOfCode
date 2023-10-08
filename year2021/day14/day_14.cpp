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
#include <set>
#include <algorithm>

//---------------------------------------------------------------------------//
#include "day_14.h"

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_14 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::unordered_map<int, char> data;

    std::string line, t;
    std::getline ( fs, t );
    std::getline ( fs, line );
    char a, b, c;
    while ( fs >> a >> b >> line >> c ) {
        data[a << 8 | b] = c;
    }

    return std::pair{t, data};
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0;
    auto [temp, data] = load ( "../input" );

    /*std::cout << temp << '\n';
    for ( auto [a,b,c]: data )
        std::cout << a<<b<<c << '\n';*/

    std::string t = temp;
    std::string out;
    for ( auto step : Range ( 0, 10 ) ) {
        out = std::string{t[0]};
        for ( auto i = 0; i < t.size() - 1; i++ ) {
            char a = t[i], b = t[i + 1], c = data[a << 8 | b];
            out = out + c + b;
        }
        t = out;
    }

    std::unordered_map<char, int> map;
    for ( auto c : out ) {
        map[c]++;
    }

    auto[min, max] = std::minmax_element ( map.begin(), map.end(), [] ( const auto & a, const auto & b ) {
        return a.second < b.second;
    } );
    ans = max->second - min->second ;
    std::cout << "Task 1: " << ans << "\n";
}

std::unordered_map<int,
    std::unordered_map<char, uint64_t>> memo;


//---------------------------------------------------------------------------//
std::unordered_map<char, uint64_t> cnt ( std::unordered_map<int, char>& map, char a, char b, char depth ) {
    if ( depth == 0 ) return {{b, 1}};
    int i = depth << 16 | a << 8 | b;
    if ( memo.contains ( i ) ) return memo[i];
    char c = map[a << 8 | b];
    auto z1 = cnt ( map, a, c, depth - 1 );
    auto z2 = cnt ( map, c, b, depth - 1 );
    for ( auto v : z2 ) {
        z1[v.first] += v.second;
    }
    memo[i] = z1;
    return memo[i];
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ull;
    auto [temp, data] = load ( "../input" );

    ans = 0;
    std::unordered_map<char, uint64_t> zz;
    zz[ temp[0] ] = 1;
    for ( auto i = 0u; i < temp.size() - 1; i++ ) {
        for ( auto v : cnt ( data, temp[i], temp[i + 1], 40 ) ) {
            zz[v.first] += v.second;
        }
    }

    auto [min, max] = std::minmax_element ( zz.begin(), zz.end(), [] ( const auto & a, const auto & b ) {
        return a.second < b.second;
    } );
    std::cout << max->first << " " << min->first << '\n';
    ans = max->second - min->second ;

    // 1715515050209 too low
    // 1715515050212 too low
    // 2884513602164 ?
    // 3945763545598 too high
    std::cout << "Task 2: " << ans << "\n";
}

}
