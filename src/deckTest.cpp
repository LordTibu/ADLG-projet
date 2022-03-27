#include"deckBuilder.h"
using namespace std;

int main(void){
    deckBuilder test;
    test.init();
    while(test.Stay()){
        test.run();
    }
    return 0;
}