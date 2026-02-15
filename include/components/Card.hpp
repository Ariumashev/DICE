#ifndef DICE_CARD_HPP
#define DICE_CARD_HPP

#include "core/GameObject.hpp"

namespace dice::components {

class Card : public core::GameObject {
public:
    Card(const std::string& id, const std::string& name);

    // ================= Player =================

    void setPlayer(int player_num) {
        player_num_ = player_num;
    }
    int getPlayer() const {
        return player_num_;
    }

    // ================= Textures =================

    void setFrontTexture(const sf::Texture* texture);

    void setBackTexture(const sf::Texture* texture);

    const sf::Texture* getFrontTexture() const {
        return front_texture_;
    }

    const sf::Texture* getBackTexture() const {
        return back_texture_;
    }

    // ================= State =================

    void setFaceUp(bool face_up);

    bool isFaceUp() const {
        return face_up_;
    }

    void flip() {
        setFaceUp(!face_up_);
    }

    // ================= Serialization =================

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& json) override;

private:
    int player_num_;
    const sf::Texture* front_texture_;
    const sf::Texture* back_texture_;
    bool face_up_;
};

} // namespace dice::components

#endif