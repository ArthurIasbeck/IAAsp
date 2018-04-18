#ifndef NODE_H
#define NODE_H

#include "stateasp.hpp"

class Node
{
public:
    //Para externalizar a geração do número de identificação e facilitar o problema
    Node(int idNodeGenerated, int idParentGiven, int prevAction, int depth);
    int getIdNode();
    int getIdParent();
    int getPrevAction();
    int getDepth();
    void setNodeState(StateAsp nodeState);
    void setIdNode(int idNode);
    void setIdParent(int idParent);
    void setPrevAction(int prevAction);
    void setDepth(int depth);
    StateAsp getNodeState();

private:
    StateAsp nodeState;
    //Para termos controle de que nó é quem, e fazer o esquema de pai e filho 
    int idNode;
    int idParent;
    int depth;
    int prevAction;
}; 

#endif // NODE_H