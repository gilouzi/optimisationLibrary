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
    solver->addLazyCallback(this);
    //solver->addUserCutCallback(this);

    solve(data);
    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
}  


void ModelPickerRouting::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        printf("\nSolution: \n");
        for (int i = 0; i < xVariableCount; i++) {
            std::cout << sol_x_names[i] << " = ";
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

        for (int i = 0; i < xVariableCount; i++) {
            sol_x[i] = solver->getColValue(sol_x_names[i]);
        }
    }
}


void ModelPickerRouting::addBinaryVariableX(Warehouse warehouse) {
    /*

    Constraint 1

    */
    // min  30 * x0_2  +  10 * x1_2  +  10 * x1_3  +  30 * x2_0  +  10 * x2_1  +  10 * x3_1 //(1)aresta*edge -> quer minimizar esse caminho

    if (debug)
        std::cout << "addBinaryVariableX" << std::endl;

    int warehouseSize = warehouse.getSize();

    for (int i = 0; i < warehouseSize; i++) {
        std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(i);
        for (Adjacency adjacency : adjacencyList) {
            double distance = adjacency.getDistance();
            int id = adjacency.getId();
            if (debug)
                std::cout << "Adding binary variable " << x + lex(i) + "_" + lex(id) << ": " << distance << std::endl;
            string variableName = x + lex(i) + "_" + lex(id);
            solver->addBinaryVariable(distance, variableName);
            sol_x_names.push_back(variableName);
            xVariableCount += 1;
        }

    }
}


void ModelPickerRouting::addBinaryVariableY(std::vector<int> verticesId) {
    if (debug)
        std::cout << "addBinaryVariableY" << std::endl;

    int verticesIdSize = verticesId.size();
    for (int i = 0; i < verticesIdSize; i++) {
        int id = verticesId[i];
        if (debug)
            std::cout << "Adding binary variable " << y + lex(id) << std::endl;
        solver->addBinaryVariable(0, y + lex(id));
    }
}


void ModelPickerRouting::addVariableG(std::vector<int> verticesId) {
    if (debug)
        std::cout << "addVariableG" << std::endl;

    int verticesIdSize = verticesId.size();
    for (int i = 0; i < verticesIdSize; i++) {
        int id = verticesId[i];
        if (debug)
            std::cout << "Adding variable " << g + lex(id) << std::endl;
        solver->addVariable(std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), 0, g + lex(id));
    }
}


void ModelPickerRouting::addConstraintVerticesToVisit(Warehouse warehouse, std::vector<int> verticesToVisit) {
    /*

    Constraint 2

    */
    // 1 * x1_2 + 1 * x_1_3 >= 1 //(2)obrigatoriedade de pegar vertice 1
    if (debug)
        std::cout << "addConstraintVerticesToVisit" << std::endl;

    for (int id : verticesToVisit) {
        this->verticesToVisit.insert(id);
        std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(id);
        vector<string> colNames;
        vector<double> elements;

        for (Adjacency adjacency : adjacencyList) {
            string colName = x + lex(id) + "_" + lex(adjacency.getId());
            colNames.push_back(colName);
            elements.push_back(1);
        }

        string constraintName = "constraint: vertice to visit" + lex(id);
        solver->addRow(colNames, elements, 1, 'G', constraintName);
    }
}

void ModelPickerRouting::addConstraintVerticeInAndOutMustBeEqual(Warehouse warehouse, std::vector<int> verticesId) {
    /*

    Constraint 3

    */
    // x1_2 + x1_3 = x2_1 + x3_1 //(3)entrada e saida do vertice 1
    // x1_2 + x1_3 - x2_1 - x3_1 = 0
    if (debug)
        std::cout << "addConstraintVerticeInAndOutMustBeEqual" << std::endl;

    for (int id : verticesId) {
        std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(id);
        vector<string> colNames;
        vector<double> elements;

        for (Adjacency adjacency : adjacencyList) {
            int adjacency_id = adjacency.getId();
            string colName = x + lex(id) + "_" + lex(adjacency_id);
            colNames.push_back(colName);
            elements.push_back(1);

            colName = x + lex(adjacency_id) + "_" + lex(id);
            colNames.push_back(colName);
            elements.push_back(-1);
        }

        string constraintName = "constraint: vertice " + lex(id) + " in and out must be equal";
        solver->addRow(colNames, elements, 0, 'E', constraintName);
    }
}


