#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//----------------------------------------------------------------------------//
std::istringstream testinput{
R"(r, wr, b, g, bwu, rb, gb, br

brwrr
bggr
gbbr
rrbgbr
ubwu
bwurrg
brgr
bbrgwb
)"};

//----------------------------------------------------------------------------//
auto load( std::istream& file ) {
    std::vector<std::string> data;
    while ( !file.eof() ) {
        std::string line;
        std::getline ( file, line );
        if( !line.empty ( ) )
            data.push_back ( line );
    }
    return data;
}

//----------------------------------------------------------------------------//
auto load_patterns( std::vector<std::string>& data ) {
    std::istringstream is{data[0]};
    std::vector<std::string> patterns;
    while ( !is.eof() ) {
        std::string str;
        is >> str;
        if ( str.back()==',' ) str.resize( str.size() - 1 );
        patterns.push_back ( str );
    }
    return patterns;
}

//----------------------------------------------------------------------------//
bool search ( const std::vector<std::string>& patterns, const std::string_view& sv, uint i=0 ) {
    static std::unordered_set<std::string> h;
    if ( !i ) h.clear();
    if ( i >= sv.size() ) return true;
    auto key = (std::string)sv.substr(0,i);
    if ( h.contains ( key ) ) return false;

    for ( auto& p : patterns ) {
        auto s = sv.substr ( i, p.size() );
        if ( p == s )
            if ( search ( patterns, sv, i+p.size() ) )
                return true;
    }

    h.insert(key);
    return false;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled()?testinput:puzzle_input;
    auto data = load ( file );
    auto patterns = load_patterns( data );

    for ( const auto& s : data | std::views::drop(1) ) {
        ans += search ( patterns, s );
    }

    OUT ( ans );
}

//----------------------------------------------------------------------------//
uint64_t search2 ( const std::vector<std::string>& patterns, const std::string_view& sv, uint i=0 ) {
    static std::unordered_map<std::string, uint64_t> h;
    uint64_t ret=0;
    if ( !i ) h.clear();

    if ( i >= sv.size() ) return 1;
    auto key = (std::string)sv.substr(0,i);
    if ( h.contains ( key ) ) return h[key];

    for ( const auto& p : patterns )
        if ( p == sv.substr ( i, p.size() ) )
            ret += search2 ( patterns, sv, i+p.size() );

    h[key] = ret;
    return ret;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    uint64_t ans;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled()?testinput:puzzle_input;
    auto data = load ( file );
    auto patterns = load_patterns( data );

    for ( const auto& s : data | std::views::drop(1) ) {
        ans += search2 ( patterns, s );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
