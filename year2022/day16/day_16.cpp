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
    int opening_time=0;
};

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

int traverse2 ( std::unordered_map<int, Room>& rooms, int f1, int f2, int b1, int b2, int t, bool open1, bool open2 ) {
    static int max = 0;
    if ( t<=0 ) {
        int sum=0;
        for ( auto& [key, r] : rooms ) {
            //if ( r.opening_time>0 )
            sum += (r.opening_time-1)*r.rate;
        }
        max = std::max( max, sum );
        //std::cout << max << " ";
    }
    if ( t > 0 ) {
        auto o1 = rooms[b1].opening_time;
        auto o2 = rooms[b2].opening_time;
        //open1 = o1==0 && rooms[b1].rate;
        //open2 = o2==0 && rooms[b2].rate;
        if ( open1 && !open2 ) {
            rooms[b1].opening_time = std::max( t, o1 );
            for ( auto r2 : rooms[b2].rooms ) {
                traverse2( rooms, b1, b2, b1, r2, t-1, false, false );
            }
            rooms[b1].opening_time = o1;
        } else if( !open1 && open2 ){
            rooms[b2].opening_time = std::max( t, o2 );
            for ( auto r1 : rooms[b1].rooms ) {
                traverse2( rooms, b1, b2, r1, b2, t-1, false, false );
            }
            rooms[b2].opening_time = o2;
        }/* else if ( open1 && open2 ) {
            rooms[b1].opening_time = std::max( t, o1 );
            rooms[b2].opening_time = std::max( t, o2 );
            traverse2( rooms, b1, b2, b1, b2, t-1, false, false );
            rooms[b1].opening_time = o1;
            rooms[b2].opening_time = o2;
        }*/else
        for ( auto r1 : rooms[b1].rooms ) {
            for ( auto r2 : rooms[b2].rooms ) {
                if ( (f1!=r1 || rooms[b1].rooms.size()==1) && (f2!=r2|| rooms[b2].rooms.size()==1) ) {
                    auto o1 = rooms[r1].opening_time;
                    auto o2 = rooms[r2].opening_time;

                    //traverse2( rooms, b1, b2, r1, r2, t-1, false, false );
                    if ( (o1 || rooms[r1].rate==0) && (o2 || rooms[r1].rate==0) ) {
                        traverse2( rooms, b1, b2, r1, r2, t-2, false, false );
                    }
                    if ( !o1 && rooms[r1].rate && !o2 && rooms[r1].rate ) {
                        traverse2( rooms, b1, b2, r1, r2, t-1, true, true );
                    }
                    if( !o1 && rooms[r1].rate ) {
                        traverse2( rooms, b1, b2, r1, r2, t-1, false, false );
                        traverse2( rooms, b1, b2, r1, r2, t-1, true, false );
                    }
                    if( !o2 && rooms[r2].rate ) {
                        traverse2( rooms, b1, b2, r1, r2, t-1, false, false);
                        traverse2( rooms, b1, b2, r1, r2, t-1, false, true);
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

    ans = traverse2( rooms, 0, 0, AA, AA, 26, false, false );

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//

