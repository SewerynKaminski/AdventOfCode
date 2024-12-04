#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput[] {
    R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))",
    R"(xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5)))"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input(int i=1) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput[i-1] );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    char c;
    while ( !file.get(c).eof() ) {
        if ( c=='m' ) {
            int v1, v2;
            file.get(c); if(c!='u') continue;
            file.get(c); if(c!='l') continue;
            file.get(c); if(c!='(') continue;
            file >> v1;
            file.get(c); if(c!=',') continue;
            file >> v2;
            file.get(c); if(c!=')') continue;
            ans += v1*v2;
        }
    }
    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input(2) : puzzle_input;

    bool enable = true;
    char c;
    while ( !file.get(c).eof() ) {
        if ( c=='m' ) {
            int v1, v2;
            file.get(c); if(c!='u') continue;
            file.get(c); if(c!='l') continue;
            file.get(c); if(c!='(') continue;
            file >> v1;
            file.get(c); if(c!=',') continue;
            file >> v2;
            file.get(c); if(c!=')') continue;
            if ( enable ) {
                ans += v1*v2;
            }
        } else if ( c=='d' ) {
            file.get(c); if(c!='o') continue;
            file.get(c);
            if ( c=='n' ) {
                file.get(c); if(c!='\'') continue;
                file.get(c); if(c!='t') continue;
                file.get(c); if(c!='(') continue;
                file.get(c); if(c!=')') continue;
                enable = false;
            } else if ( c=='(' ) {
                file.get(c); if(c!=')') continue;
                enable = true;
            }
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
