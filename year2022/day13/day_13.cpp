#include "day"

//---------------------------------------------------------------------------//
namespace aoc::YEAR::DAY {

//---------------------------------------------------------------------------//
// Test data
std::string testinput
{
    R"([1,1,3,1,1]
[1,1,5,1,1]

[[1],[2,3,4]]
[[1],4]

[9]
[[8,7,6]]

[[4,4],4,4]
[[4,4],4,4,4]

[7,7,7,7]
[7,7,7]

[]
[3]

[[[]]]
[[]]

[1,[2,[3,[4,[5,6,7]]]],8,9]
[1,[2,[3,[4,[5,6,0]]]],8,9])" };

//---------------------------------------------------------------------------//
inline std::istream& test_input ( ) {
    static std::stringstream ss;
    return ss = std::stringstream ( testinput );
}

//---------------------------------------------------------------------------//
std::string getLine ( std::istream& file ) {
    std::string line;
    getline ( file, line );
    return line;
}

//---------------------------------------------------------------------------//
struct Obj {
    std::vector<Obj*> o;
    int v=0;
    bool _isObject = false;
    inline bool isObject() {
        return _isObject;
    }
    inline bool isValue() {
        return !_isObject;
    }
    void push_back ( auto no ) {
        o.push_back( no );
        _isObject = true;
    }
    void clear(){
        //std::cout << ".";
        for ( auto t: o ) {
            t->clear();
            delete t;
        }
    }
};

//---------------------------------------------------------------------------//
int parse ( Obj* o, std::string_view s, uint i=0 ) {
    while( i < s.length() ){
        if ( s[i]=='[' ) {
            //std::cout << "Obj[";
            auto no = new Obj{};
            no->_isObject = true;
            o->push_back ( no );
            i = parse ( no, s, i+1 );
        }else
        if ( s[i]>='0' && s[i]<='9' ) {
            int val=0;
            while ( s[i]>='0' && s[i]<='9' ) {
                val *= 10;
                val += s[i]-'0';
                i++;
            }
            auto no = new Obj{};
            no->v = val;
            o->o.push_back( no );
            //std::cout << val << ",";
        }else
        if ( s[i]==',' ) {
            i++;
        } else
        if ( s[i]==']' ){
            //std::cout << "]";
            return i+1;
        }
    }
    return i;
}


int check( Obj* o1, Obj* o2 ) {
    uint i=0;
    while ( i < o1->o.size() && i < o2->o.size() ) {
        if ( o1->o[i]->isValue() && o2->o[i]->isValue() ) {
            if ( o1->o[i]->v < o2->o[i]->v ) {
                return 1;
            }
            if ( o1->o[i]->v > o2->o[i]->v ) {
                return -1;
            }
        }else if ( o1->o[i]->isObject() && o2->o[i]->isObject() ) {
            auto e = check ( o1->o[i], o2->o[i] );
            if (e) return e;
        } else if ( o1->o[i]->isValue() && o2->o[i]->isObject() ) {
            auto v = o1->o[i]->v;
            Obj o{};
            auto no = new Obj{{},v};
            o.push_back( no );
            auto e = check( &o, o2->o[i] );
            if (e) return e;
            delete no;
        } else if ( o1->o[i]->isObject() && o2->o[i]->isValue() ) {
            auto v = o2->o[i]->v;
            Obj o{};
            auto no = new Obj{{},v};
            o.push_back( no );
            auto e = check( o1->o[i], &o );
            if (e) return e;
            delete no;
        }
        i++;
    }

    if ( o1->o.size() < o2->o.size() ) {
        return 1;
    }else
    if ( o1->o.size() > o2->o.size() ) {
        return -1;
    }

    return 0;
}

//---------------------------------------------------------------------------//
void Task_1 ( std::istream& puzzle_input ) {
    auto ans = 0ul;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    uint idx=1;
    while ( file ) {
        auto line1 = getLine ( file );
        auto line2 = getLine ( file );
        //std::cout << line1 << " " << line2 << "\n";

        Obj o1, o2;
        parse( &o1, line1, 1 );
        parse( &o2, line2, 1 );
        int q = check ( &o1, &o2 );
        o1.clear();
        o2.clear();

        getLine ( file );
        if ( q>0 ) {
            ans += idx;
        }
        idx++;
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//
void Task_2 ( std::istream & puzzle_input ) {
    auto ans = 0;

    //aoc::test_enable();

    auto& file = aoc::is_test_enabled() ? test_input ( ) : puzzle_input;

    std::vector<std::string> lines{"[[2]]","[[6]]"};
    while ( file ) {
        auto line1 = getLine ( file );
        auto line2 = getLine ( file );
        lines.push_back( line1 );
        lines.push_back( line2 );
        getLine ( file );
    }

    std::sort( lines.begin(), lines.end(),[](std::string& a, std::string& b){
        Obj o1, o2;
        parse( &o1, a, 1 );
        parse( &o2, b, 1 );
        int q = check ( &o1, &o2 );

        o1.clear();
        o2.clear();
        return q>0;
    });

    ans = 1;
    for( auto i=0u; i<lines.size(); i++ ){
        if ( lines[i]=="[[2]]" || lines[i]=="[[6]]" ) {
            ans *= i+1;
        }
    }

    OUT ( ans );
}

//---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------//
