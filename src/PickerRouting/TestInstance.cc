#include "TestInstance.h"

using namespace std;

TestInstance::TestInstance()
{
    totalVertices = 58;

    vector<VerticeType> verticesType(totalVertices);
    verticesType[0] = VerticeType::source;
    for (int i = 1; i <= 45; i++)
        verticesType[i] = VerticeType::normal;
    for (int i = 46; i <= 57; i++)
        verticesType[i] = VerticeType::artificial;
    this->verticesType = verticesType;

    vector<int> verticesToVisit(totalVertices, 0);
}

TestInstance::~TestInstance() {}

vector<VerticeType> TestInstance::get_vertices_type()
{
    return verticesType;
}

// Teste 1: pick em todos pick aisles e todos blocks
Warehouse TestInstance::get_warehouse_1()
{
    Warehouse warehouse(totalVertices);
    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 8, 40);
    warehouse.addNewAdjacency(8, 49, 40);

    warehouse.addNewAdjacency(52, 8, 40);
    warehouse.addNewAdjacency(8, 52, 40);

    warehouse.addNewAdjacency(52, 55, 80);
    warehouse.addNewAdjacency(55, 52, 80);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 50, 80);
    warehouse.addNewAdjacency(50, 47, 80);

    warehouse.addNewAdjacency(50, 21, 20);
    warehouse.addNewAdjacency(21, 50, 20);

    warehouse.addNewAdjacency(21, 23, 20);
    warehouse.addNewAdjacency(23, 21, 20);

    warehouse.addNewAdjacency(23, 53, 40);
    warehouse.addNewAdjacency(53, 23, 40);

    warehouse.addNewAdjacency(53, 28, 40);
    warehouse.addNewAdjacency(28, 53, 40);

    warehouse.addNewAdjacency(28, 56, 40);
    warehouse.addNewAdjacency(56, 28, 40);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 39, 50);
    warehouse.addNewAdjacency(39, 51, 50);

    warehouse.addNewAdjacency(39, 54, 30);
    warehouse.addNewAdjacency(54, 39, 30);

    warehouse.addNewAdjacency(54, 42, 30);
    warehouse.addNewAdjacency(42, 54, 30);

    warehouse.addNewAdjacency(42, 45, 30);
    warehouse.addNewAdjacency(45, 42, 30);

    warehouse.addNewAdjacency(45, 57, 20);
    warehouse.addNewAdjacency(57, 45, 20);

    return warehouse;
}

// Teste 2: sem picks no pick aisle 0 e pick em todos blocks
Warehouse TestInstance::get_warehouse_2()
{
    Warehouse warehouse(58);

    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 52, 80);
    warehouse.addNewAdjacency(52, 49, 80);

    warehouse.addNewAdjacency(52, 55, 80);
    warehouse.addNewAdjacency(55, 52, 80);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 50, 80);
    warehouse.addNewAdjacency(50, 47, 80);

    warehouse.addNewAdjacency(50, 21, 20);
    warehouse.addNewAdjacency(21, 50, 20);

    warehouse.addNewAdjacency(21, 23, 20);
    warehouse.addNewAdjacency(23, 21, 20);

    warehouse.addNewAdjacency(23, 53, 40);
    warehouse.addNewAdjacency(53, 23, 40);

    warehouse.addNewAdjacency(53, 28, 40);
    warehouse.addNewAdjacency(28, 53, 40);

    warehouse.addNewAdjacency(28, 56, 40);
    warehouse.addNewAdjacency(56, 28, 40);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 39, 50);
    warehouse.addNewAdjacency(39, 51, 50);

    warehouse.addNewAdjacency(39, 54, 30);
    warehouse.addNewAdjacency(54, 39, 30);

    warehouse.addNewAdjacency(54, 42, 30);
    warehouse.addNewAdjacency(42, 54, 30);

    warehouse.addNewAdjacency(42, 45, 30);
    warehouse.addNewAdjacency(45, 42, 30);

    warehouse.addNewAdjacency(45, 57, 20);
    warehouse.addNewAdjacency(57, 45, 20);

    return warehouse;
}

// Teste 3: sem picks no pick aisle 0 e sem pick no último block
Warehouse TestInstance::get_warehouse_3()
{
    Warehouse warehouse(58);

    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 52, 80);
    warehouse.addNewAdjacency(52, 49, 80);

    warehouse.addNewAdjacency(52, 55, 80);
    warehouse.addNewAdjacency(55, 52, 80);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 50, 80);
    warehouse.addNewAdjacency(50, 47, 80);

    warehouse.addNewAdjacency(50, 21, 20);
    warehouse.addNewAdjacency(21, 50, 20);

    warehouse.addNewAdjacency(21, 23, 20);
    warehouse.addNewAdjacency(23, 21, 20);

    warehouse.addNewAdjacency(23, 53, 40);
    warehouse.addNewAdjacency(53, 23, 40);

    warehouse.addNewAdjacency(53, 56, 80);
    warehouse.addNewAdjacency(56, 53, 80);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 39, 50);
    warehouse.addNewAdjacency(39, 51, 50);

    warehouse.addNewAdjacency(39, 54, 30);
    warehouse.addNewAdjacency(54, 39, 30);

    warehouse.addNewAdjacency(54, 57, 80);
    warehouse.addNewAdjacency(57, 54, 80);

    return warehouse;
}

