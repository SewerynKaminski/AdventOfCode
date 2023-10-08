//---------------------------------------------------------------------------//
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <fstream>
#include <limits>
#include <algorithm>

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_9 {

//---------------------------------------------------------------------------//
struct Display {
    std::vector<std::string> patterns;
    std::vector<std::string> output;
};

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::vector<Display> data;

    char c;
    std::string str;
    while ( fs.good() ) {
        std::vector<std::string> p;
        std::vector<std::string> o;

        for ( int i = 0; i < 10; i++ ) {
            if ( fs >> str ) {
                std::sort ( str.begin(), str.end() );
                //std::cout << str << " ";
                p.push_back ( str );
            }
        }
        fs >> c;
        //std::cout << " - ";
        for ( int i = 0; i < 4; i++ ) {
            if ( fs >> str ) {
                std::sort ( str.begin(), str.end() );
                //std::cout << str << " ";
                o.push_back ( str );
            }
        }
        //std::cout << "\n";
        if ( p.size() == 10 )
            data.push_back ( Display{p, o} );
    }
    return data;
}

//---------------------------------------------------------------------------//
void Task_1() {
    auto ans = 0;

    auto data = load ( "../input" );

    for ( auto& display : data )
        for ( auto& o : display.output )
            if ( o.length() == 2 || o.length() == 4 || o.length() == 7 || o.length() == 3 )
                ans++;

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
int cnt ( const std::string& a, const std::string& b ) {
    int r = 0;
    for ( auto& c : b ) {
        r += a.end() != std::find ( a.begin(), a.end(), c );
    }
    return r;
}

//---------------------------------------------------------------------------//
bool contains ( const std::string& a, const std::string& b ) {
    for ( auto& c : b ) {
        if ( a.end() == std::find ( a.begin(), a.end(), c ) ) {
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------//
void Task_2() {
    auto ans = 0;

    auto data = load ( "../input" );

    for ( auto& display : data ) {
        std::string digits[10];
        for ( auto& s : display.patterns ) {
            if ( s.size() == 2 ) digits[1] = s;
            else if ( s.size() == 4 ) digits[4] = s;
            else if ( s.size() == 3 ) digits[7] = s;
            else if ( s.size() == 7 ) digits[8] = s;
        }
        for ( auto& s : display.patterns ) {
            if ( s.size() == 5 ) { // 2 lub 3 lub 5
                // 235 => tylko 3 zawiera 1 lub 7 w calosci
                //  25 => tylko 5 zawiera >4
                //   2 => tylko 2
                if ( contains ( s, digits[1] ) ) {
                    digits[3] = s;
                } else { // 2 lub 5
                    if ( cnt ( s, digits[4] ) == 3 ) {
                        digits[5] = s;
                    } else {
                        digits[2] = s;
                    }
                }
            } else if ( s.size() == 6 ) { // 0 lub 6 lub 9
                if ( !contains ( s, digits[1] ) ) {
                    digits[6] = s;
                } else { // 0 lub 9
                    if ( cnt ( s, digits[4] ) == 3 ) {
                        digits[0] = s;
                    } else {
                        digits[9] = s;
                    }
                }
            }
        }

        int num = 0;
        for ( auto& o : display.output ) {
            //std::cout << digit << " ";
            for ( int i = 0; i < 10; i++ ) {
                if ( digits[i] == o ) {
                    //std::cout << i;
                    num = 10 * num + i;
                }
            }
        }
        ans += num;
        //std::cout << " == " << num << "\n";
    }

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
