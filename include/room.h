#ifndef ROOM_H
#define ROOM_H

#include "resources.h"
#include <iostream>
#include <vector>

// Класс комнаты в подземелье, который просто хранит в себе информацию о ресурсах
class Room {
private:
    num id_; // Уникальный ID
    Resources resources_; // Количества разных ресурсов в комнате
    std::map<std::string, bool> collected_list_; // запоминаем, какие ресурсы персонаж забирал
    bool is_visited_ = false; // Запоминаем, был ли персонаж в этой комнате

public:
    Room(num id, Resources resources);
    const Resources &getResources() const noexcept;
    num getId() const noexcept;
    void getState() noexcept;

    // При взятии какого-то ресурса, его количестве в пещере становится равным 0
    num takeResource(const std::string& target) noexcept;

    // Управление состоянием конкретной комнаты
    void visite() noexcept;
    bool isVisited() const noexcept;
    bool isCollected() const noexcept;
};

#endif