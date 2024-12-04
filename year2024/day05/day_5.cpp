#include "day"
#include <functional>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    "    [D]    \n"
    "[N] [C]    \n"
    "[Z] [M] [P]\n"
    " 1   2   3 \n"
    "\n"
    "move 1 from 2 to 1\n"
    "move 3 from 1 to 3\n"
    "move 2 from 2 to 1\n"
    "move 1 from 1 to 2\n" );

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

std::vector<std::list<char>> parseCrates ( std::istream& file ) {
    std::string line;
    std::vector<std::list<char>> stacks;
    while ( getline ( file, line ) ) {
        if ( line[1] == '1' ) break;
        int cols = ( line.length() + 1 ) / 4;
        stacks.resize ( cols );
        for ( int i = 0; i < cols; i++ ) {
            auto c = line[1 + i * 4];
            if ( c > ' ' ) {
                stacks[i].push_back ( c );
            }
        }
    }
    getline ( file, line );
    return stacks;
}

//---------------------------------------------------------------------------//
std::string top_of_each_stack ( std::vector<std::list<char>>& stacks ) {
    std::string ans;
    for ( auto& stack : stacks ) {
        ans.append ( &stack.front(), 1 );
    }
    return ans;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    std::string ans;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto stacks = parseCrates ( file );

    while ( getline ( file, line ) ) {
        std::stringstream ss ( line );
        std::string s;
        int len, from, to;
        ss >> s >> len >> s >> from >> s >> to;
        for ( int i = 0; i < len ; i++ ) {
            auto c = stacks[from - 1].front();
            stacks[from - 1].pop_front();
            stacks[to - 1].push_front ( c );
        }
    }

    ans = top_of_each_stack ( stacks );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    std::string ans;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto stacks = parseCrates ( file );
    while ( getline ( file, line ) ) {
        std::stringstream ss ( line );
        std::string s;
        int len, from, to;
        ss >> s >> len >> s >> from >> s >> to;

        auto it = stacks[to - 1].begin();
        for ( int i = 0; i < len ; i++ ) {
            auto c = stacks[from - 1].front();
            stacks[from - 1].pop_front();
            stacks[to - 1].insert ( it, c );
        }
    }

    ans = top_of_each_stack ( stacks );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
