//---------------------------------------------------------------------------//
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <map>
//#include <unordered_map>
//#include <vector>
//#include <ranges>
//#include <fstream>
//#include <limits>
//#include <unordered_set>
//#include <unordered_set>
//#include <iomanip>
//#include <bit>
#include <optional>

//---------------------------------------------------------------------------//
#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
struct Point3 {
    int64_t x, y, z;
    Point3& operator-= ( const Point3& b ) {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }
    Point3& operator+= ( const Point3& b ) {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    Point3& operator/= ( const int v ) {
        x /= v;
        y /= v;
        z /= v;
        return *this;
    }
    Point3& operator- (){
        x=-x;
        y=-y;
        z=-z;
        return *this;
    }
    uint64_t tou() {
        return ( uint64_t ( x ) << 22 ) ^ ( uint64_t ( y ) << 11 ) ^ uint64_t ( z );
    }
};

//---------------------------------------------------------------------------//
bool operator< ( const Point3&a, const Point3&b ) {
    return a.x + a.y + a.z < b.x + b.y + b.z;
}

//---------------------------------------------------------------------------//
bool operator== ( const Point3&a, const Point3&b ) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

//---------------------------------------------------------------------------//
Point3 operator- ( const Point3& a, const Point3& b ) {
    return Point3{a.x - b.x, a.y - b.y, a.z - b.z };
}

//---------------------------------------------------------------------------//
Point3 operator+ ( const Point3& a, const Point3& b ) {
    return Point3{a.x + b.x, a.y + b.y, a.z + b.z };
}

//---------------------------------------------------------------------------//
Point3 operator* ( const Point3& a, const Point3& b ) {
    return Point3{a.x * b.x, a.y * b.y, a.z * b.z };
}

//---------------------------------------------------------------------------//
struct Scanner {
    std::vector<Point3> beacons;
    Point3 min;
    Point3 max;
    int r=-1;
    Point3 pos{0,0,0};
};

Point3 minxyz ( const Point3& a, const Point3& b ) {
    return {std::min ( a.x, b.x ),
            std::min ( a.y, b.y ),
            std::min ( a.z, b.z ) };
}

Point3 maxxyz ( const Point3& a, const Point3& b ) {
    return {std::max ( a.x, b.x ),
            std::max ( a.y, b.y ),
            std::max ( a.z, b.z ) };
}

//---------------------------------------------------------------------------//
constexpr int INT_MAX = ( int ) ( ( unsigned int ) ( -1 ) >> 1 );
constexpr int INT_MIN = ( int ) ( ( unsigned int ) 1 << 31 );
//---------------------------------------------------------------------------//
auto load ( std::istream& fs ) {
    //std::fstream fs ( file );
    //std::vector<std::vector<Point3>> data;
    std::vector<Scanner> data;
    Point3 min, max, ctr;
    //int min_x=0, min_y=0, min_z=0;
    std::string line;
    while ( fs.good() ) {
        std::getline ( fs, line );
        //if ( line.starts_with ( "---" ) ) {
        if ( line.substr(0,3) == "---" ) {
            min.x = min.y = min.z = INT_MAX;
            max.x = max.y = max.z = INT_MIN;
            ctr.x = ctr.y = ctr.z = 0;
            //std::cout << '\n';
            data.push_back (  Scanner() );
        } else if ( !line.empty() ) {
            int64_t x, y, z;
            char c;
            std::stringstream ss ( line );
            while ( ss >> x >> c >> y >> c >> z ) {
                auto p = Point3{x, y, z};
                min = minxyz ( min, p );
                max = maxxyz ( max, p );
                ctr += p;
                //std::cout << x << "|" << y << "|" << z << '\n';
                data.back().beacons.push_back ( p );
            }
        } else {
            //data.back().min = {min_x, min_y, min_z};
            data.back().min = min;
            data.back().max = max;
        }
    }
#ifdef DEBUG

#endif

    return data;
}

Point3 rotateY90 ( Point3 p ) {
    return {p.z, p.y, -p.x};
}

Point3 rotateY_90 ( Point3 p ) {
    return {-p.z, p.y, p.x};
}

Point3 rotateX90 ( Point3 p ) {
    return {p.x, -p.z, p.y};
}

Point3 rotateX_90 ( Point3 p ) {
    return {p.x, p.z, -p.y};
}

Point3 rotateZ90 ( Point3 p ) {
    return {-p.y, p.x, p.z};
}

Point3 rotate ( int r, Point3 d ) {
    switch ( r ) {
    case 0:
        return { d.x,  d.y,  d.z};
        break;
    case 1:
        return { d.x,  d.z, -d.y};
        break;
    case 2:
        return { d.x, -d.y, -d.z};
        break;
    case 3:
        return { d.x, -d.z,  d.y}; // left
        break;
    case 4:
        return {-d.y, d.x, d.z};
        break;
    case 5:
        return { d.z, d.x,  d.y};
        break;
    case 6:
        return { d.y, d.x, -d.z};
        break;
    case 7:
        return {-d.z, d.x, -d.y}; // top
        break;
    case 8:
        return {-d.x, -d.y,  d.z};
        break;
    case 9:
        return {-d.x,  d.z,  d.y};
        break;
    case 10:
        return {-d.x,  d.y, -d.z};
        break;
    case 11:
        return {-d.x, -d.z, -d.y}; // right
        break;
    case 12:
        return { d.y, -d.x, d.z};
        break;
    case 13:
        return { d.z, -d.x, -d.y};
        break;
    case 14:
        return {-d.y, -d.x, -d.z};
        break;
    case 15:
        return {-d.z, -d.x, d.y}; // bottom
        break;
    case 16:
        return {-d.z,  d.y, d.x};
        break;
    case 17:
        return { d.y, d.z,  d.x};
        break;
    case 18:
        return { d.z, -d.y,  d.x};
        break;
    case 19:
        return {-d.y, -d.z,  d.x}; // back
        break;
    case 20:
        return { d.z,  d.y, -d.x};
        break;
    case 21:
        return { d.y, -d.z, -d.x};
        break;
    case 22:
        return {-d.z, -d.y, -d.x};
        break;
    case 23:
        return {-d.y,  d.z, -d.x}; // front
        break;
    }
    return d;
}

Point3 rotate2 ( int r, Point3 d ) {
    switch ( r ) {
    case 0:
        return { d.x,  d.y,  d.z}; // no rotation
        break;
    case 1:
        return { d.x,  d.z, -d.y}; //
        break;
    case 2:
        return { d.x, -d.y, -d.z};
        break;
    case 3:
        return { d.x, -d.z,  d.y}; // left
        break;
    case 4:
        return {-d.x,  d.z,  d.y};
        break;
    case 5:
        return {-d.x,  d.y, -d.z};
        break;
    case 6:
        return {-d.x, -d.z, -d.y};
        break;
    case 7:
        return {-d.x, -d.y,  d.z}; // right
        break;
    case 8:
        return {-d.y,  d.x,  d.z};
        break;
    case 9:
        return {-d.y,  d.z, -d.x};
        break;
    case 10:
        return {-d.y, -d.x, -d.z};
        break;
    case 11:
        return {-d.y, -d.z,  d.x};; // top
        break;
    case 12:
        return { d.y,  -d.x,  d.z};
        break;
    case 13:
        return { d.z,  -d.x, -d.y};
        break;
    case 14:
        return {-d.y,  -d.x, -d.z};
        break;
    case 15:
        return {-d.z,  -d.x,  d.y}; // bottom
        break;
    case 16:
        return {-d.z,  d.y,  d.x};
        break;
    case 17:
        return { d.y,  d.z,  d.x};
        break;
    case 18:
        return { d.z, -d.y,  d.x};
        break;
    case 19:
        return {-d.y, -d.z,  d.x}; // back
        break;
    case 20:
        return { d.z,  d.y, -d.x};
        break;
    case 21:
        return { d.y, -d.z, -d.x};
        break;
    case 22:
        return {-d.z, -d.y, -d.x};
        break;
    case 23:
        return {-d.y,  d.z, -d.x}; // front
        break;
    }
    return d;
}

int compare_scanners ( std::vector<Point3>& s1, std::vector<Point3>& s2 ) {
    int meq = 0, eq = 0;
    for ( size_t i1 = 0; i1 < s1.size() ; i1++ ) {
        for ( auto r=0; r<24; r++ ) {
            eq = 0;
            for ( size_t i2 = 0; i2 < s2.size() ; i2++ ) {
                if ( s1[i1] == rotate ( r, s2[i2] ) ) {
                    eq++;
                }
            }
            meq = std::max ( meq, eq );
        }
        //   std::cout << eq << '\n';
    }
    return meq;
}


inline Point3 Rr ( int r, Point3 d ) {
    //if ( r == 0 ) return { d.x, d.y, d.z };
    if ( r == 1 ) return { d.y, d.z, d.x };
    if ( r == 2 ) return { d.z, d.x, d.y };
    return d;
}

Point3 R ( int r, Point3 p ) {
    Point3 d = p;

    d = rotateY_90 ( d );
    if ( r < 3 ) return Rr ( r, d );
    d = rotateY_90 ( d );
    if ( r < 6 ) return Rr ( r - 3, d );
    d = rotateX90 ( d );
    if ( r < 9 ) return Rr ( r - 6, d );
    d = rotateX90 ( d );
    if ( r < 12 ) return Rr ( r - 9, d );
    d = rotateY90 ( d );
    if ( r < 15 ) return Rr ( r - 12, d );
    d = rotateY90 ( d );
    if ( r < 18 ) return Rr ( r - 15, d );
    d = rotateX_90 ( d );
    if ( r < 21 ) return Rr ( r - 18, d );
    d = rotateX_90 ( d );
    if ( r < 24 ) return Rr ( r - 21, d );

    return p;
}

inline bool cmp0 ( Point3& p1, Point3& d ) {
    return p1.x == d.x && p1.y == d.y && p1.z == d.z;
}
inline bool cmp1 ( Point3& p1, Point3& d ) {
    return p1.x == d.y && p1.y == d.z && p1.z == d.x;
}
inline bool cmp2 ( Point3& p1, Point3& d ) {
    return p1.x == d.z && p1.y == d.x && p1.z == d.y;
}
std::ostream& operator <<(std::ostream& o, Point3 p){
    return o << '{'<< p.x <<',' << p.y <<','<< p.z << '}';
}


std::tuple<bool, int> cmp ( Point3 p1, Point3 p2 ) {
    Point3 d = p2;
    //std::cout << 0;
    /*for ( auto r : Range ( 0, 24 ) ) {
        auto dd = R ( r, p2 );
        if ( p1 == dd ) return {true, r};
    }
    return {false, -1};*/
    d = rotateY_90 ( d );
    //std::cout << 1;
    if ( cmp0 ( p1, d ) ) return {true, 0};
    if ( cmp1 ( p1, d ) ) return {true, 1};
    if ( cmp2 ( p1, d ) ) return {true, 2};
    d = rotateY_90 ( d );
    //std::cout << 2;
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 3};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 4};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 5};
    d = rotateX90 ( d );
    //std::cout << 3;
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 6};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 7};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 8};
    d = rotateX90 ( d );
    //std::cout << 4;
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 9};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 10};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 11};
    d = rotateY90 ( d );
    //std::cout << 5;
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 12};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 13};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 14};
    d = rotateY90 ( d );
    //std::cout << 6;
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 15};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 16};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 17};
    d = rotateX_90 ( d );
    //std::cout << 7;
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 18};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 19};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 20};
    d = rotateX_90 ( d );
    if ( p1.x == d.x && p1.y == d.y && p1.z == d.z ) return {true, 21};
    if ( p1.x == d.y && p1.y == d.z && p1.z == d.x ) return {true, 22};
    if ( p1.x == d.z && p1.y == d.x && p1.z == d.y ) return {true, 23};
    return {false, -1};
}

