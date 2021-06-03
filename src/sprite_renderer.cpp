#include "sprite_renderer.h"
#include "engine.h"
#include "resource_loader.h"

#include <cstring>
#include <glad/glad.h>

mk::SpriteRenderer::SpriteRenderer()
{
    memset(this->vertex_data, 0, sizeof(vertex_data)); //initialize array to 0
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

void mk::SpriteRenderer::begin()
{
    this->sprite_count = 0; //reset sprite counter
}

void mk::SpriteRenderer::draw(const Sprite &sprite, Vector2 position, Vector2 scale)
{
    if (sprite.loaded == false)
    {
        log_info("trying to draw a sprite that isn't loaded");
        return;
    }

    this->check_flush(sprite.texture_ptr);
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
        this->flush();
        this->texture = new_texture;
    }
}

void mk::SpriteRenderer::push_sprite_data(const Sprite &sprite, Vector2 position, Vector2 scale)
{
    Vector2 size = {sprite.texture_ptr->width * scale.x, sprite.texture_ptr->height * scale.y};

    Vector2 tex_size(sprite.texture_rect.z / sprite.texture_ptr->width, sprite.texture_rect.w / sprite.texture_ptr->height);
    Vector2 tex_coords(sprite.texture_rect.x / sprite.texture_ptr->width, sprite.texture_rect.y / sprite.texture_ptr->height);

    //define every vertex the sprite has
    float sprite_vertices[VERTEX_PER_SPRITE][VERTEX_SIZE_IN_FLOATS] = {
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
        memcpy(this->vertex_data + sprt_offst + ver_offset, sprite_vertices[i], VERTEX_SIZE_IN_FLOATS * sizeof(float));
    }

    this->has_data = true;
}

//send data to the GPU
void mk::SpriteRenderer::flush()
{
    //only draw if we have data, a shader and a texture binded
    if (this->has_data == false || this->shader == nullptr || this->texture == nullptr)
        return;

    this->has_data = false;

    //bind texture and shader
    this->texture->use();
    this->shader->use();

    if (mk::StateManager::get()->current_projection_matrix != mk::Display::projection)
    {
        this->shader->set_mat4("projection", mk::Display::projection);
        mk::StateManager::get()->current_projection_matrix = mk::Display::projection;
        fst("updated projection matrix");
    }

    mk::StateManager::get()->change_vao(this->vao_id); //just in case

    //send data
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_count * SPRITE_SIZE_IN_FLOATS * sizeof(float), this->vertex_data);

    glDrawArrays(GL_TRIANGLES, 0, sprite_count * VERTEX_PER_SPRITE); //draw vertices

    //prepare to render again
    this->begin();
}