void ModelPickerRouting::addConstraintInAndOutOfVerticeZeroMustBeOne(Warehouse warehouse) {
    /*

     Constraint 4

     */
     // x0_2 + x0_4 = x2_0 + x4_0 = 1 //(4)entrada e saida do vertice 0 tem que ser igual a 1
     // x0_2 + x0_4 = 1 //(4) saida do vertice 0 igual a 1
    //  x2_0 + x4_0 = 1 //(4) entrada do vertice 0 igual a 1
    if (debug)
        std::cout << "addConstraintInAndOutOfVerticeZeroMustBeOne" << std::endl;

    std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(0);
    vector<string> colNamesIn;
    vector<double> elementsIn;

    vector<string> colNamesOut;
    vector<double> elementsOut;

    for (Adjacency adjacency : adjacencyList) {
        int adjacency_id = adjacency.getId();
        string colNameIn = x + lex(0) + "_" + lex(adjacency_id);
        colNamesIn.push_back(colNameIn);
        elementsIn.push_back(1);

        string colNameOut = x + lex(adjacency_id) + "_" + lex(0);
        colNamesOut.push_back(colNameOut);
        elementsOut.push_back(1);
    }

    string constraintName = "constraint: vertice 0 'in' must be one";
    solver->addRow(colNamesIn, elementsIn, 1, 'E', constraintName);

    constraintName = "constraint: vertice 0 'out' must be one";
    solver->addRow(colNamesOut, elementsOut, 1, 'E', constraintName);
    
}


void ModelPickerRouting::addConstraintSetVerticesOutdegree(Warehouse warehouse, std::vector<int> verticesId) {
    /*

       Constraint 5

    */

    // x1_2 + x1_3 = g1 //(5)outdegree do vertice 1
    // x1_2 + x1_3 - g1 = 0
    if (debug)
        std::cout << "addConstraintSetVerticesOutdegree" << std::endl;

    for (int id : verticesId) {
        std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(id);
        vector<string> colNames;
        vector<double> elements;

        for (Adjacency adjacency : adjacencyList) {
            string colName = x + lex(id) + "_" + lex(adjacency.getId());
            colNames.push_back(colName);
            elements.push_back(1);
        }

        colNames.push_back(g + lex(id));
        elements.push_back(-1);

        string constraintName = "constraint: vertice " + lex(id) + " outdegree";
        solver->addRow(colNames, elements, 0, 'E', constraintName);
    }
}


void ModelPickerRouting::addConstraintSetVerticesYVariable(Warehouse warehouse, std::vector<int> verticesId) {
    /*

        Constraint 6

    */
    // y1 >= x1_2 //(6)
    // y1 - x1_2 >= 0
    if (debug)
        std::cout << "addConstraintSetVerticesYVariable" << std::endl;

    for (int id : verticesId) {
        std::vector<Adjacency> adjacencyList = warehouse.getAllAdjacencies(id);
        vector<string> colNames;
        vector<double> elements;

        for (Adjacency adjacency : adjacencyList) {
            string colName = x + lex(id) + "_" + lex(adjacency.getId());
            if (debug)
                std::cout << colName << std::endl;
            colNames.push_back(colName);
            elements.push_back(-1);
            colNames.push_back(y + lex(id));
            elements.push_back(1);

            string constraintName = "constraint: y" + lex(id) + ">= " + colName;
            solver->addRow(colNames, elements, 0, 'G', constraintName);
        }
    }
}


void ModelPickerRouting::createModel(const Data* data) {
    
    const DataPickerRouting* dataPickerRouting = dynamic_cast<const DataPickerRouting*>(data);
    Warehouse warehouse = dataPickerRouting->getWarehouse();
    std::vector<int> verticesId = dataPickerRouting->getVerticesId();
    std::vector<int> verticesToVisit = dataPickerRouting->getVerticesToVisit();

    solver->changeObjectiveSense(0);

    //salvar todas as arestas com respectivos pesos
    addBinaryVariableX(warehouse);

    //salvar todos os vertices com valor 0
    addBinaryVariableY(verticesId);
    addVariableG(verticesId);

    //adicionar as restricoes
    addConstraintVerticesToVisit(warehouse, verticesToVisit);
    addConstraintVerticeInAndOutMustBeEqual(warehouse, verticesId);
    addConstraintInAndOutOfVerticeZeroMustBeOne(warehouse);
    addConstraintSetVerticesOutdegree(warehouse, verticesId);
    addConstraintSetVerticesYVariable(warehouse, verticesId);
}