// Teste 4: sem picks no pick aisle 0 e sem pick no último block
Warehouse TestInstance::get_warehouse_4()
{
    Warehouse warehouse(58);

    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 52, 80);
    warehouse.addNewAdjacency(52, 49, 80);

    warehouse.addNewAdjacency(52, 55, 80);
    warehouse.addNewAdjacency(55, 52, 80);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 50, 80);
    warehouse.addNewAdjacency(50, 47, 80);

    warehouse.addNewAdjacency(50, 53, 80);
    warehouse.addNewAdjacency(53, 50, 80);

    warehouse.addNewAdjacency(53, 56, 80);
    warehouse.addNewAdjacency(56, 53, 80);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 54, 80);
    warehouse.addNewAdjacency(54, 51, 80);

    warehouse.addNewAdjacency(54, 57, 80);
    warehouse.addNewAdjacency(57, 54, 80);

    return warehouse;
}

// Teste 5: so um subaisle a ser percorrido no ultimo block
Warehouse TestInstance::get_warehouse_5()
{
    Warehouse warehouse(totalVertices);
    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 8, 40);
    warehouse.addNewAdjacency(8, 49, 40);

    warehouse.addNewAdjacency(52, 8, 40);
    warehouse.addNewAdjacency(8, 52, 40);

    warehouse.addNewAdjacency(52, 55, 80);
    warehouse.addNewAdjacency(55, 52, 80);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 50, 80);
    warehouse.addNewAdjacency(50, 47, 80);

    warehouse.addNewAdjacency(50, 21, 20);
    warehouse.addNewAdjacency(21, 50, 20);

    warehouse.addNewAdjacency(21, 23, 20);
    warehouse.addNewAdjacency(23, 21, 20);

    warehouse.addNewAdjacency(23, 53, 40);
    warehouse.addNewAdjacency(53, 23, 40);

    warehouse.addNewAdjacency(53, 56, 80);
    warehouse.addNewAdjacency(56, 53, 80);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 39, 50);
    warehouse.addNewAdjacency(39, 51, 50);

    warehouse.addNewAdjacency(39, 54, 30);
    warehouse.addNewAdjacency(54, 39, 30);

    warehouse.addNewAdjacency(54, 42, 30);
    warehouse.addNewAdjacency(42, 54, 30);

    warehouse.addNewAdjacency(42, 45, 30);
    warehouse.addNewAdjacency(45, 42, 30);

    warehouse.addNewAdjacency(45, 57, 20);
    warehouse.addNewAdjacency(57, 45, 20);

    return warehouse;
}

// Teste 6: sem picks no pick aisle 0 e sem pick no último block
Warehouse TestInstance::get_warehouse_6()
{
    Warehouse warehouse(58);

    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 52, 80);
    warehouse.addNewAdjacency(52, 49, 80);

    warehouse.addNewAdjacency(52, 55, 80);
    warehouse.addNewAdjacency(55, 52, 80);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 20, 60);
    warehouse.addNewAdjacency(20, 47, 60);

    warehouse.addNewAdjacency(20, 50, 20);
    warehouse.addNewAdjacency(50, 20, 20);

    warehouse.addNewAdjacency(50, 53, 80);
    warehouse.addNewAdjacency(53, 50, 80);

    warehouse.addNewAdjacency(53, 56, 80);
    warehouse.addNewAdjacency(56, 53, 80);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 54, 80);
    warehouse.addNewAdjacency(54, 51, 80);

    warehouse.addNewAdjacency(54, 57, 80);
    warehouse.addNewAdjacency(57, 54, 80);

    return warehouse;
}

