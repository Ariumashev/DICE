#include "components/Chip.hpp"

#include <algorithm>
#include <cmath>

namespace dice::components {

Chip::Chip(const std::string& id, const std::string& name)
    : GameObject(id, name), player_num_(0), asset_id_(""), radius_(32.f) {
    setType("Chip");
}

bool Chip::hitTest(const sf::Vector2f& world_point) const {
    if (radius_ > 0.f) {
        const auto center = getPosition();
        const auto scale = getScale();
        const float r = radius_ * std::max(std::abs(scale.x), std::abs(scale.y));

        const float dx = world_point.x - center.x;
        const float dy = world_point.y - center.y;
        return (dx * dx + dy * dy) <= (r * r);
    }

    return contains(world_point);
}

nlohmann::json Chip::toJson() const {
    nlohmann::json json = GameObject::toJson();
    json["player"] = player_num_;
    if (!asset_id_.empty()) {
        json["assetId"] = asset_id_;
    }
    json["radius"] = radius_;
    return json;
}

void Chip::fromJson(const nlohmann::json& json) {
    GameObject::fromJson(json);

    if (json.contains("player")) {
        player_num_ = json["player"].get<int>();
    }

    if (json.contains("assetId")) {
        asset_id_ = json["assetId"].get<std::string>();
    }

    if (json.contains("radius")) {
        radius_ = json["radius"].get<float>();
    }
}

} // namespace dice::components
