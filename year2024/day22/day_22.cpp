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
    R"(        ...#
        .#..
        #...
        ....
...#.......#
........#...
..#....#....
..........#.
        ...#....
        .....#..
        .#......
        ......#.

10R5L5R10L4R5L5)"
};

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//

std::pair<std::string, std::vector<std::string>> parse( std::istream& ss ){
    std::vector<std::string> board;
    std::string line;
    while( getline(ss,line) ) {
        if ( line.empty() ) break;
        board.push_back ( line );
    }
    getline ( ss, line );
    return { line, board };
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ll;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    auto r = parse( file );
    std::string path = r.first;
    std::vector<std::string> board = r.second;

    auto getBoard = [&board]( int x, int y ) -> char {
        if ( (int)board.size() > y && (int)board[y].size() > x && x >= 0 && y >= 0 ) {
                return board[y][x];
        }
        return ' ';
    };

    int x=0, y=0, d=0;
    x = board[y].find_first_of('.');

    std::stringstream l(path);
    int steps;
    char c;

    while ( l ) {
        l >> steps;
        while ( steps ) {
            if ( d == 0 ) {     // right
                auto cc = getBoard ( x+1, y );
                if ( cc!=' ' ) {
                    if ( cc=='.' ) {
                        x++;
                    }
                    if ( cc=='#' ) {
                        break;
                    }
                } else {
                    auto nx = board[y].find_first_not_of(' ');
                    if ( getBoard(nx,y) == '#' ) {
                        break;
                    }
                    x = nx;
                }
            }
            else if ( d == 1 ) {    // down
                auto cc = getBoard( x, y + 1);
                if ( cc != ' ' ) {
                    if ( cc == '.' ) {
                        y++;
                    }
                    if ( cc=='#' ) {
                        break;
                    }
                } else {
                    auto ny = 0;
                    while ( getBoard ( x, ny )==' ' ) {
                       ny++;
                    }
                    if ( getBoard ( x, ny )=='.' ) {
                        y = ny;
                    }
                }
            }
            else if ( d == 2 ) {    // left
               auto cc = getBoard ( x-1, y );
               if ( cc!=' ' ) {
                   if ( cc=='.' ) {
                       x--;
                   }
                   if ( cc=='#' ) {
                       break;
                   }
               } else {
                   auto nx = board[y].size()-1;
                   if ( getBoard(nx,y) == '#' ) {
                       break;
                   }
                   x = nx;
               }

            }
            else if ( d == 3 ) {    // up
                auto cc = getBoard( x, y - 1);
                if ( cc != ' ' ) {
                    if ( cc == '.' ) {
                       y--;
                    }
                    if ( cc=='#' ) {
                       break;
                    }
                } else {
                    auto ny = board.size()-1;
                    while ( getBoard ( x, ny )==' ' ) {
                        ny--;
                    }
                    if ( getBoard ( x, ny )=='.' ) {
                        y = ny;
                    }
               }

            }
            steps--;
        }

        if ( l >> c ) {
            if ( c=='R' ) d = (d+1)%4;
            if ( c=='L' ) d = (d+3)%4;
        }
    }

    ans = 1000 * (y+1) + 4 * (x+1) + d;

    OUT ( ans );
}

//---------------------------------------------------------------------------//
template<class T>
inline T sign ( T v ) {
    return ( T(0) < v ) - ( T(0) < v );
}
struct Point2{ int x,y;};
struct Point3{ int x,y,z;
        Point3 operator -(){
            return Point3{-x,-y,-z};
    }
    };

struct Face{
    Point3 X;
    Point3 Y;
};

Point3 face00_1_2d_to_3d ( const Point2& p ) {
    // D [00-1]    [ p.x  p.y ]  <- [ X Y-1]   [ X -Y -1 ]
    return { p.x, -p.y, -1 };
}

Point3 face010_2d_to_3d ( const Point2& p ) {
    //A [010]     [ X -Z ]  <- [ X 1 Z]   [ X -Y -1 ] > [ X  1 -Y ]
    return { p.x, 1, -p.y };
}

int face_id ( Point3 p ) {   // return value from 0 to 5
    return (p.x + 3*p.y + 5*p.z + 5) / 2;
}

int calculate_cube_edge_size( const std::vector<std::string>& tab ) {
    int size=0;
    for ( const std::string& s : tab ) {
        for( auto c : s ) {
            size += c!=' ';
        }
    }
    return sqrt(size/6);
}

std::ostream& operator << ( std::ostream& o, const Point3& p ) {
    o << '{' << p.x << ',' <<p.y << ',' << p.z << '}';
    return o;
}

std::ostream& operator << ( std::ostream& o, const Point2& p ) {
    o << '{' << p.x << ',' <<p.y << '}';
    return o;
}

//---------------------------------------------------------------------------//
void turn_right ( Point3 &dir, Point3& face ) {
    dir = { face.y*dir.z-face.z*dir.y, -face.x*dir.z+face.z*dir.x, face.x*dir.y-face.y*dir.x };
};

//---------------------------------------------------------------------------//
void turn_left ( Point3& dir, Point3& face ) {
    dir=-dir;
    turn_right ( dir, face );
};

