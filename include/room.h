#ifndef ROOM_H
#define ROOM_H

#include "resources.h"
#include <iostream>

// Класс комнаты в подземелье, который просто хранит в себе уникальный ID и доступные ресурсы
class Room {
private:
    num id_;
    Resources resources_;
    bool is_visited_ = false;

public:
    Room(num id, Resources resources);
    const Resources &getResources() const noexcept;
    num getId() const noexcept;
    void getState() noexcept;

    // При взятии какого-то ресурса, его количестве в пещере становится равным 0
    num takeResource(const std::string& target) noexcept;

    // Управление посещением конкретной комнаты
    void visite() noexcept;
    bool isVisited() const noexcept;
};

#endif