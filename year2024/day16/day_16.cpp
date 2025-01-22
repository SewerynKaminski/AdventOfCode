#include "day"
#include <climits>
#include <format>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(#################
#...#...#...#..E#
#.#.#.#.#.#.#.#.#
#.#.#.#...#...#.#
#.#.#.#.###.#.#.#
#...#.#.#.....#.#
#.#.#.#.#.#####.#
#.#...#.#.#.....#
#.#.#####.#.###.#
#.#.#.......#...#
#.#.###.#####.###
#.#.#...#.....#.#
#.#.#.#####.###.#
#.#.#.........#.#
#.#.#.#########.#
#S#.............#
#################
)"
);

enum FROM{
    LEFT, RIGHT, TOP, BOTTOM,
};

//---------------------------------------------------------------------------//
struct P {
    int x = 0, y = 0;
    FROM d=RIGHT;
    void operator +=( const P& o ) { x += o.x; y += o.y; }
    void operator +=( const int o ) { x += o; y += o; }
    void operator *=( const int o ) { x *= o; y *= o; }
    P operator +( const P& o ) const { return { x + o.x, y + o.y }; }
    P operator -( const P& o ) const { return { x + o.x, y + o.y }; }
    P operator *( const int o ) { return { x * o, y * o }; }
    P operator /(const int o ) { return { x / o, y / o }; }
    bool operator ==(const P& o ) const { return x==o.x && y==o.y; }
    bool operator !=(const P& o ) const { return x!=o.x || y!=o.y; }
    int len_squared() const { return x * x + y * y; }
};

//---------------------------------------------------------------------------//
inline ::std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
struct Data{
    ::std::vector<std::string> map;
    ::std::string movements;
};

constexpr int WALL = INT32_MIN;
//---------------------------------------------------------------------------//
::std::vector<int> load ( ::std::istream& file ) {
    ::std::string line;
    ::std::vector<int> maze;
    while ( ::std::getline ( file, line ) ) {
        for ( char c : line )
            if ( c=='#') maze.push_back ( WALL );
            else if ( c=='S') maze.push_back(1);
            else if ( c=='E') maze.push_back(2);
            else maze.push_back ( INT32_MAX );
    }

    return maze;
}

//---------------------------------------------------------------------------//

int min=INT_MAX;
constexpr int W=141;
//constexpr int W=17;

