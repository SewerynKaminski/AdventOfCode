#include "day"
#include <ranges>
#include <functional>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3

Monkey 1:
  Starting items: 54, 65, 75, 74
  Operation: new = old + 6
  Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 0

Monkey 2:
  Starting items: 79, 60, 97
  Operation: new = old * old
  Test: divisible by 13
    If true: throw to monkey 1
    If false: throw to monkey 3

Monkey 3:
  Starting items: 74
  Operation: new = old + 3
  Test: divisible by 17
    If true: throw to monkey 0
    If false: throw to monkey 1)" };

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
auto ignore ( int i = 1 ) {
    return [ i ] ( std::istream & o )->std::istream& {
        //return o.ignore ( i, ' ' );
        std::string tmp;
        int c = i;
        while ( c-- ) {
            o >> tmp;
        }
        return o;
    };
}

//---------------------------------------------------------------------------//
std::istream& operator >> ( std::istream& o, std::function< std::istream& ( std::istream& ) > f ) {
    return f ( o );
}

//---------------------------------------------------------------------------//
struct Monkey {
    std::list<int64_t> items;
    char op;
    int64_t opValue;
    int64_t divBy;
    int toMonkeyIfPass;
    int toMonkeyIfFail;
    int64_t inspections = 0;

    int64_t operator<=> ( const Monkey&m ) {
        return inspections - m.inspections;
    }
};

//---------------------------------------------------------------------------//
std::string getLine ( std::istream& file ) {
    std::string line;
    getline ( file, line );
    return line;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::vector<Monkey> monkeys;
    std::string line;
    while ( file ) {
        Monkey monkey;
        std::string tmp;
        std::stringstream ss;

        auto input = [&file]()->auto {
            return std::stringstream ( getLine ( file ) );
        };

        input();
        ss = ( input() >> ignore ( 2 ) );
        while ( ss >> tmp ) {
            monkey.items.push_back ( stoull ( tmp ) );
        }
        input() >> ignore ( 4 ) >> monkey.op >> tmp;
        tmp[0] == 'o' ? monkey.op = '^' : monkey.opValue = stoll ( tmp );

        input() >> ignore ( 3 ) >> monkey.divBy;
        input() >> ignore ( 5 ) >> monkey.toMonkeyIfPass;
        input() >> ignore ( 5 ) >> monkey.toMonkeyIfFail;
        input();

        monkeys.push_back ( monkey );
    }

    for ( int round = 0; round < 20; round++ ) {
        for ( auto& m : monkeys ) {
            while ( m.items.size() ) {
                m.inspections++;
                auto level = m.items.front();
                m.items.pop_front();
                if ( m.op == '*' ) {
                    level *= m.opValue;
                } else if ( m.op == '+' ) {
                    level += m.opValue;
                } else if ( m.op == '^' ) {
                    level *= level;
                }
                level /= 3;
                monkeys[ level % m.divBy ? m.toMonkeyIfFail : m.toMonkeyIfPass].items.push_back ( level );
            }
        }
    }

    std::sort ( monkeys.begin(), monkeys.end(), [] ( Monkey & m1, Monkey & m2 ) {
        return m1.inspections > m2.inspections;
    } );
    ans = monkeys[0].inspections * monkeys[1].inspections;

    /*for ( auto& monkey : monkeys ) {
        std::cout << "Items: ";
        for ( auto item : monkey.items ) {
            std::cout << item << ", ";
        }
        std::cout << "\nInspections: " << monkey.inspections << "\n";
        std::cout << "  Value: " << monkey.op << monkey.opValue << "\n";
        std::cout << "  Test: " << monkey.divBy << "\n";
        std::cout << "    If true: " << monkey.ifTrueThrowToMonkey << "\n";
        std::cout << "    If false: " << monkey.ifFalseThrowToMonkey << "\n";
    }*/

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::vector<Monkey> monkeys;
    int64_t M = 1;
    std::string line;
    while ( file ) {
        Monkey monkey;
        std::string tmp;
        std::stringstream ss;

        auto input = [&file]()->auto {
            return std::stringstream ( getLine ( file ) );
        };

        input();
        ss = ( input() >> ignore ( 2 ) );
        while ( ss >> tmp ) {
            monkey.items.push_back ( stoull ( tmp ) );
        }
        input() >> ignore ( 4 ) >> monkey.op >> tmp;
        tmp[0] == 'o' ? monkey.op = '^' : monkey.opValue = stoull ( tmp );

        input() >> ignore ( 3 ) >> monkey.divBy;
        input() >> ignore ( 5 ) >> monkey.toMonkeyIfPass;
        input() >> ignore ( 5 ) >> monkey.toMonkeyIfFail;
        input();

        M *= monkey.divBy;
        monkeys.push_back ( monkey );
    }

    for ( auto round = 0; round < 10000; round++ ) {
        for ( auto& m : monkeys ) {
            while ( m.items.size() ) {
                m.inspections++;
                auto level = m.items.front();
                m.items.pop_front();
                if ( m.op == '*' ) {
                    level *= m.opValue;
                } else if ( m.op == '+' ) {
                    level += m.opValue;
                } else if ( m.op == '^' ) {
                    level *= level;
                }
                level %= M;
                monkeys [ level % m.divBy ? m.toMonkeyIfFail : m.toMonkeyIfPass].items.push_back ( level );
            }
        }
    }

    std::sort ( monkeys.begin(), monkeys.end(), std::greater<Monkey&>() );
    ans = monkeys[0].inspections * monkeys[1].inspections;

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
