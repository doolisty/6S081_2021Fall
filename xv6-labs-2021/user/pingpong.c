#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    // close(1);
    
    if (fork() == 0) {
        char buf[32];
        dup(p[1]);
        close(p[1]);
        read(p[1], buf, 32);
        int child_pid = getpid();
        
        printf("%d: received ping\n", child_pid);
        write(p[1], "start", 5);
    } else {
        dup(p[0]);
        close(p[0]);
        write(p[0], "start", 5);

        char buf[32];
        read(p[0], buf, 32);
        int parent_pid = getpid();
        wait(0);
        printf("%d: received pong\n", parent_pid);
    }

    exit(0);
} 