#include "core/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

namespace dice::core {

// ========== Load by filename ==========
template <typename resource>
std::shared_ptr<resource> ResourceManager<resource>::load(const std::string& id,
                                                          const std::string& filename) {
    if (auto it = resources_.find(id); it != resources_.end()) {
        spdlog::error(
            "ResourceManager: failed to load file from '{}' by assigning existing id - '{}'",
            filename,
            id);

        return fallback_;
    }

    auto resource = std::make_shared<resource>();

    if (!resource->loadFromFile(filename)) {
        spdlog::error("ResourceManager: failed to load from '{}'", filename);

        return fallback_;
    }

    resources_.emplace(id, resource);
    return resource;
}

// ========== Get resource by id ==========
template <typename resource>
std::shared_ptr<resource> ResourceManager<resource>::get(const std::string& id) const {
    if (auto it = resources_.find(id); it != resources_.end()) {
        return it->second;
    }

    spdlog::warn("ResourceManager: resource '{}' not found", id);

    return fallback_;
}

} // namespace dice::core
