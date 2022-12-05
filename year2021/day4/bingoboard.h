#ifndef BINGOBOARD_H
#define BINGOBOARD_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class BingoBoard {
    std::vector<int> _board;
    int _last_move = -1;
    bool _enabled = true;
public:
    BingoBoard();
    void setBoardFrom ( std::string str );
    void mark ( int value );
    bool wins();
    void show();
    int  last_move();
    int  score();
    void reset();
    void setEnabled ( bool enabled );
    bool enabled();
};

#endif // BINGOBOARD_H
