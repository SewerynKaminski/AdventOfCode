#include <day>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

std::istringstream test_input{
R"(+2
-1)"};

::std::vector<int> load ( ::std::istream& file ) {
    ::std::vector<int> ret;
    while( !file.eof() ){
        int v;
        file >> v;
        ret.push_back(v);
    }
    return ret;
}

void Task_1 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;
    auto data = load ( file );

    auto ans=0ull;
    for ( auto v : data ) {
        ans += v;
    }

    OUT(ans);
}

void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;
    auto data = load( file );

    std::unordered_set<int> d;

    auto i = 0;
    auto len = data.size();
    auto s = 0;
    do {
        d.insert ( s );
        s += data[i++%len];
    } while ( !d.contains ( s ) );

    ans = s;

    OUT(ans);
}
//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
