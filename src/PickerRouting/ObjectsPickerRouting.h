#ifndef OBJECTSPICKERROUTING_HPP
#define OBJECTSPICKERROUTING_HPP

#include <vector>
#include <string>

enum class VerticeType {source, artificial, normal};

//struct subaisle_path
//{
//    float distance = 0;
//    int size = 0;
//    int distanceBeforeLargestGap = 0;
//    int verticeBeforeLargestGap;
//    int largestGap;
//    std::vector<int> path;
//};

//struct vertice_t
//{
//    int id;
//    float distance;
//};

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


//struct parameter_t
//{
//    std::string name;
//    float value;
//};
//
//struct vertice_locations_t
//{
//    int vertice_id;
//    vertice_type verticeType;
//    std::vector<int> locations;
//};
//
//struct arcs_distances_t
//{
//    int vertice_id;
//    std::vector<vertice_t> vertices;
//};
//
//struct position_artificial_vertices_t
//{
//    int vertice_id;
//    int pickAisle;
//    int crossAisle;
//};
//
//struct input_parameters_t
//{
//    int numAisles;
//    int numExtraCrossAisles;
//    int numShelves;
//    int minimumProductsRequired;
//    int aisleWidth;
//    int rackDepth;
//    int locationWidth;
//    int crossAisleWidth;
//    int sourceToFirstCrossAisle;
//};
//
//struct data_parameters_t
//{
//    int numLocationsPerAisleSide;
//    int totalLocations;
//    int totalVertices;
//    int numProductVertices;
//    int numArtificialVertices;
//    // int crossAislesPositions;
//};

#endif