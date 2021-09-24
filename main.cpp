#include <iostream>
using namespace std;

void user2(){
    cout << "1212121 User2" << endl;
}
void user1(){
    cout << "12171896 User1" << endl;
}
void User3(){
    cout << "user3" << endl;
}
int main(){
    user2();
    user1();

    cout << "hello main";
    User3();
    return 0;
}