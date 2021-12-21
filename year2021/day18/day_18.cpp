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
#include <set>
#include <iomanip>
#include <bit>

//---------------------------------------------------------------------------//
#include "day_18.h"

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_18 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::vector<std::string> data;

    std::string line;
    while ( fs >> line ) {
        data.push_back ( line );
    }
#ifdef DEBUG

#endif

    return data;
}

//---------------------------------------------------------------------------//
bool explode ( std::string& s ) {
    size_t i = 0, n = 0,
           right = -1,
           left = -1;
    while ( i < s.size() && n < 5 ) {
        char c = s[i++];
        n += c == '[';
        n -= c == ']';
    }

    if ( i < s.size() ) {
        size_t bi = i - 1;
        //std::cout << s << " [ at " << bi << "\n";
        while ( s[i] != ']' ) {
            i++;
        }

        auto bj = i;
        //std::cout << " ] at " << bj << "\n";


        // wartosc po prawej od pary
        auto ri = s.find_first_not_of ( "],[", i );
        auto rj = ri;
        if ( ri != -1 ) {
            rj = s.find_first_not_of ( "0123456789", ri );
            right = stoi ( s.substr ( ri, rj - ri ) );
            //std::cout << ri << " - " << rj << ' ' << right << '\n';
        }
        // wartosc po lewej od pary
        i = bi;
        while ( ( s[i] == ']' || s[i] == ',' || s[i] == '[' ) && i < -1 ) {
            i--;
        }
        auto lj = i;
        if ( i != -1 ) {
            lj = i + 1;
            while ( s[i] >= '0' && s[i] <= '9' ) {
                i--;
            }
            i++;
        }
        auto li = i;
        if ( li != -1 ) {
            //std::cout << li << ' ' << lj << " " << stoi ( s.substr ( li, lj - li ) ) << '\n';
            left = stoi ( s.substr ( li, lj - li ) );
        }

        // para lewo
        auto comma = s.find ( ',', bi );
        auto bleft = stoi ( s.substr ( bi + 1,  comma - ( bi + 1 ) ) );
        auto bright = stoi ( s.substr ( comma + 1,  comma - ( bj ) ) );

        if ( ri != -1 ) {
            s.replace ( ri, rj - ri, std::to_string ( right + bright ) );
        }

        s.replace ( bi, bj - bi + 1, "0" );

        if ( li != -1 ) {
            s.replace ( li, lj - li, std::to_string ( left + bleft ) );
        }
        //std::cout << s;
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------//
bool split ( std::string& s ) {
    auto i = 0ul;
    while ( i != -1 ) {
        i = s.find_first_not_of ( "[,]", i );
        if ( i != -1 ) {
            auto j = s.find_first_of ( "[,]", i );
            if ( j - i > 1 ) {
                int v = stoi ( s.substr ( i, j - i ) );
                s.replace ( i, j - i, "[" + std::to_string ( v / 2 ) + "," + std::to_string ( v / 2 + ( v & 1 ) ) + "]" );
                //std::cout << s;
                return true;
            }
            i = j;
        }
    }
    return false;
}

//---------------------------------------------------------------------------//
std::string reduce ( std::string s ) {
    while ( explode ( s ) || split ( s ) ) ;
    return s;
}

//---------------------------------------------------------------------------//
std::string sum ( const std::string& a, const std::string& b ) {
    return reduce ( "[" + a + "," + b + "]" );
}

//---------------------------------------------------------------------------//
uint64_t magnitude ( std::string& s, size_t& i ) {
    uint64_t sum = 0ul;
    if ( s[i] == ']' ) {
        i++;
    } else if ( s[i] == '[' ) {
        i++;
        sum = 3 * magnitude ( s, i );
        sum += magnitude ( s, i );
    } else if ( s[i] == ',' ) {
        i++;
        sum = 2 * magnitude ( s, i );
        magnitude ( s, i );
    } else {
        sum = s[i++] - '0';
    }

    return sum;
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0ull;
    auto data = load ( "../input" );

    std::string a = data[0];
    for ( auto i = 1; i < data.size(); i++ ) {
        //std::cout << num << '\n';
        a = sum ( a, data[i] );
    }

    //sum ( "[[[[9,8],10],2],3]", "4" );

    //std::cout << reduce ( "[[[[[9,8],1],2],3],4]" );
    //std::cout << reduce ( "[7,[6,[5,[4,[3,2]]]]]" );
    //std::cout << reduce ( "[[6,[5,[4,[3,2]]]],1]" );
    size_t i = 0;
    //std::string s = //"[[1,2],[[3,4],5]]";    // 143
    // "[[1,2],[3,4]]";    // 55
    //"[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]";
    ans = magnitude ( a, i );
    // 4140 too low
    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ul;
    auto data = load ( "../input" );

    for ( int j = 0; j < data.size() - 1; j++ ) {
        std::string a = data[0];
        for ( auto i = j + 1; i < data.size(); i++ ) {
            size_t k = 0;
            a = sum ( data[j], data[i] );
            ans = std::max ( ans, magnitude ( a, k ) );
        }
    }

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
