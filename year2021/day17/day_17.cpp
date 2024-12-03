//---------------------------------------------------------------------------//
// #include <string>
// #include <iostream>
// #include <sstream>
// #include <map>
// #include <unordered_map>
// #include <vector>
#include <ranges>
// #include <fstream>
// #include <limits>
// #include <set>
// #include <iomanip>
// #include <bit>

//---------------------------------------------------------------------------//
#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    //std::fstream fs ( file );

    std::string line;
    char c;
    int xmin, xmax, ymin, ymax;
    if ( fs >> line >> line >> c >> c
            >> xmin >> c >> c >> xmax >> c >> c >> c
            >> ymin >> c >> c >> ymax ) {
#ifdef DEBUG
        std::cout << xmin << " < " << xmax << ", "
                  << ymin << " < " << ymax << '\n' ;
#endif
    }

    return std::tuple{xmin, xmax, ymin, ymax};
}


//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    auto [xmin, xmax, ymin, ymax] = load ( puzzle_input
        //"../input"
        );

    ans = -ymin - 1;
    ans = ans * ( ans + 1 ) / 2;

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
bool shot ( int vx, int vy, int xmin, int xmax, int ymin, int ymax ) {
    int x = 0, y = 0;
    while ( ( x < xmin || y > ymax ) ) {
        x += vx;
        y += vy;
        if ( vx > 0 ) vx--;
        if ( vx < 0 ) vx++;
        vy--;
        if ( x > xmax || y < ymin ) return false;
    }

    return true;
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    auto [xmin, xmax, ymin, ymax] = load ( puzzle_input
                                           //"../input"
                                         );

    for ( auto vy : Range ( ymin - 1, - ( ymin - 1 ) ) )
        for ( auto vx : Range ( 1, xmax + 1 ) )
            ans += shot ( vx, vy, xmin, xmax, ymin, ymax );

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
