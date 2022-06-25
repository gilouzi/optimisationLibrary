#include "DataPickerRouting.h"
#include "Options.h"


DataPickerRouting::DataPickerRouting(std::string fileName) : Data(){
    this->fileName = fileName;
}

DataPickerRouting::~DataPickerRouting() {
}

void DataPickerRouting::readData() {
    if (debug) printf("Initialising data for picker routing problem\n\n");

    /*WarehouseInstance warehouseInstance("../instances/warehouses/warehouse_8_1_3_1560");

    string productsFile = "../instances/products/productsDB_1560_locations";
    int minimum_products_required = warehouseInstance.get_minimum_products_required();
    std::vector<int> locationsVertice = warehouseInstance.get_locations_vertice();
    ProductsInstance productsInstance(productsFile, minimum_products_required, locationsVertice);

    string ordersFile = "../instances/orders/instances_d5_ord11";
    int totalVertices = warehouseInstance.get_total_vertices();
    vector<int> productsVertice = productsInstance.get_products_vertice();
    OrdersInstance ordersInstance(ordersFile, totalVertices, productsVertice);
    vector<int> verticesToVisit = ordersInstance.get_vertices_to_visit();
    
    Warehouse warehouse = warehouseInstance.get_warehouse();
    vector<vertice_type> verticesType = warehouseInstance.get_vertices_type();
    int numVertices = warehouseInstance.get_total_vertices();
    warehouse.reduce_graph(totalVertices, verticesToVisit, verticesType);

    this->warehouse = warehouse;
    this->verticesToVisit = verticesToVisit;
    verticesId = warehouse.getVerticesWithAdjacency();
    */

    //mock:
    Warehouse warehouse(4);

    warehouse.addNewAdjacency(0, 2, 30);
    warehouse.addNewAdjacency(2, 0, 30);

    warehouse.addNewAdjacency(2, 1, 10);
    warehouse.addNewAdjacency(1, 2, 10);

    warehouse.addNewAdjacency(1, 3, 10);
    warehouse.addNewAdjacency(3, 1, 10);

    this->warehouse = warehouse;

    verticesToVisit.push_back(1);

    verticesId = warehouse.getVerticesWithAdjacency();

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
