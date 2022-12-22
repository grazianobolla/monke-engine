#include "monke/core/sprite_renderer.h"
#include "monke/core/resource_loader.h"
#include "monke/core/display.h"

#include "monke/external/glm/gtc/matrix_transform.hpp"

void mk::SpriteRenderer::initialize()
{
    // load shader
    this->shader = static_cast<mk::Shader *>(mk::ResourceLoader::get("sprite_shader"));

    // set vertex data
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    // init empty vertex buffer
    glBufferData(GL_ARRAY_BUFFER, SPRITE_SIZE_IN_FLOATS * sizeof(float), NULL, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE_IN_FLOATS * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    log_info("sprite renderer initialized");
}

void mk::SpriteRenderer::draw(const mk::Sprite &sprite)
{
    if (!this->shader->loaded || !sprite.texture->loaded)
    {
        log_info("sprite renderer can't flush missing data");
        return;
    }

    // bind texture and shader
    sprite.texture->use();
    this->shader->use();

    // set vertex data
    mk::Vector2 tex_size = {sprite.texture_rect.w / sprite.texture->width, sprite.texture_rect.h / sprite.texture->height};
    mk::Vector2 tex_coords = {sprite.texture_rect.x / sprite.texture->width, sprite.texture_rect.y / sprite.texture->height};

    float sprite_vertex_data[SPRITE_SIZE_IN_FLOATS] =
        {0, 0, tex_coords.x, tex_coords.y,
         1, 0, tex_coords.x + tex_size.x, tex_coords.y,
         0, 1, tex_coords.x, tex_coords.y + tex_size.y,
         0, 1, tex_coords.x, tex_coords.y + tex_size.y,
         1, 1, tex_coords.x + tex_size.x, tex_coords.y + tex_size.y,
         1, 0, tex_coords.x + tex_size.x, tex_coords.y};

    //  set projection
    this->shader->set_mat4("projection", mk::Display::projection);

    // set transform
    glm::mat4 transform = this->calculateTransform(sprite);
    this->shader->set_mat4("transform", transform);

    // bind vao
    glBindVertexArray(this->vao_id);

    // send data
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, SPRITE_SIZE_IN_FLOATS * sizeof(float), sprite_vertex_data);

    glDrawArrays(GL_TRIANGLES, 0, VERTEX_PER_SPRITE); // draw vertices
}

glm::mat4 mk::SpriteRenderer::calculateTransform(const mk::Sprite &sprite)
{
    glm::vec2 size = glm::vec2(sprite.texture_rect.w * sprite.scale.x, sprite.texture_rect.h * sprite.scale.y);

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(sprite.position.x, sprite.position.y, 0));

    transform = glm::translate(transform, glm::vec3(size.x / 2.0f, size.y / 2.0f, 0));
    transform = glm::rotate(transform, glm::radians(sprite.rotation), glm::vec3(0, 0, 1));
    transform = glm::translate(transform, glm::vec3(-size.x / 2.0f, -size.y / 2.0f, 0));

    transform = glm::scale(transform, glm::vec3(size, 0));

    return transform;
}