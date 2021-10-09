#include <iostream>
#include <stdio.h>
using namespace std;

void func1(){
    cout << "func1" << endl;
}

void func2(){
    cout << "func2" << endl;
}

int main(){
    cout << "hello" << endl;
    func1();
    cout << "hello from main" << endl;
    cout << "hello vision" << endl;
    func2();
    return 0;
}