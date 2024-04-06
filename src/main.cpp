#include "inc/decoder.h"
#include "inc/utilities.h"

int main(int argc, char** argv) {
    check_cl_args(&argc, &argv);

    Decoder de{}; 

    de.read_in(argv[1]); 
    // de.print_ms(Decoder::Original);

    de.sort_ms();

    // print the measurement after sorting
    // de.print_ms(Decoder::PrintType::Original);

    // removes dups after sorting
    de.rm_dups();

    // print after removal
    de.print_ms(Decoder::PrintType::Human);
    
    // write to a file in bits format
    de.write_to(argv[2], Decoder::PrintType::Original);
    
    // printout a human readable output
    // de.print_ms(Decoder::PrintType::Human);

    de.find_exts();

    return 0;
}

