#include "day"
#include <ranges>
#include <iomanip>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi)" };

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
std::istream& operator >> ( std::istream& o, std::function< std::istream& ( std::istream& ) > f ) {
    return f ( o );
}

//---------------------------------------------------------------------------//
std::string getLine ( std::istream& file ) {
    std::string line;
    getline ( file, line );
    return line;
}

//---------------------------------------------------------------------------//
struct Point {
    int x=0,y=0;
};

//---------------------------------------------------------------------------//
int search( std::vector<std::string>& heightmap, Point pStart, Point pEnd ) {
    const int width = heightmap[0].length();
    const int height = heightmap.size();
    std::vector<Point> points;
    std::vector<std::vector<int>> distance;

    auto Distance = [&distance]( const Point& p) -> auto& {
        return distance[p.y][p.x];
    };

    auto Heightmap = [&heightmap]( const Point& p) -> auto& {
        return heightmap[p.y][p.x];
    };

    distance.resize( height );
    for( auto& row: distance ) {
        row.resize ( width,  std::numeric_limits<typeof(Distance({0,0}))>::max() );
    }

    auto check = [&Heightmap,&Distance,&points,width,height] ( int d, int h, Point p ) {
        if ( p.x >= 0 && p.x < width && p.y >= 0 && p.y < height ) {
            auto hh = Heightmap ( p );
            if ( h+1 >= hh ) {
                if ( Distance ( p ) > d+1 ) {
                    Distance ( p ) = d+1;
                    points.push_back ( p );
                }
            }
        }
    };

    Distance ( pStart ) = 0;
    points.push_back ( pStart );
    while ( points.size() ) {
        auto p = points.back();
        points.pop_back();

        auto h = Heightmap ( p );
        auto d = Distance ( p );
        check ( d, h, {p.x-1, p.y} );
        check ( d, h, {p.x+1, p.y} );
        check ( d, h, {p.x, p.y-1} );
        check ( d, h, {p.x, p.y+1} );
    }

    return Distance ( pEnd );
}

//---------------------------------------------------------------------------//
int search2( std::vector<std::string>& heightmap, Point pStart, Point pEnd ) {
    const int width = heightmap[0].length();
    const int height = heightmap.size();
    std::vector<Point> points;
    std::vector<std::vector<int>> distance;


    auto Distance = [&distance]( const Point& p ) -> auto& {
        return distance[p.y][p.x];
    };

    auto Heightmap = [&heightmap]( const Point& p ) -> auto& {
        return heightmap[p.y][p.x];
    };

    distance.resize( height );
    for ( auto& row: distance ) {
        row.resize ( width,  std::numeric_limits<typeof(Distance({0,0}))>::max() );
    }

    auto check = [&Heightmap,&Distance,&points,width,height] ( int d, int h, const Point p ) {
        if ( p.x >= 0 && p.x < width && p.y >= 0 && p.y < height ) {
            auto hh = Heightmap( p );
            if ( h+1 >= hh ) {
                if ( Distance ( p ) > d+1 ) {
                    Distance ( p ) = hh=='a' ? 0 : d+1;
                    points.push_back ( p );
                }
            }
        }
    };

    Distance ( pStart ) = 0;
    points.push_back( pStart );
    while ( points.size() ) {
        auto p = points.back();
        points.pop_back();

        auto h = Heightmap ( p );
        auto d = Distance ( p );
        check ( d, h, {p.x-1, p.y} );
        check ( d, h, {p.x+1, p.y} );
        check ( d, h, {p.x, p.y-1} );
        check ( d, h, {p.x, p.y+1} );
    }

    return Distance ( pEnd );
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    Point pStart, pEnd;
    std::vector<std::string> heightmap;
    auto y = 0;
    while ( file ) {
        auto line = getLine ( file );
        if ( int x=line.find('S'); x >= 0 ) {
            line[x] = 'a';
            pStart = {x,y};
        }
        if ( int x=line.find('E'); x >= 0 ) {
            line[x] = 'z';
            pEnd = {x,y};
        }
        y++;
        heightmap.push_back ( line );
    }

    ans  = search( heightmap, pStart, pEnd );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    Point pStart, pEnd;
    std::vector<std::string> heightmap;
    auto y = 0;
    while ( file ) {
        auto line = getLine ( file );
        if ( int x=line.find('S'); x >= 0 ) {
            line[x] = 'a';
            pStart = {x,y};
        }
        if ( int x=line.find('E'); x >= 0 ) {
            line[x] = 'z';
            pEnd = {x,y};
        }
        y++;
        heightmap.push_back ( line );
    }

    ans = search2( heightmap, pStart, pEnd );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
