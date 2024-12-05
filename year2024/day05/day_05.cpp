#include "day"
#include <functional>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

struct Rules{
    int a,b;
};


bool match_rules ( const std::vector<Rules>& rules, int a, int b ) {
    for ( auto& rule : rules ) {
        if ( rule.a==a && rule.b==b ) {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------//
std::vector<Rules> load_rules ( std::istream& file ) {
    std::vector<Rules> rules;
    while ( true ) {
        std::string line;
        std::getline ( file, line );
        if( line.empty() ) break;
        std::istringstream ls { line };
        char c;
        int a, b;
        ls >> a >> c >> b;
        rules.push_back ( { a, b } );
    }
    return rules;
}

//---------------------------------------------------------------------------//
std::vector<std::vector<int>> load_updates ( std::istream& file ) {
    std::vector<std::vector<int>> updates;
    std::string line;
    while(std::getline ( file, line )){
        updates.push_back ( std::vector<int>{} );
        std::istringstream ls{line};
        while ( !ls.eof() ) {
            char c;
            int v;
            ls >> v >> c;
            updates.back().push_back( v );
        }
    }
    return updates;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto rules = load_rules( file );
    auto updates = load_updates( file );

    for ( auto& u : updates ) {
        auto match = false;
        for ( uint i=1; i<u.size(); i++ ) {
            for ( uint j=0; j<i; j++ ) {
                match|= match_rules ( rules, u[i], u[j] );
            }
        }
        if ( !match ) {
            ans += u[u.size()/2];
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans=0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto rules = load_rules( file );
    auto updates = load_updates( file );
    for ( auto& u : updates ) {
        auto match = false;
        for ( uint i=1; i<u.size(); i++ ) {
            for ( uint j=0; j<i; j++ ) {
                if ( match_rules ( rules, u[i], u[j] ) ) {
                    std::swap ( u[i], u[j] );
                    match = true;
                }
            }
        }
        if ( match ) {
            ans += u[u.size()/2];
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