//---------------------------------------------------------------------------//
int go ( std::vector<int>& maze, P p, P end ) {
    int len = 0;

    //while ( len != INT32_MAX && i < maze.size() )
    {
        std::vector<P> l { p };
        for ( int i = 0; i < W*W; i++ ) if ( maze[i]!=WALL ) maze[i] = INT32_MAX;
        maze [ p.x+p.y*W ] = 0;

        while ( !l.empty() ) {
            auto p = l.back(); l.pop_back();
            if(p==end) continue;
            int o = p.x+p.y*W;

            if ( p.x+1 < W && maze[o]+1 < maze[o+1] ) {
                auto d = maze[o] + 1;
                if ( p.d==TOP || p.d==BOTTOM ) d+=1000;
                if ( maze[o+1] > d ) {                
                    maze[o+1] = d;
                    l.push_back ( P { p.x+1, p.y, LEFT } );
                }
            }
            if ( p.x-1 >= 0 && maze[o]+1 < maze[o-1] ) {
                auto d = maze[o] + 1;
                if ( p.d==TOP || p.d==BOTTOM ) d+=1000;
                if ( maze[o-1] > d ) {
                    maze[o-1] = d;
                    l.push_back ( P { p.x-1, p.y, RIGHT } );
                }
            }
            if ( p.y+1 < W && maze[o]+1 < maze[o+W] ) {
                auto d = maze[o] + 1;
                if ( p.d==LEFT || p.d==RIGHT ) d+=1000;
                if ( maze[o+W] > d ) {
                    maze[o+W] = d;
                    l.push_back ( P { p.x, p.y+1, TOP } );
                }
            }
            if ( p.y-1 >= 0 && maze[o]+1 < maze[o-W] ) {
                auto d = maze[o] + 1;
                if ( p.d==LEFT || p.d==RIGHT ) d += 1000;
                if ( maze[o-W] > d ) {
                    maze[o-W] = d;
                    l.push_back ( P { p.x, p.y - 1, BOTTOM } );
                }
            }
        }
        len = maze [ end.x +end.y * W ];
    }

    return len;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto maze = load ( file );

    P start, end;
    for ( int y = 0; y < W; y++ ) {
        for ( int x = 0 ; x < W; x++ ) {
            if ( maze[x+y*W] == 1 ) {
                start = {x,y};
                maze[x+y*W] = INT32_MAX;
            }
            if ( maze[x+y*W] == 2 ) {
                end = {x,y};
                maze[x+y*W] = INT32_MAX;
            }
        }
    }

    start.d = LEFT;
    //std::cout << "S: " << start.x << ' ' << start.y << ' ' << start.d << '\n';
    //std::cout << "E: " << end.x << ' ' << end.y << '\n';
    ans = go ( maze, start, end );

    P p=end, last=end;

    while ( p!=start ) {
        //std::cout << p.x <<' '<< p.y << ' ' << maze[p.x+p.y*W] << '\n';
        auto c = maze[p.x+p.y*W];
        if ( maze[p.x+p.y*W+1]!=-1 && maze[p.x+p.y*W+1] < c ) {
            p.x++;
        } else if ( maze[p.x+p.y*W-1]!=-1 && maze[p.x+p.y*W-1] < c ) {
            p.x--;
        } else if ( maze[p.x+p.y*W+W]!=-1 && maze[p.x+p.y*W+W] < c ) {
            p.y++;
        } else if ( maze[p.x+p.y*W-W]!=-1 && maze[p.x+p.y*W-W] < c ) {
            p.y--;
        }
    }

    /*for ( int y = 0; y < W; y++ ) {
        for ( int x = 0 ; x < W; x++ ) {
            if ( maze[x+y*W] == -1 ) {
                std::cout << "    ##";
            } else {
                auto v = maze[x+y*W];
                if ( v<10 ) std::cout << ' ';
                if ( v<100 ) std::cout << ' ';
                if ( v<1000 ) std::cout << ' ';
                if ( v<10000 ) std::cout << ' ';
                if ( v<100000 ) std::cout << ' ';
                std::cout << maze[x+y*W];
            }
        }
        std::cout << '\n';
    }*/

    OUT ( ans );
}

//---------------------------------------------------------------------------//
bool is_branch ( int a1, int a2, int a3, int a4 ) {
    auto sum = int(a1==WALL) + int(a2==WALL) + int(a3==WALL) + int(a4==WALL);
    return sum<2;
}

