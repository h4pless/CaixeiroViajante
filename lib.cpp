#include <iostream>
#include <stdlib.h>
#include "caminho.h"
#include "grafo.h"
#include <vector>
//#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include "lib.h"


using namespace std;


char toChar(int i){
    return (char)i+65;
}

void printaPopulacao(vector<Caminho> populacao){

    for(int i = 0; i < populacao.size(); i++){
        cout << "[" << i << "]\n" <<endl;
        populacao.at(i).printa();
    }
}

void bubbleSort(vector<Caminho> *populacao){

    Caminho aux;

    for(int i = 0; i < populacao->size(); i++){
        for(int j = 1; j < populacao->size(); j++){
            if(populacao->at(j).getPeso() < populacao->at(j-1).getPeso()){
                aux = populacao->at(j);
                populacao->at(j) = populacao->at(j-1);
                populacao->at(j-1) = aux;
            }
        }
    }
}

void crossover(vector<Caminho> *buffer, Grafo grafo){

    vector<Caminho> vetor4;
    Caminho *filho0 = new Caminho();
    Caminho *filho1 = new Caminho();
    Caminho *comp0 = new Caminho();
    Caminho *comp1 = new Caminho();

    filho0->setPath(buffer->at(0).getPath().substr(3, 4));
    filho1->setPath(buffer->at(1).getPath().substr(3, 4));
    cout << endl << "Path do pai 0:\t" << buffer->at(0).getPath() << "Peso do pai0:\t" << buffer->at(0).getPeso() << endl ;
    cout << endl << "Path do pai 1:\t" << buffer->at(1).getPath() << "Peso do pai1:\t" << buffer->at(1).getPeso() << endl ;
    cout << endl << "Path do filho 0:\t" << filho0->getPath() << endl ;
    cout << endl << "Path do filho 1:\t" << filho1->getPath() << endl << endl;

    for(int i = 1; i < buffer->at(0).getPath().size(); i++){
        if(filho0->getPath().find(buffer->at(1).getPath().at(i)) > 9){
            comp0->addPath(buffer->at(1).getPath().at(i));
        }
        if(filho1->getPath().find(buffer->at(0).getPath().at(i)) > 9)
            comp1->addPath(buffer->at(0).getPath().at(i));
    }
    comp0->setPath(comp0->getPath().insert(3, filho0->getPath()));
    comp1->setPath(comp1->getPath().insert(3, filho1->getPath()));

    comp0->aplicaPeso(grafo);
    comp1->aplicaPeso(grafo);

    cout << "cruzado0\tPath: " << comp0->getPath() << "\t Peso: "<<comp0->getPeso() <<endl;
    cout << "cruzado1\tPath: " << comp1->getPath() << "\t Peso: " <<comp1->getPeso() << endl<<endl;


    buffer->pop_back();
    buffer->pop_back();
    buffer->push_back(*comp0);
    buffer->push_back(*comp1);
    /*
    buffer->push_back(*comp0);
    buffer->push_back(*comp1);
    bubbleSort(buffer);
    buffer->pop_back();
    //if(buffer->size() == 51)
        buffer->pop_back();
    */
    printaPopulacao(*buffer);


}

void esvazia(vector<Caminho> *vetor){

    while(vetor->size() > 0){
        vetor->pop_back();
    }
}

vector<Caminho> seleciona(vector<Caminho> populacao){

    vector<Caminho> selecionados;
    vector<Caminho> buffer;
    int rand1, rand2, rand3;
    srand(time(NULL));

    do{
        rand1 = rand() % populacao.size();
        do{
            rand2 = rand() % populacao.size();
        }while(rand2 == rand1);
        do{
            rand3 = rand() % populacao.size();
        }while(rand3 == rand2 || rand3 == rand1);

        cout << "[TORNEIO]" << endl << endl;
        cout << "rand1:\t" << populacao.at(rand1).getPath() << "\t" << populacao.at(rand1).getPeso() << endl;
        cout << "rand2:\t" << populacao.at(rand2).getPath() << "\t" << populacao.at(rand2).getPeso() << endl;
        cout << "rand3:\t" << populacao.at(rand3).getPath() << "\t" << populacao.at(rand3).getPeso() << endl;

        buffer.push_back(populacao.at(rand1));
        buffer.push_back(populacao.at(rand2));
        buffer.push_back(populacao.at(rand3));
        bubbleSort(&buffer);
        selecionados.push_back(buffer.at(0));
        cout << "selecionado:\t" << buffer.at(0).getPath() << "\t" << buffer.at(0).getPeso() << endl << endl << endl;
        esvazia(&buffer);
   }while(selecionados.size() < populacao.size());

    return selecionados;
}

