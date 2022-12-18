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
    R"(>>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>)"
};

std::vector<std::vector<std::string>> blocks = {
    {
        "..####.",
    },{
        "...#...",
        "..###..",
        "...#...",
    },{
        "....#..",
        "....#..",
        "..###..",
    },{
        "..#....",
        "..#....",
        "..#....",
        "..#....",
    },{
        "..##...",
        "..##...",
    }
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
std::string getLine ( std::istream& file ) {
    std::string line;
    getline ( file, line );
    return line;
}

void left( std::vector<std::string>& block ) {
    for ( auto& l : block ) {
        if ( l[0]!='.' ) {
            return;
        }
    }
    for ( auto& l : block ) {
        l = l.substr(1) + ".";
    }
}

void right( std::vector<std::string>& block ) {
    for ( auto& l : block ) {
        if ( l[l.size()-1]!='.' ) {
            return;
        }
    }
    for ( auto& l : block ) {
        l = "." + l.substr(0,l.size()-1);
    }
}

bool is_collide( std::string& a, std::string& b ) {
    for ( int i=0; i < 7;i++ ) {
        if ( a[i]=='#' && a[i]==b[i] ) return true;
    }
    return false;
}

void show( std::vector<std::string>& q ) {
    std::cout << "\n";
    for( auto& line : q ) {
        std::cout << line << "\n";
    }
}

std::vector<std::string> next_block(  ) {
    static int i=0;
    return blocks[(i++)%5];
}

char next_wind ( std::string wind ) {
    static int i=0;
    return wind[(i++)%wind.size()];
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::string wind = getLine(file);
    std::vector<std::string> stack {"#######"};

    auto colide = [&stack]( uint k, std::vector<std::string>& block ) ->bool{
        for ( uint i=0; i < block.size() ;i++ ) {
            if ( i < k ) {
                if ( is_collide ( stack[stack.size()-k-1+i], block[block.size()-1-i] ) ) {
                    return true;
                }
            }
        }
        return false;
    };

    auto addEmptylevels = [&stack]( ){
        auto it = stack.rbegin();
        std::string a("#######");
        if ( is_collide ( *it++, a ) ) {
            stack.push_back ( "......." );
            stack.push_back ( "......." );
            stack.push_back ( "......." );
            stack.push_back ( "......." );
        } else
        if ( is_collide ( *it++, a ) ) {
            stack.push_back ( "......." );
            stack.push_back ( "......." );
            stack.push_back ( "......." );
        } else
        if ( is_collide ( *it++, a ) ) {
            stack.push_back ( "......." );
            stack.push_back ( "......." );
        } else
        if ( is_collide ( *it, a ) ) {
            stack.push_back ( "......." );
        }
    };

    char c;
    int count=0;
    while ( count < 2022 ) {
        auto block = next_block( );
        count++;
        addEmptylevels();

        uint k=0;
        while ( !colide ( k, block ) ) {
            c = next_wind( wind );
            if ( c=='<' ) {
                left ( block );
                if ( colide ( k, block ) )
                    right( block );
            }
            if ( c=='>' ) {
                right( block );
                if ( colide ( k, block ) )
                    left ( block );
            }
            k++;
        }

        for ( uint l=0; l < block.size(); l++ ) {
            for ( int i=0; i<7; i++ ) {
                if ( block[block.size()-1-l][i]=='#' )
                    stack[stack.size()-k+l][i] = '#';
            }
        }
    }

    while ( stack.back().find("#")==std::string::npos ) {
        stack.pop_back();
    }

    //show ( stack );

    ans = stack.size() - 1;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ull;

    aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::string wind = getLine( file );

    // 3068 tall 2022 bricks
    // 1514285714288 tall bricks 1000000000000
    // 200 * 7571428571 = 1514285714200
    // T = 40 * 5 = 200
    // 10 * 200 = 2000
    // 15 * 200 = 3000

    // 3034 tall 2000 bricks
    // 15 * 5000000000 =    75000000000
    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
