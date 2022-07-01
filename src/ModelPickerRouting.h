#ifndef MODELPICKERROUTING_H
#define MODELPICKERROUTING_H

#include "Model.h"
#include "Solution.h"
#include "PickerRouting/Warehouse.h"

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
        vector<string> sol_x_names;

        set<int> verticesToVisit;
        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution        (const Data* data);
        virtual void assignWarmStart     (const Data* data);
        vector<SolverCut> separationAlgorithm(vector<double> sol);
        virtual void createModel         (const Data* data);
        
        SubGraph createSubGraph(vector<double> sol);
        int getIdToExplore(vector<bool>& visited);
        void getNewComponent(vector<vector<int>> graph, vector<int>& component, vector<bool>& visited, int idToExplore);
        void printGraph(vector<vector<int>> graph);
        void addBinaryVariableX(Warehouse warehouse);
        void addBinaryVariableY(std::vector<int> verticesId);
        void addVariableG(std::vector<int> verticesId);
        void addConstraintVerticesToVisit(Warehouse warehouse, std::vector<int> verticesToVisit);
        void addConstraintVerticeInAndOutMustBeEqual(Warehouse warehouse, std::vector<int> verticesId);
        void addConstraintInAndOutOfVerticeZeroMustBeOne(Warehouse warehouse);
        void addConstraintSetVerticesOutdegree(Warehouse warehouse, std::vector<int> verticesId);
        void addConstraintSetVerticesYVariable(Warehouse warehouse, std::vector<int> verticesId);
        void printSolutionVariables(int digits = 5, int decimals = 2);
        
    public:
        
        ModelPickerRouting();

        virtual ~ModelPickerRouting();

        virtual void execute(const Data *data);


};    

#endif 


