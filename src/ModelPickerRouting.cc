#include "ModelPickerRouting.h"
#include "Options.h"
#include "DataPickerRouting.h"

/**
 * INITIAL METHODS
 */

// If dataModelPickerRouting was a reference
//ModelPickerRouting::ModelPickerRouting(DataModelPickerRouting& i) : Model(), dataModelPickerRouting(i) {
ModelPickerRouting::ModelPickerRouting() : Model(){
    xVariableCount = 0;
    x = "x";
    y = "y";
    g = "g";
}

ModelPickerRouting::~ModelPickerRouting() {
}


void ModelPickerRouting::execute(const Data* data) {

    float startTime = Util::getTime();
    
    if (debug > 1) solver->printSolverName();
    createModel(data);
    reserveSolutionSpace(data);
    assignWarmStart(data);
    setSolverParameters(0);

    solver->addInfoCallback(this);
    //solver->addLazyCallback(this);
    //solver->addUserCutCallback(this);

    solve(data);
    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
}  


void ModelPickerRouting::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        vector<string> colNames;
        colNames.resize(xVariableCount);
        colNames[0] = x + lex(0) + "_" + lex(2);
        colNames[1] = x + lex(1) + "_" + lex(2);
        colNames[2] = x + lex(1) + "_" + lex(3);
        colNames[3] = x + lex(2) + "_" + lex(0);
        colNames[4] = x + lex(2) + "_" + lex(1);
        colNames[5] = x + lex(3) + "_" + lex(1);
        printf("\nSolution: \n");
        for (int i = 0; i < xVariableCount; i++) {
            std::cout << colNames[i] << " = ";
            printf("%.0f\n", sol_x[i]);
    
        }
    }

}



void ModelPickerRouting::reserveSolutionSpace(const Data* data) {
    sol_x.resize(xVariableCount);
}




void ModelPickerRouting::readSolution(const Data* data) {
    totalNodes = solver->getNodeCount();
    solution->resetSolution();
    solution->setSolutionStatus(solver->solutionExists(), solver->isOptimal(),  solver->isInfeasible(), solver->isUnbounded());
    if (!solver->solutionExists()) {
        if (debug) printf("Solution does not exist\n");        
    } else {
        solution->setValue    (solver->getObjValue() );
        solution->setBestBound(solver->getBestBound());

        /*for (int i = 0; i < V; i++) {
            sol_x[i] = solver->getColValue(x + lex(i));
        }*/

        sol_x[0] = solver->getColValue(x + lex(0) + "_" + lex(2));
        sol_x[1] = solver->getColValue(x + lex(1) + "_" + lex(2));
        sol_x[2] = solver->getColValue(x + lex(1) + "_" + lex(3));
        sol_x[3] = solver->getColValue(x + lex(2) + "_" + lex(0));
        sol_x[4] = solver->getColValue(x + lex(2) + "_" + lex(1));
        sol_x[5] = solver->getColValue(x + lex(3) + "_" + lex(1));

        // Para ler aresta 1-2
        //double xx = solver->getColValue(x + lex(1) + "_" lex(2));
    }
}


void ModelPickerRouting::addBinaryVariableX(Warehouse warehouse) {
    int warehouseSize = warehouse.getSize();

    for (int i = 0; i < warehouseSize; i++) {
        std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(i);
        for (Adjacency adjacency : adjacencyList) {
            double distance = adjacency.getDistance();
            int id = adjacency.getId();
            if (debug)
                std::cout << "Adding binary variable " << x + lex(i) + "_" + lex(id) << ": " << distance << std::endl;
            solver->addBinaryVariable(distance, x + lex(i) + "_" + lex(id));
            xVariableCount += 1;
        }

    }
}


void ModelPickerRouting::addBinaryVariableY(std::vector<int> verticesId) {
    int verticesIdSize = verticesId.size();
    for (int i = 0; i < verticesIdSize; i++) {
        int id = verticesId[i];
        if (debug)
            std::cout << "Adding binary variable " << y + lex(id) << std::endl;
        solver->addBinaryVariable(0, y + lex(id));
    }
}


