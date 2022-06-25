#include "DataPickerRouting.h"
#include "Options.h"


DataPickerRouting::DataPickerRouting(std::string fileName) : Data(){
    this->fileName = fileName;
}

DataPickerRouting::~DataPickerRouting() {
}

void DataPickerRouting::readData() {
    if (debug) printf("Initialising data for picker routing problem\n\n");

    /*WarehouseInstance warehouseInstance(filename);
    warehouse = warehouseInstance.getWarehouse;*/

    Warehouse warehouse(4);

    warehouse.addNewAdjacency(0, 2, 30);
    warehouse.addNewAdjacency(2, 0, 30);

    warehouse.addNewAdjacency(2, 1, 10);
    warehouse.addNewAdjacency(1, 2, 10);

    warehouse.addNewAdjacency(1, 3, 10);
    warehouse.addNewAdjacency(3, 1, 10);

    this->warehouse = warehouse;
}

void DataPickerRouting::print() {
    if (debug) {
        warehouse.printWarehouse();
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
