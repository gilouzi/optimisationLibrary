#ifndef DATAPICKERROUNTING_H
#define DATAPICKERROUNTING_H

#include "Util.h"
#include "Data.h"

class DataPickerRouting : public Data {

    private:
        
        // Data picker routing problem
        // x0_2 = x1
        // x1_2 = x2
        // x1_3 = x3
        // x2_0 = x4
        // x2_1 = x5
        // x3_1 = x6
        // min  30 * x0_2 + 10 * x1_2 + 10 * x1_3 + 30 * x2_0 + 10 * x2_1 + 10 * x3_1 //(1)aresta*edge -> quer minimizar esse caminho
        // 
        // s.t. 1 * x1_2 + 1 * x_1_3 >= 1 //(2)obrigatoriedade de pegar vertice 1
        // 
        // x0_2 = x2_0 // (3)entrada e saida do vertice 0
        // x1_2 + x1_3 = x2_1 + x3_1 //(3)entrada e saida do vertice 1
        // x2_0 + x2_1 = x0_2 + x1_2 //(3)entrada e saida do vertice 2
        // x3_1 = x1_3 //(3)entrada e saida do vertice 3
        // 
        // x0_2 = x2_0 = 1 //(4)entrada e saida do vertice 0 tem que ser igual a 1
        // 
        // x0_2 = g0 //(5)outdegree do vertice 0
        // x1_2 + x1_3 = g1 //(5)outdegree do vertice 1
        // x2_0 + x2_1 = g2 //(5)outdegree do vertice 2
        // x3_1 = g3 //(5)outdegree do vertice 3
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
