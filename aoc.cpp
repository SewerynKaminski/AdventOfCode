#include "defines"
#include "aoc.h"

namespace aoc {
//---------------------------------------------------------------------------//
bool t = false;

//---------------------------------------------------------------------------//
void test_enable() {
    t = true;
}

//---------------------------------------------------------------------------//
void test_disable() {
    t = false;
}

//---------------------------------------------------------------------------//
bool is_test_enabled() {
    return t;
}

//---------------------------------------------------------------------------//
void run ( ) {
    std::ifstream f;
    YEAR::Title();
    test_disable();
    f.open ( "../input" );
    YEAR::DAY::Task_1 ( f );
    f.close();
    test_disable();
    f.open ( "../input" );
    YEAR::DAY::Task_2 ( f );
    f.close();
}

//---------------------------------------------------------------------------//
//template<typename T>
//void out ( const T& a ) {
//    std::cout << __FUNCTION__ << ( aoc::is_test_enabled() ? "(TEST)" : "" ) << ": " << a << "\n";
//}

//---------------------------------------------------------------------------//
void YEAR::DAY::day ( ) {
    std::cout << "Day "
              << std::string_view ( S ( DAY ) ).substr ( 4 )
              << "\n";
}

//---------------------------------------------------------------------------//
void YEAR::Title ( ) {
    year();
    DAY::day();
}

//---------------------------------------------------------------------------//
void YEAR::year ( ) {
    std::cout << "Year "
              << std::string_view ( S ( YEAR ) ).substr ( 5 )
              << " - ";
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
