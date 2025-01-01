#include<iostream>
#include<thread>
using namespace std;
void my_function(){
    int a, b, sum = 0;
    cout<<"Enter the 1st value: ";
    cin>>a;
    cout<<"Enter the 2nd value: ";
    cin>>b;
    sum = a + b;
    cout<<"The sum is: "<<sum<<endl;
    cout<<"Thread Execution!"<<endl;
}
int main(){
    thread t(my_function);
    t.join();

    cout<<"Main function executed!"<<endl;
    return 0;
}