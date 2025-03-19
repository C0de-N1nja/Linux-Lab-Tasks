#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_RESOURCES 3

sem_t resources[NUM_RESOURCES];

void thread_function(int id) {
    int res_id = id % NUM_RESOURCES;
    
    std::cout << "Thread " << id << " is requesting resource " << res_id << "\n";
    sem_wait(&resources[res_id]);

    std::cout << "Thread " << id << " is using resource " << res_id << "\n";
    sleep(2);

    std::cout << "Thread " << id << " has released resource " << res_id << "\n";
    sem_post(&resources[res_id]);
}

int main() {
    std::vector<std::thread> threads;
    
    for (int i = 0; i < NUM_RESOURCES; i++) {
        sem_init(&resources[i], 0, 1);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(std::thread(thread_function, i));
    }
    
    for (auto &t : threads) {
        t.join();
    }
    
    return 0;
}
