#include "ui/View.hpp"

#include <iostream>

namespace dice::view {

View::View(sf::RenderWindow& window) : window_(window) {
    spdlog::info("View initialized (basic rendering)");

    if (!window_.isOpen()) {
        spdlog::error("View constructed with closed window!");
    }
}

// ========== Basic methods ==========

void View::render(const std::vector<std::shared_ptr<core::GameObject>>& objects) {
    clear();

    drawObjects(objects);

    drawHUD();
}

void View::update(float deltaTime) {
    frameCount_++;
    fpsTimer_ += deltaTime;

    if (fpsTimer_ >= 1.0f) {
        fps_ = frameCount_ / fpsTimer_;
        frameCount_ = 0;
        fpsTimer_ = 0.0f;

        spdlog::debug("FPS: {:.1f}", fps_);
    }
}

// ========== Rendering ==========

void View::clear() {
    window_.clear(config_.backgroundColor);
}

void View::drawObjects(const std::vector<std::shared_ptr<core::GameObject>>& objects) {
    if (objects.empty()) {
        return;
    }

    sortedObjects_ = objects;
    std::sort(sortedObjects_.begin(), sortedObjects_.end(), [](const auto& a, const auto& b) {
        return a->getZOrder() < b->getZOrder();
    });

    for (const auto& obj : sortedObjects_) {
        if (obj && obj->isVisible()) {
            drawObject(obj);
        }
    }
}

void View::drawObject(std::shared_ptr<core::GameObject> obj) {
    window_.draw(*obj);

    if (obj->getType() == "Card") {
        auto card = std::dynamic_pointer_cast<components::Card>(obj);
        if (card) {
            drawCard(card);
        }
    } else if (obj->getType() == "Chip") {
        auto chip = std::dynamic_pointer_cast<components::Chip>(obj);
        if (chip) {
            drawChip(chip);
        }
    }
}

void View::drawCard(std::shared_ptr<components::Card> card) {
    sf::Vector2f pos = card->getPosition();
    pos.y -= 40.f;

    sf::CircleShape indicator(5.f);
    indicator.setPosition(pos.x, pos.y);
    indicator.setFillColor(card->isFaceUp() ? sf::Color::Green : sf::Color::Red);
    window_.draw(indicator);

    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    if (fontLoaded) {
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString("Player: " + std::to_string(card->getPlayer()));
        playerText.setCharacterSize(14);
        playerText.setFillColor(sf::Color::White);
        playerText.setPosition(pos.x - 30.f, pos.y - 50.f);
        window_.draw(playerText);
    }
}

void View::drawChip(std::shared_ptr<components::Chip> chip) {
    sf::CircleShape outline(chip->getRadius());
    outline.setPosition(chip->getPosition() - sf::Vector2f(chip->getRadius(), chip->getRadius()));
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::Cyan);
    outline.setOutlineThickness(2.f);

    window_.draw(outline);

    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    if (fontLoaded) {
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString("Player: " + std::to_string(chip->getPlayer()));
        playerText.setCharacterSize(14);
        playerText.setFillColor(sf::Color::White);
        playerText.setPosition(chip->getPosition().x - chip->getRadius(),
                               chip->getPosition().y - 50.f);
        window_.draw(playerText);
    }
}

void View::drawHUD() {
    if (!config_.showFPS)
        return;

    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    if (fontLoaded) {
        sf::Text fpsText;
        fpsText.setFont(font);
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps_)));
        fpsText.setCharacterSize(16);
        fpsText.setFillColor(sf::Color::White);
        fpsText.setPosition(10, 10);

        window_.draw(fpsText);

        sf::Text countText;
        countText.setFont(font);
        countText.setString("Objects: " + std::to_string(sortedObjects_.size()));
        countText.setCharacterSize(16);
        countText.setFillColor(sf::Color::White);
        countText.setPosition(10, 30);

        window_.draw(countText);
    } else {
        spdlog::warn("Font not loaded, HUD text not displayed");
    }
}

} // namespace dice::view