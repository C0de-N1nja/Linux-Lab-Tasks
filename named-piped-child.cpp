#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    const char *fifoPath = "/tmp/parent_child_pipe"; // Path to the named pipe
    char buffer[128];

    cout << "Child: Opening pipe for reading..." << endl;

    // Open the FIFO for reading
    int fd = open(fifoPath, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Read the message from the pipe
    cout << "Child: Reading message from pipe..." << endl;
    read(fd, buffer, sizeof(buffer));
    cout << "Child: Received message: " << buffer << endl;

    // Close the pipe
    close(fd);
    cout << "Child: Pipe closed." << endl;

    return 0;
}
