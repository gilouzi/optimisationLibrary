#include "ObjectsPickerRouting.h"
#include <iostream>

Adjacency::Adjacency(int id, float distance)
{
	this->id = id;
	this->distance = distance;
}

Adjacency::~Adjacency() {}

SearchVertice::SearchVertice(int id)
{
	this->id = id;
}

SearchVertice::~SearchVertice() {}

Edge::Edge(std::string xi_j)
{
    int i = 1;

    while (xi_j[i] != '_') {
        i++;
    }

    std::string id_i = "";
    id_i.append(xi_j, 1, i - 1);
    this->id_i = stoi(id_i);


    i++;
    int j = i;

    while (j <= xi_j.size())
    {
        j++;
    }

    std::string id_j = "";
    id_j.append(xi_j, i, j - i);
    this->id_j = stoi(id_j);
}

Edge::~Edge() {}

SubGraph::SubGraph(vector<vector<int>> graph, map<int, int> mapAuxIdToOriginal, vector<vector<string>> idOutEdges)
{
    this->graph = graph;
    this->mapAuxIdToOriginal = mapAuxIdToOriginal;
    this->idOutEdges = idOutEdges;
}

SubGraph::~SubGraph(){}
