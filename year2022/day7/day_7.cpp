#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"($ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k)" );

//---------------------------------------------------------------------------//
inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
struct Info {
    std::string name;
    bool isDir = false;
    uint64_t size = 0;
};

//---------------------------------------------------------------------------//
std::string getPath ( std::string s ) {
    return s.substr ( 0, s.find_last_of ( "/" ) + 1 );
}

//---------------------------------------------------------------------------//
auto listFiles ( std::istream& file ) {
    std::string line, path;
    std::list<Info> list { Info { "/", true,  0 } };

    // build files and dirs list
    while ( getline ( file, line ) ) {
        if ( line.starts_with ( "$ cd " ) ) {
            switch ( line[5] ) {
            case '/':
                path = "/";
                break;
            case '.':
                path = getPath ( path.substr ( 0, path.length() - 1 ) );
                break;
            default:
                path += line.substr ( 5 ) + "/";
            }
        } else if ( line.starts_with ( "$ ls" ) ) {
            // ?
        } else {
            std::stringstream ssi ( line );
            std::string name;
            uint64_t size;
            if ( line.starts_with ( "dir" ) ) {
                ssi >> name >> name;
                list.push_back ( { path + name + "/", true, 0 } );
            } else {
                ssi >> size >> name;
                list.push_back ( { path + name, false, size } );
            }
        }
    }

    // count dir sizes
    list.reverse();
    for ( auto& s : list ) {
        std::string path = s.name;
        if ( s.isDir ) {
            //path = s.name.substr ( 0, s.name.length() - 1 );
            path = path.substr ( 0, path.length() - 1 );
        }
        path = getPath ( path );

        for ( auto& it : list ) {
            if ( it.isDir && it.name == path ) {
                it.size += s.size;
            }
        }
    }

    return list;
}


//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto list = listFiles ( file );

    for ( auto& s : list ) {
        if ( s.isDir && s.size <= 100000  ) {
            ans += s.size;
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto ans = 0ull;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto list = listFiles ( file );

    constexpr size_t TOTAL_SPACE = 70000000;
    constexpr size_t NEEDED_FREE_SPACE = 30000000;
    size_t free_space = TOTAL_SPACE - list.back().size;

    ans = TOTAL_SPACE;
    for ( auto& s : list ) {
        if ( s.isDir && ( free_space + s.size ) >= NEEDED_FREE_SPACE && s.size < ans ) {
            ans = s.size;
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
