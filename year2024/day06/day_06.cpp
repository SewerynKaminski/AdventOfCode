#include "day"

//---------------------------------------------------------------------------//
struct Point{
    int x,y;
    Point ( ):x(0),y(0) {}
    Point ( int x, int y ) : x(x),y(y) {}

    void operator+=(Point &o){
        x+=o.x;
        y+=o.y;
    }
    void rotate(){
        y=-y;
        std::swap(x,y);
    }
    bool in( const int w, const int h ) const {
        return y>=0 && y<h && x>=0 && x<w;
    }
    bool operator==(const Point&) const = default;
    Point operator+( const Point& b ) const {
        return {x + b.x, y + b.y };
    }

    size_t hash() const noexcept{return (((size_t)y) << 32) | x;}
};

//---------------------------------------------------------------------------//
template<> struct std::hash<Point>{
    size_t operator()(const Point& p) const noexcept{
        return p.hash();
    }
};

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
std::vector<std::string> load ( std::istream& file ) {
    std::vector<std::string> ret;
    while ( !file.eof() ) {
        std::string line;
        std::getline ( file, line );
        if( !line.empty() )
            ret.push_back ( line );
    }
    return ret;
}

//---------------------------------------------------------------------------//
char& operator<<(::std::vector<::std::string>& s, const Point& p ) {
    return s[p.y][p.x];
}

//---------------------------------------------------------------------------//
Point find_start ( ::std::vector<::std::string>& tab ) {
    Point p;
    for ( ; p.y < (int)tab.size(); p.y++ ) {
        p.x = tab[p.y].find('^');
        if ( p.x >= 0 ) return p;
    }
    return {0,0};
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ul;
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto tab = load ( file );

    Point d{ 0, -1}, p = find_start ( tab );

    const int HEIGHT = tab.size();
    const int WIDTH = tab[0].size();

    tab<<p = 'x';
    while ( (p+d).in(WIDTH,HEIGHT) ) {
        if ( tab<<(p+d) == '#' ) {
            d.rotate();
        } else {
            p += d;
            tab<<p = 'x';
        }
    }

    /*ans = std::accumulate(tab.begin(), tab.end(), 0ull, [](size_t sum, std::string s ) {
            std::print("{}\n", s );
            return std::accumulate(s.cbegin(),s.cend(),sum,[](size_t sum, char c){ return sum+(c=='x');});
        });*/

    for ( const auto& l : tab ) {
        for ( const auto c : l ) {ans += c=='x';}
    }

    OUT ( ans );
}

size_t go( ::std::vector<std::string> tab, Point p ) {
    auto ans=0ull;
    const int HEIGHT = tab.size();
    const int WIDTH = tab[0].size();
    Point d{0,-1};
    while ( (p + d).in( WIDTH, HEIGHT ) ) {
        if ( tab<<(p+d) == '#' ) {
            d.rotate();
        } else {
            p += d;
            auto c = tab << p;
            if ( (d.x>0 && c=='>') ||
                (d.x<0 && c=='<') ||
                (d.y>0 && c=='v') ||
                (d.y<0 && c=='^') ) {
                //::std::print("\n");for ( auto& l: tab )::std::print("{}\n",l);
                ans++;
                break;
            }

            /* UWAGA!!! algorytm nie obsluguje tego przypadku
                    .#.
                    ..#
                    .^.
                    #..
                    .#.
                */
            /*if ( d.x > 0 ) tab[p.y][p.x] = '>';
                if ( d.x < 0 ) tab[p.y][p.x] = '<';
                if ( d.y > 0 ) tab[p.y][p.x] = 'v';
                if ( d.y < 0 ) tab[p.y][p.x] = '^';*/
            tab<<p = '>' * (d.x>0) +
                    '<' * (d.x<0) +
                    'v' * (d.y>0) +
                    '^' * (d.y<0);
        }
    }
    return ans;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ul;
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto tab = load( file );
    Point d{0, -1}, s = find_start( tab ), p = s;

    const int HEIGHT = tab.size();
    const int WIDTH = tab[0].size();
    std::unordered_set<Point> points;

    while ( (p+d).in(WIDTH,HEIGHT) ) {
        if ( tab<<(p+d) == '#' ) {
            d.rotate();
            continue;
        }
        p += d;
        points.insert ( p );
    }
    points.erase ( s );

    for ( auto& o : points ) {
        tab << o = '#';
        ans += go ( tab, s );
        tab << o = '.';
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
