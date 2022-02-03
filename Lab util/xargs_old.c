#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

// void resolve_command(char *input_buf, char *command[], int needFirstArg) {
//     char arg_tmp[512], *arg_tmp_p = arg_tmp, *p;
//     memset(command, 0, MAXARG * 512);
//     int cnt = 0, isArgv = 0;
//     for (p = input_buf; *p != 0; ++p) {
//         if (*p == ' ') {
//             if (needFirstArg && !isArgv) {
//                 isArgv = 1;
//                 continue;
//             }
//             *arg_tmp_p = 0;
//             memmove(command[cnt++], arg_tmp, strlen(arg_tmp));
//             arg_tmp_p = arg_tmp;
//         } else if (!needFirstArg && isArgv) {
//             *arg_tmp_p++ = *p;
//         }
//     }
// }

// void read_from_std_input(char *command1[], char *command2[]) {
//     char buf[512], *p = buf;
//     char tmp_c;
//     while (read(0, &tmp_c, 1)) {
//         if (tmp_c == '|') {
//             break;
//         }
//         *p++ = tmp_c;
//     }
//     *p = 0;
//     resolve_command(buf, command1, 1);
//     read(0, &tmp_c, 1);
//     p = buf;
//     while (read(0, &tmp_c, 1)) {
//         *p++ = tmp_c;
//     }
//     *p = 0;
//     resolve_command(buf, command2, 0);
// }

int main(int argc, char *argv[]) {
#if 0
    char curr;
    int stat, cnt = 0;
    // char input_line[512], *p = input_line;
    printf("hihihi\n");
    char *command = argv[1];
    char xargs[MAXARG][512], *p = xargs[0];

    memset(xargs, 0, MAXARG * 512);
    for (int i = 2; i < argc; ++i) {
        strcpy(xargs[cnt++], argv[i]);
    }

    while (1) {
        stat = read(0, &curr, 1);
        if (stat == 0) {
            break;
        }
        if (curr == ' ') {
            *p = 0;
            p = xargs[cnt++];
        } else if (curr != '\n') {
            *p++ = curr;
        } else {
            cnt = argc - 2;
            p = xargs[cnt];
            printf("command = %s\n", command);
            printf("xargs = %s\n", xargs[0]);
            if (fork() == 0) {
                exec(command, (char**)xargs);
                exit(0);
            }
        }
    }
    wait(0);
    exit(0);

// ================================================================================================
#else

    char buf[512], *p = buf;
    printf("hihihi\n");
    char *command = argv[1];
    char xargs[MAXARG][512];
    int cnt = 0;
    // int fd[2];
    // pipe(fd);

    memset(xargs, 0, MAXARG * 512);
    for (int i = 2; i < argc; ++i) {
        memmove(xargs[cnt++], argv[i], strlen(argv[i]));
    }

    // if (fork() != 0) {
    while (1) { // all outputs
        // printf("hihihi\n");
        char curr, outerStat;
        while (1) { // read single line
            int stat = read(0, &curr, 1);
            printf("stat = %d, char = %c\n", stat, curr);
            if (!stat) {
                outerStat = 0;
                break;
            }
            if (curr == ' ' || curr == '\n') {
                *p = 0;
                p = buf;
                memmove(xargs[cnt++], buf, strlen(buf));
                if (curr == '\n') {
                    break;
                }
            } else {
                *p++ = curr;
            }
        }
        if (!outerStat) break;

        if (fork() == 0) {
            exec(command, (char**)xargs);
            exit(0);
        }
    }
    exit(0);
        // close(fd[0]);
    //     printf("### line = %s\n", input_line);
    //     write(fd[1], (char*)input_line, strlen(input_line));
    // }
    // close(fd[1]);
    // wait(0);
    // // } else {
    //     close(fd[1]);

    //     char command[512], *tmp_p = command;
    //     memmove(tmp_p, "/bin/", 5);
    //     tmp_p += 5;
    //     memmove(tmp_p, argv[1], strlen(argv[1]));
    //     tmp_p += strlen(argv[1]);
    //     *(++tmp_p) = 0;

    //     // char *line;
    //     char *xargs[MAXARG];
    //     int cnt = 0;
    //     for (int i = 2; i < argc; ++i) {
    //         xargs[cnt++] = argv[i];
    //     }
    //     while (read(fd[0], &xargs[cnt], 512)) {
    //         exec(argv[1], xargs);
    //         // exec(command, xargs);
    //     }
    //     close(fd[0]);
    // // }
#endif
// ================================================================================================

    // char input_command_arr[MAXARG][512], xargs_command_arr[MAXARG][512];

    // int i;
    // char *input_command, xargs_command;
    // for (i = 0; i < argc && strcmp(argv[i], "|") != 0; ++i) {
    //     if (i == 0) {
    //         input_command = argv[i];
    //     } else {
    //         memmove(input_command_arr[i - 1], argv[i], strlen(argv[i]));
    //     }
        
    // }
    // int cnt = i;
    // for (i = 1; i < argc - cnt; ++i) {
    //     if (i == 1) {
    //         xargs_command = argv[cnt + i];
    //     } else {
    //         ;
    //     }
    // }

    // read_from_std_input(input_command_arr, xargs_command_arr);

    // char *input_command = input_command_arr[0], *input_arg_p = input_command_arr + strlen(input_command);
    // char *xargs_command = xargs_command_arr[0], *xargs_arg_p = xargs_command_arr + strlen(xargs_command);
    
    // int p[2];
    // pipe(p);

    // int pid = fork();
    // if (pid < 0) {
    //     fprintf(2, "fork() failed\n");
    //     exit(1);
    // } else if (pid == 0) {
    //     close(1);
    //     close(p[0]);
    //     dup(p[0]);
    // } else {
    //     wait(0);
    // }

    // exit(0);
}