#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <iostream>
#include <vector>

#include "ObjectsPickerRouting.h"

typedef std::vector<std::vector<Adjacency>> WarehouseAdjacencyList;

class Warehouse
{
private:
    WarehouseAdjacencyList warehouseAdjacencyList;

public:
    Warehouse(int totalVertices);
    Warehouse();
    ~Warehouse();

    int getSize();
    int getSize(int id_vertice);
    Adjacency getAdjacency(int id_1, int id_2);
    WarehouseAdjacencyList getWarehouseAdjacencyList();
    std::vector<Adjacency> getAllAdjacencies(int id);
    std::vector<int> getVerticesWithAdjacency();


    void addNewAdjacency(int id_1, int id_2, float distance);

    void removeAdjacency(int id_1, int id_2);
    void removeVertice(int id);

    void printAdjacency(int id);
    void printWarehouse();

    void reduceGraph(int totalVertices, std::vector<int> verticesToVisit, std::vector<VerticeType> verticesType);
};

#endif