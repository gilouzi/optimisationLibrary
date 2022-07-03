#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>

#include "ObjectsPickerRouting.h"
#include "FileReader.h"

class Orders
{
private:
    std::vector<int> verticesToVisit;

public:
    Orders(std::string fileName, int totalVertices, std::vector<int> productsVertice, int debug);
    ~Orders();
    std::vector<int> get_vertices_to_visit();
};

#endif