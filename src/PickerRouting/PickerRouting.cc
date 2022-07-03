#include "PickerRouting.h"

using namespace std;

int INPUT_PARAMETERS_QUANTITY = 9;
int DATA_QUANTITY = 6;

PickerRouting::PickerRouting(string fileName, int debug)
{
    string warehouseFileLine;
    ifstream warehouseFile(fileName);

    FileReader file_reader;
    while (getline(warehouseFile, warehouseFileLine))
    {
        string command = file_reader.getCommand(warehouseFileLine);

        if (debug > 3)
            cout << "command: " << command << endl;

        if (command == "INPUT_PARAMETERS")
        {
            for (int i = 0; i < INPUT_PARAMETERS_QUANTITY; i++)
            {
                getline(warehouseFile, warehouseFileLine);

                parameter_t parameter = file_reader.getParameter(warehouseFileLine);
                if (debug > 3)
                    cout << parameter.name << " " << parameter.value << endl;

                save_input_parameter(parameter);
            }
        }

        if (command == "DATA")
        {
            for (int i = 0; i < DATA_QUANTITY; i++)
            {
                //TODO: arrumar o getParameter para quando parametro é o crossAislesPositions (possui dois valores)
                getline(warehouseFile, warehouseFileLine);

                parameter_t parameter = file_reader.getParameter(warehouseFileLine);
                if (debug > 3)
                    cout << parameter.name << " " << parameter.value << endl;
                save_data_parameter(parameter);
            }
        }

        if (command == "vertices_pick_which_locations")
        {
            int totalVertices = get_total_vertices();
            vector<VerticeType> verticesType(totalVertices);
            int totalLocations = get_total_locations();
            vector<int> locationsVertice(totalLocations);
            for (int i = 0; i < totalVertices; i++)
            {
                getline(warehouseFile, warehouseFileLine);
                vertice_locations_t vertice_locations = file_reader.getVerticeLocations(warehouseFileLine);

                vector<int> locations = vertice_locations.locations;
                int locations_size = locations.size();
                int vertice_id = vertice_locations.vertice_id;
                for (int j = 0; j < locations_size; j++)
                {
                    int location_id = locations[j];
                    locationsVertice[location_id] = vertice_id;
                }

                verticesType[vertice_id] = vertice_locations.verticeType;
            }

            this->verticesType = verticesType;
            this->locationsVertice = locationsVertice;

            if (debug > 3) {
                /*cout << endl
                     << "verticesType" << endl;
                for (int i = 0; i < totalVertices; i++)
                {
                    cout << i << ": " << verticesType[i] << endl;
                }*/
                cout << endl
                     << "locationsVertice" << endl;
                for (int i = 0; i < totalLocations; i++)
                {
                    cout << i << ": " << locationsVertice[i] << endl;
                }
            }
        }

        if (command == "arcs_distances")
        {
            int totalVertices = get_total_vertices();
            Warehouse warehouse(totalVertices);

            for (int i = 0; i < totalVertices; i++)
            {
                getline(warehouseFile, warehouseFileLine);
                arcs_distances_t arcs_distances = file_reader.getArcsDistances(warehouseFileLine);
                int vertices_size = arcs_distances.vertices.size();
                for (int j = 0; j < vertices_size; j++)
                {
                    vertice_t vertice = arcs_distances.vertices[j];
                    warehouse.addNewAdjacency(arcs_distances.vertice_id, vertice.id, vertice.distance);
                }
            }

            this->warehouse = warehouse;
            if (debug > 3) {
                cout << endl
                     << "warehouse:" << endl;
                this->warehouse.printWarehouse();
            }
        }

        if (command == "position_artificial_vertices_aisle_block")
        {
            int numArtificialVertices = get_num_artificial_vertices();

            int numAisles = get_num_aisles();
            int numCrossAisles = get_num_cross_aisles();
            vector<vector<int>> aisles(numCrossAisles, vector<int>(numAisles));

            if (debug > 3)
                cout << "numAisles: " << numAisles << ", numCrossAisles: " << numCrossAisles << endl;

            for (int i = 0; i < numArtificialVertices; i++)
            {
                getline(warehouseFile, warehouseFileLine);
                position_artificial_vertices_t position_artificial_vertices = file_reader.getPositionArtificialVertice(warehouseFileLine);

                int crossAisle = position_artificial_vertices.crossAisle;
                int pickAisle = position_artificial_vertices.pickAisle;
                int vertice_id = position_artificial_vertices.vertice_id;
                aisles[crossAisle][pickAisle] = vertice_id;

                if (debug > 3)
                    cout << "crossAisle: " << crossAisle << ", pickAisle: " << pickAisle << ", vertice_id: " << vertice_id << endl;
            }

            this->aisles = aisles;
        }
    }
}

