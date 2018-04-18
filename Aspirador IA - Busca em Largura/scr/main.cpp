#include "node.hpp"
#include "stateasp.hpp"
#include <vector>
#include <iostream>
#include <string>

#define CLEAN 0
#define DIRT 1
#define A 'A'
#define B 'B'
#define ACTION_CLEAN 0
#define ACTION_RIGHT 1
#define ACTION_LEFT 2
#define ACTION_NULL -1

void testStateAsp(StateAsp testState);
void testNode();
//void testFindState();
void testFindState();
int findState(std::vector<Node> exploredStates, StateAsp state);
int findNode(std::vector<Node> exploredStates, int idToFind);
void nodesInfo(std::vector<Node> edge);

int main(void)
{
    // Inicializando a busca
    int idCurrentNode = 1;                      // ID do nó a ser gerado
    int currentSize = 0;                        // Tamanho da borda antes da expansão
    Node nodeToExpand(0,0,0,0);                 // Nó a ser expandido
    Node newNode(0,0,0,0);                      // Nó gerado na expansão
    Node objNode(0,0,0,0);                      // Nó objetivo
    StateAsp objState(0,0,'A');                 // Estado objetivo
    StateAsp previousState(0,0,'A');            // Estado utilizado no caminho objetio -> raiz
    StateAsp nodeState(0,0,'A');                // Estado do nó gerado na expansão
    StateAsp initialState(DIRT,DIRT,A);         // Estado do nó inicial (raiz)
    // StateAsp initialState;                      // Estado do nó inicial aleatório
    Node initialNode(0,-1,ACTION_NULL,0);       // Nó inicial
    std::vector<Node> edge;                     // Borda
    std::vector<Node> exploredStates;           // Nós já explorados

    // No começo da busca, a borda possui apenas o nó raiz
    initialNode.setNodeState(initialState);
    edge.push_back(initialNode); 
    exploredStates.push_back(initialNode);
    std::cout << "Estado inicial: " << std::endl;
    std::cout << "------> ";
    nodesInfo(edge); 
    std::cout << std::endl;          

    while(true)
        {
        // --- Verificação da borda ---
        // Neste passo eu percorro a borda e verifico se algum do nós dentro dela 
        // contém o estado objetivo. Se a resposta for sim, eu paro o algoritmo, e
        // se a resposta for não, eu expando todos os nós contidos na borda para 
        // para o próximo nível.
        std::cout << "Verificação da borda: " << std::endl;
        for(int i = 0; i < edge.size(); i++)
        {
            if( edge[i].getNodeState().getDirt()[0] == CLEAN &&     // Testa se A está limpo
                edge[i].getNodeState().getDirt()[1] == CLEAN    )   // Testa se B está limpo
            {  
                std::cout << "O estado objetivo " << edge[i].getNodeState().getInfo() << " foi alcançado" << std::endl; 
                std::cout << "O estado objetivo foi encontrado na profundidade " << edge[i].getDepth() << std::endl;

                // --- Caminho percorrido até a solução ---
                // Primeiro, obtenho do nó solução o nó do qual ele foi gerado e o busco nos nós analisados.
                // Após isso, seguindo essa mesma ideia, vou iterando até chegar no nó inicial.
                // Por fim, tendo essa sequência, guardada em um vetor por exemplo, basta ir percorrendo ele
                // e ir printando desde o começo, as informações referentes a id do nó, seu estado e a ação
                // que gera o próximo.
                
                std::vector<Node> solutionPath;
                int idParentFind;
                int prevAction;
                solutionPath.push_back(edge[i]);

                while( solutionPath[ (int) (solutionPath.size() - 1) ].getIdNode() )
                {
                    idParentFind = solutionPath[ (int) (solutionPath.size() - 1)].getIdParent();
                    solutionPath.push_back( exploredStates[ findNode(exploredStates, idParentFind) ] );
                }
                
                std::cout << "\nO caminho até a solução é: " << std::endl;
                
                for (int j = (int) (solutionPath.size() - 1); j >= 0;j-- )
                {
                    std::cout << "\t" << solutionPath[j].getNodeState().getInfo() << std::endl;
                    if(j)
                    {    
                        prevAction = solutionPath[j-1].getPrevAction();
                        if(prevAction == ACTION_CLEAN){
                            std::cout << "\tAção -> Limpar" << std::endl;
                        }
                        else if(prevAction == ACTION_RIGHT){
                            std::cout << "\tAção -> Virar à direita" << std::endl;
                        }
                        else if(prevAction == ACTION_LEFT){
                            std::cout << "\tAção -> Virar à esquerda" << std::endl;
                        }
                    }
                }
                std::cout << std::endl;

                return 0;
            }
        }
        std::cout << "Estado objetivo não encontrado" << std::endl;

        // --- Expansão dos nós da camanda n e geração da camanda n+1 ---
        // Neste caso percorro a borda e expando cada um dos nós desde que o estado do nó 
        // a ser expandido não tenha aparecido até o momento (busca-em-grafo).


        std::cout << "Expansão dos nós da camada " << edge[0].getDepth() << std::endl;
        currentSize = edge.size(); // Esta variável é utilizada porque o size muda ao longo da expansão
        for(int i = 0; i < currentSize; i++)
        {
            
            // Aqui ocorre a expansão do nó. O primeiro nó da fila é selecionado. Em seguida, seu 
            // estado é obtido e modificado através de uma das ações possíveis (limpar, mover para 
            // a direita ou mover para a esquerda) e em seguida um novo nó é configurado e inserido 
            // ao fim da fila. O processo se repete para cada uma das ações possíveis até que o 
            // primeiro nó da fila tenha sido totalmente expandido. Em seguida este nó é removido 
            // e o mesmo se dá para o nó seguinte até que todos os nós da camada tenham sido 
            // expandidos.
            nodeToExpand = edge[0];
            std::cout << "Expandindo o nó " << nodeToExpand.getNodeState().getInfo() << std::endl;
            for(int i = 1; i < 4; i++)
            {
                nodeState = nodeToExpand.getNodeState();
                if(i == 1)
                {
                    nodeState.clean();
                    newNode.setPrevAction(ACTION_CLEAN);
                    std::cout << "Ação de limpar: ";
                }
                else if(i == 2)
                {
                    nodeState.moveRight();
                    newNode.setPrevAction(ACTION_RIGHT);
                    std::cout << "Ação virar para a direita: ";
                }
                else if(i == 3)
                {
                    nodeState.moveLeft();
                    newNode.setPrevAction(ACTION_LEFT);
                    std::cout << "Ação virar para a esquerda: ";
                }
                newNode.setNodeState(nodeState);
                newNode.setIdParent(nodeToExpand.getIdNode());
                newNode.setIdNode(idCurrentNode++);
                newNode.setDepth(nodeToExpand.getDepth() + 1);

                // O novo nó deve ser adicionado à borda somente se não contiver um estado que já 
                // tenha sido analisado
                if(findState(exploredStates,newNode.getNodeState()) == -1){
                    edge.push_back(newNode);
                    std::cout   << "Nó " << newNode.getNodeState().getInfo() 
                                << " acrescentado - ID = " << newNode.getIdNode() << std::endl;
                    exploredStates.push_back(newNode);
                }
                else
                {
                    std::cout << "Nó " << newNode.getNodeState().getInfo() << " já explorado" << std::endl;
                }
            }
            edge.erase(edge.begin());
            std::cout << std::endl;
        }
        std::cout << "Borda após a expansão" << std::endl;
        std::cout << "------> ";
        nodesInfo(edge);
        std::cout << std::endl;
        
        // Caso a borda esteja vazia é porque todas as expansões possíveis foram realizadas e todos os 
        // estados obtidos a partir estas expansões já haviam sido previamente analisados. Assim sendo 
        // não há mais o que fazer ou o que analisar e é possível dizer que o algoritmo não encontrou 
        // a solução.
        if(edge.empty()){
            std::cout << "Não foi possível encontrar a solução" << std::endl;
            return -1;
        }
    }
}

