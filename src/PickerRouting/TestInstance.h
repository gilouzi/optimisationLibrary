#ifndef TEST_INSTANCE_HPP
#define TEST_INSTANCE_HPP

#include <iostream>
#include <vector>

#include "ObjectsPickerRouting.h"
#include "Warehouse.h"

class TestInstance
{
private:
    std::vector<VerticeType> verticesType;
    int totalVertices;

public:
    TestInstance();
    ~TestInstance();
    std::vector<VerticeType> get_vertices_type();
    Warehouse get_warehouse_1();
    Warehouse get_warehouse_2();
    Warehouse get_warehouse_3();
    Warehouse get_warehouse_4();
    Warehouse get_warehouse_5();
    Warehouse get_warehouse_6();
    Warehouse get_warehouse_7();

    vector<int> get_vertices_to_visit_1();
    vector<int> get_vertices_to_visit_2();
    vector<int> get_vertices_to_visit_3();
    vector<int> get_vertices_to_visit_4();
    vector<int> get_vertices_to_visit_5();
    vector<int> get_vertices_to_visit_6();
    vector<int> get_vertices_to_visit_7();
};

#endif