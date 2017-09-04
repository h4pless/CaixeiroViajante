#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>
#include <vector>
#define tam 9

using namespace std;
class Grafo{

    private:

        int **matriz =(int**)malloc(sizeof(int*) * tam);
        int  *buf = (int*)malloc(sizeof(int) * tam * tam);
    public:

        Grafo();
        int **getMatriz();
        void setMatriz(int matriz[tam][tam]);
        void printa();
};
#endif // GRAFO_H