void nodesInfo(std::vector<Node> edge){
    for(int i = 0; i < edge.size(); i++){
        std::cout << edge[i].getNodeState().getInfo() << "   ";
    }
    std::cout << "\n";
}

// Esta função deve verificar se um dado estado state já existe no vector exploredStates
int findState(std::vector<Node> exploredStates, StateAsp state)
{
    for(int i = 0; i < exploredStates.size(); i++)
    {
        if( exploredStates[i].getNodeState().getDirt()[0] == state.getDirt()[0] && 
            exploredStates[i].getNodeState().getDirt()[1] == state.getDirt()[1] &&
            exploredStates[i].getNodeState().getPosition() == state.getPosition())
            {
                return i;            
        }
    }
    return -1;
}

int findNode(std::vector<Node> exploredStates, int idToFind)
{
    for(int i = 0; i < exploredStates.size(); i++)
    {
        if( exploredStates[i].getIdNode() == idToFind )
        {
            return i;     
        }       
    }
    return -1;
}

void testStateAsp(StateAsp testState)
{
    // Teste da classe StateAsp
    std::cout << "-> Estado antes da ação" << std::endl;
    std::cout << "Sujeira A: " << testState.getDirt()[0] << std::endl;
    std::cout << "Sujeira B: " << testState.getDirt()[1] << std::endl;
    std::cout << "Posição: " << testState.getPosition() << std::endl;
    testState.moveRight();
    std::cout << "\n-> Estado depois de virar a direita" << std::endl;
    std::cout << "Sujeira A: " << testState.getDirt()[0] << std::endl;
    std::cout << "Sujeira B: " << testState.getDirt()[1] << std::endl;
    std::cout << "Posição: " << testState.getPosition() << std::endl;
    testState.moveRight();
    std::cout << "\n-> Estado depois de virar a direita" << std::endl;
    std::cout << "Sujeira A: " << testState.getDirt()[0] << std::endl;
    std::cout << "Sujeira B: " << testState.getDirt()[1] << std::endl;
    std::cout << "Posição: " << testState.getPosition() << std::endl;
    testState.moveLeft();
    std::cout << "\n-> Estado depois de virar a esquerda" << std::endl;
    std::cout << "Sujeira A: " << testState.getDirt()[0] << std::endl;
    std::cout << "Sujeira B: " << testState.getDirt()[1] << std::endl;
    std::cout << "Posição: " << testState.getPosition() << std::endl;
    testState.moveLeft();
    std::cout << "\n-> Estado depois de virar a esquerda" << std::endl;
    std::cout << "Sujeira A: " << testState.getDirt()[0] << std::endl;
    std::cout << "Sujeira B: " << testState.getDirt()[1] << std::endl;
    std::cout << "Posição: " << testState.getPosition() << std::endl;
    testState.clean();
    std::cout << "\n-> Estado depois da limpeza" << std::endl;
    std::cout << "Sujeira A: " << testState.getDirt()[0] << std::endl;
    std::cout << "Sujeira B: " << testState.getDirt()[1] << std::endl;
    std::cout << "Posição: " << testState.getPosition() << std::endl;
}

