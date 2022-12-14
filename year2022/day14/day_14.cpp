#include "day"
#include <ranges>
#include <iomanip>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"(498,4 -> 498,6 -> 496,6
503,4 -> 502,4 -> 502,9 -> 494,9)"
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

//---------------------------------------------------------------------------//
struct Point{ int x,y;
    Point operator-(const Point& p){
        return {x-p.x,y-p.y};
    }
    bool operator ==(const Point& p ) const {
        return x==p.x && y==p.y;
    }
};

//---------------------------------------------------------------------------//
void show ( auto& tab ) {
    std::cout << "\n";
    for ( auto& l : tab ) {
        std::cout << l << "\n";
    }
};

//---------------------------------------------------------------------------//
auto count_o( auto& tab ){
    auto cnt = 0ull;
    for ( auto& l : tab ) {
        for ( auto& c : l ) {
            cnt += c=='o';
        }
    }
    return cnt;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::string line;
    std::vector<std::vector<Point>> points;
    while ( getline(file, line) ) {
        std::stringstream ss(line);
        char comma;
        int x, y;
        points.push_back ( std::vector<Point>{} );
        while ( ss ) {
            ss >> x >> comma >> y >> comma >> comma;
            points.back().push_back ( {x, y} );
        }
    }

    int xmin=0xffff, xmax=0, ymax=0;
    for ( auto& l : points ) {
        for ( auto& p : l ) {
            xmin = std::min(xmin, p.x);
            xmax = std::max(xmax, p.x);
            ymax = std::max(ymax, p.y);
        }
    }

    int dropx = 500 - xmin + 1;
    std::vector<std::string> tab(ymax+1);
    for ( int i=0; i <=ymax; i++ ) {
        tab[i] = std::string ( (xmax-xmin) + 3, ' ' );
    }

    // center points
    for ( auto& l : points ) {
        for ( auto& p: l ) {
            p.x += - xmin + 1;
        }
    }

    // draw lines
    for ( auto& l : points ) {
        for ( uint i=1; i<l.size(); i++ ) {
            auto p1=l[i-1];
            auto p2=l[i];
            auto dp = p1-p2;
            dp.x = (dp.x>0) - (dp.x<0);
            dp.y = (dp.y>0) - (dp.y<0);
            tab[p2.y][p2.x] = '#';
            while ( p2!=p1 ) {
                p2.x += dp.x;
                p2.y += dp.y;
                tab[p2.y][p2.x] = '#';
            }
        }
    }

    // drop sand
    auto drop = [&tab]( uint x, uint y ) -> bool {
        while ( y < tab.size()-1 ) {
            if ( tab[y+1][x]==' ' ) {
                y++;
            } else if ( tab[y+1][x-1]==' ' ) {
                y++;
                x--;
            } else if ( tab[y+1][x+1]==' ' ) {
                y++;
                x++;
            } else {
                tab[y][x]='o';
                return true;    // rest
            }
        }
        return false;   // fall through
    };

    while ( drop(dropx,0) ) {
        //show(tab);
    }
    ans = count_o( tab );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::string line;
    std::vector<std::vector<Point>> points;
    while ( file ) {
        std::stringstream ss ( getLine ( file ) );
        char comma;
        int x, y;
        points.push_back ( std::vector<Point>{} );
        while ( ss ) {
            ss >> x >> comma >> y >> comma >> comma;
            points.back().push_back ( {x, y} );
        }
    }

    // min-max
    int ymax=0;
    for ( auto& l : points ) {
        for ( auto& p : l ) {
            ymax = std::max(ymax, p.y);
        }
    }
    ymax+=1;

    std::vector<std::string> tab(ymax+1);
    for ( int i=0; i <=ymax; i++ ) {
        tab[i] = std::string ( 500+ymax+1, '.' );
    }

    // draw lines
    for ( auto& l : points ) {
        for ( uint i=1; i<l.size(); i++ ) {
            auto p1=l[i-1];
            auto p2=l[i];
            auto dp = p1-p2;
            dp.x = (dp.x>0) - (dp.x<0);
            dp.y = (dp.y>0) - (dp.y<0);
            tab[p2.y][p2.x] = '#';
            while ( p2!=p1 ) {
                p2.x += dp.x;
                p2.y += dp.y;
                tab[p2.y][p2.x] = '#';
            }
        }
    }

    auto drop = [&tab]( uint x, uint y ) -> bool {
        if ( tab[y][x]=='o' ) return false;
        while ( y+1 < tab.size() ) {
            if ( tab[y+1][x]=='.' ) {
                y++;
            } else if ( tab[y+1][x-1]=='.' ) {
                y++;
                x--;
            } else if ( tab[y+1][x+1]=='.' ) {
                y++;
                x++;
            } else {
                tab[y][x]='o';
                return true;// rest
            }
        }
        tab[y][x]='o';
        return true;
    };

    while ( drop(500,0) ) {
        // show();
    }
    ans = count_o( tab );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
