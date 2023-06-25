#include "monke/core/batch_renderer.h"
#include "monke/core/engine.h"
#include "monke/core/resource_loader.h"
#include "monke/core/types.h"

#include "monke/external/glad/glad.h"

#include <cstring>

mk::BatchRenderer::BatchRenderer()
{
    memset(this->vertex_data, 0, sizeof(vertex_data)); // initialize array to 0
}

void mk::BatchRenderer::initialize()
{
    // set shader
    this->shader = static_cast<mk::Shader *>(mk::ResourceLoader::get("batch_shader"));

    // set vertex data
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    // init empty vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex_data), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    log_info("batch renderer initialized");
}

void mk::BatchRenderer::begin()
{
    this->sprite_count = 0; // reset sprite counter
}

void mk::BatchRenderer::draw(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale)
{
    this->check_flush(texture);
    this->push_draw_data(texture, texture_rect, position, scale);
    this->sprite_count++;
}

void mk::BatchRenderer::check_flush(mk::Texture *new_texture)
{
    // if we filled the stack, we flush
    if (sprite_count + 1 > MAX_SPRITES)
    {
        this->flush();
        return;
    }

    if (this->texture != new_texture)
    {
        this->flush();
        this->texture = new_texture;
        return;
    }
}

void mk::BatchRenderer::push_draw_data(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale)
{
    int tex_width = texture->get_width();
    int tex_height = texture->get_height();

    mk::Vector2 size = {tex_width * scale.x, tex_height * scale.y};

    mk::Vector2 tex_size = {texture_rect.w / tex_width, texture_rect.h / tex_height};
    mk::Vector2 tex_coords = {texture_rect.x / tex_width, texture_rect.y / tex_height};

    // define every vertex the sprite has
    float sprite_vertices[VERTEX_PER_SPRITE][VERTEX_SIZE_IN_FLOATS] = {
        {position.x, position.y, tex_coords.x, tex_coords.y},                                    // top left
        {position.x + size.x * tex_size.x, position.y, tex_coords.x + tex_size.x, tex_coords.y}, // top right
        {position.x, position.y + size.y * tex_size.y, tex_coords.x, tex_coords.y + tex_size.y}, // bottom left

        {position.x, position.y + size.y * tex_size.y, tex_coords.x, tex_coords.y + tex_size.y},                                    // bottom left
        {position.x + size.x * tex_size.x, position.y + size.y * tex_size.y, tex_coords.x + tex_size.x, tex_coords.y + tex_size.y}, // bottom right
        {position.x + size.x * tex_size.x, position.y, tex_coords.x + tex_size.x, tex_coords.y},                                    // top right

    };

    int sprt_offst = sprite_count * SPRITE_SIZE_IN_FLOATS;

    for (int i = 0; i < VERTEX_PER_SPRITE; i++)
    {
        int ver_offset = i * VERTEX_SIZE_IN_FLOATS; // space between each vertex

        // add those vertices to the vertex array
        memcpy(this->vertex_data + sprt_offst + ver_offset, sprite_vertices[i], VERTEX_SIZE_IN_FLOATS * sizeof(float));
    }

    this->has_data = true;
}

// send data to the GPU
void mk::BatchRenderer::flush()
{
    // only draw if we have data, a shader and a texture binded
    if (this->has_data == false || this->shader == nullptr || this->texture == nullptr)
        return;

    this->has_data = false;

    // bind texture and shader
    this->texture->use();
    this->shader->use();

    // set projection
    this->shader->set_mat4("projection", mk::Display::projection);

    // bind vao
    glBindVertexArray(this->vao_id);

    // send data
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_count * SPRITE_SIZE_IN_FLOATS * sizeof(float), this->vertex_data);

    glDrawArrays(GL_TRIANGLES, 0, sprite_count * VERTEX_PER_SPRITE); // draw vertices

    // prepare to render again
    this->begin();
}