void check_scanner_pair ( std::vector<std::vector<Point3>>& data, int s1, int s2 ) {
    int sum;
    for ( size_t j = 0; j < data[s2].size() ; j++ ) {
        for ( size_t i = 0; i < data[s1].size() ; i++ ) {
            auto vs1 = data[s1];
            for ( auto& p : vs1 ) {
                p -= data[s1][i];
            }
            auto vs2 = data[s2];
            for ( auto& p : vs2 ) {
                p -= data[s2][j];
            }

            sum = 0;
            int r = -1;
            for ( size_t ii=0ul; ii< vs1.size(); ii++ ) {
                for ( size_t jj=0ul; jj <vs2.size(); jj++ ) {
                    auto [s, rot] = cmp ( vs1[ii], vs2[jj] );
                    if ( s ) {
                        sum++;
                        r = rot;
                        if ( sum == 12 ) {
                            std::cout << s1 << ' ' << s2 << ' ' << r << ' ' << sum << '\n';
                            std::cout << vs1[i].x << vs1[i].y << vs1[i].z << ' ' << vs2[j].x << vs2[j].y << vs2[j].z << '\n';
                            std::cout << data[s1][i].x << data[s1][i].y << data[s1][i].z << ' ' << data[s2][j].x << data[s2][j].y << data[s2][j].z << '\n';
                            auto p = R ( rot, data[s2][j] );
                            p = data[s1][i] - p;
                            std::cout << rot << " Pos " << s2 << ':' << p.x << ',' << p.y << ',' << p.z << '\n';

                            auto [s, rot] = cmp ( vs2[j], vs1[i] );

                            std::cout << rot << " Pos " << s1 << ':' << p.x << ',' << p.y << ',' << p.z << '\n';
                        }
                    }
                }
            }
            if ( sum >= 12 ) {
                /*std::cout << s1 << ' ' << s2 << ' ' << r << ' ' << sum << '\n';
                std::cout << '\n' << s1 << ':';
                for ( auto p : data[s1] ) {
                    std::cout << '(' << p.x << ',' << p.y << ',' << p.z << "), ";
                }
                std::cout << '\n';
                for ( auto p : data[s2] ) {
                    std::cout << '(' << p.x << ',' << p.y << ',' << p.z << "), ";
                }

                std::cout << '\n';*/
                return;
            }
        }
    }
}

