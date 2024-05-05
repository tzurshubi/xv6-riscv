#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        exit(0,"missing argument\n");
    }

    int policy = atoi(argv[1]);

    if(policy < 0 || policy > 2){
        exit(0,"invalid argument, policy must be 0, 1 or 2\n");
    }
    else if(set_policy(policy) == 0){
        exit(0,"success\n");
    }
    else{
        exit(1,"error\n");
    }
}