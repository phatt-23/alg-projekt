#include "inc/utilities.h"

void check_cl_args(int t_argc, char** t_argv) {
    if(t_argc < 4) {
        printf(__red__ __bld__ "[wrong usage]\n" __reset__ __bld__ "  $");
        for(int i = 0; i < t_argc; ++i)
            printf(" %s", t_argv[i]);
        printf(__reset__ "\n\n");
        printf(__grn__ __bld__ "[correct usage]\n" __reset__);
        printf(__bld__ "  $ ./iotdecoder [input] [output] [num_of_intervals]\n" __reset__);
        printf("\t [input]  - input file required\n");
        printf("\t [output] - output file required\n");
        printf("\t [num_of_intervals] - number of intervals of the histogram\n");
        exit(EXIT_FAILURE);
    }
}
