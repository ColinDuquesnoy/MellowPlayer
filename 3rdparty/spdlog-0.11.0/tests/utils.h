#pragma once

#include <string>
#include<cstddef>

std::size_t count_lines(const std::string& filename);

void prepare_logdir();

std::string file_contents(const std::string& filename);

std::size_t count_lines(const std::string& filename);

std::size_t get_filesize(const std::string& filename);

