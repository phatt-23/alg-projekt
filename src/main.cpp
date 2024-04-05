#include "inc/decoder.h"
#include "inc/utilities.h"

int main(int argc, char** argv) {
    check_cl_args(&argc, &argv);

    // unspecified path of data
    Decoder de{}; 

    // bring in data from this file
    de.read_in(argv[1]); 

    // print the inputed measurements
    // de.print_ms(Decoder::PrintType::Bits);

    // sort the measuremenets by time
    de.sort_ms();

    // print the measurement after sorting
    // de.print_ms(Decoder::PrintType::Bits);

    // removes dups after sorting
    de.rm_dups();

    // print after removal
    // de.print_ms(Decoder::PrintType::Bits);
    
    // write to a file in bits format
    de.write_to(argv[2], Decoder::PrintType::Human);
    
    // printout a human readable output
    de.print_ms(Decoder::PrintType::Human);

    de.find_exts();

    return 0;
}

