#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <sstream>  

#include "ObjectsPickerRouting.h"

class FileReader
{
public:
    FileReader();
    ~FileReader();
    parameter_t getParameter(std::string line);
    vertice_locations_t getVerticeLocations(std::string line);
    arcs_distances_t getArcsDistances(std::string line);
    position_artificial_vertices_t getPositionArtificialVertice(std::string line);
    std::string getCommand(std::string line);
};

#endif