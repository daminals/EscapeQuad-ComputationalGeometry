#include <stdio.h>

#define X 0
#define Y 1
#define DIM 2
typedef int tPointi[DIM]; // reference O'Rourke Textbook
typedef enum { false, true } bool;

void printPoint(tPointi a) {
    printf("(%d,%d)\n",a[X],a[Y]);
}

int Area2(tPointi a, tPointi b, tPointi c) {// reference O'Rourke Textbook
    return (b[X] - a[X]) * (c[Y] - a[Y]) - (c[X] - a[X]) * (b[Y] - a[Y]);
}

bool Left(tPointi a, tPointi b, tPointi c) {// reference O'Rourke Textbook
    return Area2(a, b, c) > 0;
}

bool LeftOn(tPointi a, tPointi b, tPointi c) {// reference O'Rourke Textbook
    return Area2(a, b, c) >= 0;
}

bool Collinear(tPointi a, tPointi b, tPointi c) {// reference O'Rourke Textbook
    return Area2(a, b, c) == 0;
}

bool Xor(bool x, bool y) {// reference O'Rourke Textbook
    return !x ^ !y;
}

bool Xor4(bool x, bool y,  bool z,  bool a) {
    return Xor(x, y) || Xor(y,z) || Xor(z, a) ;
}

bool IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d) {// reference O'Rourke Textbook
    if (Collinear(a, b, c) || Collinear(a, b, d) || Collinear(c, d, a) || Collinear(c, d, b))
        return false;
    return Xor(Left(a, b, c), Left(a, b, d)) && Xor(Left(c, d, a), Left(c, d, b));
}


bool Between(tPointi a, tPointi b, tPointi c) {// reference O'Rourke Textbook
    tPointi ba, ca;
    if (!Collinear(a, b, c))
        return false;
    if (a[X] != b[X])
        return ((a[X] <= c[X]) && (c[X] <= b[X])) || ((a[X] >= c[X]) && (c[X] >= b[X]));
    else
        return ((a[Y] <= c[Y]) && (c[Y] <= b[Y])) || ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}

bool Intersect(tPointi a, tPointi b, tPointi c, tPointi d) {// reference O'Rourke Textbook
    if (IntersectProp(a, b, c, d))
        return true;
    else if (Between(a, b, c) || Between(a, b, d) || Between(c, d, a) || Between(c, d, b))
        return true;
    else
        return false;
}


bool EscapeQuad(tPointi a, tPointi b, tPointi c, tPointi d, tPointi e, tPointi f) {
    
    // if e,f are collinear with any vertex, they can only cross it thru that vertex
    bool collinear = (Between(e,f,a) || Between(e,f,b) || Between(e,f,c) || Between(e,f,d));
    
    // point in polygon test
    // do a left test on each line 
    // does not matter if it is ccw or cw, bc one should be true and one should be false anyway
    bool eInside = !Xor4(Left(a, b, e), Left(b, c, e), Left(c, d, e),Left(d, a, e));
    bool fInside = !Xor4(Left(a, b, f), Left(b, c, f), Left(c, d, f), Left(d, a, f)); 
    
    return Xor(eInside, fInside) && collinear;
}


int main() {
    tPointi a = {0,0};
    tPointi b = {0,2};
    tPointi c = {2,2};
    tPointi d = {2,0};
    tPointi e = {1,1};
    tPointi f = {3,3};
    
    // test case 1: 
    printf("%d", EscapeQuad(a,b,c,d,e,f)); // expect true
    
    tPointi a1 = {4,6};
    tPointi b1 = {1,6};
    tPointi c1 = {1,2};
    tPointi d1 = {4,2};
    tPointi e1 = {2,3};
    tPointi f1 = {0,1};
    
    printf("%d", EscapeQuad(a1,b1,c1,d1,e1,f1)); // expect true
    
    tPointi f2 = {2,7};
    printf("%d", EscapeQuad(a1,b1,c1,d1,e1,f2)); // expect false

    return 0;
}
