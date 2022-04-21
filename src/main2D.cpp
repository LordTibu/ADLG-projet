#include "affichage2D.h"

int main(){
    affichage2D *dd;
    dd = new affichage2D();
    dd->init2D();
    while(dd->isRun){
        dd->menu2D();
    }
    dd->clean2D();
    dd = NULL;
    return 0;
}