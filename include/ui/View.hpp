#ifndef DICE_VIEW_HPP
#define DICE_VIEW_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "components/Card.hpp"
#include "components/Chip.hpp"
#include "core/GameObject.hpp"
#include <spdlog/spdlog.h>

namespace dice::view {

struct ViewConfig {
    sf::Color backgroundColor = sf::Color(50, 50, 50);
    bool showFPS = true;
};

class View {
public:
    View(sf::RenderWindow& window);

    // ========== Basic methods ==========

    void render(const std::vector<std::shared_ptr<core::GameObject>>& objects);

    void update(float deltaTime);

    // ========== Settings ==========

    void setConfig(const ViewConfig& config) {
        config_ = config;
    }
    ViewConfig& getConfig() {
        return config_;
    }

private:
    // ========== Internal rendering methods ==========

    void clear();

    void drawObjects(const std::vector<std::shared_ptr<core::GameObject>>& objects);

    void drawObject(std::shared_ptr<core::GameObject> obj);

    void drawCard(std::shared_ptr<components::Card> card);
    void drawChip(std::shared_ptr<components::Chip> chip);

    void drawHUD();

    // ========== Condition ==========

    sf::RenderWindow& window_;
    ViewConfig config_;

    float fps_ = 0.0f;
    int frameCount_ = 0;
    float fpsTimer_ = 0.0f;

    mutable std::vector<std::shared_ptr<core::GameObject>> sortedObjects_;
};

} // namespace dice::view

#endif