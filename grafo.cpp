 #include "grafo.h"
 #include <time.h>
 #include <stdlib.h>
 #include <iostream>
 #include "caminho.h"

Grafo::Grafo(){
    for(int i = 0; i<tam; i++){
        this->matriz[i] = &buf[tam * i];
    }
}

int **Grafo::getMatriz(){
    return matriz;
}

void Grafo::setMatriz(int matriz[tam][tam]){
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            this->matriz[i][j] = matriz[i][j];
        }
    }
}

void Grafo::printa(){
    cout << endl;
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            cout << matriz[i][j] << "\t" ;
        }
        cout << endl;
        cout << endl;
    }
    cout << endl;
}



