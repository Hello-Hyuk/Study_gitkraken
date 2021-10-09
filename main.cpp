#include <iostream>
#include <stdio.h>
using namespace std;

void func2(){
    cout << "hello from func2" << endl;
}
void func1(){
    cout << "hello from func1" << endl;
}

int main(){
    cout << "hello from main" << endl;
    printf("maybe this one occur conflict\n");
    for(;;){
        func2();
        func1();
        break;
    }
    func2();
    func1();
    return 0;
}