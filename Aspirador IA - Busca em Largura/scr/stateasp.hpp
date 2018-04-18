#ifndef STATEASP_H
#define STATEASP_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

/* Definição do Problema:
 *  _ _
 * |A|B| -> Ambiente composto por dois quadrados A e B dispostos da forma à esquerda
 *          Temos um aspirador que tem a função de limpar o ambiente. 
 */
class StateAsp
{
public:
    StateAsp();
    //Constrói um estado com informações aleatórias para a,b e posição do robô
    StateAsp(int aGiven, int bGiven, char robotPositionGiven);
    //Constrói um estado recebendo informações (para fazer o objetivo na mão)
    void clean(void);
    void moveRight(void);
    void moveLeft(void);
    char getPosition(void);
    std::vector<int> getDirt(void);
    void setClean(int a, int b);
    std::string getInfo();
    
private:
    //0 = limpo, 1 = sujo
    int a, b;
    //0 = em A, 1 = em B
    char robotPosition;
};

#endif //STATEASP_H