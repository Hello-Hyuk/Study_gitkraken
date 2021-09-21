#include <iostream>
using namespace std;

void foo(){
    cout << "hello from JAY branch";
}
void foo2(){
    cout << "hello from jay2";
}
void foo3(){
    cout << "hello from Choi";
}
void foo4(){
    cout << "hello from jay2 and 4";
}
int main(){
    cout << "hello main";
    foo();
    foo2();
    foo3();
    foo4();

    return 0;
}