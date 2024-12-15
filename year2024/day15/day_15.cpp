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
    int64_t x=0,y=0;
    void operator +=( const P& o ) {
        x += o.x;
        y += o.y;
    }
    void operator +=( const int64_t o ) {
        x+=o;
        y+=o;
    }
    void operator *=( const int64_t o ) {
        x*=o;
        y*=o;
    }
    P operator *( const int64_t o ) { return { x * o, y * o }; }
    P operator /(const int64_t o ) { return { x / o, y / o }; }
    P operator -( const P& o ) const { return { x - o.x, y - o.y }; }
    int64_t len_squared() const { return x * x + y * y; }
};

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
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
        if( line.empty() ) break;
        map.push_back ( line );
    }

    std::string movements;
    while ( ::std::getline ( file, line ) ) {
        movements.append( line );
    }

    return { map, movements };
}

//---------------------------------------------------------------------------//
bool go( ::std::vector<::std::string>& map, int x, int y, int dx, int dy ) {
    if ( map[y+dy][x+dx] == '#' ) return false;
    if ( map[y+dy][x+dx] == '.' ) {
        map[y+dy][x+dx] = 'O';
        return true;
    }
    bool ret = false;
    if ( map[y+dy][x+dx] == 'O') {
        return go ( map, x+dx, y+dy, dx, dy );
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    int x=0,y=0;

    for ( const auto& m : data.map ) {
        auto i = m.find ( '@' );
        if ( i != ::std::string::npos ) {
            x = (int)i;
            data.map[y][x] = '.';
            break;
        }
        y++;
    }

    for ( auto m : data.movements ) {
        switch ( m ) {
            case '^':
                if ( go ( data.map, x, y, 0, -1 ) ) {
                    y--;
                    data.map[y][x]='.';
                }
                break;
            case 'v':
                if ( go ( data.map, x, y, 0, 1 ) ) {
                    y++;
                    data.map[y][x]='.';
                }
                break;
            case '<':
                if ( go ( data.map, x, y, -1, 0 ) ) {
                    x--;
                    data.map[y][x]='.';
                }
                break;
            case '>':
                if ( go ( data.map, x, y, 1, 0 ) ) {
                    x++;
                    data.map[y][x]='.';
                }
                break;
        }
    }

    y=0;
    for( const auto& l : data.map ) {
        //::std::cout << l << '\n';
        int x=0;
        for ( const auto c : l ) {
            if ( c=='O' )
                ans += 100 * y + x;
            x++;
        }
        y++;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
bool go_wide ( ::std::vector<::std::string>& map, int x, int y, int dx, int dy, bool move=false ) {
    if ( map[y+dy][x+dx] == '#' ) return false;
    if ( map[y+dy][x+dx] == '.' ) return true;

    if ( dy == 0 ) {
        auto ret = go_wide ( map, x+dx, y, dx, 0, move );
        if ( ret && move ) {
            //map[y][x+dx*3] = map[y][x+dx*2];
            map[y][x+dx*2] = map[y][x+dx*1];
            map[y][x+dx*1] = '.';
        }
        return ret;
    }
    if ( dx == 0 ) {
        auto ret = false;
        int d = -1;
        if ( map[y+dy][x] == '[' ) d=1;
        ret = go_wide ( map, x, y+dy, 0, dy, move )
           && go_wide ( map, x+d, y+dy, 0, dy, move );
        if ( ret && move ) {
            map[y+dy*2][x] = map[y+dy][x];
            map[y+dy*2][x+d] = map[y+dy][x+d];
            map[y+dy][x] = '.';
            map[y+dy][x+d] = '.';
        }
        return ret;
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
                case '#': new_row.append("##");break;
                case '.': new_row.append("..");break;
                case '@': new_row.append("@.");break;
                case 'O': new_row.append("[]");break;
            }
        row = new_row;
    }

    // find start position
    int x=0,y=0;
    for ( const auto& m : data.map ) {
        auto i = m.find ( '@' );
        if ( i != ::std::string::npos ) {
            x = (int)i;
            data.map[y][x] = '.';
            break;
        }
        y++;
    }

    // do the movement
    for ( auto m : data.movements ) {
        switch ( m ) {
        case '^':
            if ( go_wide ( data.map, x, y, 0, -1 ) ) {
                 go_wide ( data.map, x, y, 0, -1, true );
                y--;
            }
            break;
        case 'v':
            if ( go_wide ( data.map, x, y, 0, 1 ) ) {
                 go_wide ( data.map, x, y, 0, 1, true );
                y++;
            }
            break;
        case '<':
            if ( go_wide ( data.map, x, y, -1, 0 ) ) {
                 go_wide ( data.map, x, y, -1, 0, true );
                x--;
            }
            break;
        case '>':
            if ( go_wide ( data.map, x, y, 1, 0 ) ) {
                 go_wide ( data.map, x, y, 1, 0, true );
                x++;
            }
            break;
        }
    }

    // Sum GPS coordinate
    y=0;
    for( const auto& row : data.map ) {
       //::std::cout << row << '\n'; // show map
        x=0;
        for ( auto c : row ) {
            if ( c=='[' ) ans += 100 * y + x;
            x++;
        }
        y++;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
