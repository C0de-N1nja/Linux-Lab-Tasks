#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

#define NUM_VMS 5
#define NUM_CPUS 2

sem_t cpu_cores;

void vm_request(int id) {
    std::cout << "VM " << id << " is requesting a CPU core...\n";
    sem_wait(&cpu_cores);
    
    std::cout << "VM " << id << " is executing on a CPU core.\n";
    sleep(3);
    
    std::cout << "VM " << id << " has released the CPU core.\n";
    sem_post(&cpu_cores);
}

int main() {
    sem_init(&cpu_cores, 0, NUM_CPUS);
    std::vector<std::thread> vms;
    
    for (int i = 0; i < NUM_VMS; i++) {
        vms.push_back(std::thread(vm_request, i));
    }
    
    for (auto &vm : vms) {
        vm.join();
    }
    
    return 0;
}
