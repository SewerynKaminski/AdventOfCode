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
    R"(Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
Valve BB has flow rate=13; tunnels lead to valves CC, AA
Valve CC has flow rate=2; tunnels lead to valves DD, BB
Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
Valve EE has flow rate=3; tunnels lead to valves FF, DD
Valve FF has flow rate=0; tunnels lead to valves EE, GG
Valve GG has flow rate=0; tunnels lead to valves FF, HH
Valve HH has flow rate=22; tunnel leads to valve GG
Valve II has flow rate=0; tunnels lead to valves AA, JJ
Valve JJ has flow rate=21; tunnel leads to valve II)"
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
struct Room {
    int name;
    int rate;
    std::vector<int> rooms;
    int distance;
};

void permute( std::string s, uint n, std::function<void(std::string)> f ) {
    for ( auto i=n; i<s.size(); i++ ) {
        std::swap ( s[i], s[n] );
        if ( n+1 < s.size() ) {
            permute( s, n+1, f );
        } else {
            f( s );
        }
    }
}

void clear_distance( std::unordered_map<int, Room>& rooms ) {
    for ( auto& r: rooms ) {
        r.second.distance = -1;
    }
}
//---------------------------------------------------------------------------//
int find ( std::unordered_map<int, Room>& rooms, int start, int end, int n=0 ) {
    if ( rooms[start].distance==-1 ) rooms[start].distance = n;
    if ( start==end ) {
        rooms[end].distance = n;
        return n;
    }
    for ( auto r : rooms[start].rooms ) {
        if ( rooms[r].distance==-1 || rooms[r].distance > n) {
            rooms[r].distance = n;
            find ( rooms, r, end, n+1 );
        }
    }
    return rooms[end].distance;
};

//---------------------------------------------------------------------------//
std::vector<int> generate_distance_table( std::unordered_map<int, Room>& rooms ) {
    std::cout << "generate\n";
    std::vector<int> tab;
    for ( auto& r1 : rooms ) {
        //std::cout << ".\n";
        if ( r1.second.rate==0 && r1.first!=*(uint16_t*)"AA" ) continue;
        for ( auto& r2 : rooms ) {
            if ( r2.second.rate==0 && r2.first!=*(uint16_t*)"AA" ) continue;
            //std::cout << (char*)&r1.first << "-" << (char*)&r2.first << " ";
            clear_distance( rooms );
            auto l = find( rooms, r1.first, r2.first );
            tab.push_back ( l );
            //std::cout << r2.second.distance << " ";
        }
        //std::cout << "\n";
    }
    //std::cout << "\n";
    return tab;
}

int traverse ( std::unordered_map<int, Room>& rooms, int from, int b, int t, int v = 0 ) {
    int max = v;
    if ( t > 0 ) {
        for ( auto r : rooms[b].rooms ) {
            if ( from != r || rooms[b].rooms.size()==1 ) {
                max = std::max(traverse( rooms, b, r, t-1, v ), max );
                if ( rooms[r].rate  ) {
                    auto rate = rooms[r].rate;
                    rooms[r].rate = 0;
                    max = std::max(traverse( rooms, b, r, t-2, v + (t-2) * rate), max );
                    rooms[r].rate = rate;
                }
            }
        }
    }
    return max;
}

int traverse2 ( std::unordered_map<int, Room>& rooms, int f1, int f2, int b1, int b2, int t1, int t2, int v = 0 ) {
    int max = v;
    if ( t1 > 0 || t2 > 0 ) {
        for ( auto r1 : rooms[b1].rooms ) {
            for ( auto r2 : rooms[b2].rooms ) {
                if ( r1>r2 && f1!=b1 && f2!=b2 ) {
                    auto rate1 = rooms[r1].rate;
                    auto rate2 = rooms[r2].rate;
                    if ( t1<0 ) rate1=0;
                    if ( t2<0 ) rate2=0;
                            max = std::max( traverse2( rooms, b1, b2, r1, r2, t1-1, t2-1, v ), max );
                        if ( rate1 && rate2==0 ) {
                            rooms[r1].rate = 0;
                            max = std::max( traverse2( rooms, b1, b2, r1, r2, t1-2, t2-1, v+(t1-2)*rate1 ), max );
                            rooms[r1].rate = rate1;
                        }else
                        if ( rate1==0 && rate2 ) {
                            rooms[r2].rate = 0;
                            max = std::max( traverse2( rooms, b1, b2, r1, r2, t1-1, t2-2, v+(t2-2)*rate2 ), max );
                            rooms[r2].rate = rate2;
                        }else
                        if ( rate1 && rate2 ) {
                            rooms[r1].rate = 0;
                            rooms[r2].rate = 0;
                            max = std::max( traverse2( rooms, b1, b2, r1, r2, t1-2, t2-2, v+(t1-2)*rate1+(t2-2)*rate2 ), max );
                            rooms[r1].rate = rate1;
                            rooms[r2].rate = rate2;
                        }
                }
            }
        }
    }
    return max;
}

const int AA = *(uint16_t*)"AA";

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::unordered_map<int, Room> rooms;
    std::string line;
    std::string t, str_room, str_rate;
    int room;
    while ( getline(file, line) ) {
        Room r;
        std::stringstream ss(line);
        ss >> t >> str_room >> t >> t >> str_rate >> t >> t >> t >> t;
        r.name = *(uint16_t*)str_room.data();
        r.rate = stoi(str_rate.substr(5));
        while ( ss >> str_room ) {
            room = *(uint16_t*)str_room.data();
            r.rooms.push_back(room);
        }
        rooms[r.name] = r;
    }

    /*
     * Example
     * AA rate=0;  DD, II, BB
     * BB rate=13; CC, AA
     * CC rate=2;  DD, BB
     * DD rate=20; CC, AA, EE
     * EE rate=3;  FF, DD
     * HH rate=22; GG
     * JJ rate=21; II
     *
     *     B13 - C2
     *     |     |
     *     A0 - D20 - E3 - F0 - G0 - H22
     *     |
     *     I0
     *     |
     *     J21
     *
    */

    ans = traverse( rooms, 0, AA, 30 );

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ull;

    aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::unordered_map<int, Room> rooms;
    std::string line;
    std::string t, str_room, str_rate;
    int room;
    while ( getline(file, line) ) {
        Room r;
        std::stringstream ss(line);
        ss >> t >> str_room >> t >> t >> str_rate >> t >> t >> t >> t;
        r.name = *(uint16_t*)str_room.data();
        r.rate = stoi(str_rate.substr(5));
        while ( ss >> str_room ) {
            room = *(uint16_t*)str_room.data();
            r.rooms.push_back(room);
        }
        rooms[r.name] = r;
    }

    ans = traverse2( rooms, 0, 0, AA, AA, 26, 26 );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//

