#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <regex>

#include "../include/Graph.hpp"
#include "../include/Matrix.hpp"
#include "../include/Teacher.hpp"
#include "../include/School.hpp"

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
 *  - The constructed graph
*/
void build(std::vector<std::string>, Graph* = nullptr, Matrix<Node>* = nullptr);   // Read from stream

/** build
 * Creates a courses DAG from text representation
 * Receives:
 *  - A filename that references a local file with the graoh`s text definition
 * Returns:
 *  - The constructed graph
*/
void build(std::string, Graph* = nullptr, Matrix<Node>* = nullptr);                // Read from file
