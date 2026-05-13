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
    bool is_collected_ = false; // Смотрит, когда

    // Смерть персонажа - оповещение программы и ее завершение
    void death() noexcept;

public:
    Person() noexcept;
    // В начале известны только целевой ресурс и количество еды
    explicit Person(num foods) noexcept;

    // Вход в комнату
    void enter(Room& next_room) noexcept;
    // Сборка персонажем определенного ресурса в текущей пещере, где он находится
    void collect(const Room& current_room, std::string target) noexcept;

    num currentRoomIndex() const noexcept;
};

#endif