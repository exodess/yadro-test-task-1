#ifndef RESOURSES_H
#define RESOURSES_H

#include <cstdint>

// Ценности каждого ресурса в у.е
#define IRON_COST 7
#define GOLD_COST 11
#define GEMS_COST 23
#define EXP_COST 1

// Все игровые значения в пределах [0, 255],
// поэтому можно использовать 8-битное беззнаковое число для их хранения
using num = uint8_t;

// Класс для хранения игровых ресурсов
class Resourses {
private:
    num iron_;
    num gold_;
    num gems_;
    num exp_;

public:
    Resourses() noexcept : iron_(0), gold_(0), gems_(0), exp_(0) {}

    Resourses(num iron, num gold, num gems, num exp) noexcept
    : iron_(iron), gold_(gold), gems_(gems), exp_(exp) {}

    // Поля доступа к приватным членам класса
    num& iron() noexcept { return iron_; }
    num& gems() noexcept { return gems_; }
    num& gold() noexcept { return gold_; }
    num& exp() noexcept { return exp_; }
};

enum ASSETS {
    IRON = 0,
    GOLD,
    GEMS,
    EXP
};

#endif