#include <iostream>
using namespace std;

void func2(){
    cout << "hello from func2" << endl;
}

int main(){
    cout << "hello from main" << endl;
    func2();
    return 0;
}