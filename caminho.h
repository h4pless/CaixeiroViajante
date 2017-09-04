#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"
#include <string>

using namespace std;

class Caminho{

    private:
        string path;
        int peso;
    public:
        Caminho();
        string getPath();
        int getPeso();
        void setPath(string path);
        void setPeso(int peso);
        void printa();
        void addPath(char path);
        void addPeso(int i);
        int contido(char test);
        void aplicaPeso(Grafo grafo);
        void toDefault();

};

#endif // CAMINHO_H
