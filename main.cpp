#include <iostream>
#include <stdio.h>
using namespace std;

void func1(){
    cout << "hello from func1" << endl;
}

int main(){
    cout << "hello from main" << endl;
    printf("maybe this one occur conflict\n");
    for(;;){
        func1();
        break;
    }
    func1();
    return 0;
}