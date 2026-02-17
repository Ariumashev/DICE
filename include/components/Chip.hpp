#ifndef DICE_CHIP_HPP
#define DICE_CHIP_HPP

#include "core/GameObject.hpp"

namespace dice::components {

class Chip : public core::GameObject {
public:
    Chip(const std::string& id, const std::string& name);

    // ================= Visual / picking =================

    void setAssetId(const std::string& asset_id) {
        asset_id_ = asset_id;
    }
    const std::string& getAssetId() const {
        return asset_id_;
    }

    void setRadius(float radius) {
        radius_ = radius;
    }
    float getRadius() const {
        return radius_;
    }

    bool hitTest(const sf::Vector2f& world_point) const;

    // ================= Player =================

    void setPlayer(int player_num) {
        player_num_ = player_num;
    }
    int getPlayer() const {
        return player_num_;
    }

    // ========== Serialization ==========

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

private:
    int player_num_;

    std::string asset_id_;
    float radius_;
};

} // namespace dice::components

#endif