vector<Caminho> popula(Grafo *grafo){

    Caminho buffer;
    vector<Caminho> populacao;
    int rng;
    int atual;

    srand(time(NULL));

    for(int i = 0; populacao.size() < 50 ; i++){

        atual = 0;
        while(buffer.getPath().size() < tam){
            do{
            rng = rand()%tam;
            }while(grafo->getMatriz()[atual][rng] == 0);
            if(!buffer.contido((char)rng+65)){
                buffer.addPath((char)rng+65);
                buffer.addPeso(grafo->getMatriz()[atual][rng]);
                //cout << "Peso\t" << grafo->getMatriz()[atual][rng] << "Path\t" << toChar(rng) << endl;
                atual = rng;
            }
        }
        buffer.addPath('A');
        buffer.addPeso(grafo->getMatriz()[atual][0]);
        //cout << "Peso\t" << grafo->getMatriz()[atual][0] << "Path\t" << toChar(0) << endl;
        if(!contidoPopulacao(populacao, buffer))
            populacao.push_back(buffer);

        buffer.toDefault();

    }
    return populacao;
}

vector<Caminho> cruzamento(vector<Caminho> populacao, Grafo grafo){

    vector<Caminho> buffer;
    vector<Caminho> cruzados;

    for(int i = 0; i < populacao.size(); i += 2){
        buffer.push_back(populacao.at(i));
        buffer.push_back(populacao.at(i+1));
        crossover(&buffer, grafo);
        cruzados.push_back(buffer.at(0));
        cruzados.push_back(buffer.at(1));
        esvazia(&buffer);
    }
    return cruzados;
}

string invertePath(string cromossomo){

    string s_aux;
    char c_aux;
    int rand1, rand2;
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);

    int cromo_2 = (cromossomo.size()-1)/2;
    int cromo = cromossomo.size()-1;

    //srand(localtime());

    do{
        rand1 = rand() % cromo;
    }while(rand1 > cromo_2 || rand1 == 0);
    do{
        rand2 = rand() % cromo;
    }while(rand1 + rand2 >= cromo || rand2 == 0);

    cout << "rand1\t" << rand1 << "\trand2\t" << rand2 << endl;

    s_aux = cromossomo.substr(rand1, rand2);


    for(int i = 0; i < s_aux.size()/2; i++){
        c_aux = s_aux.at(i);
        s_aux.at(i) = s_aux.at(s_aux.size()-i-1);
        s_aux.at(s_aux.size()-i-1) = c_aux;
    }

    cromossomo.replace(rand1, rand2, s_aux);

    return cromossomo;

}

vector<Caminho> muta(vector<Caminho> populacao, int i, Grafo grafo){

    vector<int> rand1;
    Caminho mutado;
    int aux;


    for(aux = i; aux < populacao.size(); aux++){

        mutado.setPath(invertePath(populacao.at(aux).getPath()));
        mutado.aplicaPeso(grafo);
        cout << endl << "rand:\t" << aux << endl << "antes da inversao\t" << populacao.at(aux).getPath() <<"\t" << populacao.at(aux).getPeso() << endl;
        populacao.at(aux) = mutado;


        cout << "depois da inversao\t" << mutado.getPath() << "\t" << mutado.getPeso() << endl << endl;
        mutado.toDefault();

        cout << "x" << endl;
        //aux = populacao.size(); //só pra resetar o aux;
    }

    return populacao;


}

bool contidoRandom(vector<int> vetor, int rand1){

    for(int i = 0; i < vetor.size(); i++){
        if(vetor.at(i) == rand1)
            return true;
    }
    return false;

}

bool contidoPopulacao(vector<Caminho> populacao, Caminho buffer){
    for(int i = 0; i < populacao.size(); i++)
        if(populacao.at(i).getPath() == buffer.getPath())
            return true;
    return false;
}

void copiaPop(vector<Caminho> *pop1, vector<Caminho> *pop2){
    esvazia(pop2);
    for(int i = 0; i < pop1->size(); i++){
        pop2->push_back(pop1->at(i));
    }
    bubbleSort(pop2);
}

