#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    // Create a unique key
    key_t key = ftok("shmfile", 65);

    // Create a shared memory segment
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        std::cerr << "Failed to create shared memory segment" << std::endl;
        return 1;
    }

    // Attach the shared memory segment
    char* str = (char*)shmat(shmid, nullptr, 0);
    if (str == (void*)-1) {
        std::cerr << "Failed to attach shared memory segment" << std::endl;
        return 1;
    }

    // Display the data read from the shared memory segment
    std::cout << "Data read from memory: " << str << std::endl;

    // Detach the shared memory segment
    if (shmdt(str) == -1) {
        std::cerr << "Failed to detach shared memory segment" << std::endl;
        return 1;
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
        std::cerr << "Failed to remove shared memory segment" << std::endl;
        return 1;
    }

    return 0;
}