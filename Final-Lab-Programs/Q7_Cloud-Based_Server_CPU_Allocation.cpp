#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
using namespace std;

const int NUM_VM = 5;
const int NUM_CPU_CORES = 3;
sem_t cpuCores;

void virtualMachine(int id) {
    cout << "VM " << id << " is waiting for a CPU core.\n";
    sem_wait(&cpuCores);
    cout << "VM " << id << " is using a CPU core.\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "VM " << id << " has released a CPU core.\n";
    sem_post(&cpuCores);
}

int main() {
    sem_init(&cpuCores, 0, NUM_CPU_CORES);
    vector<thread> vms;

    for (int i = 0; i < NUM_VM; ++i) {
        vms.emplace_back(virtualMachine, i);
    }

    for (auto& vm : vms) {
        vm.join();
    }

    sem_destroy(&cpuCores);
    return 0;
}
