// greetZ dolphin-emu and WIT team!
#include <algorithm>
#include "options.h"
#include <format>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <memory>

// execute cmds and capture output//exit status
int executeCommand(const std::string& command, bool printOutput = true) {
    std::cout << "Executing: " << command << "\n";
    
    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen((command + " 2>&1").c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Error: Failed to execute command\n";
        return -1;
    }

    // read the output from the command
    char buffer[128];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        output += buffer;
        if (printOutput) {
            std::cout << buffer;
        }
    }

    // get the exit status of the command after closing the pipe
    int status = pclose(pipe.release());
    if (WIFEXITED(status)) {
        status = WEXITSTATUS(status);
    }
    
    if (status != 0) {
        std::cerr << "Command failed with exit code: " << status << "\n";
        if (!printOutput) {
            std::cerr << "Error output:\n" << output << "\n";
        }
    }
    return status;
}

int main(const int argc, char *argv[]) {
    // parse command line options
    parseOptions(argc, argv);
    char *filepath = argv[argc - 1];
    std::string tmpIso = "tmp_conversion.iso";

    try {
        // Step 1: Convert RVZ to ISO using dolphin-tool
        std::cout << "\n=== Converting RVZ to ISO ===\n";
        auto dolphinCommand = std::format("dolphin-tool convert -i \"{}\" -f iso -o {}", filepath, tmpIso);
        if (executeCommand(dolphinCommand) != 0) {
            throw std::runtime_error("RVZ to ISO conversion failed");
        }

        // Step 2: Extract Game ID with WIT
        std::cout << "\n=== Extracting Game ID ===\n";
        if (executeCommand("wit id " + tmpIso + " > id.txt", false) != 0) {
            throw std::runtime_error("Game ID extraction failed");
        }

        std::ifstream idFile("id.txt");
        if (!idFile) {
            throw std::runtime_error("Failed to open ID file");
        }
        
        std::string id;
        std::getline(idFile, id);
        id.erase(std::remove_if(id.begin(), id.end(), ::isspace), id.end());
        idFile.close();
        std::remove("id.txt");
        
        if (id.empty()) {
            throw std::runtime_error("Obtained empty Game ID");
        }
        std::cout << "Game ID: " << id << "\n";

        // Step 3: Convert to WBFS with progress bar using WIT
        std::cout << "\n=== Converting to WBFS ===\n";
        auto witCommand = std::format("wit cp --progress {} \"[{}].wbfs\"", tmpIso, id);
        if (executeCommand(witCommand) != 0) {
            throw std::runtime_error("WBFS conversion failed");
        }

        std::cout << "\n=== Conversion Complete! ===\n";
    }
    catch (const std::exception& e) {
        std::cerr << "\n!!! ERROR: " << e.what() << " !!!\n";
        return 1;
    }

    // cleanup temporary files
    std::remove(tmpIso.c_str());
    return 0;
}