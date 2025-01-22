#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//----------------------------------------------------------------------------//
std::istringstream testinput{
R"(x00: 1
x01: 1
x02: 1
y00: 0
y01: 1
y02: 0

x00 AND y00 -> z00
x01 XOR y01 -> z01
x02 OR y02 -> z02
)"};

std::istringstream testinput2{
R"(x00: 1
x01: 0
x02: 1
x03: 1
x04: 0
y00: 1
y01: 1
y02: 1
y03: 1
y04: 1

ntg XOR fgs -> mjb
y02 OR x01 -> tnw
kwq OR kpj -> z05
x00 OR x03 -> fst
tgd XOR rvg -> z01
vdt OR tnw -> bfw
bfw AND frj -> z10
ffh OR nrd -> bqk
y00 AND y03 -> djm
y03 OR y00 -> psh
bqk OR frj -> z08
tnw OR fst -> frj
gnj AND tgd -> z11
bfw XOR mjb -> z00
x03 OR x00 -> vdt
gnj AND wpb -> z02
x04 AND y00 -> kjc
djm OR pbm -> qhw
nrd AND vdt -> hwm
kjc AND fst -> rvg
y04 OR y02 -> fgs
y01 AND x02 -> pbm
ntg OR kjc -> kwq
psh XOR fgs -> tgd
qhw XOR tgd -> z09
pbm OR djm -> kpj
x03 XOR y03 -> ffh
x00 XOR y04 -> ntg
bfw OR bqk -> z06
nrd XOR fgs -> wpb
frj XOR qhw -> z04
bqk OR frj -> z07
y03 OR x01 -> nrd
hwm AND bqk -> z03
tgd XOR rvg -> z12
tnw OR pbm -> gnj
)"};

//----------------------------------------------------------------------------//
::std::pair<::std::unordered_map<std::string, bool>,::std::vector<std::string>> load ( ::std::istream& input ) {
    ::std::unordered_map<std::string, bool> vars;
    ::std::vector<std::string> gates;
    ::std::string line;
    while ( ::std::getline( input, line ) ) {
        if ( line.empty() ) break;
        //std::cout << line << '\n';
        auto sep = line.find(':');
        auto s0 = line.substr ( 0, sep );
        auto s1 = line.substr ( sep+2 );
        vars[s0] = s1[0]=='1';
    }
    while ( ::std::getline( input, line ) ) {
        //std::cout << line << '\n';
        gates.push_back( line );
    }
    return { vars, gates };
}
//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto [vars, gates] = load ( ::aoc::is_test_enabled()?testinput:puzzle_input );

    while( gates.size() ) {
        for ( auto it=gates.rbegin() ; it!=gates.rend(); ++it ) {
            auto s = it->find ( ' ' );
            auto ss = it->find ( ' ', s + 1 );
            auto sss = it->find ( ' ', ss + 1 );
            auto ssss = it->find ( ' ', sss + 1 );
            auto s0 = it->substr ( 0, s );
            auto s1 = it->substr ( s + 1, ss-s-1 );
            auto s2 = it->substr ( ss + 1, sss-ss-1 );
            auto s4 = it->substr ( ssss + 1 );
            if ( vars.contains(s0) && vars.contains(s2) ) {
                if ( s1 == "AND" ) vars[s4] = int(vars[s0]) & int(vars[s2]);
                if ( s1 == "XOR" ) vars[s4] = int(vars[s0]) ^ int(vars[s2]);
                if ( s1 == "OR"  ) vars[s4] = int(vars[s0]) | int(vars[s2]);
                gates.erase ( std::next(it).base() );
            }
        }
    }
    for ( auto& v : vars )
        if ( v.first[0] == 'z' )
            ans |= uint64_t(v.second) << stoi(v.first.substr(1));

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    uint64_t ans=0;

    aoc::test_enable();

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
