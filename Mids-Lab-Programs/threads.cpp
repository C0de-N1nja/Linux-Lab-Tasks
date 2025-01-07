#include<iostream>
#include<thread>
using namespace std;
void my_function(){
    cout<<"Thread Execution!"<<endl;
}
int main(){
    thread t(my_function);
    t.join();

    cout<<"Main functino executed!"<<endl;
    return 0;
}