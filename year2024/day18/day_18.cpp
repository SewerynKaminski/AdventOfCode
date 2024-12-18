#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(5,4
4,2
4,5
3,0
2,1
6,3
2,4
1,5
0,6
3,3
2,6
5,1
1,2
5,5
2,5
6,5
1,4
0,4
6,4
1,1
6,1
1,0
0,5
1,6
2,0
)");

//---------------------------------------------------------------------------//
struct P{
    int x,y;
};

//---------------------------------------------------------------------------//
inline ::std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

::std::vector<::std::string> load ( ::std::istream& fs ) {
    ::std::string line;
    ::std::vector<::std::string> ret;
    while ( !fs.eof() ) {
        std::getline ( fs, line );
        if( !line.empty() )
            ret.push_back ( line );
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::vector<int> maze;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );
    constexpr int W=71;

    maze.resize ( W*W, INT32_MAX );

    for ( int i=0; i<1024; i++ ) {
        std::istringstream is{data[i]};
        int x,y;
        char c;
        is >> x >> c>> y;
        maze[x+y*W]=-1;
    }

    std::vector<P> l { P { 0, 0 } };
    maze [ 0 ] = 0;
    while ( !l.empty() ) {
        auto p = l.back(); l.pop_back();
        if ( p.x+1 < W && maze[p.x+p.y*W]+1 < maze[p.x+p.y*W+1] ) {
            maze[p.x+p.y*W+1] = maze[p.x+p.y*W]+1;
            l.push_back ( P { p.x+1, p.y } );
        }
        if ( p.x-1 >=0 && maze[p.x+p.y*W]+1 < maze[p.x+p.y*W-1] ) {
            maze[p.x+p.y*W-1] = maze[p.x+p.y*W]+1;
            l.push_back ( P { p.x-1, p.y } );
        }
        if ( p.y+1 < W && maze[p.x+p.y*W]+1 < maze[p.x+(p.y+1)*W] ) {
            maze[p.x+(p.y+1)*W] = maze[p.x+p.y*W]+1;
            l.push_back ( P { p.x, p.y+1 } );
        }
        if ( p.y-1 >=0 && maze[p.x+p.y*W]+1 < maze[p.x+(p.y-1)*W] ) {
            maze[p.x+(p.y-1)*W] = maze[p.x+p.y*W]+1;
            l.push_back ( P { p.x, p.y-1 } );
        }
    }
    ans = maze[W*W-1];

    OUT ( ans );
}


//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    ::std::string ans;
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );
    std::vector<int> maze;
    constexpr int W=71;
    maze.resize ( W*W, INT32_MAX );

    int i = 0;
    int x = 0, y = 0;
    for ( ; i < 1024; i++ ) {
        std::istringstream is{data[i]};
        char c;
        is >> x >> c>> y;
        maze [ x + y * W ] = -1;
    }

    int len = 0;
    while ( len != INT32_MAX && i < data.size() ) {
        std::vector<P> l { P { 0, 0 } };
        maze [ 0 ] = 0;
        for ( int i = 1; i < W*W; i++ ) if ( maze[i]!=-1 ) maze[i] = INT32_MAX;
        while ( !l.empty() ) {
            auto p = l.back(); l.pop_back();
            if ( p.x+1 < W && maze[p.x+p.y*W]+1 < maze[p.x+p.y*W+1] ) {
                maze[p.x+p.y*W+1] = maze[p.x+p.y*W]+1;
                l.push_back ( P { p.x+1, p.y } );
            }
            if ( p.x-1 >= 0 && maze[p.x+p.y*W]+1 < maze[p.x+p.y*W-1] ) {
                maze[p.x+p.y*W-1] = maze[p.x+p.y*W]+1;
                l.push_back ( P { p.x-1, p.y } );
            }
            if ( p.y+1 < W && maze[p.x+p.y*W]+1 < maze[p.x+(p.y+1)*W] ) {
                maze[p.x+(p.y+1)*W] = maze[p.x+p.y*W]+1;
                l.push_back ( P { p.x, p.y+1 } );
            }
            if ( p.y-1 >= 0 && maze[p.x+p.y*W]+1 < maze[p.x+(p.y-1)*W] ) {
                maze[p.x+(p.y-1)*W] = maze[p.x+p.y*W]+1;
                l.push_back ( P { p.x, p.y - 1 } );
            }
        }
        len = maze [ W * W - 1 ];
        if ( len == INT32_MAX )
            ans = std::to_string ( x ) + ',' + std::to_string ( y );

        std::istringstream is { data[i++] };
        char c;
        is >> x >> c >> y;
        maze [ x + y * W ] = -1;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
