#include "client.h"

int main(int argc, char **argv) {
    client cl;
    cl.clientInit(argv[1],argv[2]);
    cl.Communication(argv[1]);
    cl.Close();
    return 0; 
}