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

int main(){
    cout << "hello main";
    foo();
    foo2();
    foo3();
    return 0;
}