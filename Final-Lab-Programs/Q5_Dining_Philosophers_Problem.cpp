#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define NUM_PHILOSOPHERS 5
sem_t forks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    while (true) {
        cout << "Philosopher " << id << " is thinking...\n";
        sleep(1);

        // Pick up forks (left first, then right)
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        cout << "Philosopher " << id << " is eating...\n";
        sleep(2);

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
    }
}

int main() {
    thread philosophers[NUM_PHILOSOPHERS];
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i] = thread(philosopher, i);
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].join();
    }
    
    return 0;
}
