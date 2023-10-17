#include "Common.h"

namespace Common {
    bool loadFileAsString(const char* path, std::string& content)
    {
        namespace fs = std::filesystem;

        fs::path filePath = fs::absolute(path);
        std::cout << "FILESYSTEM: Loading file: " << filePath.generic_string() << std::endl;

        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream.is_open()) {
            std::cout << "FILESYSTEM: Failed to open file: " << filePath.generic_string() << std::endl;
            return false;
        }

        std::string line;
        while (getline(fileStream, line)) {
            content.append(line).append("\n");
        }
        return true;
    }

    unsigned int createShader(const char* vertex_shader_path, const char* fragment_shader_path)
    {
        //error handling vars
        int res;
        char infoLog[512];

        //create a program
        unsigned int program = glCreateProgram();
        //vertex_shader
        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        std::string vertex;
        if (!loadFileAsString(vertex_shader_path, vertex)) {
            return 0;
        };
        const char* src = vertex.c_str();
        glShaderSource(vertex_shader, 1, &src, nullptr);
        glCompileShader(vertex_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &res);
        if (res == GL_FALSE)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(vertex_shader);
            return 0;
        }

        //FragmentShader
        unsigned int fragement_shader = glCreateShader(GL_FRAGMENT_SHADER);
        std::string fragment;
        if (!loadFileAsString(fragment_shader_path, fragment)) {
            return 0;
        };
        src = fragment.c_str();
        glShaderSource(fragement_shader, 1, &src, nullptr);
        glCompileShader(fragement_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &res);
        if (res == GL_FALSE)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(fragement_shader);
            return 0;
        }

        //Attach the shader to program
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragement_shader);
        glLinkProgram(program);
        glValidateProgram(program);

        //can delete the shaders because we don't need them anymore
        glDeleteShader(vertex_shader);
        glDeleteShader(fragement_shader);

        //return our shader program
        return program;
    }
}