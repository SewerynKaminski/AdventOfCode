#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(30373
25512
65332
33549
35390)" );

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    std::string line;
    std::vector<std::string> trees;
    std::vector<std::string> visible_trees;
    while ( file >> line ) {
        trees.push_back ( line );
        visible_trees.push_back ( std::string ( line.length(), '0' ) );
    }

    const size_t HEIGHT = trees.size();
    const size_t WIDTH = trees[0].length();

    char vo1;
    char vo2;

    auto fun = [&trees, &visible_trees] ( char& vo, size_t x, size_t y ) {
        int v = trees[y][x];
        if ( v > vo ) {
            visible_trees[y][x] |= '1';
            vo = v;
        }
    };

    // Horizontal scan
    for ( auto y = 0ul; y < HEIGHT; y++ ) {
        vo1 = '/';
        vo2 = '/';
        for ( auto x = 0ul; x < WIDTH; x++ ) {
            fun ( vo1, x, y );
            fun ( vo2, WIDTH - x - 1, y );
        }
    }

    // Vertical scan
    for ( auto x = 0ul; x < WIDTH; x++ ) {
        vo1 = '/';
        vo2 = '/';
        for ( auto y = 0ul; y < HEIGHT; y++ ) {
            fun ( vo1, x, y );
            fun ( vo2, x, HEIGHT - y - 1 );
        }
    }


    for ( auto& l : visible_trees ) {
        for ( auto& v : l ) {
            ans += v == '1';
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ul;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    std::string line;
    std::vector<std::string> tab;
    while ( file >> line ) {
        tab.push_back ( line );
    }

    const size_t HEIGHT = tab.size();
    const size_t WIDTH = tab[0].length();

    auto count = [tab, WIDTH, HEIGHT] ( int x, int y, int dir, bool vert ) {
        size_t c = 0;
        auto v = tab[y][x];
        auto xy = ( y * vert ) | ( x * ( !vert ) );
        for ( size_t i = xy + dir; i < ( vert ? HEIGHT : WIDTH ) && i >= 0; i += dir ) {
            c++;
            if ( v <= tab[ ( y * ( !vert ) ) | ( i * ( vert ) ) ][ ( x * ( vert ) ) | ( i * ( !vert ) ) ] ) {
                break;
            }
        }
        return c;
    };

    auto calculateScenicScore = [ = ] ( size_t x, size_t y ) {
        return count ( x, y, 1, false ) *   // horizontal ->
               count ( x, y, -1, false ) *  // horizontal <-
               count ( x, y,  1, true ) *   // vertical down
               count ( x, y, -1, true );    // vertical up
    };

    for ( auto y = 0ul ; y < HEIGHT ; y++ ) {
        for ( auto x = 0ul ; x < WIDTH ; x++ ) {
            ans = std::max ( ans, calculateScenicScore ( x, y ) );
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
