#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    if (pipe(p)) {
        fprintf(2, "pipe() failed!\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork() failed!\n");
        exit(1);
    } else if (pid != 0) {
        close(p[0]);
        for (int i = 2; i <= 35; ++i) {
            write(p[1], &i, 4);
        }
        close(p[1]); // 先close再wait，很重要！不close，wait是等不到的
        wait(0);
        exit(0);
    }

    int prev_num, curr_num;
    int rfd, wfd;
    while (1) {
        close(p[1]);
        rfd = p[0];
        if (read(rfd, &prev_num, 4) == 0) {
            close(rfd);
            break;
        }

        if (pipe(p)) {
            fprintf(2, "pipe() failed!\n");
            exit(1);
        }
        pid = fork();
        if (pid < 0) {
            fprintf(2, "fork() failed!\n");
            exit(1);
        } else if (pid > 0) {
            close(p[0]);
            wfd = p[1];
            printf("prime %d\n", prev_num);
            while (read(rfd, &curr_num, 4)) {
                if (curr_num % prev_num != 0) {
                    write(wfd, &curr_num, 4);
                }
            }
            close(rfd);
            close(wfd);
            wait(0);
            break;
        }
    }

    exit(0);
}