#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define SIZE_INT sizeof(int)

int main(int argc, char *argv[])
{
    int p[2], sub_p[2];
    pipe(p);

    int rfd, wfd, prev_num;
    int isParent = 1, hasForked = 0, isFirstChild = 1;
    int pid;

    while (1) {
        if (!hasForked) {
            pid = fork();
            hasForked = 1;
        }
        if (pid == 0 || !isParent) {
            isParent = 0;
            
            // listen to parent
            if (isFirstChild) {
                close(p[1]);
                rfd = dup(p[0]);
                close(p[0]);
                wfd = dup(p[1]);
                close(p[1]);
                isFirstChild = 0;
            } else {
                close(sub_p[1]);
                rfd = dup(sub_p[0]);
                close(sub_p[0]);
            }
            read(rfd, &prev_num, SIZE_INT); // read from its parent
            printf("prime %d\n", prev_num);     
            wfd = 1;       

            int curr_num, sub_pid = -1, hasChild = 0;
            while (read(rfd, &curr_num, SIZE_INT)) { // keep reading from parent
                // printf("### prev_num: %d\n", prev_num);s
                // int curr_pid = getpid();
                // printf("### [%d] curr_num: %d\n", curr_pid, curr_num);
                if (curr_num % prev_num != 0) {
                    if (!hasChild) { // one process has only one child
                        hasChild = 1;
                        sub_p[0] = 0;
                        sub_p[1] = 1;
                        pipe(sub_p);
                        sub_pid = fork();
                        if (sub_pid == 0) {
                            break;
                        }
                    }
                    wfd = dup(sub_p[1]);
                    close(sub_p[1]);
                    write(wfd, &curr_num, SIZE_INT);
                }
                // else continue reading the next number, i.e., drop curr_num
            }
            if (sub_pid != 0) { // parent process
                wait(0);
                close(rfd); // no longer listening from its parent process
                close(wfd); // has had nothing to write, close write fd
                break;
            }
        } else {
            if (!isParent) {
                continue;
            }
            close(p[0]);
            wfd = dup(p[1]);
            close(p[1]);
            for (int i = 2; i <= 35; ++i) {
                write(wfd, &i, SIZE_INT);
            }
            wait(0);
            close(wfd);
            break;
        }
    }
    // printf("prime %d", i);

    // for (; i <= 35; ++i) {
    //     int pid = fork();
    //     if (pid == 0) {
    //         ;
    //     }
    //     if (!hasChild && )
    // }

    // for (; i <= 35; ++i) {
    //     int prev_num, rfd, wfd;
    //     if (fork() == 0) {
    //         rfd = dup(p[0]);
    //         wfd = dup(p[1]);
    //         read(rfd, prev_num, SIZE_INT);
    //         printf("prime %d\n", prev_num);
    //         int curr_num;
    //         while (read(rfd, curr_num, SIZE_INT)) {
    //             if (curr_num % prev_num != 0) {
    //                 write(wfd, curr_num, SIZE_INT);
    //             } else {
    //                 close(wfd);
    //                 exit(0);
    //             }
    //         }
    //         exit(0);
    //     } else {
    //         if (!hasChild) hasChild = 1;
    //         wfd = dup(p[1]);
    //         printf("prime %d\n", i);
    //         write(wfd, i, SIZE_INT);
    //     }
    // }
    exit(0);
}