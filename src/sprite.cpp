#include "sprite.h"
#include "log.h"
#include "resource_loader.h"
#include "engine.h"

#include <glad/glad.h>

void mk::Sprite::load(const char *texture_resource_name, const char *shader_resource_name)
{
    this->setup_sprite_vertex_data();

    this->shader = static_cast<mk::Shader *>(mk::ResourceLoader::get(shader_resource_name));
    this->texture = static_cast<mk::Texture *>(mk::ResourceLoader::get(texture_resource_name));

    if (shader == NULL)
        log_info("warning: shader " << shader_resource_name << " could not be loaded");

    if (texture == NULL)
        log_info("warning: texture " << texture_resource_name << " could not be loaded");
}

void mk::Sprite::draw(const glm::vec2 &position, const glm::vec2 &scale)
{
    if (this->shader == NULL || this->texture == NULL)
        return;

    this->shader->use();
    this->shader->set_mat4("projection", mk::Display::projection);

    glm::mat4 model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, {position, 0});

    model_matrix = glm::scale(model_matrix, {this->texture->width * scale.x,
                                             this->texture->height * scale.y,
                                             0});

    this->shader->set_mat4("model", model_matrix);

    this->texture->use();

    glBindVertexArray(this->sprite_vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void mk::Sprite::draw_partial(const glm::vec2 &position, const glm::vec4 &texture_coordinates, const glm::vec2 &scale)
{
    if (this->shader == NULL || this->texture == NULL)
        return;

    this->shader->use();
    this->shader->set_mat4("projection", mk::Display::projection);

    glm::mat4 model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, {position, 0});

    model_matrix = glm::scale(model_matrix, {texture_coordinates.w * scale.x,
                                             texture_coordinates.z * scale.y,
                                             0});

    this->shader->set_mat4("model", model_matrix);

    this->texture->use();

    //texture data
    float rect_x = texture_coordinates.x / this->texture->width;
    float rect_y = texture_coordinates.y / this->texture->height;
    float rect_width = texture_coordinates.z / this->texture->width;
    float rect_height = texture_coordinates.w / this->texture->height;

    float uv_data[8] = {
        rect_x, rect_y + rect_height,
        rect_x + rect_width, rect_y + rect_height,
        rect_x, rect_y,
        rect_x + rect_width, rect_y};

    //draw and update uv's
    glBindVertexArray(this->sprite_vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->uv_array_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uv_data), uv_data);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void mk::Sprite::set_tint(const glm::vec4 &tint)
{
    this->shader->set_vec4("tint", tint);
}

void mk::Sprite::setup_sprite_vertex_data()
{
    //used for the vertex array and as the uv initial data
    float data[] = {
        0, 1,
        1, 1,
        0, 0,
        1, 0};

    unsigned int indices[] = {
        2, 3, 1,
        2, 0, 1};

    glGenVertexArrays(1, &this->sprite_vao_id);
    glBindVertexArray(this->sprite_vao_id);

    unsigned int vertices_array_buffer, ebo;

    //create and fill buffers
    glGenBuffers(1, &vertices_array_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_array_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &uv_array_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_array_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    log_info("created vertex array object");
}