#include<iostream>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
using namespace std;

int main(){
    key_t key = ftok("shmfile", 65);
    int shmget(key, 1024, 0666 | IPC_CREAT);
    char* str = (char*)shmat(shmid, void*)0,0);
    cout<<"Write DAta: ";
    cin.getline(str,1024);
    cout<<"Data written in memory: "<<str<<endl;
    shmdt(str);
    return 0;
}