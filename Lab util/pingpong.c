#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2], fd;
    pipe(p);
    
    if (fork() == 0) {
        char buf[32];
        fd = dup(p[1]);
        read(fd, buf, 32);
        int child_pid = getpid();
        
        printf("%d: received ping\n", child_pid);
        write(fd, "start", 5);
    } else {
        fd = dup(p[0]);
        write(fd, "start", 5);

        char buf[32];
        read(fd, buf, 32);
        int parent_pid = getpid();
        wait(0);
        printf("%d: received pong\n", parent_pid);
    }

    exit(0);
} 