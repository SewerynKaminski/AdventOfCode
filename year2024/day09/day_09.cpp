#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
R"(2333133121414131402
)");

//---------------------------------------------------------------------------//
int next ( std::string t ) {
    static int i=-1;
    static int id=0;
    static int cnt=0;
    static bool block = false;

    while ( cnt == 0 ) {
        block = !block;
        if ( block ) {
            id++;
        }
        i++;
        cnt = t[i]-'0';
    }
    cnt--;
    return id * block;
}

//---------------------------------------------------------------------------//
int prev ( std::string t, int ofsi, int ofsid ) {
    static int i=0;
    static int id=0;
    static int cnt=0;
    static bool block = false;

    while ( cnt == 0 ) {
        block = !block;
        if ( block ) {
            id++;
        }
        i++;
        cnt = t[ofsi-i]-'0';
    }
    cnt--;
    return (ofsid-id) * block;
}

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
auto load( std::istream& file ) {
    ::std::string line;
    ::std::getline( file, line );
    return line;
}

//---------------------------------------------------------------------------//
void Task_1 ( ::std::istream& puzzle_input ) {
    auto ans=0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load ( file );
    int sum=0;
    for ( auto c : data ) sum += c-'0';
    const auto sid = 1+(data.size()+1)/2;
    int i = 0, j = sum-1;
    while ( i != j ) {
        auto id = next(data); i++;
        while ( !id ) {id = prev(data, data.size(), sid); j--;}
        ans += (i-1)*(id-1);
    }
    auto id = next(data);
    if ( id ) {
        ans += i*(id-1);
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( ::std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;
    auto data = load( file );
    auto s = data;

    for( int i=data.size()-1; i>0; i-=2 ) {
        int file_len = data[i]-'0', idx=0, id=0;
        auto sum=0ull;
        for ( int j=0; j<i;j+=2) {
            id = i/2;
            idx += s[j]-'0';
            auto free_len = s[j+1]-'0';
            if ( free_len >= file_len ) {
                s[j] += file_len;
                s[j+1] -= file_len;
                break;
            }
            idx += free_len;
        }

        sum += file_len*(file_len-1)/2;
        sum += file_len*idx;
        sum *= id;
        ans += sum;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
