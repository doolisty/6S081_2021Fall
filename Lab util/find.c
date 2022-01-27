#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  memmove(buf, p, strlen(p));
  *(buf+strlen(p)) = 0;
  return buf;
}

void find(char *path, char *filename)
{
    int fd;
    char buf[512], *start_ptr;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s", path);
        exit(1);
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "ls: cannot stat %s", path);
        close(fd);
        exit(1);
    }

    switch (st.type) {
    case T_FILE:
        if (strcmp(filename, fmtname(path)) == 0) {
            printf("%s", path);
        }
        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
            fprintf(2, "find: path too long\n");
            break;
        }
        strcpy(buf, path);
        start_ptr = buf + strlen(buf);
        *start_ptr++ = '/'; // 就算多一个/也没关系
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0) {
                continue;
            }
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                continue;
            }
            memmove(start_ptr, de.name, DIRSIZ);
            start_ptr[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            char *name = fmtname(buf);
            switch (st.type) {
            case T_FILE:
                if (strcmp(filename, name) == 0) {
                    printf("%s\n", buf);
                }
                break;
            case T_DIR:
                find(buf, filename);
                break;
            }
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(2, "usage: find {dir} {filename}\n");
        exit(1);
    }
    char *path = argv[1];
    char *filename = argv[2];

    find(path, filename);
    exit(0);
}