// Teste 7: sem pick no block do meio
Warehouse TestInstance::get_warehouse_7()
{
    Warehouse warehouse(58);

    //distance to depot
    warehouse.addNewAdjacency(0, 46, 30);
    warehouse.addNewAdjacency(46, 0, 30);

    warehouse.addNewAdjacency(0, 47, 60);
    warehouse.addNewAdjacency(47, 0, 60);

    warehouse.addNewAdjacency(0, 48, 80);
    warehouse.addNewAdjacency(48, 0, 80);

    //cross aisle 0
    warehouse.addNewAdjacency(46, 47, 40);
    warehouse.addNewAdjacency(47, 46, 40);

    warehouse.addNewAdjacency(47, 48, 40);
    warehouse.addNewAdjacency(48, 47, 40);

    //cross aisle 1
    warehouse.addNewAdjacency(49, 50, 40);
    warehouse.addNewAdjacency(50, 49, 40);

    warehouse.addNewAdjacency(50, 51, 40);
    warehouse.addNewAdjacency(51, 50, 40);

    //cross aisle 2
    warehouse.addNewAdjacency(52, 53, 40);
    warehouse.addNewAdjacency(53, 52, 40);

    warehouse.addNewAdjacency(53, 54, 40);
    warehouse.addNewAdjacency(54, 53, 40);

    //cross aisle 3
    warehouse.addNewAdjacency(55, 56, 40);
    warehouse.addNewAdjacency(56, 55, 40);

    warehouse.addNewAdjacency(56, 57, 40);
    warehouse.addNewAdjacency(57, 56, 40);

    //pick aisle 0
    warehouse.addNewAdjacency(46, 49, 80);
    warehouse.addNewAdjacency(49, 46, 80);

    warehouse.addNewAdjacency(49, 52, 80);
    warehouse.addNewAdjacency(52, 49, 80);

    warehouse.addNewAdjacency(52, 12, 30);
    warehouse.addNewAdjacency(12, 52, 30);

    warehouse.addNewAdjacency(12, 14, 20);
    warehouse.addNewAdjacency(14, 12, 20);

    warehouse.addNewAdjacency(14, 55, 30);
    warehouse.addNewAdjacency(55, 14, 30);

    //pick aisle 1
    warehouse.addNewAdjacency(47, 20, 60);
    warehouse.addNewAdjacency(20, 47, 60);

    warehouse.addNewAdjacency(20, 50, 20);
    warehouse.addNewAdjacency(50, 20, 20);

    warehouse.addNewAdjacency(50, 53, 80);
    warehouse.addNewAdjacency(53, 50, 80);

    warehouse.addNewAdjacency(53, 27, 30);
    warehouse.addNewAdjacency(27, 53, 30);

    warehouse.addNewAdjacency(27, 28, 10);
    warehouse.addNewAdjacency(28, 27, 10);

    warehouse.addNewAdjacency(28, 30, 20);
    warehouse.addNewAdjacency(30, 28, 20);

    warehouse.addNewAdjacency(30, 56, 20);
    warehouse.addNewAdjacency(56, 30, 20);

    //pick aisle 2
    warehouse.addNewAdjacency(48, 34, 50);
    warehouse.addNewAdjacency(34, 48, 50);

    warehouse.addNewAdjacency(34, 51, 30);
    warehouse.addNewAdjacency(51, 34, 30);

    warehouse.addNewAdjacency(51, 54, 80);
    warehouse.addNewAdjacency(54, 51, 80);

    warehouse.addNewAdjacency(54, 44, 50);
    warehouse.addNewAdjacency(44, 54, 50);

    warehouse.addNewAdjacency(44, 45, 10);
    warehouse.addNewAdjacency(45, 44, 10);

    warehouse.addNewAdjacency(45, 57, 20);
    warehouse.addNewAdjacency(57, 45, 20);

    return warehouse;
}

vector<int> TestInstance::get_vertices_to_visit_1() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[8] = 1;
    verticesToVisit[21] = 1;
    verticesToVisit[23] = 1;
    verticesToVisit[28] = 1;
    verticesToVisit[34] = 1;
    verticesToVisit[39] = 1;
    verticesToVisit[42] = 1;
    verticesToVisit[45] = 1;

    return verticesToVisit;
}

vector<int> TestInstance::get_vertices_to_visit_2() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[21] = 1;
    verticesToVisit[23] = 1;
    verticesToVisit[28] = 1;
    verticesToVisit[34] = 1;
    verticesToVisit[39] = 1;
    verticesToVisit[42] = 1;
    verticesToVisit[45] = 1;

    return verticesToVisit;
}

vector<int> TestInstance::get_vertices_to_visit_3() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[21] = 1;
    verticesToVisit[23] = 1;
    verticesToVisit[34] = 1;
    verticesToVisit[39] = 1;

    return verticesToVisit;
}

vector<int> TestInstance::get_vertices_to_visit_4() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[34] = 1;

    return verticesToVisit;
}

vector<int> TestInstance::get_vertices_to_visit_5() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[8] = 1;
    verticesToVisit[21] = 1;
    verticesToVisit[23] = 1;
    verticesToVisit[34] = 1;
    verticesToVisit[39] = 1;
    verticesToVisit[42] = 1;
    verticesToVisit[45] = 1;

    return verticesToVisit;
}

vector<int> TestInstance::get_vertices_to_visit_6() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[20] = 1;
    verticesToVisit[34] = 1;

    return verticesToVisit;
}

vector<int> TestInstance::get_vertices_to_visit_7() {
    vector<int> verticesToVisit(totalVertices, 0);

    verticesToVisit[12] = 1;
    verticesToVisit[14] = 1;
    verticesToVisit[20] = 1;
    verticesToVisit[27] = 1;
    verticesToVisit[28] = 1;
    verticesToVisit[30] = 1;
    verticesToVisit[34] = 1;
    verticesToVisit[44] = 1;
    verticesToVisit[45] = 1;

    return verticesToVisit;
}