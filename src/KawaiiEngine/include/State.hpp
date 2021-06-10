#pragma once

#include <string_view>
#include <unordered_map>

#include "resources/ResourceLoader.hpp"
#include "graphics/Window.hpp"
#include "graphics/Shader.hpp"
#include "Camera.hpp"

#include "Event.hpp"

namespace kawe {

struct State {
    State(entt::registry &world, const Window &window)
    {
        const auto default_vert = world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/default.vert");
        const auto default_frag = world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/default.frag");
        shaders.emplace_back(std::make_unique<ShaderProgram>(
            "default", std::vector<uint32_t>{default_vert->shader_id, default_frag->shader_id}));

        const auto texture_2D_frag =
            world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/texture_2D.vert");
        const auto texture_2D_vert =
            world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/texture_2D.frag");

        shaders.emplace_back(std::make_unique<ShaderProgram>(
            "texture_2D", std::vector<uint32_t>{texture_2D_vert->shader_id, texture_2D_frag->shader_id}));

        const auto normal_frag = world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/normal.vert");
        const auto normal_vert = world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/normal.frag");

        shaders.emplace_back(std::make_unique<ShaderProgram>(
            "normal", std::vector<uint32_t>{normal_vert->shader_id, normal_frag->shader_id}));


        const auto picking_frag = world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/picking.vert");
        const auto picking_vert = world.ctx<ResourceLoader *>()->load<Shader>("./asset/shader/picking.frag");

        shaders.emplace_back(std::make_unique<ShaderProgram>(
            "picking", std::vector<uint32_t>{picking_vert->shader_id, picking_frag->shader_id}));

        camera.emplace_back(window, glm::vec3{10.0f, 10.0f, 10.0f}, Rect4<float>{0.0f, 0.8f, 0.2f, 0.2f});
        camera.emplace_back(window, glm::vec3{5.0f, 5.0f, 5.0f}, Rect4<float>{0.0f, 0.0f, 1.0f, 1.0f});

        for (const auto &i : magic_enum::enum_values<MouseButton::Button>()) {
            state_mouse_button[i] = false;
        }
        for (const auto &i : magic_enum::enum_values<Key::Code>()) { keyboard_state[i] = false; }
    }

    std::vector<std::unique_ptr<ShaderProgram>> shaders;

    std::vector<Camera> camera;

    glm::vec4 clear_color{0.0f, 1.0f, 0.2f, 1.0f};

    // inputs.
    glm::dvec2 mouse_pos{};
    glm::dvec2 mouse_pos_when_pressed{};

    std::unordered_map<MouseButton::Button, bool> state_mouse_button;
    std::unordered_map<Key::Code, bool> keyboard_state;

    bool is_running = true;
};

} // namespace kawe