PickerRouting::~PickerRouting() {}

void PickerRouting::save_input_parameter(parameter_t parameter)
{
    if (parameter.name == "numAisles")
        inputParameters.numAisles = parameter.value;
    else if (parameter.name == "numExtraCrossAisles")
        inputParameters.numExtraCrossAisles = parameter.value;
    else if (parameter.name == "numShelves")
        inputParameters.numShelves = parameter.value;
    else if (parameter.name == "minimumProductsRequired")
        inputParameters.minimumProductsRequired = parameter.value + 1;
    else if (parameter.name == "aisleWidth")
        inputParameters.aisleWidth = parameter.value;
    else if (parameter.name == "rackDepth")
        inputParameters.rackDepth = parameter.value;
    else if (parameter.name == "locationWidth")
        inputParameters.locationWidth = parameter.value;
    else if (parameter.name == "crossAisleWidth")
        inputParameters.crossAisleWidth = parameter.value;
    else if (parameter.name == "sourceToFirstCrossAisle")
        inputParameters.sourceToFirstCrossAisle = parameter.value;
}

void PickerRouting::save_data_parameter(parameter_t parameter)
{
    if (parameter.name == "numLocationsPerAisleSide")
        dataParameters.numLocationsPerAisleSide = parameter.value;
    else if (parameter.name == "totalLocations")
        dataParameters.totalLocations = parameter.value + 1;
    else if (parameter.name == "totalVertices")
        dataParameters.totalVertices = parameter.value;
    else if (parameter.name == "numProductVertices")
        dataParameters.numProductVertices = parameter.value;
    else if (parameter.name == "numArtificialVertices")
        dataParameters.numArtificialVertices = parameter.value;
    // else if (parameter.name == "crossAislesPositions") dataParameters.crossAislesPositions = parameter.value;
}

int PickerRouting::get_num_cross_aisles()
{
    return inputParameters.numExtraCrossAisles + 2;
}

vector<vector<int>> PickerRouting::get_aisles()
{
    return aisles;
}

vector<int> PickerRouting::get_locations_vertice()
{
    return locationsVertice;
}

vector<VerticeType> PickerRouting::get_vertices_type()
{
    return verticesType;
}

Warehouse PickerRouting::get_warehouse()
{
    return warehouse;
}

int PickerRouting::get_num_aisles()
{
    return inputParameters.numAisles;
}

int PickerRouting::get_num_extra_cross_aisles()
{
    return inputParameters.numExtraCrossAisles;
}

int PickerRouting::get_num_shelves()
{
    return inputParameters.numShelves;
}

int PickerRouting::get_minimum_products_required()
{
    return inputParameters.minimumProductsRequired;
}

int PickerRouting::get_aisle_width()
{
    return inputParameters.aisleWidth;
}

int PickerRouting::get_rack_depth()
{
    return inputParameters.rackDepth;
}

int PickerRouting::get_location_width()
{
    return inputParameters.locationWidth;
}

int PickerRouting::get_cross_aisle_width()
{
    return inputParameters.crossAisleWidth;
}

int PickerRouting::get_source_to_first_cross_aisle()
{
    return inputParameters.sourceToFirstCrossAisle;
}

int PickerRouting::get_num_locations_per_aisle_side()
{
    return dataParameters.numLocationsPerAisleSide;
}

int PickerRouting::get_total_locations()
{
    return dataParameters.totalLocations;
}

int PickerRouting::get_total_vertices()
{
    return dataParameters.totalVertices;
}

int PickerRouting::get_num_product_vertices()
{
    return dataParameters.numProductVertices;
}

int PickerRouting::get_num_artificial_vertices()
{
    return dataParameters.numArtificialVertices;
}

// int WarehouseInstance::get_cross_aisles_positions(){}
