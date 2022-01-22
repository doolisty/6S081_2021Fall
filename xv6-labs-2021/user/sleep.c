#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/syscall.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *time_str;
    int num_tick;
    if (argc <= 1) {
        fprintf(2, "usage: sleep {time}\n");
        exit(1);
    }

    time_str = argv[1];
    num_tick = atoi(time_str);
    sleep(num_tick);

    exit(0);
}