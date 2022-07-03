#include "FileReader.h"

using namespace std;

FileReader::FileReader() {}

FileReader::~FileReader() {}

parameter_t FileReader::getParameter(string line)
{
    parameter_t parameter;
    stringstream check(line);
    string token;

    while (getline(check, token, ' '))
    {
        parameter.name = token;
        getline(check, token, ' ');
        parameter.value = stof(token);
    }

    return parameter;
}

vertice_locations_t FileReader::getVerticeLocations(string line)
{
    vertice_locations_t vertice_locations;
    stringstream check(line);
    string token;

    getline(check, token, ' ');
    vertice_locations.vertice_id = stof(token);

    getline(check, token, ' ');
    int locations_size = 0;

    string command = this->getCommand(token);
    if (command == "source")
        vertice_locations.verticeType = VerticeType::source;
    else if (command == "artificial")
        vertice_locations.verticeType = VerticeType::artificial;
    else
    {
        locations_size = stof(token);
        vertice_locations.verticeType = VerticeType::normal;
    }

    vector<int> locations(locations_size);

    for (int i = 0; i < locations_size; i++)
    {
        getline(check, token, ' ');
        locations[i] = stof(token);
    }

    vertice_locations.locations = locations;
    return vertice_locations;
}

arcs_distances_t FileReader::getArcsDistances(string line)
{
    arcs_distances_t arcs_distances;

    stringstream check(line);
    string token;

    getline(check, token, ' ');
    arcs_distances.vertice_id = stof(token);

    getline(check, token, ' ');
    int vertices_size = stof(token);

    vector<vertice_t> vertices(vertices_size);

    for (int i = 0; i < vertices_size; i++)
    {
        getline(check, token, ' ');
        vertices[i].id = stof(token);
        getline(check, token, ' ');
        vertices[i].distance = stof(token);
    }

    arcs_distances.vertices = vertices;
    return arcs_distances;
}

position_artificial_vertices_t FileReader::getPositionArtificialVertice(string line)
{
    position_artificial_vertices_t position_artificial_vertices;

    stringstream check(line);
    string token;

    getline(check, token, ' ');
    position_artificial_vertices.vertice_id = stof(token);

    getline(check, token, ' ');
    position_artificial_vertices.crossAisle = stof(token);

    getline(check, token, ' ');
    position_artificial_vertices.pickAisle = stof(token);

    return position_artificial_vertices;
}

string FileReader::getCommand(string line)
{
    char command[100];
    sscanf(line.c_str(), "%s", command);

    return command;
}