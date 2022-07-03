#include "Products.h"

using namespace std;

Products::Products(std::string fileName, int minimum_products_required, std::vector<int> locationsVertice)
{
    FILE *file;
    char char_id[10], char_location[10];
    int productsQuantity, product_id, location_id;
    vector<int> productsVertice(minimum_products_required);

    // char nameFile[fileName.length() + 1];
    // strcpy(nameFile, fileName.c_str());

    file = fopen(fileName.c_str(), "r");

    fscanf(file, "%d", &productsQuantity);
    fscanf(file, "%s %s", char_id, char_location);

    for (int i = 0; i < productsQuantity; i++)
    {
        fscanf(file, "%d %d", &product_id, &location_id);
        int vertice_id = locationsVertice[location_id];
        productsVertice[product_id] = vertice_id;
    }

    fclose(file);

    this->productsVertice = productsVertice;
    cout << endl
         << "productsVertice" << endl;
    for (int i = 0; i < minimum_products_required; i++)
    {
        cout << i << ": " << productsVertice[i] << endl;
    }
}

Products::~Products() {}

vector<int> Products::get_products_vertice()
{
    return this->productsVertice;
}