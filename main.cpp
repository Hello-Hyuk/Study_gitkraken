#include <iostream>
using namespace std;

void func1(){
    cout << "hello from func1" << endl;
}

int main(){
    cout << "hello from main" << endl;
    func1();
    return 0;
}