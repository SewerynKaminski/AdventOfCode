//---------------------------------------------------------------------------//
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <fstream>
#include <limits>
#include <set>
#include <iomanip>
#include <bit>
#include <math.h>
#include <numeric>

//---------------------------------------------------------------------------//
namespace aoc::year_2021::day_21 {

//---------------------------------------------------------------------------//
template<class T>
constexpr auto Range ( T a, T b ) {
    return std::views::iota ( a, b );
}

//---------------------------------------------------------------------------//
auto load ( std::string file ) {
    std::fstream fs ( file );
    std::string line;
    std::vector<int> data;

    while ( std::getline ( fs, line ), fs.good() ) {
        auto n = line.find_last_of ( ' ' );
        data.push_back ( std::stoi ( line.substr ( n + 1 ) ) );
    }

    return data;
}

//---------------------------------------------------------------------------//
struct Player {
    uint64_t pos = 0;
    uint16_t score = 0;
    Player& add_score_from_pos() {
        score += pos + 1;
        return *this;
    }
};

//---------------------------------------------------------------------------//
Player operator+ ( Player&p, int s ) {
    return { ( p.pos + s ) % 10, p.score};
}

//---------------------------------------------------------------------------//
void Task_1 ( ) {
    auto ans = 0ull;
    auto data = load ( "../input" );

    int die = 0;
    Player p1;
    Player p2;
    p1.pos = data[0] - 1;
    p2.pos = data[1] - 1;

    auto roll_die_x3 = [&die] ( Player & p ) {
        for ( auto i : Range ( 0, 3 ) ) {
            p.pos += die + 1;
            ++die %= 100;
        }
        p.pos %= 10;
    };

    auto add_score = [] ( Player & p ) {
        p.score += p.pos + 1;
    };

    bool turn = true;
    int rolls = 0;
    while ( p1.score < 1000 && p2.score < 1000 ) {
        auto& p = turn ? p1 : p2;
        roll_die_x3 ( p );
        add_score ( p );
        turn = !turn;
        rolls += 3;
    }

    ans = std::min ( p1.score, p2.score ) * rolls;

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
std::unordered_map<int, std::tuple<uint64_t, uint64_t>> h;

//---------------------------------------------------------------------------//
void throw_die_x3 ( std::vector<Player>& players, Player p, uint64_t t = 0 ) {
    if ( t < 3 ) {
        throw_die_x3 ( players, p + 1, t + 1 );
        throw_die_x3 ( players, p + 2, t + 1 );
        throw_die_x3 ( players, p + 3, t + 1 );
    } else {
        p.add_score_from_pos();
        players.push_back ( p );
    }
}

//---------------------------------------------------------------------------//
std::tuple<uint64_t, uint64_t> play ( uint64_t turn, Player p1, Player p2 ) {
    if ( p1.score > 20 || p2.score > 20 ) {
        return {p1.score > 20, p2.score > 20};
    }
    auto s1 = 0ull;
    auto s2 = 0ull;

    auto key = [& p1, & p2, turn] ( ) {
        return  p2.score << 17 | p1.score << 12 | turn << 8 | p1.pos << 4 | p2.pos;
    };

    //      1            2            3
    //    / | \        / | \        / | \
    //  1   2   3    1   2   3    1   2   3
    // /|\ /|\ /|\  /|\ /|\ /|\  /|\ /|\ /|\
    // 123 123 123  123 123 123  123 123 123
    //
    // 345 456 567  456 567 678  567 678 789
    //

    if ( h.contains ( key() ) ) {
        return h [ key() ];
    }

    std::vector<Player> list;
    throw_die_x3 ( list, turn & 1 ? p2 : p1 );
    for ( auto& p : list ) {
        auto [ w1, w2 ] = play ( turn + 1, turn & 1 ? p1 : p, turn & 1 ? p : p2 );
        s1 += w1;
        s2 += w2;
    }

    h [ key () ] = { s1, s2 };
    return { s1, s2 };
}

//---------------------------------------------------------------------------//
void Task_2 ( ) {
    auto ans = 0ull;
    auto data = load ( "../input" );
    Player p1;
    Player p2;

    p1.pos = data[0] - 1;
    p2.pos = data[1] - 1;

    auto [s1, s2] = play ( 0, p1, p2 );
    ans = std::max ( s1, s2 );

    std::cout << __FUNCTION__ << ": " << ans << "\n";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
