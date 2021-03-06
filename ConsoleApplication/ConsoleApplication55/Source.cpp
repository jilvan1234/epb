#include <iostream> 
using namespace std; 

class Point { 
    int x, y; 

public: 
    Point() { 
        x = y = 0; 
    } 

    Point(int x, int y) { 
        this->x = x; 
        this->y = y; 
    } 

    friend ostream &operator<<(ostream &s, Point p); 
}; 

ostream &operator<<(ostream &s, Point p) { 
    s << "("<< p.x << ", " << p.y << ")"; 
    return s; 
} 

int main() { 
    Point p1(1, 3), p2(10, 5); 

    cout << "p1: " << p1 << endl
         << "p2: " << p2 << endl; 
 
	system("pause");   
    return 0; 
}