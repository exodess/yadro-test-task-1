#include "room.h"
#include "person.h"
#include "logger.h"

#include <iostream>

// Создаем пустого персонажа
Person::Person() noexcept : Person(0) {}

// Создаем персонажа с заданными характеристиками
Person::Person(num foods) noexcept : count_foods_(foods){
#ifdef DEBUG
    std::cout << "[Person::Person] Constructor called:";
    std::cout << " count_foods_ = " << static_cast<int>(count_foods_) << std::endl;
#endif
}

void Person::result(Resources& costs) noexcept {
    Logger::file() << "result " << static_cast<int>(resources_["iron"]) << " ";
    Logger::file() << static_cast<int>(resources_["gold"]) << " ";
    Logger::file() << static_cast<int>(resources_["gems"]) << " ";
    Logger::file() << static_cast<int>(resources_["exp"]) << " ";

    int sum = resources_["iron"] * costs["iron"] +
            resources_["gold"] * costs["gold"] +
            resources_["gems"] * costs["gems"] +
            resources_["exp"] * costs["exp"];

    Logger::file() << sum << std::endl;

}

void Person::enter(Room& next_room) noexcept {
    current_room_ = next_room.getId();
    Logger::file() << "go " << static_cast<int>(current_room_) << std::endl;
    next_room.visite();

    count_foods_--;
}

void Person::collect(Room& current_room, const std::string& name_resource) noexcept {

    Logger::file() << "collect " << name_resource << std::endl;
    // Проверяем, брал ли персонаж в этой комнате ресурсы, или нет
    if (current_room.isCollected()) {
        count_foods_--;
    }

    // Прибавляем количество определенного ресурса, который персонаж забрал из текущей комнаты, к общему количеству
    resources_[name_resource] += current_room.takeResource(name_resource);
}

num Person::getCurrentRoomNumber() const noexcept {
    return current_room_;
}

num Person::getCurrentCountFoods() const noexcept {
    return count_foods_;
}

bool Person::isAlive() const noexcept {
    return count_foods_ > 0;
}

