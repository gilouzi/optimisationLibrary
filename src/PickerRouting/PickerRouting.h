#ifndef PICKER_ROUTING_H
#define PICKER_ROUTING_H

#include <iostream>
#include <string>
#include <fstream> 

#include "ObjectsPickerRouting.h"
#include "Warehouse.h"
#include "FileReader.h"

class PickerRouting
{
private:
    Warehouse warehouse;
    std::vector<VerticeType> verticesType;
    std::vector<std::vector<int>> aisles;
    std::vector<int> locationsVertice;
    input_parameters_t inputParameters;
    data_parameters_t dataParameters;

public:
    PickerRouting(std::string fileName);
    ~PickerRouting();

    //SAVE PARAMETERS
    void save_input_parameter(parameter_t parameter);
    void save_data_parameter(parameter_t parameter);

    //GET
    std::vector<int> get_locations_vertice();
    std::vector<VerticeType> get_vertices_type();
    Warehouse get_warehouse();
    int get_num_cross_aisles();
    std::vector<std::vector<int>> get_aisles();

    //GET INPUT PARAMETERS
    int get_num_aisles();
    int get_num_extra_cross_aisles();
    int get_num_shelves();
    int get_minimum_products_required();
    int get_aisle_width();
    int get_rack_depth();
    int get_location_width();
    int get_cross_aisle_width();
    int get_source_to_first_cross_aisle();

    //GET DATA PARAMETERS
    int get_num_locations_per_aisle_side();
    int get_total_locations();
    int get_total_vertices();
    int get_num_product_vertices();
    int get_num_artificial_vertices();
    // int get_cross_aisles_positions();
};

#endif