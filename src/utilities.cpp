#include "inc/utilities.h"

void check_cl_args(int t_argc, char** t_argv) {
    if(t_argc != 3) {
        printf(__red__ __bld__ "[wrong usage]\n" __reset__ __bld__ "  $");
        for(int i = 0; i < t_argc; ++i)
            printf(" %s", t_argv[i]);
        printf(__reset__ "\n\n");
        printf(__grn__ __bld__ "[correct usage]\n" __reset__);
        printf(__bld__ "  $ ./iotdc [input] [output]\n" __reset__);
        printf("\t [input]  - input file required\n");
        printf("\t [output] - output file required\n");
        exit(EXIT_FAILURE);
    }
}
