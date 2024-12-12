#include "day"
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
/*R"(AAAA
BBCD
BBCC
EEEC)"*/
R"(RRRRIICCFF
RRRRIICCCF
VVRRRCCFFF
VVRCCCJFFF
VVVVCJJCFE
VVIVCCJJEE
VVIIICJJEE
MIIIIIJJEE
MIIISIJEEE
MMMISSJEEE
)"
);

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load ( ::std::istream& file ) {
    ::std::vector<std::string> ret;
    ::std::string line;
    while ( ::std::getline ( file, line ) )
        ret.push_back( line );
    return ret;
}

//---------------------------------------------------------------------------//
std::pair<size_t,size_t> go ( std::vector<std::string>& t, char c, char r, int x, int y ) {
    if ( y<0 ) return { 0, 1 };
    if ( y>=(int)t.size() ) return { 0, 1 };
    if ( x<0 ) return { 0, 1};
    if ( x>=(int)t[0].size() ) return { 0, 1 };

    if ( t[y][x] == r ) return { 0, 0 };
    if ( t[y][x]!=c ) return { 0, 1 };
    size_t ret = 1;
    size_t edge = 0;
    t[y][x] = r;
    auto p = go ( t, c, r, x+1, y );
    ret += p.first;
    edge += p.second;

    p = go ( t, c, r, x-1, y );
    ret += p.first;
    edge += p.second;

    p = go ( t, c, r, x, y+1 );
    ret += p.first;
    edge+= p.second;

    p = go ( t, c, r, x, y-1 );
    ret += p.first;
    edge+= p.second;

    return {ret, edge};
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    for( int y=0; y < (int)data.size(); y++ )
        for( int x=0; x < (int)data[y].size(); x++ )
            if ( data[y][x]>0 ) {
                auto c = data[y][x];
                auto r = go ( data, c, -c, x, y );
                ans += r.first * r.second;
            }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
std::pair<size_t,size_t> go2 ( std::vector<std::string>& t, char c, char r, int x, int y, size_t& corners ) {
    if ( y<0 ) return {0, 1};
    if ( y>=(int)t.size() ) return {0, 1};
    if ( x<0 ) return {0,1};
    if ( x>=(int)t[0].size() ) return {0, 1};

    if ( t[y][x] == r ) return {0, 0};
    if ( t[y][x]!=c ) return {0, 1};
    size_t ret=1;
    t[y][x] = r;
    auto right = go2( t, c, r, x+1, y, corners );
    ret += right.first;

    auto left = go2( t, c, r, x-1, y, corners );
    ret += left.first;

    auto down = go2( t, c, r, x, y+1, corners );
    ret += down.first;

    auto up = go2( t, c, r, x, y-1, corners );
    ret += up.first;

    corners += ( up.second && left.second ) +
               ( up.second && right.second ) +
               ( down.second && left.second ) +
               ( down.second && right.second ) +
               ( !up.second && !right.second && t[y-1][x+1]!=c && t[y-1][x+1]!=r ) +
               ( !up.second && !left.second && t[y-1][x-1]!=c && t[y-1][x-1]!=r ) +
               ( !down.second && !right.second && t[y+1][x+1]!=c && t[y+1][x+1]!=r ) +
               ( !down.second && !left.second && t[y+1][x-1]!=c && t[y+1][x-1]!=r );

    return {ret, 0};
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    for( int y=0; y < (int)data.size(); y++ )
        for( int x=0; x < (int)data[y].size(); x++ )
            if ( data[y][x]>0 ) {
                size_t corners=0;
                auto c = data[y][x];
                auto r = go2 ( data, c, -c, x, y, corners );
                ans += r.first * corners;
            }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
