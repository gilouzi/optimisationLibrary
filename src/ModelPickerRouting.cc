#include "ModelPickerRouting.h"
#include "Options.h"
#include "DataPickerRouting.h"

/**
 * INITIAL METHODS
 */

// If dataModelPickerRouting was a reference
//ModelPickerRouting::ModelPickerRouting(DataModelPickerRouting& i) : Model(), dataModelPickerRouting(i) {
ModelPickerRouting::ModelPickerRouting() : Model(){
    V = 0;
    x = "x";
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
        printf("\nSolution: \n");
        for (int i = 0; i < V; i++) {
            printf("  x%d = %.0f\n", i, sol_x[i]);
    
        }
    }

}



void ModelPickerRouting::reserveSolutionSpace(const Data* data) {
    sol_x.resize(V);
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

        for (int i = 0; i < V; i++) {
            sol_x[i] = solver->getColValue(x + lex(i));
        }

        // Para ler aresta 1-2
        //double xx = solver->getColValue(x + lex(1) + "_" lex(2));
    }
}


void ModelPickerRouting::createModel(const Data* data) {
    
    const DataPickerRouting* dataCB = dynamic_cast<const DataPickerRouting*>(data);
    V = dataCB->getNumVariables();
    solver->changeObjectiveSense(0);

    /*

    Constraint 1

    */
    for (int i = 0; i < V; i++)
        solver->addBinaryVariable(dataCB->getArcsDistance(i), x + lex(i));

    vector<string> colNames;
    vector<double> elements;

    /* 
    
    Constraint 2 
    
    */
    // 0x1 + 1x2 + 1x3 + 0x4 + 0x5 + 0x6 >= 1 //(2)obrigatoriedade de pegar vertice 1
    colNames.resize(V);
    elements.resize(V);
    for (int i = 0; i < V; i++) {
        colNames[i] = x + lex(i);
        elements[i] = dataCB->getArcsVertice1(i);
    }
    solver->addRow(colNames, elements, dataCB->getMinVisitVertice1(), 'G', "constraint 2");

    /*

    Constraint 3

    */
    // x1 = x4 // (3)entrada e saida do vertice 0
    // x1 - x4 = 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(0);            
    colNames[1] = x + lex(3);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.0");

    // x2 + x3 = x5 + x6 //(3)entrada e saida do vertice 1
    // x2 + x3 - x5 - x6 = 0
    colNames.resize(4);
    elements.resize(4);
    colNames[0] = x + lex(1);
    colNames[1] = x + lex(2);
    colNames[2] = x + lex(4);
    colNames[3] = x + lex(5);
    elements[0] = 1;
    elements[1] = 1;
    elements[2] = -1;
    elements[3] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.1");

    // x4 + x5 = x1 + x2 //(3)entrada e saida do vertice 2
    // x4 + x5 - x1 - x2 = 0 
    colNames.resize(4);
    elements.resize(4);
    colNames[0] = x + lex(3);
    colNames[1] = x + lex(4);
    colNames[2] = x + lex(0);
    colNames[3] = x + lex(1);
    elements[0] = 1;
    elements[1] = 1;
    elements[2] = -1;
    elements[3] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.2");

    // x6 = x3 //(3)entrada e saida do vertice 3
    // x6 - x3 = 0
    colNames.resize(2);
    elements.resize(2);
    colNames[0] = x + lex(5);
    colNames[1] = x + lex(2);
    elements[0] = 1;
    elements[1] = -1;
    solver->addRow(colNames, elements, 0, 'E', "constraint 3.3");

    /*

    Constraint 4

    */
    // x1 = x4 = 1 //(4)entrada e saida do vertice 0 tem que ser igual a 1
    // x1 = 1 //(4) saida do vertice 0 igual a 1
    colNames.resize(1);
    elements.resize(1);
    colNames[0] = x + lex(0);
    elements[0] = 1;
    solver->addRow(colNames, elements, 1, 'E', "constraint 4 out");

    // x4 = 1 //(4) entrada do vertice 0 igual a 1
    colNames.resize(1);
    elements.resize(1);
    colNames[0] = x + lex(3);
    elements[0] = 1;
    solver->addRow(colNames, elements, 1, 'E', "constraint 4 in");

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
