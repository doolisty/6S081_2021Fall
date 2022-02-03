#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char param_buf[MAXARG][100];
    char *command = argv[1];
    char *param[MAXARG];
    char ch;

    while (1) {
        memset(param_buf, 0, MAXARG * 100);
        for (int i = 1; i < argc; ++i) {
            strcpy(param_buf[i-1], argv[i]);
        }
        int rdstat = 1, isStr = 0;
        int cnt = argc - 1, idx = 0;
        while ((rdstat = read(0, &ch, 1)) > 0 && ch != '\n') {
            if (ch == ' ' && isStr) {
                ++cnt;
                isStr = 0;
                idx = 0;
            } else if (ch != ' ') {
                isStr = 1;
                param_buf[cnt][idx++] = ch;
            }
        }
        if (rdstat <= 0) {
            break;
        }
        for (int i = 0; i < MAXARG - 1; ++i) {
            param[i] = param_buf[i];
        }
        param[MAXARG - 1] = 0;
        if (fork() == 0) {
            exec(command, param);
            exit(0);
        } else {
            wait(0);
        }
    }
    exit(0);
}