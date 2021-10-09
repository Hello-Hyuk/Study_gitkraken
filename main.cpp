#include <iostream>
#include <stdio.h>
using namespace std;

void func2(){
    cout << "hello from func2" << endl;
}

int main(){
    cout << "hello from main" << endl;
    printf("maybe this one occur conflict\n");
    for(;;){
        func2();
        break;
    }
    func2();
    return 0;
}