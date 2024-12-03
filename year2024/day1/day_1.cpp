#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(1000 10)" );

inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    std::vector<int> left;
    std::vector<int> right;

    auto l=0;
    while ( getline ( file, line ) ) {
        //sum = line.empty() ? ( ans = std::max ( ans, sum ), 0 ) : sum + stoull ( line );
        l++;
        auto i = line.find_first_of(' ');
        auto s1 = line.substr(0,i);

        //std::cout << l << ". " << i << ' ' << line << '\n';
        i = line.find_first_not_of(' ',i);
        auto s2 = line.substr(i);
        //std::cout << l << ". " << s1 << " "<< s2<< '\n';

        left.push_back( std::stoi ( s1 ) );
        right.push_back( std::stoi ( s2 ) );
    }

    std::ranges::zip_view( left, right);

    std::ranges::sort ( left, std::ranges::greater() );
    std::ranges::sort ( right, std::ranges::greater() );

    for ( uint i=0; i< left.size();i++) {
        ans += abs ( left[i] - right[i] );
    }

    // 2164381
    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    std::vector<int> left;
    std::map<int,int> right;

    while ( getline ( file, line ) ) {
        auto i = line.find_first_of(' ');
        auto s1 = line.substr(0,i);

        //std::cout << l << ". " << i << ' ' << line << '\n';
        i = line.find_first_not_of(' ',i);
        auto s2 = line.substr(i);
        //std::cout << l << ". " << s1 << " "<< s2<< '\n';

        left.push_back( std::stoi ( s1 ) );
        right[std::stoi ( s2 )]++;
    }
    for ( auto l : left) {
        ans += l*right[l];
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
