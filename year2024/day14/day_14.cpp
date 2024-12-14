#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3
)"
);

//---------------------------------------------------------------------------//
struct P {
    int64_t x=0,y=0;
    void operator +=( const P& o ) {
        x += o.x;
        y += o.y;
    }
    void operator +=( const int64_t o ) {
        x+=o;
        y+=o;
    }
    void operator *=( const int64_t o ) {
        x*=o;
        y*=o;
    }
    P operator *( const int64_t o ) {
        return {x*o, y*o};
    }
};

//---------------------------------------------------------------------------//
struct Guard{
    P p,v;
};

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load ( ::std::istream& file ) {
    ::std::string line;
    ::std::vector<Guard> ret;
    while ( ::std::getline ( file, line ) ) {
        //std::cout << line << '\n';
        std::istringstream is{line};
        P p,v; char c;
        is >> c >> c
           >> p.x >> c >> p.y
           >> c >> c
            >> v.x >> c >> v.y;

        ret.push_back ( {p,v} );
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    const int64_t W = aoc::is_test_enabled() ? 11 : 101;
    const int64_t H = aoc::is_test_enabled() ? 7 : 103;

    for ( auto& g : data ) {
        g.p += g.v*100;
        g.p.x %= W;
        g.p.y %= H;
        if ( g.p.x<0 ) g.p.x += W;
        if ( g.p.y<0 ) g.p.y += H;
    }

    int64_t q1=0, q2=0, q3=0, q4=0;
    for ( const auto& g : data ) {
        if ( (g.p.x < W/2) && (g.p.y<H/2) ) q1++;
        else if ( (g.p.x > W/2) && (g.p.y<H/2) ) q2++;
        else if ( (g.p.x < W/2) && (g.p.y>H/2) ) q3++;
        else if ( (g.p.x > W/2) && (g.p.y>H/2) ) q4++;
    }

    ans = q1 * q2 * q3 * q4;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
/*void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO| ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}*/

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    int64_t ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    const int64_t W = aoc::is_test_enabled() ? 11 : 101;
    const int64_t H = aoc::is_test_enabled() ? 7 : 103;


    //enableRawMode();

    bool search=true;
    while ( search ) {
        ans++;
        std::vector<std::string> tab;
        tab.resize(H);
        for( auto& l : tab ) l.insert ( 0, W, '.' );
        for ( auto& g : data ) {
            g.p += g.v;
            g.p.x %= W;
            g.p.y %= H;
            if ( g.p.x<0 ) g.p.x += W;
            if ( g.p.y<0 ) g.p.y += H;
            tab[g.p.y][g.p.x] = '*';
        }

        for ( const auto& l : tab ) {
            if ( l.find ( std::string{"*******************************"},0)!=std::string::npos ) {
                search = false;
                for ( const auto& l : tab ) std::cout << l <<'\n';
                break;
            }
        }

        /*char c;
        std::cout << ans <<'\n';
        read(STDIN_FILENO, &c, 1);
        //while (read(STDIN_FILENO, &c, 1) == 1)
        if( c=='l') d=1;
        if( c=='j') d=-1;
        */
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
