#include <day>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

std::istringstream test_input{
R"(abcdef
bababc
abbcde
abcccd
aabcdd
abcdee
ababab)"};

//---------------------------------------------------------------------------//
::std::vector<std::string> load ( ::std::istream& file ) {
    ::std::vector<std::string> ret;
    while( !file.eof() ){
        std::string line;
        std::getline ( file, line );
        ret.push_back ( line );
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;
    auto data = load ( file );

    auto ans = 0ull;
    int t=0,d=0;
    for ( auto& line : data ) {
        std::unordered_map<char,int> tab;
        //std::cout << line;
        bool y2=false, y3=false;
        for ( auto c : line ) {
            tab[c]++;
        }
        for ( auto cnt: tab ) {
            y2 |= cnt.second == 2;
            y3 |= cnt.second == 3;
        }
        if ( y2 ) d++;
        if ( y3 ) t++;
    }
    ans = d*t;

    OUT(ans);
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = std::string{};
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;
    auto data = load( file );

    for ( uint i=0; i < data.size(); i++ ) {
        for ( uint j=i+1; j < data.size(); j++ ) {
            auto& s1 = data[i];
            auto& s2 = data[j];
            int d=0,diff_idx=0;
            for ( uint k=0; k<s1.size(); k++ ) {
                if ( s1[k]!=s2[k] ) {
                    d++;
                    if ( d==1 ) {
                        diff_idx=k;
                    }
                }
            }
            if ( d == 1 ) {
                //std::cout << diff_idx << s1 <<' '<< s2;
                ans = s1;
                ans.erase( diff_idx, 1 );
            }
        }
    }

    OUT(ans);
}
//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
