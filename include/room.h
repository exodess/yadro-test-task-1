#ifndef DUNGEON_H
#define DUNGEON_H
#include "resources.h"
#include <iostream>

// Класс комнаты в подземелье, который просто хранит в себе уникальный ID и доступные ресурсы
class Room {
private:
    num id_;
    Resources resources_;

public:
    Room(num id, Resources resources);
    const Resources &getResources() const noexcept;

    // При взятии какого-то ресурса, его количестве в пещере становится равным 0
    num giveResource(ASSETS target);
};

#endif