void ModelPickerRouting::assignWarmStart(const Data* data) {
   
}




//////////////////////////////
//////////////////////////////
//////////////////////////////
//////////////////////////////
// Cutting plane


SubGraph ModelPickerRouting::createSubGraph(vector<double> sol) {
    vector<vector<int>> graph;
    vector<vector<string>> id_out_edges;
    map<int, int> map_original_id_to_aux;
    map<int, int> map_aux_id_to_original;

    for (int i = 0; i < xVariableCount; i++) {
        double colIndex = solver->getColIndex(sol_x_names[i]);
        double solutionValue = sol[colIndex];
        if (solutionValue == 1) {
            string x_name = sol_x_names[i];
            Edge edge(x_name);

            //std::cout << sol_x_names[i] << " " << edge.getId_i() << " " << edge.getId_j() << " " << std::endl;

            int id_i = edge.getId_i();
            int id_j = edge.getId_j();

            map<int, int>::iterator it_i = map_original_id_to_aux.find(id_i);
            map<int, int>::iterator it_j = map_original_id_to_aux.find(id_j);

            if (it_i != map_original_id_to_aux.end() && it_j == map_original_id_to_aux.end()) {
                //id_i existe e id_j nao existe
                int aux_id_i = it_i->second;
                int aux_id_j = graph.size();

                map_original_id_to_aux.insert({ id_j, aux_id_j });
                map_aux_id_to_original.insert({ aux_id_j, id_j });

                graph.push_back(vector<int>());
                graph[aux_id_i].push_back(aux_id_j);

                id_out_edges.push_back(vector<string>());
                id_out_edges[aux_id_i].push_back(x_name);
            }
            else if (it_i == map_original_id_to_aux.end() && it_j != map_original_id_to_aux.end()) {
                //id_i nao existe e id_j existe
                int aux_id_i = graph.size();
                int aux_id_j = it_j->second;

                map_original_id_to_aux.insert({ id_i, aux_id_i });
                map_aux_id_to_original.insert({ aux_id_i, id_i });

                graph.push_back(vector<int> { aux_id_j });

                id_out_edges.push_back(vector<string> {x_name});
            }
            else if (it_i == map_original_id_to_aux.end() && it_j == map_original_id_to_aux.end()) {
                //nem id_i nem id_j existem
                int aux_id_i = graph.size();
                int aux_id_j = graph.size() + 1;

                map_original_id_to_aux.insert({ id_i, aux_id_i });
                map_aux_id_to_original.insert({ aux_id_i, id_i });

                map_original_id_to_aux.insert({ id_j, aux_id_j });
                map_aux_id_to_original.insert({ aux_id_j, id_j });

                graph.push_back(vector<int> { aux_id_j });
                graph.push_back(vector<int>());

                id_out_edges.push_back(vector<string> {x_name});
                id_out_edges.push_back(vector<string>());
            }
            else if (it_i != map_original_id_to_aux.end() && it_j != map_original_id_to_aux.end()) {
                //id_i e id_j existem
                int aux_id_i = it_i->second;
                int aux_id_j = it_j->second;

                graph[aux_id_i].push_back(aux_id_j);

                id_out_edges[aux_id_i].push_back(x_name);
            }
        }
    }

    SubGraph subGraph(graph, map_aux_id_to_original, id_out_edges);
    return subGraph;
}

