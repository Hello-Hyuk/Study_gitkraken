#include <iostream>
#include <stdio.h>
using namespace std;

void func2(){
    cout << "func2" << endl;
}

int main(){
    cout << "hello from main" << endl;
    func2();
    return 0;
}