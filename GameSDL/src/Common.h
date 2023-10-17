#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "glad/glad.h"

namespace Common {
	unsigned int createShader(const char* vertex_shader_path, const char* fragment_shader_path);
	bool loadFileAsString(const char* path, std::string& content);
}



