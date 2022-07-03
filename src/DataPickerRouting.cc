#include "DataPickerRouting.h"
#include "Options.h"
#include "PickerRouting/PickerRouting.h"
#include "PickerRouting/Products.h"
#include "PickerRouting/Orders.h"


DataPickerRouting::DataPickerRouting(std::string fileName) : Data(){
    this->fileName = fileName;
}

DataPickerRouting::~DataPickerRouting() {
}

void DataPickerRouting::readData() {
    if (debug) printf("Initialising data for picker routing problem\n\n");

    PickerRouting pickerRouting("../../../instances/warehouses/warehouse_8_0_3_1560");

    printf("Initialized picker routing\n");

    string productsFile = "../../../instances/products/productsDB_1560_locations";
    int minimum_products_required = pickerRouting.get_minimum_products_required();
    std::vector<int> locationsVertice = pickerRouting.get_locations_vertice();
    Products productsInstance(productsFile, minimum_products_required, locationsVertice);

    string ordersFile = "../../../instances/orders/instances_d5_ord5";
    int totalVertices = pickerRouting.get_total_vertices();
    vector<int> productsVertice = productsInstance.get_products_vertice();
    Orders ordersInstance(ordersFile, totalVertices, productsVertice);
    vector<int> verticesToVisit = ordersInstance.get_vertices_to_visit();
    
    Warehouse warehouse = pickerRouting.get_warehouse();
    vector<VerticeType> verticesType = pickerRouting.get_vertices_type();
    int numVertices = pickerRouting.get_total_vertices();
    warehouse.reduceGraph(totalVertices, verticesToVisit, verticesType);

    this->warehouse = warehouse;
    for (int i = 0; i < verticesToVisit.size(); i++) {
        if (verticesToVisit[i] == 1) this->verticesToVisit.push_back(i);
    }
    //this->verticesToVisit = verticesToVisit;

    verticesId = warehouse.getVerticesWithAdjacency();
    

    //mock:
    /*Warehouse warehouse(12);

    warehouse.addNewAdjacency(0, 6, 10);
    warehouse.addNewAdjacency(6, 0, 10);

    warehouse.addNewAdjacency(0, 7, 20);
    warehouse.addNewAdjacency(7, 0, 20); 
    
    warehouse.addNewAdjacency(0, 8, 30);
    warehouse.addNewAdjacency(8, 0, 30);

    warehouse.addNewAdjacency(6, 7, 10);
    warehouse.addNewAdjacency(7, 6, 10);

    warehouse.addNewAdjacency(6, 1, 15);
    warehouse.addNewAdjacency(1, 6, 15);

    warehouse.addNewAdjacency(1, 9, 15);
    warehouse.addNewAdjacency(9, 1, 15);

    warehouse.addNewAdjacency(9, 10, 10);
    warehouse.addNewAdjacency(10, 9, 10);

    warehouse.addNewAdjacency(7, 2, 10);
    warehouse.addNewAdjacency(2, 7, 10);

    warehouse.addNewAdjacency(7, 8, 30);
    warehouse.addNewAdjacency(8, 7, 30);

    warehouse.addNewAdjacency(2, 10, 20);
    warehouse.addNewAdjacency(10, 2, 20);

    warehouse.addNewAdjacency(10, 11, 30);
    warehouse.addNewAdjacency(11, 10, 30);

    warehouse.addNewAdjacency(8, 3, 15);
    warehouse.addNewAdjacency(3, 8, 15);

    warehouse.addNewAdjacency(3, 4, 5);
    warehouse.addNewAdjacency(4, 3, 5);

    warehouse.addNewAdjacency(4, 5, 5);
    warehouse.addNewAdjacency(5, 4, 5);

    warehouse.addNewAdjacency(5, 11, 5);
    warehouse.addNewAdjacency(11, 5, 5);

    this->warehouse = warehouse;

    verticesToVisit.push_back(1);
    verticesToVisit.push_back(2);
    verticesToVisit.push_back(3);
    verticesToVisit.push_back(4);
    verticesToVisit.push_back(5);
    verticesId = warehouse.getVerticesWithAdjacency();*/


}

void DataPickerRouting::print() {
    if (debug) {
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

//
//int DataPickerRouting::getArcsDistance(int i) const {
//    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getInitialInvestment");
//    return arcsDistance[i];
//}
//
//int DataPickerRouting::getArcsVertice1(int i) const {
//    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getFutureValue");
//    return arcsVertice1[i];
//}
