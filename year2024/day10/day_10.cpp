#include "day"
#include <string_view>
#include <charconv>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(noop
addx 3
addx -5)" };

std::string testinput2
{
    R"(addx 15
addx -11
addx 6
addx -3
addx 5
addx -1
addx -8
addx 13
addx 4
noop
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx -35
addx 1
addx 24
addx -19
addx 1
addx 16
addx -11
noop
noop
addx 21
addx -15
noop
noop
addx -3
addx 9
addx 1
addx -3
addx 8
addx 1
addx 5
noop
noop
noop
noop
noop
addx -36
noop
addx 1
addx 7
noop
noop
noop
addx 2
addx 6
noop
noop
noop
noop
noop
addx 1
noop
noop
addx 7
addx 1
noop
addx -13
addx 13
addx 7
noop
addx 1
addx -33
noop
noop
noop
addx 2
noop
noop
noop
addx 8
noop
addx -1
addx 2
addx 1
noop
addx 17
addx -9
addx 1
addx 1
addx -3
addx 11
noop
noop
addx 1
noop
addx 1
noop
noop
addx -13
addx -19
addx 1
addx 3
addx 26
addx -30
addx 12
addx -1
addx 3
addx 1
noop
noop
noop
addx -9
addx 18
addx 1
addx 2
noop
noop
addx 9
noop
noop
noop
addx -1
addx 2
addx -37
addx 1
addx 3
noop
addx 15
addx -21
addx 22
addx -6
addx 1
noop
addx 2
addx 1
noop
addx -10
noop
noop
addx 20
addx 1
addx 2
addx 2
addx -6
addx -11
noop
noop
noop)" };

//---------------------------------------------------------------------------//
inline std::istream& test_input ( int i = 1 ) {
    static std::stringstream ss;
    return ss = std::stringstream ( i == 1 ? testinput : testinput2 );
}

//---------------------------------------------------------------------------//
class CPU {
    int _X = 1; // register
    int _cycle = 0;
    int _sum = 0;
    std::string lcd;

    void tick() {
        if (  ( ( _X - 1 ) <= ( _cycle % 40 ) ) && ( ( _cycle % 40 ) <= ( _X + 1 ) ) ) {
            lcd[_cycle] = '#';
        }
        _cycle++;
        if ( ( _cycle + 20 ) % 40 == 0 ) {
            _sum += _X * _cycle;
        }
    }

public:
    CPU() {
        lcd.resize ( 6 * 40, ' ' );
    }

    void noop() {
        tick();
    }

    void addx ( int x ) {
        tick();
        tick();
        _X += x;
    }

    inline auto sum() {
        return _sum;
    }

    inline auto lcd_line ( int n ) {
        return std::string_view ( lcd ).substr ( n * 40, 40 );
    }

    void execute ( std::string_view op ) {
        switch ( op[0] ) {
        case 'n':// noop
            noop();
            break;
        case 'a':// addx
            addx ( std::atoi ( op.substr ( 5 ).data() ) );
            break;
        }
    }
};

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ul;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( 2 ) : puzzle_input;

    std::string op;

    CPU cpu;
    while ( getline ( file, op ) ) {
        cpu.execute ( op );
    }
    ans = cpu.sum();

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ul;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( 2 ) : puzzle_input;

    std::string op;
    CPU cpu;
    while ( getline ( file, op ) ) {
        cpu.execute ( op );
    }

    for ( auto i = 0; i < 6; i++ ) {
        std::cout << cpu.lcd_line ( i ) << "\n";
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
