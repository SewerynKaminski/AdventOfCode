#include "day"
#include <functional>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8)" );

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto ignore ( int i ) {
    return [i] ( std::istream & o )->std::istream& {
        return o.ignore ( i, '\0' );
    };
}

//---------------------------------------------------------------------------//
std::istream& operator >> ( std::istream& o, std::function< std::istream& ( std::istream& ) > f ) {
    return f ( o );
}

struct Section {
    int start, end;
};

//---------------------------------------------------------------------------//
auto& operator >> ( std::istream & o, Section & s ) {
    return ( ( o.peek() == '\n' ) ? o >> ignore ( 1 ) : o ) >> s.start >> ignore ( 1 ) >> s.end;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto fully_contains = [] ( const Section & s1, const Section & s2 ) {
        return s1.start <= s2.start && s2.end <= s1.end;
    };

    Section s1, s2;
    while ( file >> s1 >> ignore ( 1 ) >> s2 ) {
        if ( fully_contains ( s1, s2 ) || fully_contains ( s2, s1 ) ) {
            ans++;
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto overlap = [] ( const Section & s1, const Section & s2 ) {
        return s1.start <= s2.end && s1.end >= s2.start;
    };

    Section s1, s2;
    while ( file >> s1 >> ignore ( 1 ) >> s2 ) {
        if ( overlap ( s1, s2 ) || overlap ( s2, s1 ) ) {
            ans++;
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
