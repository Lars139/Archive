#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>

#define BUF_SIZE 10
#define YC "\x1b[33m"
#define PC "\x1b[38;05;199m"
#define SC "\x1b[38;05;67m"
#define NC "\x1b[0m"
#define CYAN "\x1b[36m"

//#define SV_SOCK_PATH "/nfs/stak/students/s/sawaspar/hw5_sock"
#define SV_SOCK_PATH1 "./hw5_sock_p1"
#define SV_SOCK_PATH2 "./hw5_sock_p2"
