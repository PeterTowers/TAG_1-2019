#pragma once
#include "toml.h"
#include "graph.hpp"
#include "course.hpp"

/** READER MODULE
 * This module implements the ability to construct a graph of courses from
 * text input.
*/


/** build
 * Creates a courses DAG from text representation
 * Receives:
 *  - The graph`s text representation as an array of strings, where each string
 *    describes exactly one graph and however many neighbors it may have
 * Returns:
 *  - The constructed digraph
*/
digraph<course>* build(std::vector<std::string>);   // Read from stream

/** build
 * Creates a courses DAG from text representation
 * Receives:
 *  - A filename that references a local file with the graoh`s text definition
 * Returns:
 *  - The constructed digraph
*/
digraph<course>* build(std::string);                // Read from file
