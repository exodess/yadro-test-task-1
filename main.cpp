#include "bot.h"
#include "logger.h"

#ifndef INPUT_FILE_PATH
#define INPUT_FILE_PATH "in.txt"
#endif

int main() {
    try {
        Logger logger;
        AliseBot bot(INPUT_FILE_PATH);
        bot.start();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}