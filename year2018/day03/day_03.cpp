#include <day>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
constexpr uint N=1000;

//---------------------------------------------------------------------------//
std::istringstream test_input{
R"(#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2
)"};

//---------------------------------------------------------------------------//
struct S{
    uint16_t id, x, y, w, h;
    uint top(){ return y;}
    uint bottom(){ return y+h;}
    uint left(){ return x;}
    uint right(){ return x+w;}
    uint area(){ return w*h; }
};

//---------------------------------------------------------------------------//
auto load ( ::std::istream& file ) {
    ::std::vector<S> ret;
    std::string line;
    while( std::getline ( file, line ) ) {
        std::istringstream l(line);
        uint16_t id,x,y,w,h;
        char c;
        l >> c >> id >> c >> x >> c >> y >> c >> w >> c >> h;
        ret.push_back ( { id, x, y, w, h } );
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;

    auto data = load ( file );
    auto ans = 0ull;
    std::array<char,N*N> tab{0};
    for ( auto& rec : data )
        for ( uint y=rec.top(); y < rec.bottom() ; y++ )
            for ( uint x=rec.left(); x < rec.right() ; x++ )
                if ( tab[y*N+x] < 2 ) {
                    tab[y*N+x] += 1;
                    if ( tab[y*N+x] == 2 )
                        ans++;
                }

    OUT(ans);
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;

    auto data = load ( file );
    std::array<char, N*N> tab{0};
    for ( auto& rec : data )
        for ( uint y=rec.top(); y < rec.bottom(); y++ )
            for ( uint x=rec.left(); x < rec.right(); x++ )
                if ( tab[y*N+x] < 2 ) {
                    tab[y*N+x] += 1;
                    if ( tab[y*N+x] == 2 )
                        ans++;
                }

    for ( auto& rec : data ) {
        uint area = 0;
        for ( uint y=rec.top(); y < rec.bottom(); y++ )
            for ( uint x=rec.left(); x < rec.right(); x++ )
                area += tab[y*N+x];
        if ( area == rec.area() ) {
            ans = rec.id;
            break;
        }
    }

    OUT(ans);
}
//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
