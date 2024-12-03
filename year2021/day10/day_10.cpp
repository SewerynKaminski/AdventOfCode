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
//#include <algorithm>
#include <optional>
#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// template<class T>
// constexpr auto Range ( T a, T b ) {
//     return std::views::iota ( a, b );
// }

//---------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    //std::fstream fs ( file );
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
std::optional<uint> check ( std::string& s, uint& i ) {
    if ( i >= s.size() ) { return std::nullopt; }
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
void Task_1( std::istream& puzzle_input ) {
    auto ans = 0ul;

    auto data = load ( puzzle_input );

    for ( auto& l : data ) {
        uint result = 0;
        uint i = 0;

        result = check ( l, i ).value_or(0);

        ans += 3 * ( ')' == result ) +
               57 * ( ']' == result ) +
               1197 * ( '}' == result ) +
               25137 * ( '>' == result );
    }

    std::cout << __FUNCTION__  << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ul;
    std::vector<uint64_t> scores;
    auto data = load ( puzzle_input );
    for ( auto l : data ) {
        uint i = 0;
        if ( !check ( l, i ) ) {
            for ( int j = 0; j < 2 * ( int ) l.size(); j++ )
                for ( i = 0; i < l.size(); i++ ) {
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
