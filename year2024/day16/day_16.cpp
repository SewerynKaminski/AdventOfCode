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

//---------------------------------------------------------------------------//
struct P {
    int x = 0, y = 0;
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

//---------------------------------------------------------------------------//
::std::vector<::std::string> load ( ::std::istream& file ) {
    ::std::string line;
    ::std::vector<std::string> map;
    while ( ::std::getline ( file, line ) ) {
        map.push_back ( line );
    }

    return map;
}

//---------------------------------------------------------------------------//
static P UP{0,-1};
static P DOWN{0,1};
static P LEFT{-1,0};
static P RIGHT{1,0};
static P ZERO{0,0};

P end;
int min=INT_MAX;
//---------------------------------------------------------------------------//
int go ( std::vector<std::string>& maze, P p ) {
    if ( p == end ) {
        std::cout<< std::format ( "End\n" );
        return 0;
    }



    return 0;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto maze = load ( file );

    P p;
    int y=0,x=0;
    // find 'S'
    for( auto& l: maze ) {
        x = l.find('S');
        if ( x>0 ) {
            p={x,y};
            l[x]='.';
        }
        x = l.find('E');
        if ( x>0 ) {
            end={x,y};
            l[x]='.';
        }
        y++;
    }

    std::cout << p.x << ' ' << p.y << '\n';
    //ans = go ( maze, p, p, 0 );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    int64_t ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto maze = load ( file );


    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
