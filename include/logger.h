#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

// Этот класс предназначен для предоставления доступа к файлу,
// в который будут записываться результаты работы бота

class Logger {
    std::string out_file = "result.txt"; // Путь до файла назначения
    static std::ofstream fd_;

public:
    Logger();
    ~Logger();

    static std::ofstream& file() noexcept; // С помощью статического
};

#endif