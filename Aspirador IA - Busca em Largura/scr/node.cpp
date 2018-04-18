#include "node.hpp"

Node::Node(int idNodeGenerated, int idParentGiven, int prevAction, int depth)
{
    Node::idNode = idNodeGenerated;
    Node::idParent = idParentGiven;
    Node::prevAction = prevAction;
    Node::depth = depth;
}

int Node::getIdNode()
{
    return Node::idNode;
}

int Node::getIdParent()
{
    return Node::idParent;
}

int Node::getPrevAction()
{
    return Node::prevAction;
}

int Node::getDepth()
{
    return Node::depth;
}

StateAsp Node::getNodeState()
{
    return Node::nodeState;
}

void Node::setIdNode(int idNode){
    Node::idNode = idNode;
}

void Node::setIdParent(int idParent){
    Node::idParent = idParent;
}
    
void Node::setPrevAction(int prevAction){
    Node::prevAction = prevAction;
}

void Node::setDepth(int depth)
{
    Node::depth = depth;
}

void Node::setNodeState(StateAsp nodeState)
{
    Node::nodeState = nodeState;
}

