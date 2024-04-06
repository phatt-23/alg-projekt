#include "inc/decoder.h"
#include "inc/utilities.h"

int main(int argc, char** argv) {
    check_cl_args(&argc, &argv);

    Decoder de{}; 
    de.read_in(argv[1]); 

    de.sort_ms();
    de.rm_dups();
    de.find_exts();

    de.print_ms(Decoder::PrintType::Human);
    de.write_to(argv[2], Decoder::PrintType::Original);

    de.print_hist(Ms::PayloadType::Moisture, 14);
    de.print_hist(Ms::PayloadType::Temperature, 14);

    return 0;
}

