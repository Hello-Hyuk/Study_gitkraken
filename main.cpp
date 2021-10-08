#include <iostream>
#include <stdio.h>
using namespace std;

void func3(){
    cout << "hello from func2" << endl;
}

int main(){
    cout << "hello from main" << endl;
    printf("maybe this one occur conflict\n");
    for(;;){
        func3();
        break;
    }
    func3();
    return 0;
}