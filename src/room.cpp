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

num Room::giveResource(ASSETS target) noexcept {
    num result = 0;

    switch (target) {
        case ASSETS::IRON:
            result = resources_.iron();
            resources_.iron() = 0;
        case ASSETS::GOLD:
            result = resources_.gold();
            resources_.gold() = 0;
        case ASSETS::GEMS:
            result = resources_.gems();
            resources_.gems() = 0;
        case ASSETS::EXP:
            result = resources_.exp();
            resources_.exp() = 0;
    }

    return result;
}