//---------------------------------------------------------------------------//
void reverse ( ::std::vector<int>& m, P p ) {
    ::std::vector<P> list{p};
    while ( list.size() ) {
        p = list.back(); list.pop_back();
        auto o = p.x + p.y * W;
        //std::cout << p.x << ' ' << p.y << '\n';
        auto a1 = m[o-1], a2 = m[o+1], a3 = m[o-W], a4 = m[o+W];

        if ( is_branch( a1, a2, a3, a4 ) ) {
            a1 = abs(a1), a2 = abs(a2), a3 = abs(a3), a4 = abs(a4);
            if ( p.d == FROM::LEFT ) {
                if ( a1-1 > a2 && a2>0 ) list.push_back ( { p.x+1, p.y, FROM::LEFT } );
                if ( a1-1000 > a3 && a3>0 ) list.push_back ( { p.x, p.y-1, FROM::BOTTOM} );
                if ( a1-1000 > a4 && a4>0 ) list.push_back ( { p.x, p.y+1, FROM::TOP} );
            } else
            if ( p.d==FROM::RIGHT ) {
                if ( a2-1 > a1 && a1>0 ) list.push_back ( { p.x-1, p.y, FROM::RIGHT} );
                if ( a2-1000 > a3 && a3>0 ) list.push_back ( { p.x, p.y-1, FROM::BOTTOM} );
                if ( a2-1000 > a4 && a4>0 ) list.push_back ( { p.x, p.y+1, FROM::TOP} );
            } else
            if ( p.d==FROM::TOP ) {
                if ( a3-1000 > a1 && a1>0 ) list.push_back ( { p.x-1, p.y, FROM::RIGHT } );
                if ( a3-1000 > a2 && a2>0 ) list.push_back ( { p.x+1, p.y, FROM::LEFT } );
                if ( a3-1 > a4 && a4>0 ) list.push_back ( { p.x, p.y+1, FROM::TOP } );
            } else
            if ( p.d==FROM::BOTTOM ) {
                if ( a4-1000 > a1 && a1>0 ) list.push_back ( { p.x-1, p.y, FROM::RIGHT } );
                if ( a4-1000 > a2 && a2>0 ) list.push_back ( { p.x+1, p.y, FROM::LEFT } );
                if ( a4-1 > a3 && a3>0 ) list.push_back ( { p.x, p.y-1, FROM::BOTTOM } );
            }
        } else {
            auto a0 = m[o];
            if ( a1>=0 && a0 > a1 ) {
                list.push_back ( { p.x-1, p.y, FROM::RIGHT } );
            }
            if ( a2>=0 && a0 > a2 ) {
                list.push_back ( { p.x+1, p.y, FROM::LEFT } );
            }
            if ( a3>=0 && a0 > a3 ) {
                list.push_back ( { p.x, p.y-1, FROM::BOTTOM } );
            }
            if ( a4>=0 && a0 > a4 ) {
                list.push_back ( { p.x, p.y+1, FROM::TOP } );
            }
        }
        m[o] = -m[o];
    }
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    int64_t ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto maze = load ( file );

    P start, end;
    for ( int y = 0; y < W; y++ ) {
        for ( int x = 0 ; x < W; x++ ) {
            if ( maze[x+y*W] == 1 ) {
                start = {x,y};
                maze[x+y*W] = INT32_MAX;
            }
            if ( maze[x+y*W] == 2 ) {
                end = {x,y};
                maze[x+y*W] = INT32_MAX;
            }
        }
    }

    start.d = LEFT;
    go ( maze, start, end );
    reverse ( maze, end );

    for ( int y = 0; y < W; y++ ) {
        for ( int x = 0 ; x < W; x++ ) {
            if ( maze[x+y*W] == WALL ) {
                std::cout << "\033[90m" <<" ######" << "\033[39m";
            } else if ( maze[x+y*W] <= 0 ) {
                ans++;
                std::cout << "\033[32m";
                          //<< "     O "
                auto v = abs(maze[x+y*W]);
                if ( v<10 ) std::cout << ' ';
                if ( v<100 ) std::cout << ' ';
                if ( v<1000 ) std::cout << ' ';
                if ( v<10000 ) std::cout << ' ';
                if ( v<100000 ) std::cout << ' ';
                if ( v<1000000 ) std::cout << ' ';
                std::cout << v
                          << "\033[39m";
            } else {
                //std::cout << '.';
                auto v = abs(maze[x+y*W]);
                if ( v<10 ) std::cout << ' ';
                if ( v<100 ) std::cout << ' ';
                if ( v<1000 ) std::cout << ' ';
                if ( v<10000 ) std::cout << ' ';
                if ( v<100000 ) std::cout << ' ';
                if ( v<1000000 ) std::cout << ' ';
                std::cout << maze[x+y*W];
            }
        }
        std::cout << '\n';
    }
    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
