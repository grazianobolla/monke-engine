#include "sprite.h"
#include "log.h"
#include "resource_loader.h"
#include "engine.h"

#include <glad/glad.h>

#include <iostream>

void mk::Sprite::load(const char *texture_resource_name, const char *shader_resource_name)
{
    this->shader = static_cast<mk::Shader *>(mk::ResourceLoader::get(shader_resource_name));
    this->texture = static_cast<mk::Texture *>(mk::ResourceLoader::get(texture_resource_name));

    if (shader == NULL)
        log_info("warning: shader " << shader_resource_name << " could not be loaded");

    if (texture == NULL)
        log_info("warning: texture " << texture_resource_name << " could not be loaded");

    this->setup_vertex_data();

    this->shader->use();
    this->shader->set_mat4("projection", mk::Engine::projection);
}

void mk::Sprite::draw(glm::vec2 position, glm::vec2 scale)
{
    if (this->shader == NULL || this->texture == NULL)
        return;

    this->shader->use();
    glm::mat4 model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, {position, 0});

    model_matrix = glm::scale(model_matrix, {this->texture->width * scale.x,
                                             this->texture->height * scale.y,
                                             0});

    this->shader->set_mat4("model", model_matrix);

    this->texture->use();

    glBindVertexArray(this->vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void mk::Sprite::setup_vertex_data()
{
    float vertices[] = {
        0, 1, 0, 1,
        1, 1, 1, 1,
        0, 0, 0, 0,
        1, 0, 1, 0};

    unsigned int indices[] = {
        2, 3, 1,
        2, 0, 1};

    glGenVertexArrays(1, &this->vao_id);
    glBindVertexArray(this->vao_id);

    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}