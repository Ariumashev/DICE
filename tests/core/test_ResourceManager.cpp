#include <memory>
#include <string>

#include "core/ResourceManager.hpp"
#include <gtest/gtest.h>

struct MockResource {
    bool loaded = false; // NOLINT(misc-non-private-member-variables-in-classes)

    bool loadFromFile([[maybe_unused]] const std::string& filename) {
        loaded = true;
        return true;
    }
};

TEST(ResourceManagerTest, LoadAndGetResource) {
    dice::core::ResourceManager<MockResource> manager;

    auto res = manager.load("res1", "file1.txt");

    ASSERT_NE(res, nullptr);
    EXPECT_TRUE(res->loaded);

    auto res2 = manager.get("res1");
    EXPECT_EQ(res, res2);
}

TEST(ResourceManagerTest, GetNonexistentResourceReturnsFallback) {
    dice::core::ResourceManager<MockResource> manager;

    auto fallback = std::make_shared<MockResource>();
    manager.setFallback(fallback);

    auto res = manager.get("not_exist");
    EXPECT_EQ(res, fallback);
}

TEST(ResourceManagerTest, ToJsonAndFromJson) {
    dice::core::ResourceManager<MockResource> manager;

    manager.load("res1", "file1.txt");
    manager.load("res2", "file2.txt");

    const nlohmann::json json = manager.toJson();

    dice::core::ResourceManager<MockResource> manager2;
    manager2.fromJson(json);

    auto res1 = manager2.get("res1");
    auto res2 = manager2.get("res2");

    EXPECT_TRUE(res1->loaded);
    EXPECT_TRUE(res2->loaded);
}

TEST(ResourceManagerTest, UnloadAndClear) {
    dice::core::ResourceManager<MockResource> manager;

    manager.load("res1", "file1.txt");
    manager.load("res2", "file2.txt");

    manager.unload("res1");
    EXPECT_EQ(manager.get("res1"), nullptr);

    manager.clear();
    EXPECT_EQ(manager.get("res2"), nullptr);
}

TEST(ResourceManagerTest, Create) {
    dice::core::ResourceManager<sf::Texture> TextureManager;
    auto tex = TextureManager.create("chip");
    tex.create(64, 64);
    sf::Image chipImage;
    chipImage.create(64, 64, sf::Color::Red);
    tex.update(chipImage);

    auto game_obj = std::make_shared<dice::components::Chip>("chip_1", "Red Chip");
    game_obj->setTexture(tex);

    ASSERT_NE(TextureManager.get("chip"), nullptr);
}