#ifndef RESOURCES_H
#define RESOURCES_H

#include <cstdint>
#include <map>
#include <iostream>

// Ценности каждого ресурса в у.е
#define DEFAULT_IRON_COST 7
#define DEFAULT_GOLD_COST 11
#define DEFAULT_GEMS_COST 23
#define DEFAULT_EXP_COST 1

// Все игровые значения в пределах [0, 255],
// поэтому можно использовать 8-битное беззнаковое число для их хранения
using num = uint8_t;

// Класс для хранения игровых ресурсов
class Resources {
private:
    std::map<std::string, num> resources_;

public:
    Resources() noexcept : Resources(0, 0, 0, 0) {}

    Resources(num iron, num gold, num gems, num exp) noexcept {
        resources_.insert(std::make_pair("iron", iron));
        resources_.insert(std::make_pair("gold", gold));
        resources_.insert(std::make_pair("gems", gems));
        resources_.insert(std::make_pair("exp", exp));
    }

    // Поле доступа к приватным членам класса через []
    num& operator[](const std::string& name) noexcept {
        if (!resources_.contains(name)) {
            throw std::logic_error("Resource " + name + "don't exists");
        }

        return resources_[name];
    }
};

#endif