void ModelPickerRouting::printGraph(vector<vector<int>> graph) {
    int graphSize = graph.size();
    std::cout << "Quantidade de vertices: " << graphSize << std::endl;
    std::cout << "Lista de adjacencia no formato (id, distancia):" << std::endl;
    for (int i = 0; i < graphSize; i++)
    {
        std::cout << "Vertice " << i << ": ";
        int adjacencyListSize = graph[i].size();
        if (adjacencyListSize == 0)
        {
            std::cout << "vazio";
        }
        else
        {
            for (int j = 0; j < adjacencyListSize; j++)
            {
                std::cout << "(" << i << ", " << graph[i][j] << ") ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void ModelPickerRouting::getNewComponent(vector<vector<int>> graph, vector<int> &component, vector<bool> &visited, int idToExplore) {
    if (!visited[idToExplore]) {
        component.push_back(idToExplore);
        visited[idToExplore] = true;
        for (int id : graph[idToExplore]) {
            getNewComponent(graph, component, visited, id);
        }
    }
}

int ModelPickerRouting::getIdToExplore(vector<bool>& visited) {
    for (int i=0; i < visited.size(); i++) {
        if (!visited[i]) {
            return i;
        }
    }

    return -1;
}
vector<SolverCut> ModelPickerRouting::separationAlgorithm(vector<double> sol) {

    

    vector<SolverCut> cuts;
    // Finding out whether the current solution is integer or not
    /*int isInteger = 1;
    for (unsigned i = 0; i < sol.size(); i++) {
        if (fabs(sol[i] - round(sol[i])) > TOLERANCE) {
            printf("%.3f ", sol[i]);
            isInteger = 0;
            break;
        }
    }*/

    //printf("%d %d", sol.size(), sol_x.size());

    printf("separation algorithm oooooooooooooooooooooooooooooooooooooooooooooooo\n");
    
    SubGraph subGraph = createSubGraph(sol);

    vector<vector<int>> graph = subGraph.getGraph();
    map<int, int> map_aux_id_to_original = subGraph.getMapAuxIdToOriginal();
    vector<vector<string>> id_out_edges = subGraph.getIdOutEdges();

    printGraph(graph);

    vector<int> component;
    vector<bool> visited(graph.size(), false);

    getNewComponent(subGraph.getGraph(), component, visited, 0);
    int idToExplore = getIdToExplore(visited);

    for (int id : component) {
        map<int, int>::iterator it = map_aux_id_to_original.find(id);
        int original_id = it->second;
        std::cout << id << "(" << original_id << ") ";
    }
    std::cout << std::endl;

    while (idToExplore != -1) {
        component.clear();
        getNewComponent(subGraph.getGraph(), component, visited, idToExplore);
        idToExplore = getIdToExplore(visited);

        bool addedY = false;
        SolverCut cut;
        cut.setSense('G');
        cut.setRHS(0);

        for (int id : component) { 
            map<int, int>::iterator it = map_aux_id_to_original.find(id);
            int original_id = it->second;
            std::cout << id << "(" << original_id << ") "; 
        }

        std::cout << std::endl;


        for (int id : component) { 

            map<int, int>::iterator it = map_aux_id_to_original.find(id);
            int original_id = it->second;
            //std::cout << id << "(" << original_id << ") ";


            string variableName;
            int col_index;


            set<int>::iterator toVisitIt = verticesToVisit.find(original_id);
            if ( !addedY && toVisitIt != verticesToVisit.end()) {
                variableName = y + lex(original_id);
                col_index = solver->getColIndex(variableName);
                cut.addCoef(col_index, -1);
                std::cout << "adding y of " << original_id << ": -" << variableName << ' ' << std::endl;

                addedY = true;
            }

            variableName = g + lex(original_id);
            col_index = solver->getColIndex(variableName);
            cut.addCoef(col_index, 1);
            std::cout << "adding g of " << original_id << ": " << variableName << ' ' << std::endl;

            for (string x_name : id_out_edges[id]) {
                col_index = solver->getColIndex(x_name);
                cut.addCoef(col_index, -1);
                std::cout << "adding x of " << original_id << ": -" << x_name << ' ' << std::endl;

            }

        }
        std::cout << std::endl;

        cuts.push_back(cut);
    }

    //criar função de pegar id1 e id2 de sol_x_names
    //se id1 nao existir em map, vai mapear ele para sua posição no graph
    //adiciona o id2 na posicao do id1 no graph como não visited
    //roda bfs
    //o primeiro name é sempre do vertice 0 entao pode começar da posição 0 do graph
    //tudo que tiver como visited é o primeiro componente conexo ligado com o 0, deletar eles? ignorar?
    //encontrar o proximo componente conexo a partir do primeiro ainda nao visitado
    //a partir do visited desse componente, adicionar o corte para esse componente
    //compensa ao inves do visited colocar um numero pro componente? (acho q n... melhor so pra cada rodada ir adicionando)
    //parar de achar novos componentes quanto tudo for visitado

    printf("separation algorithm aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
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

