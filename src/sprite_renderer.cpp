#include "sprite_renderer.h"
#include "engine.h"
#include "resource_loader.h"

#include <cstring>
#include <glad/glad.h>

mk::SpriteRenderer::SpriteRenderer()
{
    memset(this->vertex_data, 0, sizeof(vertex_data));
}

void mk::SpriteRenderer::begin()
{
    //we dont need to clear the array, it will be overwritten on the draw() call
    //int sprite_offset = sprite_count * SPRITE_SIZE_IN_FLOATS;
    //memset(this->vertex_data, 0, sprite_offset * sizeof(float));

    this->sprite_count = 0; //reset sprite counter
}

void mk::SpriteRenderer::draw(const Sprite &sprite, glm::vec2 position, glm::vec2 scale)
{
    this->check_flush(sprite.texture);
    this->push_sprite_data(sprite, position, scale);
    this->sprite_count++;
}

void mk::SpriteRenderer::check_flush(mk::Texture *new_texture)
{
    //if we filled the stack, we flush
    if (sprite_count + 1 > MAX_SPRITES)
    {
        this->flush();
    }

    if (this->texture != new_texture)
    {
        this->texture = new_texture;
        this->flush();
    }
}

void mk::SpriteRenderer::push_sprite_data(const Sprite &sprite, glm::vec2 position, glm::vec2 scale)
{
    glm::vec2 size = {sprite.texture->width * scale.x, sprite.texture->height * scale.y};

    glm::vec2 tex_size(sprite.texture_rect.z / sprite.texture->width, sprite.texture_rect.w / sprite.texture->height);
    glm::vec2 tex_coords(sprite.texture_rect.x / sprite.texture->width, sprite.texture_rect.y / sprite.texture->height);

    //define every vertex the sprite has
    Vertex sprite_vertices[VERTEX_PER_SPRITE] = {
        {position.x, position.y, tex_coords.x, tex_coords.y},                                                 //top left
        {position.x + size.x * tex_size.x, position.y * tex_size.y, tex_coords.x + tex_size.x, tex_coords.y}, //top right
        {position.x, position.y + size.y, tex_coords.x, tex_coords.y + tex_size.y},                           //bottom left

        {position.x, position.y + size.y, tex_coords.x, tex_coords.y + tex_size.y},                                                 //bottom left
        {position.x + size.x * tex_size.x, position.y + size.y * tex_size.y, tex_coords.x + tex_size.x, tex_coords.y + tex_size.y}, //bottom right
        {position.x + size.x * tex_size.x, position.y * tex_size.y, tex_coords.x + tex_size.x, tex_coords.y},                       //top right

    };

    int sprt_offst = sprite_count * SPRITE_SIZE_IN_FLOATS;

    for (int i = 0; i < VERTEX_PER_SPRITE; i++)
    {
        int ver_offset = i * VERTEX_SIZE_IN_FLOATS; //space between each vertex

        //add those vertices to the vertex array
        memcpy(this->vertex_data + sprt_offst + ver_offset, sprite_vertices[i].data, sizeof(sprite_vertices[i].data));
    }

    this->has_data = true;
}

//send data to the GPU
void mk::SpriteRenderer::flush()
{
    //only draw if we have something to send
    if (this->has_data == false || this->shader == nullptr || this->texture == nullptr)
        return;

    this->has_data = false;

    //bind texture
    this->texture->use();

    //bind shader
    this->shader->use();

    if (mk::Engine::state_manager.current_projection_matrix != mk::Display::projection)
    {
        this->shader->set_mat4("projection", mk::Display::projection);
        mk::Engine::state_manager.current_projection_matrix = mk::Display::projection;
        fst("updated projection matrix");
    }

    mk::Engine::state_manager.change_vao(this->vao_id); //just in case

    //send data
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_count * SPRITE_SIZE_IN_FLOATS * sizeof(float), this->vertex_data);

    glDrawArrays(GL_TRIANGLES, 0, sprite_count * VERTEX_PER_SPRITE); //draw vertices

    //prepare to render again
    this->begin();
}

void mk::SpriteRenderer::initialize()
{
    //set shader
    this->shader = static_cast<mk::Shader *>(mk::ResourceLoader::get("default_shader"));

    //set vertex data
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    //init empty vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex_data), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}
