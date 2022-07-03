#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <iostream>
#include <string>

#include "ObjectsPickerRouting.h"
#include "FileReader.h"

class Products
{
private:
    std::vector<int> productsVertice;

public:
    Products(std::string fileName, int minimum_products_required, std::vector<int> locationsVertice);
    ~Products();
    std::vector<int> get_products_vertice();
};

#endif