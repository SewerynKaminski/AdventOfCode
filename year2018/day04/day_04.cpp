#include <day>

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
std::istringstream test_input{
R"([1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up
)"};

//---------------------------------------------------------------------------//
struct S {
    int64_t time_stamp;
    int id;
};

//---------------------------------------------------------------------------//
auto load ( ::std::istream& file ) {
    ::std::vector<S> ret;
    ::std::string line;
    while( std::getline ( file, line ) ) {
        std::istringstream l(line);
        int y, m, d, hh, mm; int id;
        ::std::string s;
        char c; // [1518-06-01 00:41]
        l >> c >> y >> c >> m >> c >> d >> hh >> c >> mm >> c >> c >> s >> s;
        int64_t time_stamp = (((m*32+d)*24+hh)*60+mm);
        if ( c=='w' ) {
            //std::cout << time_stamp << " -1 " <<'\n';
            id = -1;
        }
        if ( c=='f' ) {
            //std::cout << time_stamp << " -2 " <<'\n';
            id = -2;
        }
        if ( c=='G' ) {
            id = std::stoi ( &s[1] );
            //std::cout << time_stamp << " " << id <<'\n';
        }

        ret.push_back ( { time_stamp, id } );
    }
    std::sort( ret.begin(), ret.end(), [](const S& a, const S& b){ return a.time_stamp < b.time_stamp; });
    return ret;
}

constexpr int WAKEUP=-1;
constexpr int ASLEEP=-2;

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;

    auto data = load ( file );
    auto ans = 0ull;

    //std::unordered_map<int,uint64_t> guard;
    std::unordered_map<int,std::array<int,60>> guard;
    int id=0;
    int64_t sleep=0;
    for ( const auto& r : data ) {
        if ( r.id > -1 ) {
            id = r.id;
        } else {
            if ( r.id==ASLEEP ) { sleep = r.time_stamp; }
            if ( r.id==WAKEUP ) {
                for ( int i=sleep%60; i < r.time_stamp%60; i++ ) {
                    guard[id][i]++;
                }
            }
        }
    }

    for ( const auto& g : guard ) {
        uint sum=0;
        for ( auto v : g.second ) sum += v;
        if ( ans < sum ) {
            ans = sum;
            id = g.first;
        }
    }
    int m=0;
    for ( int i=0; i<60; i++ ) {
        if ( m < guard[id][i] ) {
            m = guard[id][i];
            ans = i;
        }
    }
    ans*=id;
    OUT(ans);
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input : puzzle_input;

    auto data = load ( file );
    auto ans = 0ull;

    std::unordered_map<int,std::array<int,60>> guard;
    int id=0;
    int64_t sleep=0;
    for ( const auto& r : data ) {
        if ( r.id > -1 ) {
            id = r.id;
        } else {
            if ( r.id==ASLEEP ) { sleep = r.time_stamp; }
            if ( r.id==WAKEUP ) {
                auto m_end = r.time_stamp%60;
                for ( int m=sleep%60; m < m_end; m++ ) guard[id][m]++;
            }
        }
    }

    int min_max=0;
    for ( auto g : guard ) {
        auto id = g.first;
        auto minutes = g.second;
        for ( uint i=0; i<60; i++ ) {
            if ( min_max < minutes[i] ) {
                min_max = minutes[i];
                ans = i * id;
            }
        }
    }

    OUT(ans);
}
//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
