#include "DataPickerRouting.h"
#include "Options.h"
#include "PickerRouting/PickerRouting.h"
#include "PickerRouting/Products.h"
#include "PickerRouting/Orders.h"
#include "PickerRouting/TestInstance.h"


DataPickerRouting::DataPickerRouting(std::string fileName) : Data(){
    this->fileName = fileName;
}

DataPickerRouting::~DataPickerRouting() {
}

void DataPickerRouting::readData() {
    if (debug) printf("Initialising data for picker routing problem\n\n");

    TestInstance testInstance;
    this->warehouse = testInstance.get_warehouse_7();
    vector<int> verticesToVisit = testInstance.get_vertices_to_visit_7();

   /* PickerRouting pickerRouting("../../../instances/warehouses/warehouse_8_0_3_1560", debug);

    string productsFile = "../../../instances/products/productsDB_1560_locations";
    int minimum_products_required = pickerRouting.get_minimum_products_required();
    std::vector<int> locationsVertice = pickerRouting.get_locations_vertice();
    Products productsInstance(productsFile, minimum_products_required, locationsVertice, debug);

    string ordersFile = "../../../instances/orders/instances_d5_ord5";
    int totalVertices = pickerRouting.get_total_vertices();
    vector<int> productsVertice = productsInstance.get_products_vertice();
    Orders ordersInstance(ordersFile, totalVertices, productsVertice, debug);
    vector<int> verticesToVisit = ordersInstance.get_vertices_to_visit();
    
    Warehouse warehouse = pickerRouting.get_warehouse();
    vector<VerticeType> verticesType = pickerRouting.get_vertices_type();
    int numVertices = pickerRouting.get_total_vertices();
    warehouse.reduceGraph(totalVertices, verticesToVisit, verticesType);

    this->warehouse = warehouse;
    */

    verticesId = warehouse.getVerticesWithAdjacency();
    for (int i = 0; i < verticesToVisit.size(); i++) {
        if (verticesToVisit[i] == 1) this->verticesToVisit.push_back(i);
    }
    


}

void DataPickerRouting::print() {
    if (debug > 2) {
        warehouse.printWarehouse();

        std::cout << "Vertices to visit: ";
        for (int i = 0; i < verticesToVisit.size(); i++) {
            std::cout << verticesToVisit[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Vertices id: ";
        for (int i = 0; i < verticesId.size(); i++) {
            std::cout << verticesId[i] << " ";
        }
        std::cout << std::endl;
    }
}
