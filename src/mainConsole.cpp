#include "gameBoard.h"
using namespace std;

int main(void){
    unsigned int dim = 5;
    gameBoard GB = gameBoard(dim, dim);
    GB.afficherConsole();
    return 0;
}