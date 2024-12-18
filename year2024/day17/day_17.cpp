#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
/*std::string testinput (
R"(Register A: 729
Register B: 0
Register C: 0

Program: 0,1,5,4,3,0
)");*/

std::string testinput (
R"(Register A: 2024
Register B: 0
Register C: 0
Program: 0,3,5,4,3,0
)");

//---------------------------------------------------------------------------//
inline ::std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
::std::vector<::std::string> load ( ::std::istream& file ) {
    ::std::string line;
    ::std::vector<::std::string> lines;
    while ( ::std::getline ( file, line ) ) {
        if( !line.empty() )
            lines.push_back ( line );
    }

    return lines;
}

//---------------------------------------------------------------------------//
enum OPCODE { ADV, BXL, BST, JNZ, BXC, OUT, BDV, CDV };

//---------------------------------------------------------------------------//
std::string run(::std::vector<int8_t> prog, int64_t A, int64_t B, int64_t C ) {
    std::string ans;
    uint ip = 0;

    while( ip < prog.size() ) {
        int64_t o = prog [ ip + 1 ];
        switch ( prog [ ip ] ) {
        case ADV:
            A >>= o==4?A:o==5?B:o==6?C:o;
            break;
        case BXL:
            B ^= o;
            break;
        case BST:
            B = (o==4?A:o==5?B:o==6?C:o) & 7;
            break;
        case JNZ:
            if ( A ) ip = o - 2;
            break;
        case BXC:
            B ^= C;
            break;
        case OUT:
            if( !ans.empty() ) ans += ',';
            ans += std::to_string ( (o==4?A:o==5?B:o==6?C:o)&7 );
            break;
        case BDV:
            B = A >> (o==4?A:o==5?B:o==6?C:o);
            break;
        case CDV:
            C = A >> (o==4?A:o==5?B:o==6?C:o);
            break;
        }
        ip+=2;
    }
    return ans;
}


//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    ::std::string ans;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    int64_t A = std::stoll ( data[0].substr(12) );
    int64_t B = std::stoll ( data[1].substr(12) );
    int64_t C = std::stoll ( data[2].substr(12) );

    ::std::vector<int8_t> prog{};
    auto s = data[3].substr(9);

    ::std::istringstream is{s};
    while ( !is.eof() ) {
        int v; is >> v; prog.push_back(v);
        char c; is >> c;
    }

    ans = run ( prog, A, B, C );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
int64_t find ( std::vector<int8_t> & prog, std::string& s, int p, int64_t A ) {
    int64_t ret = INT64_MAX;
    for ( int i=0; i<8; i++) {
        auto ans = run ( prog, A|i, 0, 0 );
        if ( ans[0]==s[p] ) {
            if ( p > 0 )
                ret = std::min ( ret, find( prog, s, p-2,(A|i) << 3 ));
            else
                ret = std::min ( ret, A|i );
        }
    }
    return ret;
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    auto s = data[3].substr(9);

    ::std::vector<int8_t> prog;
    ::std::istringstream is{s};
    while ( !is.eof() ) {
        int v; is >> v; prog.push_back(v);
        char c; is >> c;
    }

    auto ans = find ( prog, s, s.size()-1, 0 );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
