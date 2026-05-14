#include "bot.h"
#include "logger.h"

#ifndef INPUT_FILE_PATH
#define INPUT_FILE_PATH "in.txt"
#endif

int main(int argc, char* argv[]) {

    std::string in_file = INPUT_FILE_PATH;

    if(argc == 2) {
        in_file = argv[1];
    }

    try {
        std::cout << "input file: " << in_file << std::endl;

        Logger logger;
        AliseBot bot(in_file);
        bot.start();

        std::cout << "output file: result.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
