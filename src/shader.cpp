#include "shader.h"
#include "file.h"
#include "log.h"

bool mk::Shader::load(const char *vert_path, const char *frag_path)
{
    unsigned int vertex_id, fragment_id;
    vertex_id = this->create_shader(vert_path, GL_VERTEX_SHADER);
    fragment_id = this->create_shader(frag_path, GL_FRAGMENT_SHADER);

    if (vertex_id == 0 || fragment_id == 0)
        return false;

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex_id);
    glAttachShader(this->id, fragment_id);
    glLinkProgram(this->id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    log_info("loaded shader " << vert_path << " and " << frag_path);
    return true;
}

unsigned int mk::Shader::create_shader(const char *path, unsigned int type)
{
    //create shader
    unsigned int tmp_id = glCreateShader(type);

    //load source code
    std::string shader_source;
    if (mk::get_file(path, shader_source) == false)
        return 0;

    const char *c_src = shader_source.c_str();
    glShaderSource(tmp_id, 1, &c_src, NULL);

    //compile
    glCompileShader(tmp_id);

    //compilation data
    int success;
    glGetShaderiv(tmp_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(tmp_id, 512, NULL, info_log);
        log_info("shader compilation error (" << (type == GL_VERTEX_SHADER ? "vertex)" : "fragment)")
                                              << "\n"
                                              << info_log);
        return 0;
    }

    return tmp_id;
}

void mk::Shader::use()
{
    glUseProgram(this->id);
}

unsigned int mk::Shader::get_uniform_location(const char *uniform_name)
{
    return glGetUniformLocation(this->id, uniform_name);
}

void mk::Shader::set_mat4(const char *uniform_name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(this->get_uniform_location(uniform_name), 1, GL_FALSE, &matrix[0][0]);
}