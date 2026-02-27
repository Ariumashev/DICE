#ifndef DICE_MODEL_HPP
#define DICE_MODEL_HPP

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/GameObject.hpp"

namespace dice::core {

using ObjectFactory = std::function<std::shared_ptr<GameObject>(
    const std::string& type, const std::string& id, const std::string& name)>;

class Model final {
public:
    Model() = default;
    explicit Model(ObjectFactory factory);

    void setFactory(ObjectFactory factory);

    const std::vector<std::shared_ptr<GameObject>>& roots() const noexcept {
        return roots_;
    }

    std::shared_ptr<GameObject> getObject(const std::string& id) const;

    void addRootObject(const std::shared_ptr<GameObject>& object);
    bool attachTo(const std::string& parentId, const std::shared_ptr<GameObject>& object);
    bool removeObject(const std::string& id);

    void forEachDepthFirst(const std::function<void(const std::shared_ptr<GameObject>&)>& fn) const;

    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& j);

    void clear();

private:
    std::vector<std::shared_ptr<GameObject>> roots_;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> objects_;
    ObjectFactory factory_;

private:
    void registerRecursive(const std::shared_ptr<GameObject>& obj);
    void unregisterRecursive(const std::shared_ptr<GameObject>& obj);

    static void
    forEachDepthFirstImpl(const std::shared_ptr<GameObject>& node,
                          const std::function<void(const std::shared_ptr<GameObject>&)>& fn);

    std::shared_ptr<GameObject> makeFromJsonNode(const nlohmann::json& nodeJson);
};

} // namespace dice::core

#endif // DICE_MODEL_HPP

