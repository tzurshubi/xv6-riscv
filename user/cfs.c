#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pids[6];
    int n = 6,  i, k;
    set_policy(2);
    for (i = 0; i < n; ++i) {
        if (fork() == 0) {
            pids[i] = getpid();
            set_cfs_priority(i%3);
            int y;
            long sum = 0;
            for (k = 1; k <= 100000; k++) {
                if(k % 10000 == 0){
                    sleep(10);
                }
                for (y = 1; y <= 100000; y++) {
                    sum += k * y;
                }
            }
        int stats[4];
        get_cfs_stats(pids[i], stats);
        sleep(10*i);
        printf("PID: %d, Priority: %d, Run Time: %d, Sleep Time: %d, Runnable Time: %d\n",
            pids[i],stats[0],stats[1], stats[2], stats[3]);
        exit(0,"exit msg");
        }
    }
    exit(0,"parent job is done\n");

}