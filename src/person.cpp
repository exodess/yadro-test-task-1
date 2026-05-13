#include "room.h"
#include "person.h"

#include <iostream>

// Создаем персонажа с заданными характеристиками
Person::Person(ASSETS target, num foods) noexcept
: target_resource_(target), count_foods_(foods)
{
#ifdef DEBUG
    std::cout << "[Person::Person] Constructor called:";
    std::cout << " target_resource_ = " << target_resource_;
    std::cout << ", count_foods_ = " << count_foods_ << std::endl;
#endif
}

void Person::death() noexcept {
    std::cout << "result " << resources_.iron() << " " << resources_.gold();
    std::cout << " " << resources_.gems() << " " << resources_.exp() << std::endl;
}


void Person::enter(num dung_number) noexcept {
    current_dungeon_ = dung_number;
    if (current_dungeon_) {
        std::cout << "go " << dung_number << std::endl;
    }

    visited_dungeons_.insert(dung_number);
    is_collected_ = false;
}

void Person::collect(ASSETS resources) noexcept {
    std::string name_resource;
    switch (resources) {
        case ASSETS::IRON:
            name_resource = "iron";
        case ASSETS::GOLD:
            name_resource = "gold";
        case ASSETS::GEMS:
            name_resource = "gems";
        case ASSETS::EXP:
            name_resource = "exp";
    }

    std::cout << "collect " << name_resource;
    if (is_collected_) {
        std::cout << " [repeat]";
    }
    is_collected_ = true;
    std::cout << std::endl;
}



