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

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_10 {

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
bool isopen ( char c ) {
    return c == '(' || c == '{' || c == '[' || c == '<';
}

//---------------------------------------------------------------------------//
bool isclose ( char c ) {
    return c == ')' || c == '}' || c == ']' || c == '>';
}

//---------------------------------------------------------------------------//
int check ( std::string& s, int& i ) {
    if ( i >= s.size() ) return -1;
    while ( i < s.size() ) {
        switch ( s[i] ) {
        case '(': {
            auto r = check ( s, ++i );
            if ( r == 0 && isclose ( s[i] ) ) {
                if ( s[i] == ')' ) {
                    i++;
                    return check ( s, i );
                }
                return s[i];
            }
            return r;
        }
        case '[': {
            auto r = check ( s, ++i );
            if ( r == 0 && isclose ( s[i] ) ) {
                if ( s[i] == ']' ) {
                    i++;
                    return check ( s, i );
                }
                return s[i];
            }
            return r;
        }
        case '{': {
            auto r = check ( s, ++i );
            if ( r == 0 && isclose ( s[i] ) ) {
                if ( s[i] == '}' ) {
                    i++;
                    return check ( s, i );
                }
                return s[i];
            }
            return r;
        }
        case '<': {
            auto r = check ( s, ++i );
            if ( r == 0 && isclose ( s[i] ) ) {
                if ( s[i] == '>' ) {
                    i++;
                    return check ( s, i );
                }
                return s[i];
            }
            return r;
        }
        default:
            return 0;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------//
void Task_1() {
    auto ans = 0;

    auto data = load ( "../input" );

    for ( auto& l : data ) {
        int result = 0;
        int i = 0;
        result = check ( l, i );

        ans += 3 * ( ')' == result ) +
               57 * ( ']' == result ) +
               1197 * ( '}' == result ) +
               25137 * ( '>' == result );
    }

    std::cout << __FUNCTION__  << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
void Task_2() {
    auto ans = 0ul;
    std::vector<uint64_t> scores;
    auto data = load ( "../input" );
    for ( auto l : data ) {
        int i = 0;
        if ( -1 == check ( l, i ) ) {
            for ( int j = 0; j < 2 * ( int ) l.size(); j++ )
                for ( i = 0; i < ( int ) l.size(); i++ ) {
                    if ( ( l[i] == '(' && l[i + 1] == ')' ) ||
                            ( l[i] == '{' && l[i + 1] == '}' ) ||
                            ( l[i] == '[' && l[i + 1] == ']' ) ||
                            ( l[i] == '<' && l[i + 1] == '>' ) ) {
                        l.replace ( i, 2, "" );
                    }
                }
            auto score = 0ul;
            for ( auto c = l.rbegin(); c != l.rend(); c++  ) {
                score = score * 5
                        + 1 * ( *c == '(' )
                        + 2 * ( *c == '[' )
                        + 3 * ( *c == '{' )
                        + 4 * ( *c == '<' );
            }
            scores.push_back ( score );
        }
    }

    std::sort ( scores.begin(), scores.end() );
    ans = scores[ scores.size() / 2 ];

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
