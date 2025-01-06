#include<iostream>
#include<thread>
using namespace std;
void my_function(int num1, int num2){
    int sum = 0;
    sum = num1 + num2;
    cout<<"The sum of two numbers is: "<<sum<<endl;
    cout<<"Thread Execution!"<<endl;
}
int main(){
    thread t(my_function, 5, 5);
    t.join();

    cout<<"Main function executed!"<<endl;
    return 0;
}