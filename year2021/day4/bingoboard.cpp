
#include "bingoboard.h"
#include <iomanip>

//---------------------------------------------------------------------------//
BingoBoard::BingoBoard() {

}

//---------------------------------------------------------------------------//
void BingoBoard::setBoardFrom ( std::string str ) {
    std::stringstream ss ( str );
    int v;
    _board.clear();
    while ( ss >> v ) {
        _board.insert ( _board.end(), v );
    }
}

//---------------------------------------------------------------------------//
void BingoBoard::mark ( int value ) {
    if ( _enabled ) {
        for ( auto& cell : _board ) {
            if ( cell == value ) {
                cell = -cell - 1; // marked number
                _last_move = value;
            }
        }
    }
}

//---------------------------------------------------------------------------//
bool BingoBoard::wins() {
    if ( !_enabled ) return false;

    if ( !_board.size() ) return false;

    for ( int i = 0; i < 5; i ++ ) {
        if ( ( _board[0 + i * 5] < 0 )
                && ( _board[1 + i * 5] < 0 )
                && ( _board[2 + i * 5] < 0 )
                && ( _board[3 + i * 5] < 0 )
                && ( _board[4 + i * 5] < 0 ) ) {
            return true;
        }
    }
    for ( int i = 0; i < 5; i++ ) {
        if (    _board[0 * 5 + i] < 0 &&
                _board[1 * 5 + i] < 0 &&
                _board[2 * 5 + i] < 0 &&
                _board[3 * 5 + i] < 0 &&
                _board[4 * 5 + i] < 0 ) {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------//
void BingoBoard::show() {
    int i = 0;
    for ( auto v : _board ) {
        i++;
        std::cout << std::setw ( 4 ) << v;
        if ( i == 5 ) {
            std::cout << "\n";
            i = 0;
        }
    }
    std::cout << "\n";
}

//---------------------------------------------------------------------------//
int BingoBoard::last_move() {
    return _last_move;
}

//---------------------------------------------------------------------------//
int BingoBoard::score() {
    int sum = 0;
    for ( auto v : _board ) {
        if ( v > 0 ) {
            sum += v;
        }
    }
    return sum * _last_move;
}
//---------------------------------------------------------------------------//
void BingoBoard::reset() {
    for ( auto& cell : _board ) {
        if ( cell < 0 ) {
            cell = -cell - 1; // unmark number
            _last_move = -1;
        }
    }
}

//---------------------------------------------------------------------------//
void BingoBoard::setEnabled ( bool enabled ) {
    _enabled = enabled;
}

//---------------------------------------------------------------------------//
bool BingoBoard::enabled() {
    return _enabled;
}

//---------------------------------------------------------------------------//
