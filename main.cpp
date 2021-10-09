#include <iostream>
#include <stdio.h>
using namespace std;

<<<<<<< main
void func1(){
    cout << "func1" << endl;
}

void func2(){
    cout << "func2" << endl;
}

int main(){
    cout << "hello from sy" << endl;
    printf("maybe this one occur conflict\n");
    for(;;){
        func2();
        func1();
        break;
    }
    func2();
    return 0;
=======
void func2() {
    cout << "hell from func2" << endl;
}

int main(){
    cout << "hello from sy2" << endl;
>>>>>>> sy2func2
}