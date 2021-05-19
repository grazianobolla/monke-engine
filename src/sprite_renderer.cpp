#include "sprite_renderer.h"
#include "engine.h"
#include "resource_loader.h"

#include <cstring>
#include <glad/glad.h>

void mk::SpriteRenderer::begin()
{
    memset(this->vertex_data, 0, sizeof(this->vertex_data)); //clear vertex array
    this->sprite_count = 0;                                  //reset sprite counter
}

void mk::SpriteRenderer::draw(const Sprite &sprite, glm::vec2 position)
{
    int sprite_offset = sprite_count * SPRITE_SIZE_IN_FLOATS;

    //define every vertex the sprite has
    Vertex sprite_vertices[VERTEX_PER_SPRITE] = {

        {position.x, position.y, 0, 0},
        {position.x + sprite.texture->width, position.y, 1, 0},
        {position.x, position.y + sprite.texture->height, 0, 1},

        {position.x, position.y + sprite.texture->height, 0, 1},
        {position.x + sprite.texture->width, position.y + sprite.texture->height, 1, 1},
        {position.x + sprite.texture->width, position.y, 1, 0}

    };

    for (int i = 0; i < VERTEX_PER_SPRITE; i++)
    {
        int ver_offset = i * VERTEX_SIZE_IN_FLOATS; //space between each vertex

        //add those vertices to the vertex array
        memcpy(this->vertex_data + sprite_offset + ver_offset, sprite_vertices[i].data, sizeof(sprite_vertices[i].data));
    }

    this->sprite_count++;
}

//flish vertex data to the GPU
void mk::SpriteRenderer::flush()
{
    //TEMP--------------------------------
    static_cast<mk::Shader *>(mk::ResourceLoader::get("default_shader"))->use();
    if (mk::Engine::state_manager.current_projection_matrix != mk::Display::projection)
    {
        static_cast<mk::Shader *>(mk::ResourceLoader::get("default_shader"))->set_mat4("projection", mk::Display::projection);
        mk::Engine::state_manager.current_projection_matrix = mk::Display::projection;
        fst("updated projection matrix");
    }
    Texture *tex = static_cast<mk::Texture *>(mk::ResourceLoader::get("happy"));
    tex->use();
    //TEMP--------------------------------

    mk::Engine::state_manager.change_vao(this->vao_id); //just in case

    //send data
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sprite_count * SPRITE_SIZE_IN_FLOATS * sizeof(float), this->vertex_data);

    glDrawArrays(GL_TRIANGLES, 0, sprite_count * VERTEX_PER_SPRITE); //draw vertices

    //prepare to start again
    this->begin();
}

void mk::SpriteRenderer::init()
{
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    //init empty vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex_data), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}
