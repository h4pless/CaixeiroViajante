#include <iostream>
#include <stdlib.h>
#include "caminho.h"
#include "grafo.h"
#include <vector>
#include <stdio.h>
#include <sys/time.h>
#define tam 9
#include "lib.h"

using namespace std;

int main(void){

    vector<Caminho> populacao;
    vector<Caminho> populacao2;
    Grafo *grafo = new Grafo();
    int geracao = 1;

    int matriz[9][9] = {
        {0, 2, 4, 5, 7, 5, 3, 6, 4},
        {2, 0, 5, 6, 3, 6, 7, 7, 2},
        {4, 5, 0, 4, 7, 6, 5, 8, 5},
        {5, 6, 4, 0, 3, 3, 3, 7, 2},
        {7, 3, 7, 3, 0, 7, 6, 9, 7},
        {5, 6, 6, 3, 7, 0, 5, 2, 4},
        {3, 7, 5, 3, 6, 5, 0, 3, 7},
        {6, 7, 8, 7, 9, 2, 3, 0 ,3},
        {4, 2, 5, 2, 7, 4, 7, 3, 0}
    };

    grafo->setMatriz(matriz);
    populacao = popula(grafo);
    do{
        copiaPop(&populacao, &populacao2);

        cout << "\n\n######### POPULACAO ORDENADA POR PESO ####################\n\n" << endl;
        bubbleSort(&populacao);
        printaPopulacao(populacao);

        cout << "\n\n%%%%%%%%% POPULACAO APOS SELECAO POR TORNEIO %%%%%%%%%%%%%%%%%%%%%\n\n" << endl;
        populacao = seleciona(populacao);
        printaPopulacao(populacao);

        cout << "\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n" << endl;
        populacao = cruzamento(populacao, *grafo);

        cout << "\n\n!!!!!!!!!!!!!!cruzamento!!!!!!!!!!!!!!!!!!\n\n" << endl;
        bubbleSort(&populacao);
        printaPopulacao(populacao);
        populacao = muta(populacao, 3, *grafo);

        cout << "\n\n***************MUTADO***************\n\n" << endl;
        bubbleSort(&populacao);
        printaPopulacao(populacao);

        if(populacao.at(0).getPeso() > populacao2.at(0).getPeso()){
            copiaPop(&populacao2, &populacao);
        }
        cout << endl << endl << endl;
        //getchar();
        geracao++;
    }while(populacao.at(0).getPeso() > 28 );

    cout << "RESPOSTA:\t" << populacao.at(0).getPath() << "\t" << populacao.at(0).getPeso();
    cout << endl << endl << "GERACAO:\t" << geracao << endl;
    system("PAUSE");

}
