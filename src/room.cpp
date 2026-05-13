#include "room.h"

Room::Room(num id, Resources resources) : id_(id), resources_(resources) {
#ifdef DEBUG
    std::cout << "[Room: Constructor] ID = " << id_;
    std::cout << ", iron = " << resources_.iron();
    std::cout << ", gold = " << resources_.gold();
    std::cout << ", gems = " << resources_.gems();
    std::cout << ", exp = " << resources_.exp();
#endif
}

const Resources& Room::getResources() const noexcept {
    return resources_;
}

num Room::getId() const noexcept {
    return id_;
}

num Room::takeResource(const std::string& target) noexcept {
    num result = 0;

    if (target == "iron") {
        result = resources_.iron();
        resources_.iron() = 0;
    }
    else if (target == "gold" ) {
        result = resources_.gold();
        resources_.gold() = 0;
    }
    else if (target == "gems") {
        result = resources_.gems();
        resources_.gems() = 0;
    }
    else if (target == "exp") {
        result = resources_.exp();
        resources_.exp() = 0;
    }

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

void Room::getState() noexcept {
    // Выводим состояния для всех комнат, кроме начальной
    if (id_) {
        std::cout << "state " << id_ << " ";
        std::cout << ((resources_.iron()) ? resources_.iron() : "_") << " ";
        std::cout << ((resources_.gold()) ? resources_.gold() : "_") << " ";
        std::cout << ((resources_.gems()) ? resources_.gems() : "_") << " ";
        std::cout << ((resources_.exp()) ? resources_.exp() : "_") << " ";
    }
}