//---------------------------------------------------------------------------//
void go_forward_next_face ( Point3& dir, Point3& face){
    std::swap ( dir, face );
    dir=-dir;
};

//---------------------------------------------------------------------------//
void parse_faces ( int H, int x, int y, Point2 pd2, Point3 pf, Point3 pd, const std::vector<std::string>& tab, std::unordered_map<int,Face>& faces ) {
    if ( (x<0 || y<0 || y*H>=(int)tab.size() || x*H>=(int)tab[y*H].size()) ) return;
    if ( faces.contains ( face_id(pf) ) ) return;
    if ( tab[y*H][x*H]==' ' ) return;

    Face face;
    std::cout << x << " "<< y << ' ' << pf << pd2 <<'\n';
    auto pdo  = pd;
    auto pfo  = pf;
    auto pd2o = pd2;

    while ( !(pd2.x==0 && pd2.y==1) ) {
        pd2 = {pd2.y,-pd2.x};
        turn_left ( pd, pf );
    }
    face.Y = pd;
    turn_left ( pd, pf );
    face.X = pd;
    faces [face_id(pf)] = face;
    std::cout << 'T' << x << " "<< y << ' ' << face.X << face.Y <<'\n';


    pd=pdo;
    pd2=pd2o;
    pf=pfo; go_forward_next_face( pd, pf );
    parse_faces ( H, x+pd2.x, y+pd2.y, pd2, pf, pd, tab, faces );

    turn_left ( pd, pf ); pf=pfo; pd2 = {pd2.y,-pd2.x};  go_forward_next_face( pd, pf );
    parse_faces ( H, x+pd2.x, y+pd2.y, pd2, pf, pd, tab, faces );

    turn_left ( pd, pf ); pf=pfo; pd2 = {pd2.y,-pd2.x}; go_forward_next_face( pd, pf );
    parse_faces ( H, x+pd2.x, y+pd2.y, pd2, pf, pd, tab, faces );

    turn_left ( pd, pf ); pf=pfo; pd2 = {pd2.y,-pd2.x}; go_forward_next_face( pd, pf );
    parse_faces ( H, x+pd2.x, y+pd2.y, pd2, pf, pd, tab, faces );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0ll;

    aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;
    auto data = parse( file );

    auto H = calculate_cube_edge_size ( data.second );
    std::unordered_map<int,Face> faces;
    parse_faces( H, 2, 0, {1,0},{0,0,-1},{1,0,0},data.second, faces );

    Point3 face = {0,0,-1};
    Point3 dir  = {0,1,0};

    std::cout << face << dir << '\n';
    go_forward_next_face ( dir, face );
    go_forward_next_face ( dir, face );
    turn_left ( dir, face );
    std::cout << face << dir << '\n';
    while ( false ) {
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
/*
            0,1,0
            +-----+
            |00-1 |
            |  v  |
            +-----+
    -1,0,0  0,0,-1  1,0,0   0,0,1
    +-----+ +-----+ +-----+ +-----+
    |0-10 | |0-10 | |0-10 | |0-10 |
    |  v  | |  v  | |  v  | |  v  |
    +-----+ +-----+ +-----+ +-----+
            0,-1,0
            +-----+
            |001  |
            |  v  |
            +-----+

    -1,0,0 0,0,-1 1,0,0  0,0,1      XYZ -> -ZYX

    0,-1,0     >        1,0,0       XYZ -> -YXZ

            010
            +----v+
            |     |
            |  v  |
            +^----+
    -100    00-1    100     001
    +-----+ +^----+ +-----+ +^----+
    |     | |010  | |     | |010  |
    |  v  | |  v  | |  v  | |  v  |
    +-----+ +-----+ +-----+ +-----+
            0-10
            +-----+
            |     |
            |  v  |
            +-----+

    Jestem w 001
        Ide w gore 01 do 010
        ~(010+001)=~011=100     (obrot OX)
        010 obrot w lewo 00-1   (XYZ -> XZ-Y)

    Jestem w 00-1
        Ide w gore 01 do 010
        ~(010+00-1)=~01-1=100   (obrot OX)
        010 obrot w prawo 001   (XYZ -> X-ZY)

    Jestem w 010
        Ide w prawo 10 do 100  (XYZ -> Y-XZ)
        ~(010+100)=~110=001     (obrot OZ)
        100 obrot w prawo 0-10   (XYZ -> Y-XZ)

    Jestem w 010
        Ide w gore 01 do 100  (XYZ -> XZ-Y)
        ~(010+100)=~110=001     (obrot OZ)
        100 obrot w prawo 0-10   (XYZ -> Y-XZ)



        +--+
        |A |
        +--+
+--++--++--+
|B ||C ||D |
+--++--++--+
        +--++--+
        |E ||F |
        +--++--+

A - 00-1    start
B - 010     C->B left os 001  (-100 rotZ 90 = )      -100 + 010 > 001
C - -100    D->C left os 001  (0-10 rotZ 90 = )      0-10 + 100 > 001
D - 0-10    A->D down os 100  (00-1 rotX 90 = 0-10)  00-1 + 010 > 100
E - 001     D->E down os 100 = ~(0-10 + 001)
F - 100     E->F right os 010 = ~(001 + 100)
            E->B down os 100 = ~(001 + 100) 001 rotX 90 = 010

  X Y Z     X Y Z
[-1 0 0] + [0 1 0] = [-1 1 0]

Uklad wspolzednych lokalnych na sciance 2D
        +--|--+
        |X |  |
       ----+---->OX
        |  |  |
        +--|--+
           v
           OY

0   4   8   12 15
        +--+
        |A |
        +--+
+--++--++--+
|B ||C ||D |
+--++--++--+
        +--++--+
        |E ||F |
        +--++--+
6 scianek
12 krawedzi


D [00-1]    [ X  Y ]  <- [ X Y-1]   [ X -Y -1 ]                 no rot
A [010]     [ X -Z ]  <- [ X 1 Z]   [ X -Y -1 ] > [ X  1 -Y ]   rotOX -90
C [-100]    [-Z  Y ]  <- [-1 Y Z]   [ X -Y -1 ] > [-1 -Y -X ]   rotOY -90
B [001]     [-X  Y ]  <- [ X Y 1]   [-1 -Y -X ] > [-X -Y  1 ]   rotOY -90
E [0-10]    [ X  Z ]  <- [ X-1 Z]   [ X -Y -1 ] > [ X -1  Y ]   rotOX  90
F [100]     [ Y  Z ]  <- [ 1 Y Z]   [ X -1  Y ] > [ 1  X  Y ]   rotOY  90

id = (x+3y+5z + 5)/2;

1x+3y+5z + 5=
00-1= -5+5=  0 > 0
0-10= -3+5=  2 > 1
-100= -1+5=  4 > 2
001 =  5+5= 10 > 5
010 =  3+5=  8 > 4
100 =  1+5=  6 > 3


struct Face {
    Point3 X, Y, Z;
};

Point2 convert_3d_to_2d ( const Face& face ) {
    return { p3.x*face.X.x + p3.y*face.X.y + p3.z*face.X.z,
             p3.x*face.Y.x + p3.y*face.Y.y + p3.z*face.Y.z }
}

convert_2d_to_3d ( const Face& face ) {
    return { p2.x * face.X.x + p2.y * face.Y.x + face.Z.x,
             p2.x * face.X.y + p2.y * face.Y.y + face.Z.y,
             p2.x * face.X.z + p2.y * face.Y.z + face.Z.z }
}
    // A 2d -> 3d
    // [X Y 1] * T = [X 1 -Y]
    //[X Y 1][1  0  0 ] = [ X 1 -Y]
    //       [0  0 -1 ]
    //       [0  1  0 ]
    // A 3d -> 2d
    // [X Y Z] * T' = [X -Z]
    //[X Y Z][ 1  0 ] = [ X -Z  ]
    //       [ 0  0 ]
    //       [ 0 -1 ]

    D -> F
    D: 2D->3D: [1 0] -> [1 0 -1]                [00-1]+[100]
    F: 3D-2D:  [1 0 -1] -> [0 -1]               [100]

    D: [0 1][0 -1 -1]
        X [ 1 0 0 ]*
        Y [ 0-1 0 ]*
        Z [ 0 0 1 ]
    E: [0 -1 -1] > [0 -1]
        X [ 1 0 0 ]*
        Y [ 0 0 1 ]
        Z [ 0 1 0 ]*
    F: [1 -1 -1] > [0 -1]
        X [ 1 0 0 ]
        Y [ 0 -1 0 ]*
        Z [ 0 0 -1 ]*

    D -> F
    D: 2D->3D: [0 1] -> [0 -1 -1]
    E: 3D-2D:  [0 -1 -1] -> [0 0]

    F -> B
    F: 2D->3D: [1 1] -> [1 1 1]                 [100]+[011]
    B: 3D-2D:  [1 1 1] -> [-1 -1]               [001]+[-1-10]

    F: 2D->3D: [1 -1] -> [1 1 -1]
    A: 3D-2D:  [1 1 -1] -> [1 1]

    F: 2D->3D: [1 1] -> [1 1 1]
    A: 3D-2D:  [1 1 1] -> [1 -1]

    F: 2D->3D: [1 a] -> [1 1 a]
    A: 3D-2D:  [1 1 a] -> [1 -a]

    Kierunek ruchu
    D: 3D[100] kierunek 2D[10]
    F: 3D[001] kierunek 2D[01]

    0 1 2 3 4 > (0+4)/2 = 2
        y = 2x - 4
           2x| 0 2 4 6 8
            y|-4-2 0 2 4
    x=(y+4)/2| 0 1 2 3 4
          y/2|-2-1 0 1 2
(y+sign(y))/2|-2-1 0 1 2

    0 1 2 3 > (0+3)/2 = 1.5
    y = 2x - 3
           2x| 0 2 4 6
            y|-3-1 1 3
    x=(y+3)/2| 0 1 2 3
    y+sign(y)|-4-2 2 4
(y+sign(y))/2|-2-1 1 2
*/
