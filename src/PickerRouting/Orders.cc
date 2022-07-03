#include "Orders.h"

using namespace std;

Orders::Orders(string fileName, int totalVertices, vector<int> productsVertice)
{
    FILE *file;
    char char_np[20], char_p[20], char_q[20];
    int ordersQuantity, numProducts, product, quantity;
    vector<int> verticesToVisit(totalVertices, 0);

    /*char nameFile[fileName.length() + 1];
    strcpy(nameFile, fileName.c_str());*/

    file = fopen(fileName.c_str(), "r");

    fscanf(file, "%d", &ordersQuantity);
    fscanf(file, "%s %s %s", char_np, char_p, char_q);

    for (int i = 0; i < ordersQuantity; i++)
    {
        fscanf(file, "%d", &numProducts);
        for (int j = 0; j < numProducts; j++)
        {
            fscanf(file, "%d %d", &product, &quantity);
            int verticeToVisit = productsVertice[product];
            verticesToVisit[verticeToVisit] = 1;
        }
    }

    fclose(file);

    this->verticesToVisit = verticesToVisit;

    cout << endl
         << "verticesToVisit" << endl;
    for (int i = 0; i < totalVertices; i++)
    {
        cout << i << ": " << verticesToVisit[i] << endl;
    }
}

Orders::~Orders() {}

std::vector<int> Orders::get_vertices_to_visit()
{
    return this->verticesToVisit;
}