//---------------------------------------------------------------------------//
#include <string>
#include <iostream>
#include <sstream>
//#include <map>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <fstream>
//#include <limits>
//#include <set>
//#include <iomanip>
//#include <bit>
//#include <math.h>
//#include <numeric>
//#include <algorithm>
//#include <queue>
#include "fmt/core.h"
//#include "fmt/ranges.h"

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_24 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T b ) {
    return Range ( T ( 0 ), b );
}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::ifstream fs ( file );
    std::string line;
    std::vector<std::string> data;
    auto&& is = file.starts_with ( "../test" )
            ? ( std::istream&& ) std::stringstream {
                //R"(inp x
                //     mul x -1)"
                R"(
                inp z
                inp x
                mul z 3
                eql z x
                )"
            }
            :( std::istream&& ) std::ifstream ( file );

    while ( is.good() ) {
        std::getline ( is, line );
        while ( std::isspace ( line[0] ) ) line.erase ( 0, 1 );
        if ( !line.empty() ) {
            data.push_back ( line );
        }
    }

    return data;
}

struct S{
    int i1;
    int i2;
    int v;
};

//---------------------------------------------------------------------------//
std::vector<S> analize ( std::vector<std::string> data ) {
    int i=0,j=-1,a,b;
    bool open=false;
    std::vector<S> stack;
    std::vector<S> pairs;

    //while ( end!=std::string::npos ) {
    for ( auto& s : data ) {
        //std::cout << s;

        if ( s=="inp w") {
            //std::cout << s << '\n';
            i=0;
            j++;
        } else
            if ( i==4) { // div 1/26
                //std::cout << s << '\n';
                open = s[6]=='1';
            } else
                if ( i==5) { // add x 2
                    a = stoi(s.substr(6));
                    //std::cout << s << " a="<< a <<'\n';
                } else
                    if ( i==15) {// add y 2
                        b = stoi(s.substr(6));
                        //std::cout << s <<" b="<< b << '\n';
                        if ( open ) {
                            //std::cout << "b="<< b << '\n';
                            S ss{j,0,b};
                            stack.push_back( ss );
                        } else {
                            //std::cout << "a="<< a << '\n';
                            auto ss = stack.back( );
                            stack.pop_back();
                            pairs.push_back({ss.i1,j,ss.v+a});
                        }
                    }
        i++;
    }
    return pairs;
}
//---------------------------------------------------------------------------//
constexpr uint64_t OP ( const char* s ) {
    return s[3] << 24 | s[2] << 16 | s[1] << 8 | s[0];
};

//---------------------------------------------------------------------------//
std::unordered_map<char, int64_t> cpu;
std::string in_string{};

//---------------------------------------------------------------------------//
inline char get_reg ( std::string& l ) {
    return l[4];
}

//---------------------------------------------------------------------------//
inline int64_t get_val ( std::string& l ) {
    try {
        return std::stoi ( l.substr ( 6 ) );
    } catch ( std::invalid_argument ) {
        return cpu[l[6]];
    } catch ( std::out_of_range ) {

    }
    return 0;
}

//---------------------------------------------------------------------------//
auto check ( std::vector<std::string>& data, int64_t val ) {
    int i = 0;
    in_string = std::to_string ( val );
    while ( in_string.size() != 14 ) in_string = '0' + in_string;
    cpu.clear();
    for ( auto & l : data ) {
        auto a = get_reg ( l );
        auto b = get_val ( l );
        switch ( OP ( l.data() ) ) {
        case OP ( "inp " ) :
            cpu[a] = in_string [i++] - '0';
            //fmt::print ( "x:{} y:{} z:{} w:{}\n", cpu['x'], cpu['y'], cpu['z'], cpu['w'] );
            //fmt::print ( "{}\n", cpu[a] );
            break;
        case OP ( "add " ) :
            cpu[a] += b;
            break;
        case OP ( "mul " ) :
            cpu[a] *= b;
            break;
        case OP ( "div " ) :
            cpu[a] /= b;
            break;
        case OP ( "mod " ) :
            cpu[a] %= b;
            break;
        case OP ( "eql " ) :
            cpu[a] = cpu[a] == b;
            break;
        default:
            fmt::print ( "Error\n" );
        }
    }
    return cpu['z'];
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto data = load ( "../input" );
    auto pairs = analize( data );
// aȧ bḃ cċ dḋ eė fḟ gġ
    // MONAD:
    // +++-+-+++-----
    // abcċdḋefgġḟėḃȧ
    //  a - 6 = ȧ
    //  b - 2 = ḃ
    //  c + 7 = ċ
    //  ċ - 7 = c
    //  d + 1 = ḋ
    //  ḋ - 1 = d
    //  e - 1 = ė
    //  f + 6 = ḟ
    //  g + 8 = ġ
    //  ġ - 8 = ġ
    /*fmt::print ( "{} {}\n", in_string, check ( data, 99'298'993'199'873 ) ); // highest
    fmt::print ( "{} {}\n", in_string, check ( data, 88'295'693'199'862 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 79'295'693'199'871 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 78'295'693'199'861 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 77'295'693'199'851 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 76'295'693'199'841 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 75'295'693'199'831 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 17'295'693'199'851 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 11'295'693'199'851 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 11'295'623'199'951 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 11'295'619'199'951 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 11'295'619'199'991 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 13'295'611'199'991 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 13'295'611'999'991 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 11'225'678'987'654 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 12'345'678'999'999 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 99'999'999'999'995 ) );
    fmt::print ( "{} {}\n", in_string, check ( data, 99'999'999'999'999 ) );*/

    std::string max{"              "};
    for ( auto& p : pairs ) {
        max[p.i1] = '9';
        max[p.i2] = '9';
        if ( p.v < 0 ) {
            max[p.i2] += p.v;
        } else {
            max[p.i1] -= p.v;
        }
    }
    auto ans = max;

    //fmt::print ( "{}\n", check ( data, 99'298'993'199'873) );

    fmt::print ( "{}: {}\n", __FUNCTION__, ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto data = load ( "../input" );
    auto pairs = analize ( data );

    // 73181221197111
    // abcċdḋefgġḟėḃȧ
    // a - 6 = ȧ
    // b - 2 = ḃ
    // c + 7 = ċ
    // d + 1 = ḋ
    // e - 1 = ė
    // f + 6 = ḟ
    // g + 8 = ġ
    // fmt::print ( "{} {}\n", in_string, check ( data, 73'181'221'197'111 ) );
    //ans = 73'181'221'197'111;
    std::string min{"              "};
    for ( auto& p : pairs ) {
        min[p.i1] = '1';
        min[p.i2] = '1';
        if ( p.v < 0 ) {
            min[p.i1] -= p.v;
        } else {
            min[p.i2] += p.v;
        }
    }

    auto ans = min;

    fmt::print ( "{}: {}\n", __FUNCTION__, ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