std::optional<Point3> compare2 ( Scanner& a, Scanner& b ) {
    int cnt = 0;
    std::optional<Point3>  ret;
    if ( a.r==-1 ) return ret;
    if ( a.r>-1 && b.r>-1 ) return ret;

    for ( size_t i=0; i<a.beacons.size() && cnt<12; i++ ) {
        for ( size_t j=0; j<b.beacons.size() && cnt<12; j++ ) {
            std::unordered_map<uint64_t,Point3> map;

            a.min = a.beacons[i];
            b.min = b.beacons[j];
            for ( auto& p : a.beacons ) {
                auto pp = rotate(a.r, p - a.min);
                map[pp.tou()] = p;
                //map.insert ( pp.tou() );
            }
            for ( auto r=0; r<24; r++ ) {
                cnt = 0;
                for ( auto& p : b.beacons ) {
                    auto pp = rotate ( r, p - b.min );
                    //cnt += map.contains ( pp.tou() );
                    auto mp = map.find ( pp.tou() );
                    cnt += map.end()!=mp;
                    if ( cnt >=12 ) {
                        // mamy pare
                        if ( b.r==-1 ) {
                            b.r = r;
                            b.pos = rotate(b.r, b.min) - rotate(a.r, a.min) + a.pos;
                            //std::cout << b.pos;
                            ret = b.pos;
                        }
                        else if ( a.r==-1 ) {
                            //a.r = r;
                            //a.pos = -rotate(b.r, b.min) + rotate(a.r, a.min) + b.pos;
                            //std::cout << a.pos;
                        } else{
                            //std::cout << a.pos << b.pos;
                        }
                        //std::cout << r << ' ' << pp - rotate(r, p) + a.min;
                        //std::cout << r << ' ' << rotate(b.r, b.min) - rotate(a.r, a.min);
                        //if( )
                        return ret;
                    }
                }
            }
        }
    }
    return ret;
}

