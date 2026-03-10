#ifndef DICE_VIEW_HPP
#define DICE_VIEW_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "core/GameObject.hpp"
#include <spdlog/spdlog.h>

namespace dice::view {

struct ViewConfig {
    sf::Color backgroundColor = sf::Color(50, 50, 50);

    // Interface Settings
    bool showFPS = true;
    bool showObjectCount = true;
    bool showControls = true;

    sf::Color textColor = sf::Color::White;

    // Font
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
};

class View {
public:
    explicit View(sf::RenderWindow& window);

    View(const View&) = delete;
    View& operator=(const View&) = delete;

    ~View() = default;

    // ========== Basic methods ==========

    void render(const std::vector<std::shared_ptr<core::GameObject>>& objects);

    void update(float deltaTime);

    void handleEvent(const sf::Event& event);

    // ========== Settings ==========

    void setConfig(const ViewConfig& config) {
        config_ = config;
    }
    ViewConfig& getConfig() {
        return config_;
    }

    // ========== Coordinate transformation ==========

    sf::Vector2f screenToWorld(const sf::Vector2i& screenPoint) const;
    sf::Vector2i worldToScreen(const sf::Vector2f& worldPoint) const;

    // ========== Object search ==========

    std::shared_ptr<core::GameObject>
    pickObject(const sf::Vector2f& worldPos,
               const std::vector<std::shared_ptr<core::GameObject>>& objects) const;

private:
    // ========== Internal rendering methods ==========

    void clear();

    void drawObjects(const std::vector<std::shared_ptr<core::GameObject>>& objects);

    void drawObject(std::shared_ptr<core::GameObject> obj);

    void drawHUD(const std::vector<std::shared_ptr<core::GameObject>>& objects);

    void drawFPS();
    void drawObjectCount(const std::vector<std::shared_ptr<core::GameObject>>& objects);
    void drawControls();

    // Support functions

    sf::Font& getFont();
    sf::Text createText(
        const std::string& str, unsigned int size, const sf::Color& color, float x, float y) const;
    void sortObjectsByZOrder(std::vector<std::shared_ptr<core::GameObject>>& objects) const;

    // ========== Condition ==========

    sf::RenderWindow& window_;
    ViewConfig config_;

    float fps_ = 0.0f;
    int frameCount_ = 0;
    float fpsTimer_ = 0.0f;

    mutable sf::Font font_;
    mutable bool fontLoaded_ = false;

    mutable std::vector<std::shared_ptr<core::GameObject>> sortedObjects_;
};

} // namespace dice::view

#endif