void testNode()
{
    Node testNode(0,-1,ACTION_NULL,0);
    StateAsp testState(DIRT,DIRT,A);
    testNode.setNodeState(testState);
    testStateAsp(testNode.getNodeState());
    std::cout << "\n" << "ID do no = " << testNode.getIdNode() << std::endl;
    std::cout << "ID do no pai = " << testNode.getIdParent() << std::endl;
    std::cout << "Profundidade = " << testNode.getDepth() << std::endl;
}

// void testFindState(){
//     std::vector<Node> exploredStates;
//     StateAsp state1(DIRT,DIRT,A);
//     StateAsp state2(DIRT,CLEAN,A);
//     StateAsp state3(CLEAN,DIRT,A);
//     StateAsp state4(DIRT,DIRT,B);
//     StateAsp state5(DIRT,CLEAN,B);
//     StateAsp state6(CLEAN,CLEAN,B);
//     exploredStates.push_back(state1);
//     exploredStates.push_back(state2);
//     exploredStates.push_back(state3);
//     exploredStates.push_back(state4);
//     std::cout << "Busca de elemento existente = " << findState(exploredStates, state4) << std::endl;
//     std::cout << "Busca de elemento inexistente = " << findState(exploredStates, state5) << std::endl;
// }

void testFindState(){
    std::vector<Node> exploredStates;
    Node node1(0,-1,ACTION_NULL,0);
    Node node2(1,-1,ACTION_NULL,0);
    Node node3(2,-1,ACTION_NULL,0);
    exploredStates.push_back(node1);
    exploredStates.push_back(node2);
    exploredStates.push_back(node3);
    std::cout << "Busca de elemento existente = " << findNode(exploredStates, 1) << std::endl;
    std::cout << "Busca de elemento inexistente = " << findNode(exploredStates, 3) << std::endl;
}


