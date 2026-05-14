#include "logger.h"

std::ofstream Logger::fd_;

Logger::Logger() {
    fd_.open(out_file);

    if (!fd_.is_open()) {
        throw std::runtime_error("Could not open log file" + out_file);
    }
}

Logger::~Logger() {
    if (fd_.is_open()) {
        fd_.close();
    }
}

std::ofstream& Logger::file() noexcept {
    return fd_;
}