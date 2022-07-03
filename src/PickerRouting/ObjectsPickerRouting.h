#ifndef OBJECTS_PICKER_ROUTING_H
#define OBJECTS_PICKER_ROUTING_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

enum class VerticeType {source, artificial, normal};

class Edge {
    private:
        int id_i;
        int id_j;
    public:
        Edge(std::string xi_j);
        ~Edge();
        int getId_i() const { return id_i; }
        int getId_j() const { return id_j; }
};

class SubGraph {
    private:
        vector<vector<int>> graph;
        map<int, int> mapAuxIdToOriginal;
        vector<vector<string>> idOutEdges;
    public:
        SubGraph(vector<vector<int>> graph, map<int, int> mapAuxIdToOriginal, vector<vector<string>> idOutEdges);
        ~SubGraph();
        vector<vector<int>> getGraph() const { return graph; };
        map<int, int> getMapAuxIdToOriginal() const { return mapAuxIdToOriginal; };
        vector<vector<string>> getIdOutEdges() const { return idOutEdges; };

};

class SearchVertice {
    private:
        int id;
        bool visited;

    public:
        SearchVertice(int id);
        ~SearchVertice();
        int getId() const{ return id; }
        bool wasVisited() { return visited; }
};

class Adjacency {
    private:
        int id;
        float distance;

    public:
        Adjacency(int id, float distance);
        ~Adjacency();
        int getId() const { return id; }
        float getDistance() const { return distance; }
};

struct subaisle_path
{
    float distance = 0;
    int size = 0;
    int distanceBeforeLargestGap = 0;
    int verticeBeforeLargestGap;
    int largestGap;
    std::vector<int> path;
};

struct vertice_t
{
    int id;
    float distance;
};

struct vertice_locations_t
{
    int vertice_id;
    VerticeType verticeType;
    std::vector<int> locations;
};

struct arcs_distances_t
{
    int vertice_id;
    std::vector<vertice_t> vertices;
};

struct position_artificial_vertices_t
{
    int vertice_id;
    int pickAisle;
    int crossAisle;
};

struct parameter_t
{
    std::string name;
    float value;
};

struct input_parameters_t
{
    int numAisles;
    int numExtraCrossAisles;
    int numShelves;
    int minimumProductsRequired;
    int aisleWidth;
    int rackDepth;
    int locationWidth;
    int crossAisleWidth;
    int sourceToFirstCrossAisle;
};

struct data_parameters_t
{
    int numLocationsPerAisleSide;
    int totalLocations;
    int totalVertices;
    int numProductVertices;
    int numArtificialVertices;
    // int crossAislesPositions;
};

#endif