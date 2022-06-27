#ifndef MODELPICKERROUTING_H
#define MODELPICKERROUTING_H

#include "Model.h"
#include "Solution.h"
#include "Warehouse.h"

/**
 * Branch and cut with formulation for incomplete graph
 */
class ModelPickerRouting : public Model {

    private:
    
        // Variable names
        string x;
        string y;
        string g;
        
        // Solution values
        int xVariableCount;
        vector<double> sol_x;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution        (const Data* data);
        virtual void assignWarmStart     (const Data* data);
        virtual void createModel         (const Data* data);
        
        void addBinaryVariableX(Warehouse warehouse);
        void addBinaryVariableY(std::vector<int> verticesId);
        void addVariableG(std::vector<int> verticesId);
        void addConstraintVerticesToVisit(Warehouse warehouse, std::vector<int> verticesToVisit);
        void addConstraintVerticeInAndOutMustBeEqual(Warehouse warehouse, std::vector<int> verticesId);
        void printSolutionVariables(int digits = 5, int decimals = 2);
        
    public:
        
        ModelPickerRouting();

        virtual ~ModelPickerRouting();

        virtual void execute(const Data *data);


};    

#endif 


