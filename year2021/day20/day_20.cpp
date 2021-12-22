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
#include <math.h>
#include <numeric>

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_20 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::string line;
    std::string algo;
    std::string image;

    // algo
    while ( std::getline ( fs, line ), !line.empty() ) {
        algo.append ( line );
    }

    // image
    while ( std::getline ( fs, line ), !line.empty() ) {
        image.append ( line );
    }

    return std::tuple{algo, image};
}

//---------------------------------------------------------------------------//
inline uint64_t key ( int x, int y ) {
    return ( uint64_t ( y + 100 ) << 32 ) | uint64_t ( x + 100 );
}

//---------------------------------------------------------------------------//
void enhance ( std::string& algo, int a, int step, bool neginput, bool negoutput, std::unordered_map<uint64_t, char>& data ) {
    std::unordered_map<uint64_t, char> ndata;

    auto isLit = [&data] ( int x, int y ) {
        return data.contains ( key ( x, y ) );
    };

    //auto invert = algo[0]=='#';

    for ( int y : Range ( -step, a + step ) ) {
        for ( int x : Range ( -step, a + step ) ) {
            int i = ( isLit ( x - 1, y - 1 ) << 8 ) |
                    ( isLit ( x, y - 1 ) << 7 ) |
                    ( isLit ( x + 1, y - 1 ) << 6 ) |
                    ( isLit ( x - 1, y   ) << 5 ) |
                    ( isLit ( x, y   ) << 4 ) |
                    ( isLit ( x + 1, y   ) << 3 ) |
                    ( isLit ( x - 1, y + 1 ) << 2 ) |
                    ( isLit ( x, y + 1 ) << 1 ) |
                    ( isLit ( x + 1, y + 1 ) << 0 );
            if ( neginput ) i ^= 0x1ff;
            //std::cout << i << ' ';
            if ( negoutput ) {
                if ( algo[i] == '.' ) ndata[key ( x, y )] = '#';
            } else if ( algo[i] == '#' ) ndata[key ( x, y )] = '#';

        }
    }

    data = ndata;
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0ull;
    std::unordered_map<uint64_t, char> data;
    std::unordered_map<uint64_t, char> ndata;

    auto [algo, image] = load ( "../input" );

    //std::cout << algo.size() << "\n";
    //std::cout << image.size() << "\n";

    int a = sqrt ( image.size() );
    for ( int y : Range ( 0, a ) ) {
        for ( int x : Range ( 0, a ) ) {
            if ( image[y * a + x] == '#' )
                data[key ( x, y )] = '#';
        }
    }

    //std::cout << "*"
    //          << ( ( data.contains ( key ( 1, 0 ) ) << 8 ) | ( data.contains ( key ( 1, 0 ) ) << 7 ) )
    //          << '\n';

    bool alternate = algo[0] == '#';
    for ( auto step : Range ( 0, 2 ) )
        enhance ( algo, a, step + 1, ( step & 1 ) && alternate, ( ( step + 1 ) & 1 ) &alternate, data );

    ans = data.size();
    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ull;
    std::unordered_map<uint64_t, char> data;
    std::unordered_map<uint64_t, char> ndata;

    auto [algo, image] = load ( "../input" );

    int a = sqrt ( image.size() );
    for ( int y : Range ( 0, a ) ) {
        for ( int x : Range ( 0, a ) ) {
            if ( image[y * a + x] == '#' )
                data[key ( x, y )] = '#';
        }
    }

    bool alternate = algo[0] == '#';
    for ( auto step : Range ( 0, 50 ) ) {
        enhance ( algo, a, step + 1, ( step & 1 ) && alternate, ( ( step + 1 ) & 1 ) &alternate, data );
    }

    ans = data.size();
    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
