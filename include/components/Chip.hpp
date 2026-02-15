#ifndef DICE_CHIP_HPP
#define DICE_CHIP_HPP

#include "core/GameObject.hpp"

namespace dice::components {

class Chip : public core::GameObject {
public:
    Chip(const std::string& id, const std::string& name);

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
};

} // namespace dice::components

#endif