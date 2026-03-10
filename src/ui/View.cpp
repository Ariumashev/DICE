#include "ui/View.hpp"

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

    drawHUD(objects);
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

void View::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window_.setView(sf::View(visibleArea));
        spdlog::debug("Window resized to {}x{}", event.size.width, event.size.height);
    }
}

// ========== Coordinate transformation ==========

sf::Vector2f View::screenToWorld(const sf::Vector2i& screenPoint) const {
    return window_.mapPixelToCoords(screenPoint);
}

sf::Vector2i View::worldToScreen(const sf::Vector2f& worldPoint) const {
    return window_.mapCoordsToPixel(worldPoint);
}

// ========== Object search ==========

std::shared_ptr<core::GameObject>
View::pickObject(const sf::Vector2f& worldPos,
                 const std::vector<std::shared_ptr<core::GameObject>>& objects) const {
    sortedObjects_ = objects;
    sortObjectsByZOrder(sortedObjects_);

    for (auto it = sortedObjects_.rbegin(); it != sortedObjects_.rend(); ++it) {
        auto& obj = *it;
        if (obj && obj->isVisible() && obj->isActive()) {
            if (obj->contains(worldPos)) {
                return obj;
            }
        }
    }

    return nullptr;
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
    sortObjectsByZOrder(sortedObjects_);

    for (const auto& obj : sortedObjects_) {
        if (obj->isVisible()) {
            drawObject(obj);
        }
    }
}

void View::drawObject(std::shared_ptr<core::GameObject> obj) {
    window_.draw(*obj);
    // TODO
}

// ========== Interface rendering ==========

void View::drawHUD(const std::vector<std::shared_ptr<core::GameObject>>& objects) {
    sf::View currentView = window_.getView();
    window_.setView(window_.getDefaultView());

    if (config_.showFPS) {
        drawFPS();
    }

    if (config_.showObjectCount) {
        drawObjectCount(objects);
    }

    if (config_.showControls) {
        drawControls();
    }
    window_.setView(currentView);
}

void View::drawFPS() {
    std::stringstream ss;
    ss << "FPS: " << static_cast<int>(fps_);

    sf::Text text = createText(ss.str(), 16, config_.textColor, 10, 10);
    window_.draw(text);
}

void View::drawObjectCount(const std::vector<std::shared_ptr<core::GameObject>>& objects) {
    size_t visibleCount = 0;
    for (const auto& obj : objects) {
        if (obj && obj->isVisible()) {
            visibleCount++;
        }
    }

    std::stringstream ss;
    ss << "Objects: " << visibleCount << "/" << objects.size();
    sf::Text text = createText(ss.str(), 16, config_.textColor, 10, 30);
    window_.draw(text);
}

void View::drawControls() {
    std::vector<std::string> controls = {"Controls:", "ESC - Exit"};

    float startY = window_.getSize().y - 30.0f * controls.size();
    float y = startY;

    for (const auto& control : controls) {
        sf::Text text = createText(control, 14, config_.textColor, 10, y);
        window_.draw(text);
        y += 20.0f;
    }
}

// Support functions

sf::Font& View::getFont() {
    if (!fontLoaded_) {
        if (font_.loadFromFile(config_.fontPath)) {
            fontLoaded_ = true;
            spdlog::debug("Loaded font from {}", config_.fontPath);
        } else {
            spdlog::warn("Failed to load font from {}, using default", config_.fontPath);
        }
    }
    return font_;
}

sf::Text View::createText(
    const std::string& str, unsigned int size, const sf::Color& color, float x, float y) const {
    sf::Text text;

    if (fontLoaded_) {
        text.setFont(font_);
    }
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);

    return text;
}

void View::sortObjectsByZOrder(std::vector<std::shared_ptr<core::GameObject>>& objects) const {
    objects.erase(
        std::remove_if(objects.begin(), objects.end(), [](const auto& ptr) { return !ptr; }),
        objects.end());

    std::stable_sort(objects.begin(), objects.end(), [](const auto& a, const auto& b) {
        return a->getZOrder() < b->getZOrder();
    });
}

} // namespace dice::view