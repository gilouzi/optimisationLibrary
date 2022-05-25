#ifndef DATAPICKERROUNTING_H
#define DATAPICKERROUNTING_H

#include "Util.h"
#include "Data.h"

class DataPickerRouting : public Data {

    private:
        
        // Data picker routing problem
        // min  30x1 + 10x2 + 10x3 + 30x4 + 10x5 + 10x6
        // s.t. 0x1 +  1x2 + 1x3 + 0x4 + 1x5 + 1x6 >= 1
        // xj E {0, 1}, j = 1, ..., 6
        int numVariables;
        vector<int> arcsDistance;
        vector<int> arcsVertice1;
        int minVisitVertice1;

    public:

        DataPickerRouting();
        virtual ~DataPickerRouting();

        virtual void readData();
        virtual void print();

        int getNumVariables     (     ) const {return numVariables ;}
        int getMinVisitVertice1(     ) const {return minVisitVertice1;}
        int getArcsDistance(int i) const ;
        int getArcsVertice1(int i) const ;
};

#endif
