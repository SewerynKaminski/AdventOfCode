#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput {
R"(MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX)"};

//---------------------------------------------------------------------------//
struct Point { int x; int y; };
typedef std::vector<char> Array1;
typedef std::vector<Array1> Array2;

//---------------------------------------------------------------------------//
int find( Array2& tab, Point d ) {
    std::array<char,5> q{"XMAS"};
    Point s{0,0};
    if ( d.x<0 ) s.x = q.size()-2;
    if ( d.y<0 ) s.y = q.size()-2;
    Point m{0,0};
    if ( d.x>0 ) m.x = q.size()-2;
    if ( d.y>0 ) m.y = q.size()-2;
    int ret=0;
    for ( uint y=s.y; y<tab.size()-m.y; y++ ) {
        for ( uint x=s.x; x<tab[0].size()-m.x; x++ ){
            bool ok=true;
            int i=0;
            while ( ok && q[i]) {
                if ( tab[y+i*d.y][x+i*d.x]==q[i] ) {
                    i++;
                } else {
                    ok = false;
                }
            }
            ret += ok;
        }
    }
    return ret;
}
//---------------------------------------------------------------------------//
Array2 load ( std::istream& file ) {
    Array2 ret;
    while ( !file.eof() ) {
        std::string line;
        std::getline ( file, line );
        if ( line.size() ) {
            ret.push_back ( Array1{} );
            for ( char c:line ) {
                ret.back().push_back(c);
            }
        }
    }
    return ret;
}

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto tab = load ( file );

    constexpr std::array<Point,8> dir{
        Point{ 1, 0}, Point{-1, 0},
        Point{ 0, 1}, Point{ 0,-1},
        Point{ 1, 1}, Point{-1,-1},
        Point{-1, 1}, Point{ 1,-1},
    };

    for ( auto& d : dir ) {
        ans += find ( tab, d );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto tab = load ( file );

    for ( uint y=1; y < tab.size()-1; y++) {
        for ( uint x=1; x < tab[0].size()-1; x++ ) {
            ans += tab[y][x]=='A'
                   && tab[y-1][x-1] + tab[y+1][x+1] == 'M'+'S'
                   && tab[y+1][x-1] + tab[y-1][x+1] == 'M'+'S';
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
