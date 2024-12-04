#include "day"
#include <ranges>
#include <iomanip>
#include <unordered_set>
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(root: pppw + sjmn
dbpl: 5
cczh: sllz + lgvd
zczc: 2
ptdq: humn - dvpt
dvpt: 3
lfqf: 4
humn: 5
ljgn: 2
sjmn: drzm * dbpl
sllz: 4
pppw: cczh / lfqf
lgvd: ljgn * ptdq
drzm: hmdt - zczc
hmdt: 32)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
struct S{
    bool isValue;
    double val;
    char op;
    std::string n1, n2;
};

//---------------------------------------------------------------------------//

auto parse( std::istream& ss ){
    std::unordered_map<std::string,S> hash;
    while( ss.good() ) {
        std::string name,val;
        ss >> name >> val;
        name = name.substr(0, name.size()-1);
        if ( val[0]>='0' && val[0]<='9' ) {
            hash[name] = {true, stod(val), 0,"","" };
        } else {
            std::string name1;
            char op;
            ss >> op >> name1;
            hash[name] = {false, 0, op, val, name1 };
        }
    }
    return hash;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    auto hash = parse( file );

    while ( !hash["root"].isValue ) {
        for ( auto& [key,v] : hash ) {
            if ( !v.isValue ) {
                if ( hash[v.n1].isValue && hash[v.n2].isValue ) {
                   v.isValue = true;
                   switch(v.op){
                   case '+': v.val = hash[v.n1].val + hash[v.n2].val; break;
                   case '-': v.val = hash[v.n1].val - hash[v.n2].val; break;
                   case '*': v.val = hash[v.n1].val * hash[v.n2].val; break;
                   case '/': v.val = hash[v.n1].val / hash[v.n2].val; break;
                   }
                }
            }
        }
    }
    ans = hash["root"].val;

    OUT ( ans );
}

double calculate ( std::unordered_map<std::string,S>& hash, std::string name, double humn ) {
    if ( name=="humn" ) return humn;
    S& s = hash[name];
    if ( s.isValue ) return s.val;

    double val1 = calculate( hash, s.n1, humn );
    double val2 = calculate( hash, s.n2, humn );

    switch( s.op ) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/': return val1 / val2;
    }
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    auto hash = parse( file );

    double humn = 0;
    double o1 = calculate ( hash, hash["root"].n1, humn )-calculate ( hash, hash["root"].n2, humn );
    humn = 1;
    double o2 = calculate ( hash, hash["root"].n1, humn)-calculate ( hash, hash["root"].n2, humn );

    double add = 1;
    bool up = (std::abs(o1) > std::abs(o2)) ^ (o2<0);

    double diff = 1;
    while ( std::abs(diff) != 0.f ) {
        diff = calculate ( hash, hash["root"].n1, humn ) - calculate ( hash, hash["root"].n2, humn );
        diff *= 2 * up - 1;

        if ( diff > 0 ) {
            humn += add;
            add *= 2;
        }
        if ( diff < 0 ) {
            add /= 2;
            humn -= add;
            add /= 2;
        }
    }
    ans = humn;

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
