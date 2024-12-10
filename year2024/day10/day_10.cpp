#include "day"

//---------------------------------------------------------------------------//
struct P {
    int x,y;
    size_t hash() const { return ((size_t)y<<32)|(size_t)x; }
    bool operator==(const P& o ) const { return y==o.y && x==o.x; }
};

//---------------------------------------------------------------------------//

template<>
struct std::hash<P> {
    size_t operator()( const P& p) const { return p.hash();}
};

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    ::std::vector<::std::string> ret;
    ::std::string line;
    while(::std::getline( file, line ))
        ret.push_back ( line );

    return ret;
}

//---------------------------------------------------------------------------//
size_t go ( std::vector<std::string>& t, int x, int y, std::unordered_set<P>& p ) {
    size_t ret = 0;
    int h = t.size(), w = t[0].size();
    auto c = t[y][x];
    if ( c=='9' ) {
        p.insert ( { x, y } );
        return 1;
    }

    if ( x +1 <  w && c + 1 == t[y][x+1] ) ret += go ( t, x+1, y  , p );
    if ( x -1 >= 0 && c + 1 == t[y][x-1] ) ret += go ( t, x-1, y  , p );
    if ( y +1 <  h && c + 1 == t[y+1][x] ) ret += go ( t, x  , y+1, p );
    if ( y -1 >= 0 && c + 1 == t[y-1][x] ) ret += go ( t, x  , y-1, p );

    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );

    for ( uint y = 0; y < data.size(); y++ ) {
        for ( uint x = 0; x < data[0].size(); x++ ) {
            if ( data[y][x] == '0' ) {
                std::unordered_set<P> p;
                go ( data, x, y, p );
                ans += p.size();
            }
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );

    for ( uint y = 0; y < data.size(); y++ ) {
        for ( uint x = 0; x < data[0].size(); x++ ) {
            if ( data[y][x] == '0' ) {
                std::unordered_set<P> p;
                ans += go ( data, x, y, p );
            }
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
