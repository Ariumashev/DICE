#ifndef DICE_DEFAULT_FACTORY_HPP
#define DICE_DEFAULT_FACTORY_HPP

#include <memory>

#include "components/Card.hpp"
#include "components/Chip.hpp"
#include "core/GameObject.hpp"
#include "core/Model.hpp"

namespace dice::scene {

inline dice::core::ObjectFactory makeDefaultFactory() {
    return [](const std::string& type,
              const std::string& id,
              const std::string& name) -> std::shared_ptr<dice::core::GameObject> {
        if (type == "Chip") {
            return std::make_shared<dice::components::Chip>(id, name);
        }
        if (type == "Card") {
            return std::make_shared<dice::components::Card>(id, name);
        }
        return std::make_shared<dice::core::GameObject>(id, name);
    };
}

} // namespace dice::scene

#endif // DICE_DEFAULT_FACTORY_HPP
