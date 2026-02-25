#ifndef DICE_RESOURCE_MANAGER_HPP
#define DICE_RESOURCE_MANAGER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include <spdlog/spdlog.h>

namespace dice::core {

template <typename resource> class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    // ========== Load by filename ==========
    std::shared_ptr<resource> load(const std::string& id, const std::string& filename);

    // ========== Get resource by id ==========
    std::shared_ptr<resource> get(const std::string& id) const;

    // ========== Remove resource ==========
    void unload(const std::string& id) {
        resources_.erase(id);
    };

    // ========== Clear all resources ==========
    void clear() {
        resources_.clear();
    };

    // ========== Set fallback resource ==========
    void setFallback(std::shared_ptr<resource> fallback) {
        fallback_ = std::move(fallback);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<resource>> resources_{};
    std::shared_ptr<resource> fallback_ = nullptr;
};

} // namespace dice::core

#endif // DICE_RESOURCE_MANAGER_HPP
