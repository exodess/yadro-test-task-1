#include "bot.h"

#ifndef INPUT_FILE_PATH
#define INPUT_FILE_PATH "in1_success.txt"
#endif

int main() {
    try {
        AliseBot bot(INPUT_FILE_PATH);
        bot.start();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}