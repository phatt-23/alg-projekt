#include "inc/decoder.h"
#include "inc/utilities.h"

int main(int argc, char **argv)
{
    check_cl_args(argc, argv);

    // read in the data
    Decoder de{};
    de.read_in(argv[1]);

    // sort the measurements and remove duplicates
    de.sort_ms();
    de.rm_dups();

    // find the extremes and print them to stdout
    de.find_exts();

    // print out to stdout in human redable form
    // de.print_ms(Decoder::PrintType::Human);

    // write the sorted and filtered data to a file
    de.write_to(argv[2], Decoder::PrintType::Original);

    int number_of_intervals = std::atoi(argv[3]);

    // print histograms
    de.print_hist(Ms::PayloadType::Moisture, number_of_intervals);
    de.print_hist(Ms::PayloadType::Temperature, number_of_intervals);

    // printing out some retrieved measurements 
    // (only for the iot_sensor_data_2.txt)
    Measurement* l_ms = nullptr;
    if((l_ms = de.get_ms("2023-04-13T22:00:00")))
        l_ms->print_formated();
    else printf("nothing found\n");
    
    if((l_ms = de.get_ms("2023-04-27T10:00:00")))
        l_ms->print_formated();
    else printf("nothing found\n");
    
    // this one wont find anything
    if((l_ms = de.get_ms("2024-02-01T12:03:56")))
        l_ms->print_formated();
    else printf("nothing found\n");

    return 0;
}
