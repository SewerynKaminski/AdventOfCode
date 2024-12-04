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
    R"(#.######
#>>.<^<#
#.<..<<#
#>v.><>#
#<^v^^>#
######.#)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
struct Point{
    int x=0, y=0;
    //Point(){}
    bool operator== ( const Point& p ) const {
        return p.x==x && p.y==y;
    }
    Point operator+( const Point& p ) const {
        return {x+p.x, y+p.y};
    }
    Point operator-( const Point& p ) const {
        return {x-p.x, y-p.y};
    }
};

struct Hash{
    size_t operator()(const Point& p ) const {
        return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y)<<1);
    }
};

auto parse( std::istream& ss ){
    std::vector<std::string> board;
    std::string line;

    while ( getline(ss,line) ) {
        board.push_back( line );
    }
    return board;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    auto board = parse( file );

    int H = board.size() - 2;
    int W = board[0].size() - 2;

    auto tick = [&](int t, const Point& p)->bool {
        if ( p.x<0 || p.x>=W ) return true;
        if ( p.y<0 || p.y>=H ) return true;
        return
        board [ 1 + p.y                    ][ 1 + (p.x+W-t%W) % W ]=='>' ||
        board [ 1 + p.y                    ][ 1 + (p.x+t) % W ]=='<' ||
        board [ 1 + (p.y + H - t  % H) % H ][ 1 +  p.x ]=='v' ||
        board [ 1 + (p.y +     t) % H      ][ 1 +  p.x ]=='^';
    };

    std::unordered_set<Point,Hash> elfs;

    auto t=1ull;
    while ( !elfs.contains({W-1,H-1}) ) {
        elfs.insert( {0,0} );
        for ( auto it = elfs.begin(); it!=elfs.end() ; ) {
            if ( tick ( t, *it ) ) {
                it = elfs.erase( it );
            } else {
                it++;
            }
        }
        std::unordered_set<Point,Hash> newelfs;
        for ( auto e: elfs ) {
            if ( Point p{e.x+1,e.y}; !tick(t+1, p ) ) newelfs.insert ( p );
            if ( Point p{e.x-1,e.y}; !tick(t+1, p ) ) newelfs.insert ( p );
            if ( Point p{e.x,e.y-1}; !tick(t+1, p ) ) newelfs.insert ( p );
            if ( Point p{e.x,e.y+1}; !tick(t+1, p ) ) newelfs.insert ( p );
        }
        elfs.insert( newelfs.begin(), newelfs.end() );
        /*std::cout << "Minute: " << t << '\n';
        for( auto y=0; y < H; y++) {
            for( auto x=0; x < W; x++ ) {
                Point p{x,y};
                auto o = tick ( t, p );
                if ( elfs.contains(p) ) std::cout << '*';
                else if ( o ) std::cout << 'x';
                else std::cout << '.';
            }
            std::cout << '\n';
        }
        std::getchar();*/
        t++;
    }
    ans = t+1;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 1;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    auto board = parse( file );  

    int H = board.size() - 2;
    int W = board[0].size() - 2;

    auto is_blizzard = [&](int t, const Point& p)->bool {
        if ( p.x<0 || p.x>=W ) return true;
        if ( p.y<0 || p.y>=H ) return true;
        return
        board [ 1 + p.y                    ][ 1 + (p.x+W-t%W) % W ]=='>' ||
        board [ 1 + p.y                    ][ 1 + (p.x+t) % W ]=='<' ||
        board [ 1 + (p.y + H - t  % H) % H ][ 1 +  p.x ]=='v' ||
        board [ 1 + (p.y +     t) % H      ][ 1 +  p.x ]=='^';
    };

    auto go = [&is_blizzard]( int& t, Point begin, Point end ) {
        std::unordered_set<Point,Hash> elfs;
        while ( !elfs.contains( end ) ) {
            elfs.insert( begin );
            for ( auto it = elfs.begin(); it!=elfs.end() ; ) {
                if ( is_blizzard ( t, *it ) ) {
                    it = elfs.erase( it );
                } else {
                    it++;
                }
            }
            std::unordered_set<Point,Hash> newelfs;
            t++;
            for ( auto e: elfs ) {
                if ( Point p{e.x+1,e.y}; !is_blizzard(t, p ) ) newelfs.insert ( p );
                if ( Point p{e.x-1,e.y}; !is_blizzard(t, p ) ) newelfs.insert ( p );
                if ( Point p{e.x,e.y-1}; !is_blizzard(t, p ) ) newelfs.insert ( p );
                if ( Point p{e.x,e.y+1}; !is_blizzard(t, p ) ) newelfs.insert ( p );
            }
            elfs.insert( newelfs.begin(), newelfs.end() );
        }
        t++;
    };

    go ( ans, {  0,   0}, {W-1, H-1} );
    go ( ans, {W-1, H-1}, {  0,   0} );
    go ( ans, {  0,   0}, {W-1, H-1} );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
