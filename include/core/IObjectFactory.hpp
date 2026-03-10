#ifndef DICE_IOBJECT_FACTORY_HPP
#define DICE_IOBJECT_FACTORY_HPP

#include <memory>
#include <string>

#include "core/GameObject.hpp"

namespace dice::core {

class IObjectFactory {
public:
    virtual ~IObjectFactory() = default;
    virtual std::shared_ptr<GameObject>
    create(const std::string& type, const std::string& id, const std::string& name) = 0;
};

class GameObjectFactory : public IObjectFactory {
public:
    std::shared_ptr<GameObject>
    create(const std::string&, const std::string& id, const std::string& name) override {
        return std::make_shared<GameObject>(id, name);
    }
};

} // namespace dice::core

#endif // DICE_IOBJECT_FACTORY_HPP