void find ( std::vector<Scanner>& data, size_t i, size_t j ) {
    std::optional<Point3> n;
    if( i >= data.size() ||
        j >= data.size() ) return;
    if ( data[i].r!=-1 && data[j].r==-1) {
        n = compare2 ( data[i], data[j] );
        if( n.has_value() ) {
            std::cout << n.value() << i << ' ' << j << '\n';
            find ( data, j, 0 );
        }
    }else if ( data[j].r!=-1 && data[i].r==-1) {
        n = compare2 ( data[j], data[i] );
        if ( n.has_value() ) {
            std::cout << n.value() << ' ' << i << '\n';
            find ( data, i, 0 );
        }
    }
    find ( data, i, j+1 );
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto data = load (
        puzzle_input
        //"../testinput"
        //"../input"
        );

    data[0].r = 0;
    find ( data, 0, 1 );

    std::unordered_set<uint64_t> ans;
    for ( auto& s : data ) {
        for ( auto& b : s.beacons ) {
            auto bp = s.pos - rotate ( s.r, b );
            ans.insert ( bp.tou() );
        }
    }

    std::cout << __FUNCTION__ << ": " << ans.size() << '\n';
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream& puzzle_input ) {
    auto data = load (
        puzzle_input
        //"../input"
        );

    data[0].r = 0;
    find ( data, 0, 1 );

    int64_t ans = 0;
    for ( size_t i = 0; i < data.size(); i++ ) {
        for ( size_t j = i + 1; j < data.size(); j++ ) {
            int64_t d = std::abs ( data[i].pos.x - data[j].pos.x )
                      + std::abs ( data[i].pos.y - data[j].pos.y )
                      + std::abs ( data[i].pos.z - data[j].pos.z );
            ans = std::max ( d, ans );
        }
    }

    std::cout << __FUNCTION__ << ": " << ans << '\n';
}

//---------------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//
