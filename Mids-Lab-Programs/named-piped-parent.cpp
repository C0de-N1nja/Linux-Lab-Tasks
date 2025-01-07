#include <sys/stat.h> // For mkfifo
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    const char *fifoPath = "/tmp/parent_child_pipe"; // Path to the named pipe
    const char *message = "Hello from parent to child";

    // Create the FIFO if it doesn't exist
    if (mkfifo(fifoPath, 0666) == -1)
    {
        perror("mkfifo");
    }

    cout << "Parent: Opening pipe for writing..." << endl;

    // Open the FIFO for writing
    int fd = open(fifoPath, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Write the message to the pipe
    cout << "Parent: Writing message to pipe..." << endl;
    write(fd, message, strlen(message) + 1);

    // Close the pipe
    close(fd);
    cout << "Parent: Message sent and pipe closed." << endl;

    return 0;
}
