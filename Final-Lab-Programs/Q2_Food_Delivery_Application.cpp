#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<string> orderQueue;
mutex mtx;
condition_variable cv;

void producer(int customerID, string order) {
    unique_lock<mutex> lock(mtx);
    orderQueue.push("Customer " + to_string(customerID) + " ordered: " + order);
    cout << "Order placed: " << order << endl;
    cv.notify_one();
}

void consumer(int workerID) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !orderQueue.empty(); });
    string order = orderQueue.front();
    orderQueue.pop();
    cout << "Worker " << workerID << " preparing: " << order << endl;
}

int main() {
    thread customer1(producer, 1, "Pizza");
    thread worker1(consumer, 101);
    thread customer2(producer, 2, "Burger");
    thread worker2(consumer, 102);
    
    customer1.join();
    worker1.join();
    customer2.join();
    worker2.join();
    
    return 0;
}
