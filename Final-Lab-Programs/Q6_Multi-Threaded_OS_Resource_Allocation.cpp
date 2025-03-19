#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

using namespace std;

#define NUM_THREADS 5
#define NUM_RESOURCES 3

sem_t resources[NUM_RESOURCES];

void thread_function(int id) {
    int res_id = id % NUM_RESOURCES;
    
    cout << "Thread " << id << " is requesting resource " << res_id << "\n";
    sem_wait(&resources[res_id]);

    cout << "Thread " << id << " is using resource " << res_id << "\n";
    sleep(2);

    cout << "Thread " << id << " has released resource " << res_id << "\n";
    sem_post(&resources[res_id]);
}

int main() {
    vector<thread> threads;
    
    for (int i = 0; i < NUM_RESOURCES; i++) {
        sem_init(&resources[i], 0, 1);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(thread_function, i));
    }
    
    for (auto &t : threads) {
        t.join();
    }
    
    return 0;
}
