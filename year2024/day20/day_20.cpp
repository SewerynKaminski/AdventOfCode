#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//----------------------------------------------------------------------------//
std::istringstream testinput{
R"(###############
#...#...#.....#
#.#.#.#.#.###.#
#S#...#.#.#...#
#######.#.#.###
#######.#.#...#
#######.#.###.#
###..E#...#...#
###.#######.###
#...###...#...#
#.#####.#.###.#
#.#...#.#.#...#
#.#.#.#.#.#.###
#...#...#...###
###############
)"};

//----------------------------------------------------------------------------//
struct P2{
    int x=0,y=0;
};

//----------------------------------------------------------------------------//
constexpr int PATH = INT32_MAX;
constexpr int WALL = -1;

//----------------------------------------------------------------------------//
auto go ( std::vector<int>& maze, P2 start, P2 stop, const int W ) {
    int o = start.y*W+start.x;
    std::vector<int> l{o};
    const int e = stop.x + stop.y*W;

    maze[o] = 0;
    while ( l.size() ) {
        auto o = l.back(); l.pop_back();
        std::array<int,4> dirs{-1,1,-W,W};
        for ( auto d : dirs )
            if ( maze[o+d]!=WALL && maze[o] < maze[o+d] ) {
                maze[o+d] = maze[o] + 1;
                l.push_back ( o+d );
            }
    }
    return maze[e];
}

auto load ( std::istream& fs ) {
    ::std::vector<::std::string> data;
    while ( !fs.eof() ) {
        ::std::string line;
        ::std::getline ( fs, line );
        if( !line.empty ( ) )
            data.push_back ( line );
    }
    return data;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    P2 start, stop;

    auto data = load ( ::aoc::is_test_enabled()?testinput:puzzle_input );
    ::std::vector<int> maze;
    const int W = data[0].size();
    for( int y=0; y<W; y++ )
        for( int x=0; x<W; x++ ) {
            if ( data[y][x]=='#' ) {
                maze.push_back ( WALL );
            } else {
                maze.push_back ( PATH );
                if ( data[y][x]=='S' ) start = P2{x,y};
                if ( data[y][x]=='E' ) stop = P2{x,y};
            }
        }


    auto m = maze;
    auto max = go ( maze, start, stop, W );
    maze = m;

    for ( int y=1; y<W-1; y++ )
        for ( int x=1; x<W-1; x++ ) {
            if ( maze[x+y*W]==PATH ) continue;
            maze[x+y*W] = PATH;
            auto m = maze;
            auto len = go ( maze, start, stop, W );
            maze = m;
            if ( max-len >= 100 ) ans++;
            maze[x+y*W] = WALL;
        }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    uint64_t ans=0;

    //aoc::test_enable();

    P2 start, stop;
    auto data = load ( ::aoc::is_test_enabled() ? testinput : puzzle_input );
    const int W = data[0].size();

    std::vector<int> maze;
    for( int y=0; y<W; y++ )
        for( int x=0; x<W; x++ ) {
            if ( data[y][x]=='#' ) {
                maze.push_back ( WALL );
            } else {
                maze.push_back ( PATH );
                if ( data[y][x]=='S' ) start = P2{x,y};
                if ( data[y][x]=='E' ) stop = P2{x,y};
            }
        }

    go( maze, start, stop, W );

    for ( auto y=1; y<W-1; y++ ) {
        for ( auto x=1; x<W-1; x++ ) {
            if ( maze[x+y*W]!=WALL ) {
                for ( auto sy=y; sy<y+21 && sy<W-1; sy++ )
                    for ( auto sx=x+1; sx<x+21 && sx<W-1; sx++ ) {
                        auto d = sx-x + sy-y;
                        if ( d < 21 && maze[sx+sy*W]!=WALL ) {
                            auto l1 = maze[x+y*W];
                            auto l2 = maze[sx+sy*W];
                            if ( std::abs(l2-l1)-d>=100 )
                                ans++;
                        }
                    }
                for ( auto sy=y-1; sy>y-21 && sy>0; sy-- )
                    for ( auto sx=x; sx<x+21 && sx<W-1; sx++ ) {
                        auto d = sx-x + y-sy;
                        if ( d < 21 && maze[sx+sy*W]!=WALL ) {
                            auto l1 = maze[x+y*W];
                            auto l2 = maze[sx+sy*W];
                            if ( std::abs(l2-l1)-d>=100 )
                                ans++;
                        }
                    }
            }
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
