#include "day"
#include <ranges>
#include <iomanip>
#include <unordered_set>
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(1=-0-2
12111
2=0=
21
2=01
111
20012
112
1=-1=
1-12
12
1=
122)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
int64_t to_dec ( std::string str ) {
    auto value = 0ll;
    for( auto c : str ) {
        value *= 5;
        switch ( c ) {
            case '=': value-=2; break;
            case '-': value-=1; break;
            case '0': value+=0; break;
            case '1': value+=1; break;
            case '2': value+=2; break;
        }
    }
    return value;
}

//---------------------------------------------------------------------------//
std::string to_snafu ( int64_t value ) {
    std::string snafu;
    auto q = 1ll;

    while ( (value+q/2)/q > 2 ) {
        q *= 5;
    }

    while ( q ) {
        auto w = value;
        w += ( (w > 0) - (w < 0) ) * q/2;
        w /= q;

        if ( w == -2 ) snafu.append( "=" );
        else if ( w == -1 ) snafu.append( "-" );
        else snafu.append( std::to_string ( w ) );
        value -= q*w;
        q /= 5;
    }

    return snafu;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::string line;
    while ( getline( file, line ) ) {
        //std::cout << line << " " << to_dec(line) << " " << to_snafu(to_dec(line)) << '\n';
        ans += to_dec(line);
    }

    OUT ( to_snafu(ans) );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
