#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<string> printQueue;
mutex mtx;
condition_variable cv;

void producer(int userID, string document) {
    unique_lock<mutex> lock(mtx);
    printQueue.push("User " + to_string(userID) + " submitted: " + document);
    cout << "Print job submitted: " << document << endl;
    cv.notify_one();
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !printQueue.empty(); });
        string job = printQueue.front();
        printQueue.pop();
        cout << "Printing: " << job << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}

int main() {
    thread printer(consumer);
    thread user1(producer, 1, "Report.pdf");
    thread user2(producer, 2, "Invoice.docx");
    thread user3(producer, 3, "Slides.pptx");
    
    user1.join();
    user2.join();
    user3.join();
    
    printer.detach(); // Keep the printer running
    return 0;
}
