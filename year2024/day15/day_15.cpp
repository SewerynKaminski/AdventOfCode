#include "day"
#include <ranges>
#include <iomanip>
#include <unordered_set>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(Sensor at x=2, y=18: closest beacon is at x=-2, y=15
Sensor at x=9, y=16: closest beacon is at x=10, y=16
Sensor at x=13, y=2: closest beacon is at x=15, y=3
Sensor at x=12, y=14: closest beacon is at x=10, y=16
Sensor at x=10, y=20: closest beacon is at x=10, y=16
Sensor at x=14, y=17: closest beacon is at x=10, y=16
Sensor at x=8, y=7: closest beacon is at x=2, y=10
Sensor at x=2, y=0: closest beacon is at x=2, y=10
Sensor at x=0, y=11: closest beacon is at x=2, y=10
Sensor at x=20, y=14: closest beacon is at x=25, y=17
Sensor at x=17, y=20: closest beacon is at x=21, y=22
Sensor at x=16, y=7: closest beacon is at x=15, y=3
Sensor at x=14, y=3: closest beacon is at x=15, y=3
Sensor at x=20, y=1: closest beacon is at x=15, y=3)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
std::string getLine ( std::istream& file ) {
    std::string line;
    getline ( file, line );
    return line;
}

//---------------------------------------------------------------------------//
struct Point{
    int x=0,y=0;
    Point(){}
    Point(int xx, int yy){x=xx,y=yy;}
    Point operator-(const Point& p){
        return {x-p.x,y-p.y};
    }
    bool operator ==(const Point& p ) const {
        return x==p.x && y==p.y;
    }
};

//---------------------------------------------------------------------------//
struct Sensor{
    Point p, b;
    int r=0;
    Sensor ( const Point& aa, const Point& bb ) {
        p = aa;
        b = bb;
        radius();
    }

    void radius(){
        r = abs(p.x - b.x)+abs(p.y - b.y);
    }

};

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    int y = aoc::is_test_enabled() ? 20 : 2000000;

    std::string line;
    std::vector<Sensor> sensors;
    while ( getline(file, line) ) {
        std::stringstream ss( line );
        std::string t,sx,sy,bx,by;
        Point s, b;
        ss >> t >> t >> sx >> sy
           >> t >> t >> t >> t >> bx >> by;

        s.x = stoi ( sx.substr ( 2 ) );
        s.y = stoi ( sy.substr ( 2 ) );
        b.x = stoi ( bx.substr ( 2 ) );
        b.y = stoi ( by.substr ( 2 ) );

        Sensor se ( s, b );
        sensors.push_back( se );
    }

    std::unordered_set <int> q;
    for ( auto& s : sensors ) {
        if ( s.p.y - s.r <= y && y <= s.p.y + s.r ){
            int strip_len = 2*(s.r - abs(s.p.y - y))+1;
            int strip_x = s.p.x - (s.r - abs(s.p.y - y));
            for ( int i=0; i<strip_len; i++ ) {
                q.insert ( { i + strip_x } );
            }
        }
    }
    for ( auto& s : sensors ) {
        if ( s.b.y == y && q.contains( s.b.x ) ) {
            q.erase( s.b.x );
        }
    }
    ans = q.size();

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    const int w = aoc::is_test_enabled() ? 20 : 4000000;

    std::string line;
    std::vector<Sensor> sensors;
    while ( getline(file, line) ) {
        std::stringstream ss( line );
        std::string t,sx,sy,bx,by;
        Point s, b;
        ss >> t >> t >> sx >> sy
           >> t >> t >> t >> t >> bx >> by;

        s.x = stoi ( sx.substr ( 2 ) );
        s.y = stoi ( sy.substr ( 2 ) );
        b.x = stoi ( bx.substr ( 2 ) );
        b.y = stoi ( by.substr ( 2 ) );

        Sensor se ( s, b );
        sensors.push_back( se );
    }

    struct Hash{
            size_t operator()(const Point& p) const {
                return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y)<<1);
            }
    };

    std::unordered_set<Point, Hash> points;
    auto total = 0ull;
    for ( auto& s : sensors ) {
        total += s.r*4;
    }
    points.reserve ( total );

    for ( auto& s : sensors ) {
        int xr = s.p.x;
        int xl = s.p.x;
        int y1 = s.p.y - s.r - 1;
        int y2 = s.p.y + s.r + 1;
        for ( int i = 0; i <= s.r ; i++ ) {
            if ( xr >= 0 && xr < w ) {
                if ( y1 >= 0 && y1 < w )
                    points.insert ( Point ( xr, y1 ) );
                if ( y2 >= 0 && y2 < w )
                    points.insert ( Point ( xr, y2 ) );
            }
            if ( xl >= 0 && xl < w ) {
                if ( y1 >= 0 && y1 < w )
                    points.insert ( Point ( xl, y1 ) );
                if ( y2 >= 0 && y2 < w )
                    points.insert ( Point ( xl, y2 ) );
            }
            xr++;
            xl--;
            y1++;
            y2--;
        }
    }

    for ( auto& p : points ) {
            bool in = false;
            for ( auto& s : sensors ) {
                if ( abs(p.x-s.p.x) + abs(p.y-s.p.y) <= s.r ) {
                    in = true;
                    break;
                }
            }
            if ( !in ) {
                std::cout << "x: " << p.x << " y: " << p.y << "\n";
                ans = p.x*4000000ull + p.y;
                break;
            }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
