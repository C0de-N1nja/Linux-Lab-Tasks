#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

int main() {
    key_t key = ftok("shmfile", 65); // Generate unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create shared memory

    char* str = (char*)shmat(shmid, (void*)0, 0); // Attach shared memory
    cout << "Write Data: ";
    cin.getline(str, 1024); // Get user input
    cout << "Data written in memory: " << str << endl;

    shmdt(str); // Detach shared memory
    return 0;
}
