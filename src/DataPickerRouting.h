#ifndef DATAPICKERROUNTING_H
#define DATAPICKERROUNTING_H

#include "Util.h"
#include "Data.h"
#include "PickerRouting/Warehouse.h"

class DataPickerRouting : public Data {

    private:
        std::string fileName;
        Warehouse warehouse;
        std::vector<int> verticesToVisit;
        std::vector<int> verticesId; // (usar para inicializar as variaveis y e g)
        // Data picker routing problem
        // x0_2 = x1
        // x1_2 = x2
        // x1_3 = x3
        // x2_0 = x4
        // x2_1 = x5
        // x3_1 = x6
        // 
        // (usar o warehouse para criar)
        // min  30 * x0_2 + 10 * x1_2 + 10 * x1_3 + 30 * x2_0 + 10 * x2_1 + 10 * x3_1 //(1)aresta*edge -> quer minimizar esse caminho 
        // 
        // (usar o verticesToVisit + warehouse para criar)
        // s.t. 1 * x1_2 + 1 * x_1_3 >= 1 //(2)obrigatoriedade de pegar vertice 1 
        // 
        // (usar o warehouse para criar)
        // x0_2 = x2_0 // (3)entrada e saida do vertice 0
        // x1_2 + x1_3 = x2_1 + x3_1 //(3)entrada e saida do vertice 1 
        // x2_0 + x2_1 = x0_2 + x1_2 //(3)entrada e saida do vertice 2
        // x3_1 = x1_3 //(3)entrada e saida do vertice 3
        // 
        // (usar warehouse[0] para criar)
        // x0_2 + x0_? = x2_0 + x?_0 = 1 //(4)entrada e saida do vertice 0 tem que ser igual a 1
        // 
        // (usar warehouse[x] e warehouse[x].getSize
        // x0_2 = g0 //(5)outdegree do vertice 0
        // x1_2 + x1_3 = g1 //(5)outdegree do vertice 1
        // x2_0 + x2_1 = g2 //(5)outdegree do vertice 2
        // x3_1 = g3 //(5)outdegree do vertice 3
        // 
        // (usar warehouse)
        // y0 >= x0_2 //(6)
        // y1 >= x1_2 //(6)
        // y1 >= x1_3 //(6)
        // y2 >= x2_0 //(6)
        // y2 >= x2_1 //(6)
        // y3 >= x3_1 //(6)
        // 
        // xj E {0, 1}, j = 1, ..., 6

    public:

        DataPickerRouting(std::string fileName);
        virtual ~DataPickerRouting();

        virtual void readData();
        virtual void print();

        Warehouse getWarehouse() const { return warehouse; }
        std::vector<int> getVerticesToVisit() const { return verticesToVisit; }
        std::vector<int> getVerticesId() const { return verticesId; }
};

#endif
