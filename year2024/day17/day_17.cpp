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
    int count = 0;
    // 1536
    // 3016

    while ( count < 2022 ) {
    //while ( count < 960*2 ) {
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

    char c;
    std::string wind = getLine( file );
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

    auto count = 0ull;
    while( count < 1000 ) {
        count++;
        //std::cout << count << "\n";
        auto block = next_block( );
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
        while ( stack.back().find("#")==std::string::npos ) {
            stack.pop_back();
        }

        //for ( uint n=1 ;n < stack.size()/2; n++) {
        //if ( (stack.size()&1)==0 )
        //for ( uint n=1 ;n < stack.size()/2; n++) {
        for ( uint n=53 ;n < 53+1; n++) {
            bool ok=true;
            for( uint i=1; i<n ; i++ ) {
                if( stack[stack.size()-i]!=stack[stack.size()-i-n] ||
                    stack[stack.size()-i-n]!=stack[stack.size()-i-n*2] ) {
                    ok=false;
                    break;
                }
            }
            if ( ok ) {
                std::cout << count << " " << stack.size() << " " << n << "\n";
            }
        }
    }

    //show( stack );
// 10 klockow - 53 wysokosc

    ans = 1000000000000ll + stack.size() - 1;
// 1514285714288
// 1000000000457
    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
