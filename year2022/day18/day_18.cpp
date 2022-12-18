#include "day"
#include <ranges>
#include <iomanip>
#include <unordered_set>
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(2,2,2
1,2,2
3,2,2
2,1,2
2,3,2
2,2,1
2,2,3
2,2,4
2,2,6
1,2,5
3,2,5
2,1,5
2,3,5)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
struct Point {
    int x, y, z;
};

//---------------------------------------------------------------------------//
struct Hash{
    size_t operator()(const Point& p) const {
        return std::hash<int>{}(p.x)
            ^(std::hash<int>{}(p.y)<<1)
            ^(std::hash<int>{}(p.z)<<2);
    }
};

//---------------------------------------------------------------------------//
bool operator== ( const Point& a, const Point& b ) {
    return a.x==b.x && a.y==b.y && a.z==b.z;
}

//---------------------------------------------------------------------------//
using Points = std::unordered_map<Point, int, Hash>;

//---------------------------------------------------------------------------//
auto getPoints ( auto& file ) {
    char c;
    Point p;
    std::string line;
    Points points;

    while( file >> line ) {
        std::stringstream ss(line);
        ss >> p.x >> c >> p.y >> c >> p.z;
        points.insert ( {p,1} );
    }
    return points;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    Points points = getPoints( file );

    for ( auto& [p,v] : points ) {
        ans += !points.contains( {p.x-1,p.y,p.z} )
             + !points.contains( {p.x+1,p.y,p.z} )
             + !points.contains( {p.x,p.y-1,p.z} )
             + !points.contains( {p.x,p.y+1,p.z} )
             + !points.contains( {p.x,p.y,p.z-1} )
             + !points.contains( {p.x,p.y,p.z+1} );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    Points points = getPoints ( file );

    auto contains = [&points]( const Point& p ) -> int {
        return points.contains ( p ) * points[ p ];
    };

    Point min { points.begin()->first}, max{points.begin()->first };
    for ( auto& [p,v] : points ) {
        min.x = std::min ( min.x, p.x );
        min.y = std::min ( min.y, p.y );
        min.z = std::min ( min.z, p.z );
        max.x = std::max ( max.x, p.x );
        max.y = std::max ( max.y, p.y );
        max.z = std::max ( max.z, p.z );
    }

    std::vector<Point> tab { min };
    while ( tab.size() ) {
        auto p = tab.back();
        tab.pop_back();

        if ( p.x<min.x-1 || p.x>max.x+1 ||
             p.y<min.y-1 || p.y>max.y+1 ||
             p.z<min.z-1 || p.z>max.z+1 ) continue;

        auto v = contains(p);
        if ( v==1 || v==2 ) continue;

        points[p] = 2;
        tab.push_back ( { p.x - 1, p.y    , p.z     } );
        tab.push_back ( { p.x + 1, p.y    , p.z     } );
        tab.push_back ( { p.x    , p.y + 1, p.z     } );
        tab.push_back ( { p.x    , p.y - 1, p.z     } );
        tab.push_back ( { p.x    , p.y    , p.z - 1 } );
        tab.push_back ( { p.x    , p.y    , p.z + 1 } );
    }

    for ( auto& [p,v] : points ) {
        if ( v==1 ) {
            ans += (contains ( { p.x - 1, p.y    , p.z     } ) == 2)
                 + (contains ( { p.x + 1, p.y    , p.z     } ) == 2)
                 + (contains ( { p.x    , p.y - 1, p.z     } ) == 2)
                 + (contains ( { p.x    , p.y + 1, p.z     } ) == 2)
                 + (contains ( { p.x    , p.y    , p.z - 1 } ) == 2)
                 + (contains ( { p.x    , p.y    , p.z + 1 } ) == 2);
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
