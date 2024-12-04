#include "day"
#include "bingoboard.h"
//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {
//---------------------------------------------------------------------------//
// Test data
std::string testinput (
    R"(7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7)" );

inline std::istream& test_input() {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );;
}

//---------------------------------------------------------------------------//
// Play bingo on all boards
std::vector<BingoBoard*> play ( std::vector<int> numbers, std::vector<BingoBoard>& boards ) {
    std::vector<BingoBoard*> ret;
    for ( auto n : numbers ) {
        for ( auto& board : boards ) {
            board.mark ( n );
            if ( board.wins() ) {
                board.setEnabled ( false );
                ret.push_back ( &board );
            }
        }
    }
    return ret;
}

//---------------------------------------------------------------------------//
// Read numbers data form file
std::vector<int> parseNumbers ( std::istream& fs ) {
    std::vector<int> numbers{};
    std::string line;
    std::getline ( fs, line );
    std::stringstream ss ( line );
    while ( ss.good() ) {
        char c;
        int v;
        ss >> v;
        numbers.push_back ( v );
        ss >> c;
    }
    return numbers;
}

//---------------------------------------------------------------------------//
// Read boards data form file
std::vector<BingoBoard> parseBoards ( std::istream& fs ) {
    std::string line;
    std::vector<BingoBoard> boards;

    while ( fs.good() ) {
        if ( std::getline ( fs, line ) ) {
            if ( line.empty() ) {
                std::string l, s;
                for ( int i = 0; i < 5; i++ ) {
                    std::getline ( fs, l );
                    s += l + " ";
                }
                //std::cout << s << "\n";
                BingoBoard board;
                board.setBoardFrom ( s );
                boards.push_back ( board );
            }
        }
    }
    return boards;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    //aoc::test_enable();
    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto numbers = parseNumbers ( file );
    auto boards = parseBoards ( file );
    auto win = play ( numbers, boards );
    // first winning board
    OUT ( win.front()->score() );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input() : puzzle_input;

    auto numbers = parseNumbers ( file );
    auto boards = parseBoards ( file );
    auto win = play ( numbers, boards );
    // last winning board
    OUT ( win.back()->score() );
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
