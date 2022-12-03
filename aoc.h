#ifndef AOC_H
#define AOC_H
#include <fstream>
#include <iostream>
#include <string>

namespace aoc{
    void test_enable();
    void test_disable();
    bool is_test_enabled();
    void run();
    namespace YEAR{
        void Title();
        void year();
        namespace DAY{
            void day();
            void Task_1( std::istream&  );
            void Task_2( std::istream&  );
        }
    }
}

#endif // AOC_H
