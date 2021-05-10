#include "sprite.h"
#include "engine.h"
#include "resource_loader.h"
#include "log.h"

#include <glad/glad.h>

void mk::Sprite::load(const char *texture_resource_name, const glm::vec4 &tex_coord, const char *shader_resource_name)
{
    mk::setup_sprite_vertex_data(this->vao_id, this->uv_data_id, false);

    this->shader = static_cast<mk::Shader *>(mk::ResourceLoader::get(shader_resource_name));
    this->texture = static_cast<mk::Texture *>(mk::ResourceLoader::get(texture_resource_name));

    if (shader == nullptr)
        log_info("warning: shader " << shader_resource_name << " could not be loaded");

    if (texture == nullptr)
        log_info("warning: texture " << texture_resource_name << " could not be loaded");

    if (shader != nullptr && texture != nullptr)
        this->loaded = true;

    this->update_rect(tex_coord);
}

void mk::Sprite::set_tint(const glm::vec4 &tint)
{
    this->shader->set_vec4("tint", tint);
}

void mk::Sprite::draw(const glm::vec2 &position, float angle, const glm::vec2 &scale)
{
    if (this->loaded == false)
        return;

    this->shader->use();

    if (mk::Engine::state_manager.current_projection_matrix != mk::Display::projection)
    {
        this->shader->set_mat4("projection", mk::Display::projection);
        mk::Engine::state_manager.current_projection_matrix = mk::Display::projection;
        fst("updated projection matrix");
    }

    glm::mat4 model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, {position, 0});
    model_matrix = glm::rotate(model_matrix, glm::radians(angle), glm::vec3(0, 0, 1));
    model_matrix = glm::scale(model_matrix, {this->texture_coordinates.z * scale.x,
                                             this->texture_coordinates.w * scale.y,
                                             0});

    this->shader->set_mat4("model", model_matrix);

    this->shader->set_vec2("texture_coordinates_multiplier", {((h_inverted == true) ? -1 : 1), ((v_inverted == true) ? -1 : 1)});

    this->texture->use();

    //draw and update uv's
    mk::Engine::state_manager.change_vao(this->vao_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void mk::Sprite::update_rect(const glm::vec4 &tex_coord)
{
    if (this->loaded == false)
        return;

    this->texture_coordinates = tex_coord;
    //texture data
    float rect_x = tex_coord.x / this->texture->width;
    float rect_y = tex_coord.y / this->texture->height;
    float rect_width = tex_coord.z / this->texture->width;
    float rect_height = tex_coord.w / this->texture->height;

    float uv_data[8] = {
        rect_x, rect_y + rect_height,
        rect_x + rect_width, rect_y + rect_height,
        rect_x, rect_y,
        rect_x + rect_width, rect_y};

    //update uv's
    //glBindVertexArray(this->vao_id); <-------
    glBindBuffer(GL_ARRAY_BUFFER, this->uv_data_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uv_data), uv_data);
}

unsigned int glboal_sprite_vertex_buffer_id = 0;
unsigned int glboal_sprite_ebo_id = 0;
void mk::setup_sprite_vertex_data(unsigned int &vertex_array, unsigned int &uv_data, bool uv_static)
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

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    //element index buffer
    if (glboal_sprite_ebo_id == 0)
    {
        glGenBuffers(1, &glboal_sprite_ebo_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glboal_sprite_ebo_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
    else
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glboal_sprite_ebo_id);

    //vertex data
    if (glboal_sprite_vertex_buffer_id == 0)
    {
        glGenBuffers(1, &glboal_sprite_vertex_buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, glboal_sprite_vertex_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }
    else
        glBindBuffer(GL_ARRAY_BUFFER, glboal_sprite_vertex_buffer_id);

    //uv texture buffer
    glGenBuffers(1, &uv_data);
    glBindBuffer(GL_ARRAY_BUFFER, uv_data);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, uv_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    log_info("created vertex array object vao: " << vertex_array << " vbo: " << glboal_sprite_vertex_buffer_id << " uvbo: " << uv_data << " ebo: " << glboal_sprite_ebo_id);
}

mk::Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &this->vao_id);
    glDeleteBuffers(1, &this->uv_data_id);
}