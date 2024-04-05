#include "inc/decoder.h"
#include "inc/colours.h"
#include "inc/precomp.h"

void check_cl_args(int* t_argc, char*** t_argv);

int main(int argc, char** argv) {
    check_cl_args(&argc, &argv);

    // unspecified path of data
    Decoder de{}; 

    // bring in data from this file
    de.read_in(argv[1]); 

    // print the inputed measurements
    de.print_ms(Decoder::PrintType::Bits);

    // sort the measuremenets by time
    de.sort_ms();

    // print the measurement after sorting
    de.print_ms(Decoder::PrintType::Bits);

    // removes dups after sorting
    de.rm_dups();

    // print after removal
    de.print_ms(Decoder::PrintType::Bits);
    
    // write to a file in bits format
    de.write_to(argv[2], Decoder::PrintType::Human);

    return 0;
}

void check_cl_args(int* t_argc, char*** t_argv) {
    if(*t_argc > 3 || *t_argc == 1) {
        printf(__red__ __bld__ "[wrong usage]\n" __reset__ __bld__ "  $");
        for(int i = 0; i < *t_argc; ++i)
            printf(" %s", (*t_argv)[i]);
        printf(__reset__ "\n\n");
        printf(__grn__ __bld__ "[correct usage]\n" __reset__);
        printf(__bld__ "  $ ./iotdc [input] [output]\n" __reset__);
        printf("\t [input]  - input file required\n");
        printf("\t [output] - output file is optional (defaults to '" __iot_def_out__ "')\n");
        exit(EXIT_FAILURE);
    } else if(*t_argc == 2) {
        __info_all__ printf("defaulting the output file to '" __iot_def_out__ "'\n");

        char** tm_argv = (char**) malloc(sizeof(char*) * 3);
        for(int i = 0; i < 2; ++i) {
            tm_argv[i] = (char*) malloc(sizeof(char) * strlen((*t_argv)[i]) + 1);
            memcpy(tm_argv[i], (*t_argv)[i], strlen((*t_argv)[i]));
        }
        tm_argv[2] = (char*) malloc(sizeof(char) * strlen(__iot_def_out__) + 1);
        memcpy(tm_argv[2], __iot_def_out__, strlen(__iot_def_out__));
        // not freeing memory of the original char** argv 
        // beause it is causing SigAbrt
        (*t_argv) = tm_argv; 
        (*t_argc)++;
    }
}
