#include "day"
#include <unordered_set>

//---------------------------------------------------------------------------//
struct Point {
    int16_t x = 0, y = 0;
    Point ( ) : x ( 0 ), y ( 0 ) {}
    Point ( const Point& p ) : x ( p.x ), y ( p.y ) {}
    Point ( int16_t xx, int16_t yy ) : x ( xx ), y ( yy ) {}
    Point operator < ( const Point& p ) const {
        return Point ( int16_t ( x < p.x ), int16_t ( y < p.y ) );
    }
    bool operator == ( const Point p ) const {
        return x == p.x && y == p.y;
    }
    Point& operator * ( int s ) {
        x *= s;
        y *= s;
        return *this;
    }

    Point operator - ( const Point& p ) {
        return {int16_t ( x - p.x ), int16_t ( y - p.y ) };
    }

    Point& operator += ( const Point& p ) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator += ( const Point&& p ) {
        x += p.x;
        y += p.y;
        return *this;
    }

    auto abs() {
        return Point ( std::abs ( x ), std::abs ( y ) );
    }

    operator bool( ) {
        return x || y;
    }

};

//---------------------------------------------------------------------------//
template<>
struct std::hash<Point> {
    std::size_t operator() ( const Point& p ) const {
        return std::hash<int16_t> {} ( p.x )
               | ( std::hash<int16_t> {} ( p.y ) << 1 );
    }
};

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)" );
std::string testinput2 (
    R"(R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20)" );

//---------------------------------------------------------------------------//
inline std::istream& test_input ( int i = 1 ) {
    static std::stringstream ss;
    return ss = std::stringstream ( i == 1 ? testinput : testinput2 );
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    char dir;
    int steps;
    Point p;
    Point Head{0, 0};
    Point Tail{0, 0};
    std::unordered_set<Point> trace;
    trace.insert ( Tail );

    while ( file >> dir >> steps ) {
        p += Point ( ( ( dir == 'R' ) ) - ( dir == 'L' ),
                     ( ( dir == 'U' ) ) - ( dir == 'D' ) ) * steps;
        while ( p - Head ) {
            Head += ( Head < p ) - ( p < Head );
            if ( Point ( 1, 1 ) < ( Head - Tail ).abs() ) {
                Tail += ( Tail < Head )  - ( Head < Tail );
                trace.insert ( Tail );
            }
        }
    }
    ans = trace.size();

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ul;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( 2 ) : puzzle_input;

    char dir;
    int steps;
    Point p;

    Point Head[10];
    std::unordered_set<Point> trace;

    while ( file >> dir >> steps ) {
        p += Point ( ( - ( dir == 'L' ) + ( dir == 'R' ) ),
                     ( - ( dir == 'D' ) + ( dir == 'U' ) ) ) * steps;
        while ( p - Head[0] ) {
            Head[0] += ( Head[0] < p ) - ( p < Head[0] );
            for ( int i = 0; i < 9; i++ ) {
                if ( Point ( 1, 1 ) < ( Head[i] - Head[i + 1] ).abs() ) {
                    Head[i + 1] += ( Head[i + 1] < Head[i] ) - ( Head[i] < Head[i + 1] );
                    trace.insert ( Head[9] );
                }
            }
        }
    }
    ans = trace.size();

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