void ModelPickerRouting::addVariableG(std::vector<int> verticesId) {
    int verticesIdSize = verticesId.size();
    for (int i = 0; i < verticesIdSize; i++) {
        int id = verticesId[i];
        if (debug)
            std::cout << "Adding variable " << g + lex(id) << std::endl;
        solver->addVariable(std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), 0, g + lex(id));
    }
}


void ModelPickerRouting::createModel(const Data* data) {
    
    const DataPickerRouting* dataPickerRouting = dynamic_cast<const DataPickerRouting*>(data);
    Warehouse warehouse = dataPickerRouting->getWarehouse();
    std::vector<int> verticesId = dataPickerRouting->getVerticesId();

    solver->changeObjectiveSense(0);

    /*

    Constraint 1

    */
    // min  30 * x0_2  +  10 * x1_2  +  10 * x1_3  +  30 * x2_0  +  10 * x2_1  +  10 * x3_1 //(1)aresta*edge -> quer minimizar esse caminho

    //salvar todas as arestas com respectivos pesos
    addBinaryVariableX(warehouse);


    //salvar todos os vertices com valor 0
    addBinaryVariableY(verticesId);
    addVariableG(verticesId);

    vector<string> colNames;
    vector<double> elements;

    /* 
    
    Constraint 2 
    
    */
    // 1 * x1_2 + 1 * x_1_3 >= 1 //(2)obrigatoriedade de pegar vertice 1
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(1) + "_" + lex(2);
    colNames[1] = x + lex(1) + "_" + lex(3);
    elements[0] = 1;
    elements[1] = 1;
    solver->addRow(colNames, elements, 1, 'G', "constraint 2");

    /*

    Constraint 3

    */
    // x0_2 = x2_0 // (3)entrada e saida do vertice 0
    // x0_2 - x2_0 = 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(0) + "_" + lex(2);
    colNames[1] = x + lex(2) + "_" + lex(0);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.0");

    // x1_2 + x1_3 = x2_1 + x3_1 //(3)entrada e saida do vertice 1
    // x1_2 + x1_3 - x2_1 - x3_1 = 0
    colNames.resize(4);
    elements.resize(4);
    colNames[0] = x + lex(1) + "_" + lex(2);
    colNames[1] = x + lex(1) + "_" + lex(3);
    colNames[2] = x + lex(2) + "_" + lex(1);
    colNames[3] = x + lex(3) + "_" + lex(1);
    elements[0] = 1;
    elements[1] = 1;
    elements[2] = -1;
    elements[3] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.1");

    // x2_0 + x2_1 = x0_2 + x1_2 //(3)entrada e saida do vertice 2
    //  x2_0 + x2_1 - x0_2 - x1_2 = 0 
    colNames.resize(4);
    elements.resize(4);
    colNames[0] = x + lex(2) + "_" + lex(0);
    colNames[1] = x + lex(2) + "_" + lex(1);
    colNames[2] = x + lex(0) + "_" + lex(2);
    colNames[3] = x + lex(1) + "_" + lex(2);
    elements[0] = 1;
    elements[1] = 1;
    elements[2] = -1;
    elements[3] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.2");

    // x3_1 = x1_3 //(3)entrada e saida do vertice 3
    // x3_1 - x1_3 = 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(3) + "_" + lex(1);
    colNames[1] = x + lex(1) + "_" + lex(3);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.3");

    /*

    Constraint 4

    */
    // x0_2 = x2_0 = 1 //(4)entrada e saida do vertice 0 tem que ser igual a 1
    // x0_2 = 1 //(4) saida do vertice 0 igual a 1
    colNames.resize(1);
    elements.resize(1);
    colNames[0] = x + lex(0) + "_" + lex(2);
    elements[0] = 1;
    solver->addRow(colNames, elements, 1, 'E', "constraint 4 out");

    // x2_0 = 1 //(4) entrada do vertice 0 igual a 1
    colNames.resize(1);
    elements.resize(1);
    colNames[0] = x + lex(2) + "_" + lex(0);
    elements[0] = 1;
    solver->addRow(colNames, elements, 1, 'E', "constraint 4 in");

    /*

       Constraint 5

    */
    // x0_2 = g0 //(5)outdegree do vertice 0
    // x0_2 - g0 = 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(0) + "_" + lex(2);
    colNames[1] = g + lex(0);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 5.0");

    // x1_2 + x1_3 = g1 //(5)outdegree do vertice 1
    // x1_2 + x1_3 - g1 = 0
    colNames.resize(3);
    elements.resize(3);
    colNames[0] = x + lex(1) + "_" + lex(2);
    colNames[1] = x + lex(1) + "_" + lex(3);
    colNames[2] = g + lex(1);
    elements[0] = 1;
    elements[1] = 1;
    elements[2] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 5.1");

    // x2_0 + x2_1 = g2 //(5)outdegree do vertice 2
    // x2_0 + x2_1 - g2 = 0
    colNames.resize(3);
    elements.resize(3);
    colNames[0] = x + lex(2) + "_" + lex(0);
    colNames[1] = x + lex(2) + "_" + lex(1);
    colNames[2] = g + lex(2);
    elements[0] = 1;
    elements[1] = 1;
    elements[2] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 5.2");

    // x3_1 = g3 //(5)outdegree do vertice 3
    // x3_1 - g3 = 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(3) + "_" + lex(1);
    colNames[1] = g + lex(3);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 5.3");

    /*

        Constraint 6

    */
    //y0 >= x0_2 //(6)
    // y0 - x0_2 >= 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = y + lex(0);
    colNames[1] = x + lex(0) + "_" + lex(2);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'G', "constraint 6.0.0");
    
    // y1 >= x1_2 //(6)
    // y1 - x1_2 >= 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = y + lex(1);
    colNames[1] = x + lex(1) + "_" + lex(2);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'G', "constraint 6.1.0");

    // y1 >= x1_3 //(6)
    // y1 - x1_3 >= 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = y + lex(1);
    colNames[1] = x + lex(1) + "_" + lex(2);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'G', "constraint 6.1.1");

    // y2 >= x2_0 //(6)
    // y2 - x2_0 >= 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = y + lex(2);
    colNames[1] = x + lex(2) + "_" + lex(0);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'G', "constraint 6.2.0");
    // y2 >= x2_1 //(6)
    // y2 - x2_1 >= 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = y + lex(2);
    colNames[1] = x + lex(2) + "_" + lex(1);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'G', "constraint 6.2.1");
    // y3 >= x3_1 //(6)
    // y3 - x3_1 >= 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = y + lex(3);
    colNames[1] = x + lex(3) + "_" + lex(1);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'G', "constraint 6.3.0");

    //x1 + 5*x2 <= 3
    //colNames.resize(2);
    //elements.resize(2);
    //colNames[0] = x + lex(1);            
    //colNames[1] = x + lex(2);
    //elements[0] = 1;
    //elements[1] = 5;
    //solver->addRow(colNames, elements, 3, 'L', "restricaoExemplo");

    // Suponha o lista de adjacencia:
    //vector<vector<int>>vvv;
    //0: 1 2
    //1: 2
    //2: 3       
    //3
    // Criar variavel para cada aresta:
    //for (int i  = 0; i < (int) vvv.size(); i++) {
    //    for (int j = 0; j < (int) vvv[i].size(); j++) {
    //        solver->addBinaryVariable(1, x + lex(i) + "_" + lex(vvv[i][j]);
    //    }
    //}



}


void ModelPickerRouting::assignWarmStart(const Data* data) {
   
}




//////////////////////////////
//////////////////////////////
//////////////////////////////
//////////////////////////////
// Cutting plane

/*
vector<SolverCut> ModelPickerRouting::separationAlgorithm(vector<double> sol) {

    

    vector<SolverCut> cuts;

    // Finding out whether the current solution is integer or not
    int isInteger = 1;
    for (unsigned i = 0; i < sol.size(); i++) {
        if (fabs(sol[i] - round(sol[i])) > TOLERANCE) {
            //printf("%.3f ", sol[i]);
            isInteger = 0;
            break;
        }
    }


    ///////
    // Cut example
    
    // Finding the value of a specific variable in the current linear relaxation
    //double ysol = sol[solver->getColIndex(y + lex(t) + "_" + lex(b))];
      
    // Creating and adding a cut y_{tb} >= -1 as an example
    //SolverCut cut;
    //cut.setSense('G');
    //cut.addCoef(solver->getColIndex(y + lex(t) + "_" + lex(b)), 1);
    //cut.setRHS(-1);
    //cuts.push_back(cut);



    return cuts;
}
*/
