#include "bot.h"
#include "logger.h"
#include <stdexcept>

#ifndef INPUT_FILE_PATH
#define INPUT_FILE_PATH "in.txt"
#endif

int main(int argc, char* argv[]) {

    Logger logger;
    std::string in_file = INPUT_FILE_PATH;

    if(argc == 2) {
        in_file = argv[1];
    }
    std::cout << "input file: " << in_file << std::endl;

    try {

        AliseBot bot(in_file);
        bot.start();

    } catch (const std::exception& e) {
        // Ошибки при работе программы отслеживаются через исключения,
        // информация об ошибке записывается в выходной файл
        Logger::file() << e.what() << '\n';
    } 

    std::cout << "output file: result.txt" << std::endl;

    return 0;
}
