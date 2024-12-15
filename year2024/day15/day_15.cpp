#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(##########
#..O..O.O#
#......O.#
#.OO..O.O#
#..O@..O.#
#O#..O...#
#O..O..O.#
#.OO.O.OO#
#....O...#
##########

<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^
vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v
><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<
<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^
^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><
^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^
>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^
<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>
^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>
v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^
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
Data load ( ::std::istream& file ) {
    ::std::string line;
    ::std::vector<std::string> map;
    while ( ::std::getline ( file, line ) ) {
        if ( line.empty() ) break;
        map.push_back ( line );
    }

    ::std::string movements;
    while ( ::std::getline ( file, line ) ) {
        movements.append( line );
    }

    return { map, movements };
}

//---------------------------------------------------------------------------//
static P UP{0,-1};
static P DOWN{0,1};
static P LEFT{-1,0};
static P RIGHT{1,0};
static P ZERO{0,0};

//---------------------------------------------------------------------------//
bool go( ::std::vector<::std::string>& map, P p, P d ) {
    P pd = p+d;
    if ( map[pd.y][pd.x] == '.' ) return true;

    if ( map[pd.y][pd.x] == 'O') {
        if ( go ( map, pd, d ) ) {
            map[pd.y+d.y][pd.x+d.x] = map[pd.y][pd.x];
            map[pd.y][pd.x] = '.';
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    P p;
    for ( const auto& m : data.map ) {
        auto i = m.find ( '@' );
        if ( i != ::std::string::npos ) {
            p.x = (int)i;
            data.map[p.y][p.x] = '.';
            break;
        }
        p.y++;
    }

    P dir;
    for ( auto m : data.movements ) {
        switch ( m ) {
            case '^': dir = UP; break;
            case 'v': dir = DOWN; break;
            case '<': dir = LEFT; break;
            case '>': dir = RIGHT; break;
            default : dir = ZERO; break;
        }
        if ( go ( data.map, p, dir ) )
            p += dir;
    }

    p.y=0;
    for( const auto& l : data.map ) {
        //::std::cout << l << '\n';
        p.x=0;
        for ( const auto c : l ) {
            if ( c=='O' ) ans += 100 * p.y + p.x;
            p.x++;
        }
        p.y++;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
bool go_wide ( ::std::vector<::std::string>& map, P p, P d, bool move=false ) {
    P pd = p + d;
    if ( map[pd.y][pd.x] == '#' ) return false;
    if ( map[pd.y][pd.x] == '.' ) return true;

    if ( d.y == 0 ) {
        if ( go_wide ( map, pd, d, move ) ) {
            if ( move ) {
                map[pd.y][pd.x+d.x] = map[pd.y][pd.x];
                map[pd.y][pd.x] = '.';
            }
            return true;
        }
    } else if ( d.x == 0 ) {
        P dir = map[pd.y][pd.x] == '[' ? RIGHT : LEFT;
        if ( go_wide ( map, pd, d, move )
            && go_wide ( map, pd+dir, d, move ) ) {
            if ( move ) {
                map[pd.y+d.y][pd.x] = map[pd.y][pd.x];
                map[pd.y+d.y][pd.x+dir.x] = map[pd.y][pd.x+dir.x];
                map[pd.y][pd.x] = '.';
                map[pd.y][pd.x+dir.x] = '.';
            }
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    int64_t ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    // double map width
    for ( auto& row : data.map ) {
        ::std::string new_row;
        for ( auto c : row )
            switch ( c ) {
                case '#': new_row.append ( "##" ); break;
                case '.': new_row.append ( ".." ); break;
                case '@': new_row.append ( "@." ); break;
                case 'O': new_row.append ( "[]" ); break;
            }
        row = new_row;
    }

    // find start position
    P p;
    for ( const auto& m : data.map ) {
        auto i = m.find ( '@' );
        if ( i != ::std::string::npos ) {
            p.x = (int)i;
            data.map[p.y][p.x] = '.';
            break;
        }
        p.y++;
    }

    // do the movement
    P dir;
    for ( auto m : data.movements ) {
        switch ( m ) {
        case '^': dir = UP; break;
        case 'v': dir = DOWN; break;
        case '<': dir = LEFT; break;
        case '>': dir = RIGHT; break;
        default : dir = ZERO; break;
        }
        if ( go_wide ( data.map, p, dir ) ) {
            go_wide ( data.map, p, dir, true );
            p += dir;
        }
    }

    // Sum GPS coordinate
    p.y=0;
    for( const auto& row : data.map ) {
       //::std::cout << row << '\n'; // show map
        p.x=0;
        for ( auto c : row ) {
            if ( c=='[' ) ans += 100 * p.y + p.x;
            p.x++;
        }
        p.y++;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
