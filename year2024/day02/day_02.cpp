#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput =
R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)";

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
bool calc ( std::stringstream& ss, int& a, int& b, int& d ) {
    a = b;
    ss >> b;
    d = a - b;
    bool s = d > 0;
    d = abs(d);
    return s;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    std::istream& file = is_test_enabled() ? test_input() : puzzle_input;

    int a,b,d;

    while ( getline ( file, line ) ) {
        bool sign,sign2;
        std::stringstream s{line};
        s >> b;

        sign = sign2 = calc ( s, a, b, d );
        while ( sign==sign2 && d>0 && d<4 ) {
            if ( s.eof() ) {
                ans++;
            }
            sign2 = calc ( s, a, b, d );
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
bool valid2 ( std::string s ) {
    std::istringstream is{s};
    std::vector<int> tab;
    int v;
    while ( !is.eof() ) {
        is >> v;
        tab.push_back(v);
    }
    int d;
    uint j;
    uint ia = 0, ib = 1;
    bool sign,sign2;

    auto calc = [&]() {
        if ( j==ia ) {ia++;ib++; return true;}
        if ( j==ib ) {ib++; return true;}
        d = tab[ia] - tab[ib];
        sign2 = d>0; d=abs(d);
        ib=++ia+1;
        return false;
    };

    for ( j=0; j<tab.size(); j++ ) {
        ia = 0, ib = 1;
        while(calc());
        sign = sign2;
        while ( sign==sign2 && d>0 && d<4 ) {
            if ( ib==tab.size() ) return true;
            calc();
        }
    }
    return false;
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    std::istream& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    while ( !file.eof() ) {
        std::string line;
        std::getline ( file, line );
        ans += valid2( line );
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
