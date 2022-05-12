#include "game2D.h"

int main(){
    
    game2D * world;
    world = new game2D();
    world->initgame2D();
    world->updategame2D();
    world->cleangame2D();
   
   
    delete world;
    world = NULL;
    return 0;
}