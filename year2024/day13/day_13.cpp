#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279
)"
);

//---------------------------------------------------------------------------//
struct P {
    int64_t x=0,y=0;
    void operator +=( const int64_t o ) {
        x+=o;
        y+=o;
    }
};

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
::std::vector<std::string> load ( ::std::istream& file ) {
    ::std::string line;
    ::std::vector<::std::string> ret;
    while ( ::std::getline ( file, line ) ) {
        if( !line.empty() ) {
            ret.push_back ( line );
        }
    }
    return ret;
}

//---------------------------------------------------------------------------//
int64_t calc ( const P& a, const P& b, const P& prize ) {
    auto q = prize.y*a.x - prize.x*a.y;
    auto w = a.x*b.y - a.y*b.x;

    auto nb = q / w;
    if ( !(q % w) ) {
        q = prize.x - b.x*nb;
        w = a.x;
        auto na = q / w;
        if ( !(q % w) ) {
            return  3 * na + nb;
        }
    }

    return 0;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    P a, b, p;
    for ( const auto& line : data ) {
        std::string s;
        char c;
        std::istringstream is{line};
        if ( line.starts_with ( "Button A: " ) ) {
            is >> s >> s >> c >> c >> a.x >> c >> c >> c >> a.y;
        } else if ( line.starts_with ( "Button B: " ) ){
            is >> s >> s >> c >> c >> b.x >> c >> c >> c >> b.y;
        } else if ( line.starts_with ( "Prize: " ) ){
            is >> s >> c >> c >> p.x >> c >> c >> c >> p.y;
            ans += calc ( a, b, p );
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    int64_t ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    P btnA, btnB, prize;
    for ( const auto& line : data ) {
        std::string s;
        char c;
        std::istringstream is { line };
        if ( line.starts_with ( "Button A: " ) ) {
            is >> s >> s >> c >> c >> btnA.x >> c >> c >> c >> btnA.y;
        } else if ( line.starts_with ( "Button B: " ) ) {
            is >> s >> s >> c >> c >> btnB.x >> c >> c >> c >> btnB.y;
        } else if ( line.starts_with ( "Prize: " ) ) {
            is >> s >> c >> c >> prize.x >> c >> c >> c >> prize.y;
            prize += 10'000'000'000'000;
            ans += calc ( btnA, btnB, prize );
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
