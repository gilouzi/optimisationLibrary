#include "DataPickerRouting.h"
#include "Options.h"


DataPickerRouting::DataPickerRouting() : Data(){
    numVariables  = 0;
    minVisitVertice1 = 0;
}

DataPickerRouting::~DataPickerRouting() {
}

void DataPickerRouting::readData() {
    if (debug) printf("Initialising data for capital budgeting problem\n\n");

    numVariables     = 6;
    minVisitVertice1 = 1;
    arcsDistance.resize(numVariables);
    arcsVertice1.resize(numVariables);

    arcsDistance      [0] = 30;
    arcsDistance      [1] = 10;
    arcsDistance      [2] = 10;
    arcsDistance      [3] = 30;
    arcsDistance      [4] = 10;
    arcsDistance      [5] = 10;

    arcsVertice1[0] = 0;
    arcsVertice1[1] = 1;
    arcsVertice1[2] = 1;
    arcsVertice1[3] = 0;
    arcsVertice1[4] = 0;
    arcsVertice1[5] = 0;
}

void DataPickerRouting::print() {
    if (debug) {
        printf("Num variables : %2d\n", numVariables);
        printf("Max investment: %2d\n", minVisitVertice1);
        for (int i = 0; i < numVariables; i++) {
            printf(" x %2d: dist %2d, v1 arc %2d\n", i, arcsDistance[i], arcsVertice1[i]);
        }
    }

}


int DataPickerRouting::getArcsDistance(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getInitialInvestment");
    return arcsDistance[i];
}

int DataPickerRouting::getArcsVertice1(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getFutureValue");
    return arcsVertice1[i];
}
