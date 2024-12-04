#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {
//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010)" );

inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    std::vector<int> data{};
    std::string line;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto cnt = 0ul;
    while ( std::getline ( file, line ) ) {
        //std::cout << line << "\n";
        auto l = line.length();
        if ( l > data.size() ) {
            data.resize ( l );
        }
        for ( auto i = 0ul; i < l; i++ ) {
            data[i] += line[i] - '0';
        }
        cnt++;
    }
    auto ans = 0ul;
    for ( auto ones : data ) {
        int zeros = cnt - ones;
        ans = ( ans << 1 ) | ( ones > zeros );
    }
    ans = ans * ( ( ~ans ) & 0xfff );

    OUT ( ans );
}


auto count_ones ( std::vector<std::string>& d, int i ) {
    size_t ret = 0;
    //size_t total = 0;
    for ( auto& s : d ) {
        if ( !s.empty() ) {
            //total++;
            ret += s[i] == '1';
        }
    }

    return ret;
}

int generator_rating ( std::vector<std::string> data, bool o2 ) {
    int len = data.size();
    for ( auto i = 0; len > 1 ; i++ ) {
        auto ones = count_ones ( data, i );
        bool b = ( ones >= len - ones ) ^ o2;
        for ( auto& s : data ) {
            if ( !s.empty() && s[i] == ( '0' + b ) ) {
                s.clear();
                len--;
            }
        }
    }

    for ( auto& s : data ) {
        if ( !s.empty() ) {
            return std::stoi ( s, nullptr, 2 );
        }
    }

    return 0;
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    std::vector<std::string> data{};
    std::string line;
    int ans;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    while ( std::getline ( file, line ) ) {
        data.insert ( data.end(), line );
    }

    int o2_generator_rating = generator_rating ( data, true );
    int co2_generator_rating = generator_rating ( data, false );

    ans = o2_generator_rating * co2_generator_rating;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
