#include "monke/core/renderer.h"
#include "monke/core/resource_loader.h"

void mk::Renderer::initialize()
{
    this->default_shader = static_cast<mk::Shader *>(mk::ResourceLoader::get("default_shader"));
    this->batch_renderer.initialize();
    this->sprite_renderer.initialize();
}

void mk::Renderer::draw(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale)
{
    this->batch_renderer.draw(texture, texture_rect, position, scale);
}

void mk::Renderer::draw(const mk::Sprite &sprite)
{
    this->sprite_renderer.draw(sprite);
}

void mk::Renderer::flush()
{
    this->batch_renderer.flush();
    // other flushes here
}

void mk::Renderer::update_shader(const glm::mat4 &projection_matrix, const glm::mat4 &view_matrix)
{
    // set default shader values (projection & camera/view)
    this->default_shader->set_mat4("projection", projection_matrix); //  set projection
    this->default_shader->set_mat4("view", view_matrix);             // set camera matrix
}