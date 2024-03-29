//---------------------------------------------------------------------------//
#include "day_23.h"

//---------------------------------------------------------------------------//
int main ( ) {
    aoc::year_2021::day_23::Task_1();
    aoc::year_2021::day_23::Task_2();
}

//---------------------------------------------------------------------------//
/*
A - 1
B - 10
C - 100
D - 1000


.......
  B A
  A B

    B......
      . A
      A B

        BA.....
          . .
          A B

            .......
              A B
              A B

        B..A...
          . .
          A B

            .......
              A B
              A B

        B....A.
          . .
          A B

            .......
              A B
              A B

        B.....A
          . .
          A B

            .......
              A B
              A B

    .B.....
      . A
      A B

        .B.A...
          . .
          A B

            .......
              A B
              A B

    ...B...
      . A
      A B

        ...B.A.
          . .
          A B

        ...B..A
          . .
          A B

    .....B.
      . A
      A B

    ......B
      . A
      A B

  ...........
    A C A C
    B D B D

  uint64t 3x"..............." game state
  Jedno pole zapisujemy na trzech bitach
      0b000 - '.'
      0b001 - 'A'
      0b010 - 'B'
      0b011 - 'C'
      0b100 - 'D'

            000 000 --- 000 --- 000 --- 000 --- 000 000
                    000     000     000     000
                    000     000     000     000
                    [A]     [B]     [C]     [D]

  Cala plansza miesci sie na 45bitach
*/
