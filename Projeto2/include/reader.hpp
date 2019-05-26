#pragma once
#include "toml.h"
#include "graph.hpp"
#include "course.hpp"

digraph<course>* build(std::vector<std::string>);   // Read from stream
digraph<course>* build(std::string);                // Read from file
