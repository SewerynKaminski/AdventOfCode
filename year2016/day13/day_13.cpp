#include "day"
#include <cmath>

//---------------------------------------------------------------------------//
struct P{
    int x, y;
    size_t hash() const { return ((size_t)y<<32) | x;}
    P operator+(const P& o) const { return {x+o.x,y+o.y};}
    bool operator==(const P& o) const { return x==o.x && y==o.y; }
};

//---------------------------------------------------------------------------//
template<>
struct std::hash<P>{
    size_t operator()(const P& p) const { return p.hash(); }
};

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(10
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    size_t ret;
    file >> ret;
    return ret;
}

//---------------------------------------------------------------------------//
bool is_wall( size_t fav, int x, int y ) {
    return std::popcount(x*x + 3*x + 2*x*y + y + y*y + fav)&1;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto favorite_number = load( file );

    ::std::vector<P> pos{ {1,1} };

    const P end = aoc::is_test_enabled()?P{7,4}:P{31,39};

    std::unordered_set<P> visited;
    visited.insert({1,1});
    auto ok = true;
    while ( ok ) {
        std::vector<P> new_pos;
        while ( !pos.empty() ) {
            auto check = [favorite_number,&visited,&new_pos](const P& p){
                if ( !is_wall ( favorite_number, p.x, p.y ) && !visited.contains(p) ) {
                    visited.insert ( p );
                    new_pos.push_back ( p );
                }
            };

            auto p = pos.back();
            if ( p == end ) {
                ok=false;
                break;
            }

            if ( p.x > 0 ) check ( p + P{-1,0} );
            check ( p + P{1,0} );
            if ( p.y > 0 ) check ( p + P{0,-1} );
            check ( p + P{0,1} );

            pos.pop_back();
        }
        pos = std::move ( new_pos );
        ans++;
    }

    OUT ( ans-1 );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto favorite_number = load ( file );

    ::std::vector<P> pos{ {1,1} };

    std::unordered_set<P> visited;
    visited.insert({1,1});
    auto steps = 0ull;
    while ( steps < 50 ) {
        std::vector<P> new_pos;
        while ( !pos.empty() ) {
            auto check = [favorite_number,&visited,&new_pos](const P& p){
                if ( !is_wall ( favorite_number, p.x, p.y ) && !visited.contains(p) ) {
                    visited.insert ( p );
                    new_pos.push_back ( p );
                }
            };

            auto p = pos.back();
            if ( p.x > 0 ) check ( p + P{-1,0} );
            check ( p + P{1,0} );
            if ( p.y > 0 ) check ( p + P{0,-1} );
            check ( p + P{0,1} );

            pos.pop_back();
        }
        pos = std::move ( new_pos );
        steps++;
    }
    ans = visited.size();

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
