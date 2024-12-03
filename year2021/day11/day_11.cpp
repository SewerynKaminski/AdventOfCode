//---------------------------------------------------------------------------//
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <map>
//#include <unordered_map>
//#include <vector>
//#include <ranges>
//#include <fstream>
//#include <limits>
#include <ranges>
#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    //std::fstream fs ( file );
    std::vector<std::string> data;
    std::string line;

    while ( fs >> line ) {
        data.push_back ( line );
    }

    return data;
}

//---------------------------------------------------------------------------//
void show ( std::vector<std::string>& data ) {
    for ( auto& l : data ) std::cout << l << '\n';
    std::cout << '\n';
}

//---------------------------------------------------------------------------//
void inc ( std::vector<std::string>& data ) {
    for ( auto& l : data ) {
        for ( auto& o : l )
            o++;
    }
}

//---------------------------------------------------------------------------//
auto flash ( std::vector<std::string>& data ) {
    int cnt = 0;
    bool flash;
    do {
        flash = false;
        for ( auto r : Range ( 0, 10 ) ) {
            for ( auto c : Range ( 0, 10 ) ) {
                if ( data[r][c] > '9' ) {
                    data[r][c] = '0';
                    cnt++;
                    if ( r > 0 &&          data[r - 1][c    ] != '0' ) data[r - 1][c    ]++;
                    if ( r > 0 && c < 9 && data[r - 1][c + 1] != '0' ) data[r - 1][c + 1]++;
                    if ( c < 9 &&          data[r    ][c + 1] != '0' ) data[r    ][c + 1]++;
                    if ( r < 9 && c < 9 && data[r + 1][c + 1] != '0' ) data[r + 1][c + 1]++;
                    if ( r < 9 &&          data[r + 1][c    ] != '0' ) data[r + 1][c    ]++;
                    if ( r < 9 && c > 0 && data[r + 1][c - 1] != '0' ) data[r + 1][c - 1]++;
                    if ( c > 0 &&          data[r    ][c - 1] != '0' ) data[r    ][c - 1]++;
                    if ( r > 0 && c > 0 && data[r - 1][c - 1] != '0' ) data[r - 1][c - 1]++;
                    flash = true;
                }
            }
        }
    } while ( flash );

    return cnt;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0;

    auto data = load ( puzzle_input );

    //show ( data );

    for ( auto step : Range ( 0, 100 ) ) {
        (void)step;
        //std::cout << "Step: " << (step+1) << '\n';
        inc ( data );
        ans += flash ( data );

        //show ( data );
    }

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ul;

    auto data = load ( puzzle_input );

    do {
        ans++;
        inc ( data );
    } while ( 100 != flash ( data ) );
    //show ( data );

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
