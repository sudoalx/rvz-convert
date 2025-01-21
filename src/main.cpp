// greetZ dolphin-emu and WIT team!
#include <algorithm>

#include "options.h"
#include <format>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main(const int argc, char *argv[]) {
    // get runtime flags/filepath
    parseOptions(argc, argv);
    char *filepath = argv[argc - 1];

    // convert rvz to iso using dolphin engine
    auto dolphinCommand =  std::format("dolphin-tool convert -i \"{}\" -f iso -o tmp.iso", filepath);
    std::system(dolphinCommand.c_str());

    // get game ID using wit (required for USB loader GX)
    std::system("wit id tmp.iso > id.txt");
    auto idstream = std::ifstream("id.txt");
    std::stringstream filebuf;
    filebuf << idstream.rdbuf();
    std::string id = filebuf.str();
    std::system("rm id.txt");
    id.erase(std::remove_if(id.begin(), id.end(), ::isspace), id.end());

    // convert iso to WBFS using wit
    auto witCommand = std::format("wit cp tmp.iso [{}].wbfs", id);
    std::system(witCommand.c_str());
    return 0;
}
