#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//----------------------------------------------------------------------------//
std::istringstream testinput{
R"(kh-tc
qp-kh
de-cg
ka-co
yn-aq
qp-ub
cg-tb
vc-aq
tb-ka
wh-tc
yn-cg
kh-ub
ta-co
de-co
tc-td
tb-wq
wh-td
ta-ka
td-qp
aq-cg
wq-ub
ub-vc
de-ta
wq-aq
wq-vc
wh-yn
ka-de
kh-ta
co-tc
wh-qp
tb-vc
td-yn
)"};

//----------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    ::std::vector<::std::string> data;
    while ( !fs.eof() ) {
        ::std::string line;
        ::std::getline ( fs, line );
        if( !line.empty ( ) )
            data.push_back ( line );
    }
    return data;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto data = load ( ::aoc::is_test_enabled()?testinput:puzzle_input );

    for ( uint i=0; i < data.size(); i++ ) {
        const auto pair1 = std::string_view(data[i]);
        auto l1 = pair1.substr ( 0, 2 );
        auto r1 = pair1.substr ( 3, 2 );
        for ( uint j=i+1; j < data.size(); j++ ) {
            const auto pair2 = std::string_view(data[j]);
            auto l2 = pair2.substr ( 0, 2 );
            auto r2 = pair2.substr ( 3, 2 );
            std::string_view pl,pr,pm;
            bool ok=false;
            if ( l1==l2 ) {pl = r1; pr=r2; pm=l1; ok=true;}
            else if ( l1==r2 ) {pl = r1; pr=l2; pm=l1; ok=true;}
            else if ( r1==r2 ) {pl = l1; pr=l2; pm=r1; ok=true;}
            else if ( r1==l2 ) {pl = l1; pr=r2; pm=r1; ok=true;}
            if ( ok && (pl[0]=='t' || pr[0]=='t' || pm[0]=='t') )
                for ( uint k=j+1; k < data.size(); k++ ) {
                    const auto pair3 = std::string_view(data[k]);
                    const auto l3 = pair3.substr ( 0, 2 );
                    const auto p3 = pair3.substr ( 3, 2 );
                    if ( (l3==pl && p3==pr) || (l3==pr && p3==pl) )
                        ans++;
                }
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    uint64_t ans=0;

    aoc::test_enable();

    auto data = load ( ::aoc::is_test_enabled()?testinput:puzzle_input );

    ::std::unordered_map<::std::string, int> map;

    for ( uint i=0; i < data.size(); i++ ) {
        const auto pair1 = std::string_view ( data[i] );
        auto l1 = (::std::string)pair1.substr ( 0, 2 );
        auto r1 = (::std::string)pair1.substr ( 3, 2 );
        map[l1]++;
        map[r1]++;
    }
    for ( auto& v : map ) {
        //std::cout << v.first << ' ' << v.second << '\n';
        for ( uint i=0; i < data.size(); i++ ) {
            const auto pair1 = std::string_view ( data[i] );
            auto l1 = (::std::string)pair1.substr ( 0, 2 );
            auto r1 = (::std::string)pair1.substr ( 3, 2 );
            /*if ( l1==v.first )
                std::cout << ' ' << r1 << ' ' << map[r1] << '\n';
            if ( r1==v.first )
                std::cout << ' ' << l1 << ' ' << map[l1] << '\n';*/
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
