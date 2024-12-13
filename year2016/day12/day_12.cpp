#include "day"
#include <cmath>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(cpy 41 a
inc a
inc a
dec a
jnz a 2
dec a
)");

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    ::std::vector<::std::string> ret;
    ::std::string line;
    while ( ::std::getline(file, line) )
        ret.push_back ( line );
    return ret;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );

    uint ip=0;
    ::std::map<char,int64_t> regs;
    while ( ip < data.size() ) {
        const std::string& ins = data[ip];
        if ( ins.starts_with("cpy ") ) {
            auto idx = ins.find ( ' ', 4 )+1; // to
            auto a = ins.substr ( 4, idx-5 ); // from
            if ( std::isdigit(ins[4]) ) {
                regs[ ins[idx] ] = stoi(a);
            } else {
                regs[ ins[idx] ] = regs[ a[0] ];
            }
            ip++;
        } else
        if ( ins.starts_with("inc ") ) {
            regs[ ins[4] ]++;
            ip++;
        } else
        if ( ins.starts_with("dec ") ) {
            regs[ ins[4] ]--;
            ip++;
        } else
        if ( ins.starts_with("jnz ") ) {
            auto idx = ins.find ( ' ', 4 )+1; // ofs
            auto a = ins.substr ( 4, idx-5 ); // cond
            auto ofs = stoi( ins.substr(idx) );
            if ( std::isdigit(ins[4]) ) {
                if ( stoi(a) ) ip+= ofs-1;
            } else {
                if ( regs[ a[0] ] ) ip+= ofs-1;
            }
            ip++;
        }
    }

    ans = regs['a'];

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );

    uint ip=0;
    ::std::map<char,int64_t> regs;
    regs['c']=1;
    while ( ip < data.size() ) {
        const std::string& ins = data[ip];
        if ( ins.starts_with("cpy ") ) {
            auto idx = ins.find ( ' ', 4 )+1; // to
            auto a = ins.substr ( 4, idx-5 ); // from
            if ( std::isdigit(ins[4]) ) {
                regs[ ins[idx] ] = stoi(a);
            } else {
                regs[ ins[idx] ] = regs[ a[0] ];
            }
            ip++;
        } else
            if ( ins.starts_with("inc ") ) {
                regs[ ins[4] ]++;
                ip++;
            } else
                if ( ins.starts_with("dec ") ) {
                    regs[ ins[4] ]--;
                    ip++;
                } else
                    if ( ins.starts_with("jnz ") ) {
                        auto idx = ins.find ( ' ', 4 )+1; // ofs
                        auto a = ins.substr ( 4, idx-5 ); // cond
                        auto ofs = stoi( ins.substr(idx) );
                        if ( std::isdigit(ins[4]) ) {
                            if ( stoi(a) ) ip+= ofs-1;
                        } else {
                            if ( regs[ a[0] ] ) ip+= ofs-1;
                        }
                        ip++;
                    }
    }

    ans = regs['a'];

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
