#include "stateasp.hpp"

StateAsp::StateAsp()
{
    int robotPosition;
    std::srand(std::time(NULL));
    
    StateAsp::a = std::rand() % 2;
    StateAsp::b = std::rand() % 2;
    robotPosition = std::rand() % 2;
    if(!robotPosition) StateAsp::robotPosition = 'A';
    else if(robotPosition) StateAsp::robotPosition = 'B';
}

StateAsp::StateAsp(int aGiven, int bGiven, char robotPositionGiven)
{
    std::srand(std::time(NULL));
    
    StateAsp::a = aGiven;
    StateAsp::b = bGiven;
    if(robotPositionGiven != 'A' && robotPositionGiven != 'B')
    {
        StateAsp::robotPosition = 'A';
    }
    else
    {
        StateAsp::robotPosition = robotPositionGiven;
    }
    

}

void StateAsp::clean(void)
{
    if (StateAsp::robotPosition == 'A')
    {
        StateAsp::a = 0;
    } else
    {
        StateAsp::b = 0;
    }
}

void StateAsp::moveLeft(void)
{
    if (StateAsp::robotPosition == 'B')
    {
        StateAsp::robotPosition = 'A';
    }
    //não preciso fazer para estar em A, pois é loop
}

void StateAsp::moveRight(void)
{
    if (StateAsp::robotPosition == 'A')
    {
        StateAsp::robotPosition = 'B';
    }
    //não preciso fazer para estar em B, pois é loop
}

char StateAsp::getPosition()
{
    return StateAsp::robotPosition;
}

std::vector<int> StateAsp::getDirt()
{
    std::vector<int> dirt;
    dirt.push_back(StateAsp::a);  
    dirt.push_back(StateAsp::b);
    return dirt;
}

void StateAsp::setClean(int a, int b)
{
    StateAsp::a = a;
    StateAsp::b = b;
}

// Esta função foi feita em português para facilitar a verificação do funcionamento do algoritmo
std::string StateAsp::getInfo()
{
    std::string limpo = "L";
    std::string sujo = "S";
    std::string A = "A";
    std::string B = "B";
    std::string retorno = "";

    if(StateAsp::a) retorno += sujo;
    else retorno += limpo;

    if(StateAsp::b) retorno += sujo;
    else retorno += limpo;

    if(StateAsp::robotPosition == 'A') retorno += "A";
    else retorno += "B";
    
    return retorno;
}