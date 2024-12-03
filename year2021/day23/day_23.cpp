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
//#include <set>
//#include <iomanip>
//#include <bit>
//#include <math.h>
//#include <numeric>
//#include <algorithm>
//#include <queue>

#include "day"
//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    //std::ifstream fs ( file );
    std::string line;
    uint64_t data = 0;
//     auto&& is = file.starts_with ( "../test" )
//     ? ( std::istream&& ) std::istringstream{
//         "#############\n"
//         "#...........#\n"
//         "###B#C#B#D###\n"
//         "  #A#D#C#A#\n"
//         "  #########\n"}
// :
//     ( std::istream&& ) std::ifstream ( file );

    for ( fs >> line >> line; auto i : Range ( 2 ) ) {
        (void)i;
        for ( fs >> line; auto c : line )
            ( c != '#' ) && ( data = ( data << 3 ) | uint64_t ( c - 'A' + 1 ) );
    }

    return data;
}

template<int a, int b>
constexpr uint64_t get ( uint64_t board ) {
    return ( board >> ( 9 - a * 3 + 12 * ( 1 - b ) ) ) & 7;
}

template<int b>
constexpr uint64_t get ( int a, uint64_t board ) {
    return ( board >> ( 9 - a * 3 + 12 * ( 1 - b ) ) ) & 7;
}

template<int b>
constexpr void set ( uint64_t& board, uint64_t a ) {
    board |= ( a + 1 ) << ( 9 - a * 3 + 12 * ( 1 - b ) );
}

template<int a>
constexpr uint64_t hdr ( uint64_t board ) {
    return ( board >> ( 24 + 3 * a ) ) & 7;
}

uint64_t hdr ( int a, uint64_t board ) {
    return ( board >> ( 24 + 3 * a ) ) & 7;
}

template<int a, int b>
constexpr uint64_t mask ( uint64_t board ) {
    return board & ~ ( 7ull << ( 9 - a * 3 + 12 * ( 1 - b ) ) );
}

template<int a, int b>
constexpr uint64_t move ( int c, uint64_t board ) {
    return mask<a, b> ( board ) | ( get<a, b> ( board ) << ( 24 + ( 6 - c ) * 3 ) );
}


void go ( uint64_t board );


int line ( int a, int b, uint64_t board ) {
    int n = std::min ( a, b ), m = std::max ( a, b );
    int i = 0, q = 0;
    if ( i >= n && i <= m ) q += hdr<6> ( board );
    i++;
    if ( i >= n && i <= m ) q += hdr<5> ( board );
    i++;
    if ( i >= n && i <= m ) q += hdr<4> ( board );
    i++;
    if ( i >= n && i <= m ) q += hdr<3> ( board );
    i++;
    if ( i >= n && i <= m ) q += hdr<2> ( board );
    i++;
    if ( i >= n && i <= m ) q += hdr<1> ( board );
    i++;
    if ( i >= n && i <= m ) q += hdr<0> ( board );
    i++;
    return q;
}

template<int a>
inline void call ( uint64_t board ) {
    for ( auto i : Range ( a + 2 ) ) {
        auto h = line ( 1 + a, i, board ); // w lewo
        if ( !h ) {
            if ( get<a, 0> ( board ) != 0 ) {
                go ( move<a, 0> ( i, board ) );
            } else if ( get<a, 1> ( board ) != 0 && get<a, 1> ( board ) != a + 1 ) {
                go ( move<a, 1> ( i, board ) );
            }
        }
    }
    for ( auto i : Range ( 2 + a, 7 ) ) {
        auto h = line ( 2 + a, i, board ); // w prawo
        if ( !h ) {
            if ( get<a, 0> ( board ) != 0 ) {
                go ( move<a, 0> ( i, board ) );
            } else if ( get<a, 1> ( board ) != 0 && get<a, 1> ( board ) != a + 1 ) {
                go ( move<a, 1> ( i, board ) );
            }
        }
    }
}

void show ( uint64_t board ) {
    std::cout << '\n';
    std::cout << hdr<6> ( board ) << hdr<5> ( board ) << ' ' << hdr<4> ( board ) << ' ' << hdr<3> ( board ) << ' ' << hdr<2> ( board ) << ' ' << hdr<1> ( board ) << hdr<0> ( board ) << '\n';
    std::cout << "  " << get<0, 0> ( board ) << ' ' << get<1, 0> ( board ) << ' ' << get<2, 0> ( board ) << ' ' << get<3, 0> ( board ) << '\n'
              << "  " << get<0, 1> ( board ) << ' ' << get<1, 1> ( board ) << ' ' << get<2, 1> ( board ) << ' ' << get<3, 1> ( board ) << '\n';
}

void movedown ( uint64_t& board ) {
    uint64_t v;
    auto lin = [board] ( int v, int a, int b ) {
        int s = 0;
        for ( auto i : Range ( a - ( v - 1 ), b ) ) {
            s += hdr ( i,  board );
        }
        return !s;
    };
    v = hdr<6> ( board );
    if ( v && lin ( v, 5, 6 ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 6 ) );
    } else if ( v && lin ( v, 5, 6 ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 6 ) );
    }
    v = hdr<5> ( board );
    if ( v && lin ( v, 5, 5 ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 5 ) );
    } else if ( v && lin ( v, 5, 5 ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 5 ) );
    }
    v = hdr<4> ( board );
    if ( v && lin ( v, 4, 4 ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 4 ) );
    } else if ( v && lin ( v, 4, 4 ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 4 ) );
    }
    v = hdr<3> ( board );
    if ( v && lin ( v, 3, 3 ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 3 ) );
    } else if ( v && lin ( v, 3, 3 ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 3 ) );
    }
    v = hdr<2> ( board );
    if ( v && lin ( v, 2, 2 ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 2 ) );
    } else if ( v && line ( 5, v, board ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 2 ) );
    }
    v = hdr<1> ( board );
    if ( v && line ( 5, v, board ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 1 ) );
    } else if ( v && line ( 5, v, board ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 1 ) );
    }
    v = hdr<0> ( board );
    if ( v && line ( 5, v, board ) && !get<0> ( v - 1, board ) && !get<1> ( v - 1, board ) ) {
        set<1> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 0 ) );
    } else if ( v && line ( 5, v, board ) && !get<1> ( v - 1, board ) && get<1> ( v - 1, board ) == v ) {
        set<0> ( board, v - 1 );
        board &= ~ ( 7ull << ( 24 + 3 * 0 ) );
    }

}

void go ( uint64_t board ) {
    movedown ( board );
    show ( board );
    //std::string line;
    //std::cin >> line;
    getchar();


    call<0> ( board );
    call<1> ( board );
    call<2> ( board );
    call<3> ( board );

}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    auto data = load ( puzzle_input
                       //"../testinput"
                     );

    go ( data );

    std::cout << std::hex << data;

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ll;
    auto data = load ( puzzle_input
                       //"../testinput"
                     );

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
