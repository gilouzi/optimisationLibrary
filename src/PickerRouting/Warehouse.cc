#include "Warehouse.h"

Warehouse::Warehouse(int totalVertices)
{
    std::vector<std::vector<Adjacency>> warehouseAdjacencyList(totalVertices);
    this->warehouseAdjacencyList = warehouseAdjacencyList;
}

Warehouse::Warehouse() {}

Warehouse::~Warehouse() {}


int Warehouse::getSize()
{
    return warehouseAdjacencyList.size();
}

int Warehouse::getSize(int id_vertice)
{
    return warehouseAdjacencyList[id_vertice].size();
}

Adjacency Warehouse::getAdjacency(int id_1, int id_2)
{
    /*Adjacency adjacency;
    std::vector<Adjacency> adjacencies = getAllAdjacencies(id_1);
    int adjacenciesSize = adjacencies.size();
    for (int i = 0; i < adjacenciesSize; i++){
        adjacency = adjacencies[i];
        if (adjacency.getId() == id_2) return adjacency;
    }

    Adjacency nullAdjacency;
    return nullAdjacency;*/
    return warehouseAdjacencyList[id_1][id_2];
}

WarehouseAdjacencyList Warehouse::getWarehouseAdjacencyList()
{
    return warehouseAdjacencyList;
}

std::vector<Adjacency> Warehouse::getAllAdjacencies(int id)
{
    return warehouseAdjacencyList[id];
}

std::vector<int> Warehouse::getVerticesWithAdjacency()
{   
    std::vector<int> verticesWithAdjacency;
    int size = getSize();
    for (int i = 0; i < size; i++) {
        if (getSize(i) != 0) {
            verticesWithAdjacency.push_back(i);
        }
    }
    return verticesWithAdjacency;
}

void Warehouse::removeAdjacency(int id_1, int id_2)
{
    int size_1 = getSize(id_1);
    for (int i = 0; i < size_1; i++)
    {
        if (warehouseAdjacencyList[id_1][i].getId() == id_2)
        {
            warehouseAdjacencyList[id_1].erase(warehouseAdjacencyList[id_1].begin() + i);
            break;
        }
    }

    int size_2 = getSize(id_2);
    for (int i = 0; i < size_2; i++)
    {
        if (warehouseAdjacencyList[id_2][i].getId() == id_1)
        {
            warehouseAdjacencyList[id_2].erase(warehouseAdjacencyList[id_2].begin() + i);
            break;
        }
    }
}

void Warehouse::removeVertice(int id)
{
    int size = getSize(id);
    for (int i = 0; i < size; i++)
    {
        Adjacency v_1 = warehouseAdjacencyList[id][i];
        for (int j = i + 1; j < size; j++)
        {
            Adjacency v_2 = warehouseAdjacencyList[id][j];
            this->addNewAdjacency(v_1.getId(), v_2.getId(), v_1.getDistance() + v_2.getDistance());
            this->addNewAdjacency(v_2.getId(), v_1.getId(), v_1.getDistance() + v_2.getDistance());
        }
    }

    for (int i = 0; i < size; i++)
    {
        Adjacency v = this->warehouseAdjacencyList[id][0];
        this->removeAdjacency(id, v.getId());
    }
}

void Warehouse::addNewAdjacency(int id_1, int id_2, float distance)
{
    // vertice_t vertice1 = {id_1, distance};
    Adjacency adjacency = { id_2, distance };

    warehouseAdjacencyList[id_1].push_back(adjacency);
    // this->warehouse[id_2].push_back(vertice1);
}

void Warehouse::printAdjacency(int id)
{
    int adjacencyListSize = getSize(id);
    if (adjacencyListSize == 0)
    {
        std::cout << "vazio";
    }
    else
    {
        for (int i = 0; i < adjacencyListSize; i++)
        {
            Adjacency v = warehouseAdjacencyList[id][i];
            std::cout << "(" << v.getId() << ", " << v.getDistance() << ") ";
        }
    }

    std::cout << std::endl;
}
void Warehouse::printWarehouse()
{
    int sizeWarehouse = getSize();
    std::cout << "Quantidade de vertices: " << sizeWarehouse << std::endl;
    std::cout << "Lista de adjacencia no formato (id, distancia):" << std::endl;
    for (int i = 0; i < sizeWarehouse; i++)
    {
        std::cout << "Vertice " << i << ": ";
        printAdjacency(i);
    }
}

void Warehouse::reduceGraph(int totalVertices, std::vector<int> verticesToVisit, std::vector<VerticeType> verticesType)
{
    for (int i = 0; i < totalVertices; i++)
    {
        if (verticesToVisit[i] == 0 && verticesType[i] == VerticeType::normal)
            this->removeVertice(i);
    }
}
