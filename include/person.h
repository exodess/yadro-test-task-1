#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "resources.h"
#include "room.h"

class Room;
/*
Класс персонажа, который участвует в игре

Он хранит в себе информацию о:
- собранных ресурсах,
- целевом ресурсе,
- количестве оставшейся еды,
- комнатах, в которых побывал

Что может делать персонаж:
1. Входит в комнату - enter()
2. Собирать определенный ресурс - collect()
*/
class Person {
private:
    Resources resources_;
    num count_foods_;
    num current_room_ = 0;

public:
    Person() noexcept;
    // В начале известны только целевой ресурс и количество еды
    explicit Person(num foods) noexcept;
    void result(Resources& costs) noexcept; // расчет результата исходя из текущих расценок ресурсов

    // Вход в комнату
    void enter(Room& next_room) noexcept;
    // Сборка персонажем определенного ресурса в текущей пещере, где он находится
    void collect(Room& current_room, const std::string& target) noexcept;

    num getCurrentRoomNumber() const noexcept;
    num getCurrentCountFoods() const noexcept;
    bool isAlive() const noexcept;
};

#endif