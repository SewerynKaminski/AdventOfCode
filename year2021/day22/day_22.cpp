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
#include <algorithm>
#include <queue>

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_22 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
struct Box {
    int x1, y1, z1,
        x2, y2, z2;
    bool is_on = false;

    inline int64_t volume() const {
        return int64_t ( x2 - x1 ) * int64_t ( y2 - y1 ) * int64_t ( z2 - z1 );
    }
};

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::vector<Box> data;
    std::string on;
    int x1, x2, y1, y2, z1, z2;
    char c;
    while ( fs >> on
            >> c >> c >> x1
            >> c >> c >> x2
            >> c
            >> c >> c >> y1
            >> c >> c >> y2
            >> c
            >> c >> c >> z1
            >> c >> c >> z2
          ) {
        data.push_back ( Box{ x1, y1, z1, x2 + 1, y2 + 1, z2 + 1, on[1] == 'n'} );
    }

    return data;
}


//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0ull;
    std::unordered_map<uint64_t, bool> map;
    auto data = load ( "../testinput" );

    for ( auto p : data ) {
        if ( p.x1 >= -50 && p.y1 >= -50 && p.z1 >= -50 &&
                p.x2 <= 51 && p.y2 <= 51 && p.z2 <= 51 ) {
            for ( auto x : Range ( p.x1, p.x2 ) ) {
                for ( auto y : Range ( p.y1, p.y2 ) ) {
                    for ( auto z : Range ( p.z1, p.z2 ) ) {
                        auto key =  ( uint64_t ( x ) << 40 ) ^ ( uint64_t ( y ) << 20 )  ^ uint64_t ( z );
                        if ( p.is_on ) map[ key] = 1;
                        else map.erase ( key );
                    }
                }
            }

        }
    }

    ans = map.size();

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
#define I(a,b,U) (( a.U ## 1 < b.U ## 2 ) && ( a.U ## 2 > b.U ## 1 ))
#define Ix(a,b) I(a,b,x)
#define Iy(a,b) I(a,b,y)
#define Iz(a,b) I(a,b,z)

//---------------------------------------------------------------------------//
bool intersect ( const Box& a, const Box& b ) {
    return Ix ( a, b ) && Iy ( a, b ) && Iz ( a, b );
}

//---------------------------------------------------------------------------//
std::optional<Box> intersection ( const Box& a, const Box& b ) {
    if ( intersect ( a, b ) ) {
        auto x1 = std::max ( a.x1, b.x1 );
        auto x2 = std::min ( a.x2, b.x2 );
        auto y1 = std::max ( a.y1, b.y1 );
        auto y2 = std::min ( a.y2, b.y2 );
        auto z1 = std::max ( a.z1, b.z1 );
        auto z2 = std::min ( a.z2, b.z2 );

        return Box{ x1, y1, z1, x2, y2, z2 };
    }
    return std::nullopt;
}

//---------------------------------------------------------------------------//
int64_t volume (  std::vector<Box>::iterator it, std::vector<Box>::iterator end ) {
    const Box& b = *it;
    int64_t v = b.volume();
    std::vector<Box> l;

    for ( it++; it != end ; it++ ) {
        if ( auto ib = intersection ( b, *it ) ) {
            l.push_back ( ib.value() );
        }
    }

    for ( auto it = l.begin(), end = l.end(); it != end; it++ ) {
        v -= volume ( it, end );
    }

    return v;
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ll;
    auto data = load ( "../input" );

    for ( auto it = data.begin(), end = data.end(); it != end; it++ ) {
        if ( it->is_on ) {
            ans += volume ( it, end );
        }
    }

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
