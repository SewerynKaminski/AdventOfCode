#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//----------------------------------------------------------------------------//
std::istringstream testinput{
R"(#####
.####
.####
.####
.#.#.
.#...
.....

#####
##.##
.#.##
...##
...#.
...#.
.....

.....
#....
#....
#...#
#.#.#
#.###
#####

.....
.....
#.#..
###..
###.#
###.#
#####

.....
.....
.....
#....
#.#..
#.#.#
#####
)"};

//----------------------------------------------------------------------------//
::std::pair<::std::vector<::std::array<char,5>>,::std::vector<::std::array<char,5>>> load ( std::istream& fs ) {
    ::std::vector<::std::array<char,5>> locks;
    ::std::vector<::std::array<char,5>> keys;
    while ( !fs.eof() ) {
        ::std::string line;
        ::std::getline ( fs, line );
        auto is_lock = line[0]=='#';
        ::std::array<char,5> v{0};
        while ( !line.empty ( ) ) {
            for( uint i = 0; i < line.size(); i++ ) {
                v[i] += line[i]=='#';
            }
            ::std::getline ( fs, line );
        }
        if ( is_lock ) locks.push_back( v );
        else keys.push_back( v );
    }
    return {locks, keys};
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto [locks,keys] = load ( ::aoc::is_test_enabled()?testinput:puzzle_input );
    for ( const auto& lock : locks ) {
        for ( const auto& key : keys ) {
            ::std::array<char,5> sum{0};
            for ( int i=0; i < lock.size(); i++ ) {
                sum[i] = key[i] + lock[i];
                //std::cout << (int)sum[i] << ' ';
            }
            ans += ::std::all_of ( sum.cbegin(), sum.cend(), []( char v ) { return v<=7; } );
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    uint64_t ans=0;

    aoc::test_enable();

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
