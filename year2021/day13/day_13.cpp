//---------------------------------------------------------------------------//
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <map>
//#include <unordered_map>
//#include <vector>
//#include <ranges>
//#include <fstream>
//#include <limits>
#include <set>
#include "day"

//---------------------------------------------------------------------------//
//#include "day_13.h"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// template<class T>
// constexpr auto Range ( T a, T b ) {
//     return std::views::iota ( a, b );
// }
//---------------------------------------------------------------------------//
struct Point {
    int x, y;
};

//---------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    //std::fstream fs ( file );
    std::vector<Point> data;
    std::vector<std::tuple<char, int>> fold;

    std::string line;
    // punkty
    while ( fs.good() ) {
        std::getline ( fs, line );
        if ( !line.empty() ) {
            std::stringstream ss ( line );
            int x, y;
            char c;
            ss >> x >> c >> y;
            data.push_back ( {x, y} );
        } else {
            break;
        }
    }
    // zlozenia
    while ( fs.good() ) {
        std::getline ( fs, line );
        if ( !line.empty() ) {
            char c;
            int v;
            std::stringstream ss ( line );
            ss.seekg ( 11 ) >> c;
            ss.seekg ( 13 ) >> v;
            fold.push_back ( {c, v} );
        }
    }

    return std::tuple{data, fold};
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0;
    auto [data, fold] = load ( puzzle_input );

    auto [a, v] = fold[0];
    for ( auto& p : data ) {
        if ( a == 'x' ) {
            if ( p.x > v ) {
                p.x = 2 * v - p.x;
            }
        } else {
            if ( p.y > v ) {
                p.y = 2 * v - p.y;
            }
        }
    }

    std::set<int> paper;
    for ( auto& [x, y] : data ) {
        paper.insert ( ( x << 16 ) | y );
    }
    ans = paper.size();

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto [data, fold] = load ( puzzle_input );

    for ( auto [a, v] : fold )
        for ( auto& p : data ) {
            if ( a == 'x' ) {
                if ( p.x > v ) {
                    p.x = 2 * v - p.x;
                }
            } else {
                if ( p.y > v ) {
                    p.y = 2 * v - p.y;
                }
            }
        }

    auto minx = 0;
    auto maxx = 0;
    auto miny = 0;
    auto maxy = 0;
    for ( auto[x, y] : data ) {
        minx = std::min ( minx, x );
        maxx = std::max ( maxx, x );
        miny = std::min ( miny, y );
        maxy = std::max ( maxy, y );
    }

    std::vector<std::string> img ( maxy + 1 );
    for ( auto& s : img ) s.resize ( maxx + 1, ' ' );
    for ( auto& [x, y] : data ) {
        img[y][x] = '#';
    }
    for ( auto& s : img )
        std::cout << s << '\n';

    std::cout << __FUNCTION__ << ":" << '\n';
}

}
