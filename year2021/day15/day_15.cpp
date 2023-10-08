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
#include <queue>
#include <algorithm>

//---------------------------------------------------------------------------//
#include "day_15.h"

//---------------------------------------------------------------------------//
namespace aoc::year2021::day_15 {

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

    return data;
}

//---------------------------------------------------------------------------//
std::unordered_map<int, uint64_t> memo;

//---------------------------------------------------------------------------//
uint64_t traverse ( std::vector<std::string>& d, uint64_t x = 0, uint64_t y = 0 ) {
    if ( x == d.size() - 1 && y == d.size() - 1 ) return d[y][x] - '0';
    if ( x >= d.size() || y >= d.size() ) return -1;
    auto i = ( y << 16 ) | x;
    if ( memo.contains ( i ) ) return memo[i];

    auto s1 = traverse ( d, x + 1, y );
    uint64_t s2 = traverse ( d, x, y + 1 );

    return memo[i] = std::min ( s1, s2 ) + d[y][x] - '0';
}

//---------------------------------------------------------------------------//
uint64_t traverse2 ( std::vector<std::string>& d ) {
    std::vector<int> a;
    int width = d.size();

    for ( auto& l : d ) {
        for ( auto c : l ) a.push_back ( c - '0' );
        //a[y*width+x++] = c-'0';
    }

    for ( auto i = width - 1; i > 0; i-- ) {
        a[ ( i - 1 ) *width + width - 1] += a[i * width + width - 1 ];
        a[ ( width - 1 ) *width + i - 1] += a[ ( width - 1 ) * width + i];
    }

    for ( auto y = width - 2; y >= 0 ; y-- ) {
        for ( auto x = width - 2; x >= 0; x-- ) {
            auto right = a[ y    * width + x + 1];
            auto down  = a[ ( y + 1 ) * width + x    ];
            a[ y * width + x ] += std::min ( right, down );
        }
    }

    return a[0];
}

//---------------------------------------------------------------------------//
struct Q {
    int d = 0, x = 0, y = 0;
};

bool operator < ( const Q& a, const Q& b ) {
    return a.d > b.d;
}

//---------------------------------------------------------------------------//
int dijkstra ( std::vector<std::string>& d ) {
    std::vector<Q> q;         // kolejka
    const int N = d.size();
    std::vector<std::vector<int>> dist ( N );

    for ( auto& d : dist )
        d.resize ( N, INT32_MAX );

    dist[0][0] = 0;

    Q c;

    auto cmp = [ & ] ( int a, int b ) {
        auto l = dist[c.y][c.x] + d[c.y + b][c.x + a] - '0';
        if ( l < dist[c.y + b][c.x + a] ) {
            dist[c.y + b][c.x + a] = l;
            q.push_back ( { l, c.x + a, c.y + b} );
        }
    };

    do {
        if ( c.x + 1 <  N ) cmp (  1,  0 );
        if ( c.x - 1 >= 0 ) cmp ( -1,  0 );
        if ( c.y + 1 <  N ) cmp (  0,  1 );
        if ( c.y - 1 >= 0 ) cmp (  0, -1 );

        std::sort ( q.begin(), q.end() );
        c = q.back();
        if ( c.x == N - 1 && c.y == N - 1 ) return dist[N - 1][N - 1];
        q.pop_back ();
    } while ( q.size() );

    return dist[N - 1][N - 1];
}

//---------------------------------------------------------------------------//
std::string inc ( std::string s ) {
    for ( auto& c : s )
        if ( ++c > '9' ) c = '1';
    return s;
}

//---------------------------------------------------------------------------//
void inc ( std::vector<std::string>& d ) {
    for ( auto& l : d )
        l = inc ( l );
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0ull;
    auto data = load ( "../test2input" );

    /*for ( auto& l: data )
       std::cout << l << '\n';
    */
    memo.clear();

    ans = traverse2 ( data ) - data[0][0] + '0';

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ull;
    auto data = load ( "../input" );

    memo.clear();
    for ( auto& l : data ) {
        l += inc ( l + inc ( l + inc ( l + inc ( l ) ) ) );
    }

    std::vector<std::string> nd;
    for ( auto i : Range ( 0, 5 ) ) {
        nd.insert ( nd.end(), data.begin(), data.end() );
        inc ( data );
    }

    ans = dijkstra ( nd );

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
