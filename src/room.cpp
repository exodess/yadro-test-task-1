#include "room.h"

#include <ext/concurrence.h>

Room::Room(num id, Resources resources) : id_(id), resources_(resources) {
#ifdef DEBUG
    std::cout << "[Room: Constructor] ID = " << static_cast<int>(id_);
    std::cout << ", iron = " << static_cast<int>(resources_["iron"]);
    std::cout << ", gold = " << static_cast<int>(resources_["gold"]);
    std::cout << ", gems = " << static_cast<int>(resources_["gems"]);
    std::cout << ", exp = " << static_cast<int>(resources_["exp"]);
    std::cout << std::endl;
#endif
}

const Resources& Room::getResources() const noexcept {
    return resources_;
}

num Room::getId() const noexcept {
    return id_;
}

num Room::takeResource(const std::string& target) noexcept {
    num result = resources_[target];
    resources_[target] = 0;
    collected_list_[target] = true;

    getState();

    return result;
}

void Room::visite() noexcept {
    is_visited_ = true;
    getState();
}

bool Room::isVisited() const noexcept {
    return is_visited_;
}

bool Room::isCollected() const noexcept {
    return !collected_list_.empty();
}

void Room::getState() noexcept {
    // Выводим состояния для всех комнат, кроме начальной
    if (id_) {
        std::cout << "state " << static_cast<int>(id_) << " ";

        // Если персонаж забрал ресурс, будет отображаться "_"
        if (!collected_list_.count("iron")) {
            std::cout << static_cast<int>(resources_["iron"]) << " ";
        } else {
            std::cout << "_ ";
        }

        if (!collected_list_.contains("gold")) {
            std::cout << static_cast<int>(resources_["gold"]) << " ";
        } else {
            std::cout << "_ ";
        }

        if (!collected_list_.contains("gems")) {
            std::cout << static_cast<int>(resources_["gems"]) << " ";
        } else {
            std::cout << "_ ";
        }

        if (!collected_list_.contains("exp")) {
            std::cout << static_cast<int>(resources_["exp"]) << std::endl;
        } else {
            std::cout << "_" << std::endl;
        }
    }
}