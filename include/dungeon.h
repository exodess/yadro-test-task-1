#ifndef DUNGEON_H
#define DUNGEON_H
#include "person.h"

// Класс пещеры, который просто хранит в себе уникальный ID и доступные ресурсы
class Dungeon {
private:
    num id_;
    Resourses resourses_;

public:
    Dungeon(num id, Resourses resourses);

    // При взятии какого-то ресурса, его количестве в пещере становится равным 0
    num getIron() noexcept;
    num getGold() noexcept;
    num getGems() noexcept;
    num getExp() noexcept;
};

#endif