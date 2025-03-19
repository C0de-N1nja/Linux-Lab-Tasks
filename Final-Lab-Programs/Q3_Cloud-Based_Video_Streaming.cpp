#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<string> videoBuffer;
mutex mtx;
condition_variable cv;
const int BUFFER_SIZE = 5;

void producer(int userID, string video) {
    unique_lock<mutex> lock(mtx);
    while (videoBuffer.size() == BUFFER_SIZE) {
        cout << "Buffer full. Upload paused for user " << userID << endl;
        cv.wait(lock);
    }
    videoBuffer.push("User " + to_string(userID) + " uploaded: " + video);
    cout << "Video uploaded: " << video << endl;
    cv.notify_all();
}

void consumer(int viewerID) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !videoBuffer.empty(); });
    string video = videoBuffer.front();
    videoBuffer.pop();
    cout << "Viewer " << viewerID << " is watching: " << video << endl;
    cv.notify_all();
}

int main() {
    thread uploader1(producer, 1, "Movie.mp4");
    thread viewer1(consumer, 101);
    thread uploader2(producer, 2, "Documentary.mp4");
    thread viewer2(consumer, 102);
    
    uploader1.join();
    viewer1.join();
    uploader2.join();
    viewer2.join();
    
    return 0;
}
