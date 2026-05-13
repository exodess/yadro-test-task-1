#include "room.h"
#include "person.h"

#include <iostream>

// Создаем пустого персонажа
Person::Person() noexcept : Person(0) {}

// Создаем персонажа с заданными характеристиками
Person::Person(num foods) noexcept
: count_foods_(foods)
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


void Person::enter(Room& next_room) noexcept {
    current_room_ = next_room.getId();
    next_room.visite();

    if (current_room_) {
        std::cout << "go " << current_room_ << std::endl;
    }

    is_collected_ = false;
    if (count_foods_--) {
        death();
    }

}

void Person::collect(const Room& current_room, std::string name_resource) noexcept {

    std::cout << "collect " << name_resource;
    if (is_collected_) {
        std::cout << " [repeat]";
        count_foods_--;
    }
    is_collected_ = true;
    std::cout << std::endl;
}

num Person::currentRoomIndex() const noexcept {
    return current_room_;
}


