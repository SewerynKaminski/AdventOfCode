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
    R"(..............
 ..............
 .......#......
 .....###.#....
 ...#...#.#....
 ....#...##....
 ...#.###......
 ...##.#.##....
 ....#..#......
 ..............
 ..............
 ..............)"
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
};

struct Hash{
    size_t operator()(const Point& p ) const {
        return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y)<<1);
    }
};

auto parse( std::istream& ss ){
    std::unordered_map<Point,Point,Hash> board;
    std::string line;
    int y=0;
    while ( getline(ss,line) ) {
        for ( int x=0; x < (int)line.size(); x++ ) {
            if ( line[x]=='#' ) {
                //board. insert( {x,y} );
                board[{x,y}] = Point{0,0};
            }
        }
        y++;
    }
    return board;
}

auto move ( auto& board, auto& b ) {
    std::unordered_map<Point,Point,Hash> nboard;
    for ( auto& [key,d] : board ) {
        auto p = key+d;
        if ( b[p] <= 1 ) {
            nboard[p] = {0,0};
        } else {
            nboard[key] = {0,0};
        }
    }
    return nboard;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    auto board = parse( file );

    Point dirs[]{ {0,-1}, {0,1}, {-1,0}, {1,0} };

    std::unordered_map<Point,int,Hash> b;
    for ( int j=0;j<10;j++) {
        for ( auto& pp : board ) {
            auto& p = pp.first;
            pp.second = {0,0};
            //std::cout << p.x << " " << p.y << "\n";
            if ( board.contains({p.x-1, p.y-1}) ||
                 board.contains({p.x  , p.y-1}) ||
                 board.contains({p.x+1, p.y-1}) ||
                 board.contains({p.x-1, p.y  }) ||
                 board.contains({p.x+1, p.y  }) ||
                 board.contains({p.x-1, p.y+1}) ||
                 board.contains({p.x  , p.y+1}) ||
                 board.contains({p.x+1, p.y+1}) ) {
                for ( int i=0; i<4; i++ ) {
                    auto d = dirs[ (i+j) % 4 ];
                    if (    !board.contains( {p.x+d.x+d.y, p.y+d.y - d.x} ) &&
                            !board.contains( {p.x+d.x    , p.y+d.y      } ) &&
                            !board.contains( {p.x+d.x-d.y, p.y+d.y + d.x} ) ) {
                        b[ p+d ]++;
                        pp.second = d;
                        break;
                    }
                }
            }
        }
        board = move( board, b );
        b.clear();
    }
    int minx = board.begin()->first.x, maxx = minx,
        miny = board.begin()->first.y, maxy = miny;
    for ( auto& p : board ) {
        minx = std::min( minx, p.first.x );
        maxx = std::max( maxx, p.first.x );
        miny = std::min( miny, p.first.y );
        maxy = std::max( maxy, p.first.y );
    }
    ans = (maxx-minx+1)*(maxy-miny+1) - board.size();

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    auto board = parse( file );

    Point dirs[]{ {0,-1}, {0,1}, {-1,0}, {1,0} };

    std::unordered_map<Point,int,Hash> b;
    bool change = true;
    for ( int j=0; change; j++ ) {
        ans = j;
        change = false;
        for ( auto& pp : board ) {
            auto& p = pp.first;
            pp.second = {0,0};
            if ( board.contains({p.x-1, p.y-1}) ||
                 board.contains({p.x  , p.y-1}) ||
                 board.contains({p.x+1, p.y-1}) ||
                 board.contains({p.x-1, p.y  }) ||
                 board.contains({p.x+1, p.y  }) ||
                 board.contains({p.x-1, p.y+1}) ||
                 board.contains({p.x  , p.y+1}) ||
                 board.contains({p.x+1, p.y+1}) ) {
                for ( int i=0; i<4; i++ ) {
                    auto d = dirs[ (i+j) % 4 ];
                    if (    !board.contains( {p.x+d.x+d.y, p.y+d.y - d.x} ) &&
                            !board.contains( {p.x+d.x    , p.y+d.y      } ) &&
                            !board.contains( {p.x+d.x-d.y, p.y+d.y + d.x} ) ) {
                        b[ p+d ]++;
                        pp.second = d;
                        change = true;
                        break;
                    }
                }
            }
        }

        board = move ( board, b );
        b.clear();
    }
    ans++;

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
Initial state:
#0######
#>>.<^<#
#.<..<<#
#>v.><>#
#<^v^^>#
######.#

Minute 1, move down:
#.######
#E>*.<.#
#<..<<.#
#>*.**.#
#>v..^<#
######.#

Minute 2, move down:
#.######
#.*>*..#
#E^**^<#
#.>*.^>#
#.>..<.#
######.#

Minute 3, wait:
#.######
#<^<**.#
#E2<.*.#
#><*>..#
#..><..#
######.#

Minute 4, move up:
#.######
#E<..**#
#<<.<..#
#<*.>>.#
#.^**^.#
######.#

Minute 5, move right:
#.######
#2Ev.<>#
#<.<..<#
#.^>^**#
#.*..*.#
######.#

Minute 6, move right:
#.######
#>2E<.<#
#.2v^2<#
#>..>2>#
#<....>#
######.#

Minute 7, move down:
#.######
#.22^2.#
#<vE<2.#
#>>v<>.#
#>....<#
######.#

Minute 8, move left:
#.######
#.<>2^.#
#.E<<.<#
#.22..>#
#.2v^2.#
######.#

Minute 9, move up:
#.######
#<E2>>.#
#.<<.<.#
#>2>2^.#
#.v><^.#
######.#

Minute 10, move right:
#.######
#.2E.>2#
#<2v2^.#
#<>.>2.#
#..<>..#
######.#

Minute 11, wait:
#.######
#2^E^2>#
#<v<.^<#
#..2.>2#
#.<..>.#
######.#

Minute 12, move down:
#.######
#>>.<^<#
#.<E.<<#
#>v.><>#
#<^v^^>#
######.#

Minute 13, move down:
#.######
#.>3.<.#
#<..<<.#
#>2E22.#
#>v..^<#
######.#

Minute 14, move right:
#.######
#.2>2..#
#.^22^<#
#.>2E^>#
#.>..<.#
######.#

Minute 15, move right:
#.######
#<^<22.#
#.2<.2.#
#><2>E.#
#..><..#
######.#

Minute 16, move right:
#.######
#.<..22#
#<<.<..#
#<2.>>E#
#.^22^.#
######.#

Minute 17, move down:
#.######
#2.v.<>#
#<.<..<#
#.^>^22#
#.2..2E#
######.#

Minute 18, move down:
#.######
#>2.<.<#
#.2v^2<#
#>..>2>#
#<....>#
######E#
