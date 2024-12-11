#include "day"
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(125 17
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    ::std::vector<size_t> ret;
    size_t v;
    while ( file >> v )
        ret.push_back ( v );

    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );

    int i=0;
    std::vector<size_t> new_data;
    while ( i++ < 25 ) {
        for ( auto v : data ) {
            if ( v==0 ) {
                new_data.push_back ( 1 );
            } else if ( auto l=(int)std::log10(v); l&1 ) {
                auto d = (size_t)pow(10,(l+1)/2);
                new_data.push_back ( v / d );
                new_data.push_back ( v % d );
            } else {
                new_data.push_back ( v * 2024 );
            }
        }

        data = new_data;
        new_data.clear();
    }

    ans = data.size();

    OUT ( ans );
}

size_t go ( size_t v, int level=0 ) {
    static std::map<std::string,size_t> map;
    if ( level == 75 ) {
        return 1;
    }
    std::string k = std::to_string(level)+':'+std::to_string(v);
    if ( map.contains(k) ) {
        return map[k];
    }

    size_t r=0;
    if ( v==0 ) {
        r = go ( 1, level+1 );
    } else if ( auto l=((int)log10(v)); l&1 ) {
        auto d = (size_t)pow(10,(l+1)/2);
        r = go ( v / d, level+1 );
        r += go ( v % d, level+1 );
    } else {
        r = go ( v * 2024, level+1 );
    }

    map[k] = r;
    return r;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    for ( auto v : data )
        ans += go ( v );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
