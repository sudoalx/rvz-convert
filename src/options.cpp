#include <getopt.h>
#include <iostream>
#define VERSION "v1.0.0-rc1"

void version() {
    std::cout << "rvz-convert " << VERSION << std::endl;
}

void help() {
    std::cout << "Usage: rvz-convert [options] file" << std::endl;
    std::cout << "Options:\n\t-h --help\t\tDisplay this message" << std::endl;
    std::cout << "\t-v --version\tDisplay version information" << std::endl;
}

void parseOptions(int argc, char *argv[]) {
    int c;
    int option_index = 0;

    while (true) {
        static option options[] = {
            {"version",no_argument, nullptr, 'v'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, 0, nullptr, 0}
        };
        c = getopt_long(argc, argv, "hv", options, &option_index);
        if (c == -1)
            break;
        switch (c) {
            case 'h':
                help();
                break;
            case 'v':
                version();
                break;
            default:
                help();
                break;
        }
    }
}
