#include "day"

struct P {
    int x,y;
    bool operator==( const P&) const = default;
    P operator-( const P& o ){ return { x-o.x, y-o.y }; }
    void operator+=( const P& o ){ x+=o.x; y+=o.y; }
    void operator-=( const P& o ){ x-=o.x; y-=o.y; }
    size_t hash() const { return (((size_t)y)<<32) + x; }
};

template <> struct std::hash<P> {
    size_t operator() ( const P& p ) const noexcept {
        return p.hash ( );
    }
};

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    ::std::vector<std::string> ret;
    ::std::string line;
    while ( ::std::getline( file, line ) ) {
        ret.push_back ( line );
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    //std::cout << data.size() << 'x' << data[0].size() << '\n';
    std::unordered_map<char,std::vector<P>> antena;
    const auto n = (int)data.size();
    for ( int y=0; y < n; y++ ) {
        //std::cout << data[y] << '\n';
        for ( int x=0; x < n; x++ ) {
            char c = data[y][x];
            if ( c!='.') antena[c].push_back({x,y});
        }
    }

    std::unordered_set<P> antinode;
    for ( auto it : antena )
        for ( uint i=0; i < it.second.size(); i++ )
            for ( uint j=i+1; j < it.second.size(); j++ ) {
                auto p1 = it.second[i];
                auto p2 = it.second[j];
                auto d = p2 - p1;
                p1 -= d;
                p2 += d;
                if ( p1.x>=0 && p1.x<n && p1.y>=0 && p1.y<n )
                    antinode.insert ( p1 );
                if ( p2.x>=0 && p2.x<n && p2.y>=0 && p2.y<n )
                    antinode.insert ( p2 );
            }

    ans = antinode.size();
    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );

    std::unordered_map<char,std::vector<P>> antena;
    const auto n = (int)data.size();
    for ( int y=0; y < n; y++ ) {
        //std::cout << data[y] << '\n';
        for ( int x=0; x < n; x++ ) {
            char c = data[y][x];
            if ( c!='.') antena[c].push_back({x,y});
        }
    }

    std::unordered_set<P> antinode;
    for ( auto it : antena )
        for ( uint i=0; i < it.second.size(); i++ )
            for ( uint j=i+1; j < it.second.size(); j++ ) {
                auto p1 = it.second[i];
                auto p2 = it.second[j];
                auto d = p2 - p1;
                while ( p1.x>=0 && p1.x<n && p1.y>=0 && p1.y<n ) {
                    antinode.insert ( p1 );
                    p1-=d;
                }
                while ( p2.x>=0 && p2.x<n && p2.y>=0 && p2.y<n ) {
                    antinode.insert ( p2 );
                    p2+=d;
                }
            }

    ans = antinode.size();
    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
