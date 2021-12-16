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
#include "day_16.h"

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_16 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
std::string convert ( std::string line ) {
    auto data = std::string ( 1 + line.size() / 2, ' ' );
    for ( auto i = 0u; i < line.size(); i += 2 ) {
        data[i / 2] = std::stoi ( line.substr ( i, 2 ), nullptr, 16 );
    }
    return data;
}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::string data;

    std::string line;
    fs >> line;

    return convert ( line );
}

//---------------------------------------------------------------------------//
namespace BitStream {

inline uint32_t Read ( unsigned offset, unsigned count, const uint8_t *src ) {
    const uint8_t *cur_src = src + offset / 8;
    unsigned bits_left = offset % 8;
    uint32_t cur_data = 0;

    cur_data |= uint32_t ( * ( cur_src + 0 ) ) << 24;
    cur_data |= uint32_t ( * ( cur_src + 1 ) ) << 16;
    cur_data |= uint32_t ( * ( cur_src + 2 ) ) << 8;
    cur_data |= uint32_t ( * ( cur_src + 3 ) ) << 0;
    cur_data <<= bits_left;

    return cur_data >> ( 32 - count );
}

}

//---------------------------------------------------------------------------//
unsigned read_packet ( std::string data ) {
    static unsigned ofs = 0;
    int sum = 0;
    auto Read = [&] ( unsigned l ) {
        auto v = BitStream::Read ( ofs, l, ( uint8_t* ) data.data() );
        ofs += l;
        return v;
    };
    // Header
    sum += Read ( 3 );      //  Version
    auto id = Read ( 3 );   //  ID

    if ( id == 4 ) { // literal value
        bool last;
        uint32_t val = 0;
        do {
            last = Read ( 1 );
            val = val << 4 | Read ( 4 );
        } while ( last );
    } else {            // operation
        auto ii = Read ( 1 );
        if ( ii == 0 ) {
            auto end_of_bits = ofs + Read ( 15 );
            do {
                sum += read_packet ( data );
            } while ( end_of_bits - ofs );
        } else {
            auto count_packets = Read ( 11 );
            while ( count_packets-- ) {
                sum += read_packet ( data );
            }
        }
    }
    return sum;
}

//---------------------------------------------------------------------------//
uint64_t calculate_packet ( std::string data ) {
    static unsigned ofs = 0;
    uint64_t sum = 0ull;
    auto Read = [&] ( unsigned l ) {
        auto v = BitStream::Read ( ofs, l, ( uint8_t* ) data.data() );
        ofs += l;
        return v;
    };

    auto Values = [&] {
        std::vector<uint64_t> tab;
        auto ii = Read ( 1 );
        if ( ii == 0 ) {
            auto end_of_bits = ofs + Read ( 15 );
            do {
                tab.push_back ( calculate_packet ( data ) );
            } while ( end_of_bits - ofs );
        } else {
            auto count_packets = Read ( 11 );
            while ( count_packets-- ) {
                tab.push_back ( calculate_packet ( data ) );
            }
        }
        return tab;
    };

    // Header
    Read ( 3 );      //  Version
    auto id = Read ( 3 );   //  ID

    switch ( id ) {
    case 0:
        for ( auto v : Values() ) sum += v;
        break;
    case 1:
        sum = 1;
        for ( auto v : Values() ) sum *= v;
        break;
    case 2:
        sum = std::numeric_limits<typeof ( sum ) >::max();
        for ( auto v : Values() ) sum = std::min ( v, sum );
        break;
    case 3:
        sum = std::numeric_limits<typeof ( sum ) >::min();
        for ( auto v : Values() ) sum = std::max ( v, sum );
        break;
    case 4: { // literal value
        bool last;
        do {
            last = Read ( 1 );
            sum = sum << 4 | Read ( 4 );
        } while ( last );
    }
    break;
    case 5: {
        auto v = Values();
        sum = v[0] > v[1];
    }
    break;
    case 6: {
        auto v = Values();
        sum = v[0] < v[1];
    }
    break;
    case 7: {
        auto v = Values();
        sum = v[0] == v[1];
    }
    break;
    }
    return sum;
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0ull;
    auto data = load ( "../input" );

    // Examples
    /*data = convert(
                    //"D2FE28"
                    //"EE00D40C823060"
                    "8A004A801A8002F478"
                    );
    */

    ans = read_packet ( data );

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ull;
    auto data = load ( "../input" );

    /*data = convert(
                //"C200B40A82"
                //"04005AC33890"
                //"880086C3E88112"
                //"CE00C43D881120"
                //"D8005AC2A8F0"
                //"F600BC2D8F"
                //"9C005AC2F8F0"
                "9C0141080250320F1802104A08"
                 );*/

    ans = calculate_packet ( data );

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
