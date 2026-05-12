#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include "resourses.h"

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
    Resourses resourses_;
    ASSETS target_resource_;
    num count_foods_;
    std::vector<num> visited_dungeouns_;

    // Смерть персонажа - оповещение программы и ее завершение
    void death() noexcept;

public:
    // В начале известны только целевой ресурс и количество еды
    Person(ASSETS target, num foods) noexcept;

    void enter(Dungeon dung) noexcept; // Вход в пещеру
    void collect(ASSETS target) noexcept; // Сборка персонажем определенного ресурса в текущей пещере, где он находится

};

#endif