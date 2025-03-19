#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<string> messageQueue;
mutex mtx;
condition_variable cv;

void producer(int id, string message) {
    unique_lock<mutex> lock(mtx);
    messageQueue.push("User " + to_string(id) + ": " + message);
    cout << "Message sent: " << message << endl;
    cv.notify_one();
}

void consumer(int id) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !messageQueue.empty(); });
    string message = messageQueue.front();
    messageQueue.pop();
    cout << "User " << id << " received: " << message << endl;
}

int main() {
    thread sender1(producer, 1, "Hello!");
    thread receiver1(consumer, 2);
    thread sender2(producer, 3, "How are you?");
    thread receiver2(consumer, 4);
    
    sender1.join();
    receiver1.join();
    sender2.join();
    receiver2.join();
    
    return 0;
}
