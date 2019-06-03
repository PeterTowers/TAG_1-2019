#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "../include/Edge.hpp"
#include "../include/Node.hpp"
#include "../include/School.hpp"
#include "../include/Teacher.hpp"

/** PRINTER MODULE
 * This module deals with printing a graph.
 */

/** print_to_console
 * Receives a vector of paired edges and prints its content to the console.
 */
void print_to_console(std::vector<Edge> edges);

void print_adj(std::vector<School> schools, std::vector<Teacher> teachers);