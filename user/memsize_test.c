#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    printf("%d\n" ,memsize());
    int* v = (int*)malloc(20*1024);
    printf("%d\n" ,memsize());
    free(v);
    printf("%d\n" ,memsize());
    exit(0,0);
}
