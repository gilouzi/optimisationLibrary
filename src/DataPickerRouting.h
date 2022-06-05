#ifndef DATAPICKERROUNTING_H
#define DATAPICKERROUNTING_H

#include "Util.h"
#include "Data.h"

class DataPickerRouting : public Data {

    private:
        
        // Data picker routing problem
        // x_0_2 = x1
        // x_1_2 = x2
        // x_1_3 = x3
        // x_2_0 = x4
        // x_2_1 = x5
        // x_3_1 = x6
        // min  30x1 + 10x2 + 10x3 + 30x4 + 10x5 + 10x6
        // s.t. 0x1 +  1x2 + 1x3 + 0x4 + 0x5 + 0x6 >= 1 //(2)obrigatoriedade de pegar vertice 1
        // 
        // x1 = x4 // (3)entrada e saida do vertice 0
        // x2 + x3 = x5 + x6 //(3)entrada e saida do vertice 1
        // x4 + x5 = x1 + x2 //(3)entrada e saida do vertice 2
        // x6 = x3 //(3)entrada e saida do vertice 3
        // 
        // x1 = x4 = 1 //(4)entrada e saida do vertice 0 tem que ser igual a 1
        // 
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
