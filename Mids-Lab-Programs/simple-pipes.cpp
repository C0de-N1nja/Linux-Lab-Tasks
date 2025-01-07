#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
    int pipefd[2];
    pid_t pid;
    const char *msg = "Hello from parent to child";
    char buffer[128];

    if (pipe(pipefd) == -1)
    {
        cout << "pipe failed" << endl;
        return 1;
    }

    pid = fork();

    if (pid < 0)
    { // Fork failed
        cout << "fork failed" << endl;
        return 1;
    }

    if (pid > 0)
    {                     // Parent process
        close(pipefd[0]); // Close unused read end

        cout << "Parent: Writing to pipe..." << endl;
        write(pipefd[1], msg, strlen(msg) + 1); // Write message to pipe
        close(pipefd[1]);                       // Close write end after writing

        wait(NULL); // Wait for child to finish
        cout << "Parent: Child process is done." << endl;
    }
    else
    {                     // Child process
        close(pipefd[1]); // Close unused write end

        cout << "Child: Reading from pipe..." << endl;
        read(pipefd[0], buffer, sizeof(buffer)); // Read from pipe
        cout << "Child received: " << buffer << endl;

        close(pipefd[0]); // Close read end
        cout << "Child process is exiting." << endl;
    }

    return 0;
}