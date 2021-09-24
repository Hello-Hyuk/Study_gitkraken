#include <iostream>
using namespace std;

<<<<<<<<< Temporary merge branch 1
void user2(){
    cout << "1212121 User2" << endl;
}
void user1(){
    cout << "12171896 User1" << endl;
}
int main(){
    user2();
    user1();

=======
void User3(){
    cout << "user3" << endl;
}
int main(){
    user2();
    user1();

    cout << "hello main";
    User3();
>>>>>>>>> Temporary merge branch 2
    return 0;
}