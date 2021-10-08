#include <iostream>
using namespace std;

void func3(){
    cout << "hello from func2" << endl;
}

int main(){
    cout << "hello from main" << endl;
    func3();
    return 0;
}