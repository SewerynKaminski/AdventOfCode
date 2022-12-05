#include "day"
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {
//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2)" );

inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

struct Point {
    Point() : x ( 0 ), y ( 0 ) {}
    Point ( int px, int py ) {
        x = px;
        y = py;
    }
    int x, y;
};

Point& operator+= ( Point& a, const Point& b ) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Point operator+ ( const Point a, const Point b ) {
    return {a.x + b.x, a.y + b.y};
}

bool operator== ( const Point& a, const Point& b ) {
    return a.x == b.x && a.y == b.y;
}

bool operator!= ( const Point& a, const Point& b ) {
    return a.x != b.x || a.y != b.y;
}

struct Line {
    Point p1, p2;
};
struct Hash_Point {
    auto operator() ( const Point& p ) const {
        return std::hash<int> {} ( p.x + 1 ) ^ std::hash<int> {} ( p.y );
    }
};

//---------------------------------------------------------------------------//
std::ostream& operator << ( std::ostream& io, const Point& p ) {
    io << "{" << p.x << "," << p.y << "}";
    return io;
}

//---------------------------------------------------------------------------//
std::vector<Line> load ( std::istream& fs ) {
    std::vector<Line> ret;
    int x1, x2, y1, y2;
    char c;

    while ( fs >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2 ) {
        ret.push_back ( {{x1, y1}, {x2, y2}} );
    }
    return ret;
}

//---------------------------------------------------------------------------//
inline bool isVertical ( Line& line ) {
    return line.p1.y == line.p2.y;
}

//---------------------------------------------------------------------------//
inline bool isHorizontal ( Line& line ) {
    return line.p1.x == line.p2.x;
}

//---------------------------------------------------------------------------//
inline bool isVerticalOrHorizontal ( Line& line ) {
    return isHorizontal ( line ) || isVertical ( line );
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto data = load ( file );
    std::unordered_map<Point, int, Hash_Point> hash;

    //for ( auto& line : data | std::views::filter ( isVerticalOrHorizontal ) ) {
    for ( auto& line : data ) {
        if ( isVerticalOrHorizontal ( line ) ) {
            //std::cout << line.p1 << "\n";
            Point d { line.p2.x - line.p1.x, line.p2.y - line.p1.y };
            int l = std::max ( std::abs ( d.x ), std::abs ( d.y ) );
            if ( l > 0 ) {
                d.x /= l;
                d.y /= l;
            }
            for ( auto p = line.p1; p != line.p2; p += d ) {
                //std::cout << p << "\n";
                hash[p]++;
            }
            //std::cout << line.p2 << "\n";
            hash[line.p2]++;
        }
    }

    int ans = 0;
    //for ( auto v : hash | std::views::values ) {
    //    ans += v > 1;
    //};
    for ( auto [k, v] : hash ) {
        ans += v > 1;
    };

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto data = load ( file );
    std::unordered_map<Point, int, Hash_Point> hash;

    for ( auto& line : data ) {
        Point d { line.p2.x - line.p1.x, line.p2.y - line.p1.y };
        int l = std::max ( std::abs ( d.x ), std::abs ( d.y ) );
        if ( l > 0 ) {
            d.x /= l;
            d.y /= l;
        }
        for ( auto p = line.p1; p != line.p2; p += d ) {
            hash[p]++;
        }
        hash[line.p2]++;
    }

    int ans = 0;
    for ( auto v : hash | std::views::values ) {
        ans += v > 1;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
