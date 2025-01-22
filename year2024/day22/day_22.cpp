#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//----------------------------------------------------------------------------//
std::istringstream testinput {
R"(1
10
100
2024
)"};

//----------------------------------------------------------------------------//
std::istringstream testinput2 {
R"(1
2
3
2024)"
};

//----------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    ::std::vector<uint64_t> data;
    while ( !fs.eof() ) {
        ::std::string line;
        ::std::getline ( fs, line );
        if ( !line.empty ( ) )
            data.push_back ( stoi(line) );
    }
    return data;
}

uint64_t step ( uint64_t& s ) {
    auto mix_and_prune = [&s]( uint64_t v ) { s = (s^v)&0xffffff; };
    mix_and_prune ( s * 64 );
    mix_and_prune ( s / 32);
    mix_and_prune ( s * 2048 );
    return s;
}

//---------------------------------------------------------------------------//
uint64_t calc ( uint64_t seed, uint nth ) {
    uint64_t s = seed;
    auto mix_and_prune = [&s]( uint64_t v ) { s = (s^v)&0xffffff; };
    while ( nth-- ) {
        step ( s );
    }
    return s;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto data = load ( ::aoc::is_test_enabled()?testinput:puzzle_input );

    for ( const auto& v : data )
        ans += calc ( v, 2000 );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
::std::unordered_map<int,char> calc2 ( uint64_t seed ) {
    ::std::unordered_map<int,char> m;
    uint64_t s = seed;
    uint64_t s0 = seed % 10;
    int nth = 2000;
    int seq = 0;
    //std::cout << "Seed: " << seed << '\n';

    while ( nth-- ) {
        step ( s );
        auto s1 = s % 10;
        uint8_t d = s1 - s0;
        seq <<= 8;
        seq |= d;
        if ( nth<2000-4 ) {
            if ( !m.contains(seq) ) {
                m[seq] += s1;
            }
        }
        //std::cout << ' ' << s << ' ' << (int)(int8_t)d << '\n';
        s0 = s1;
    }
    return m;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans=0;

    //aoc::test_enable();

    auto data = load ( ::aoc::is_test_enabled() ? testinput2 : puzzle_input );

    ::std::unordered_map<int, int> sum;
    for ( const auto& seed : data )
        for ( const auto& v : calc2 ( seed ) )
            ans = ::std::max( ans, sum[v.first] += v.second );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
