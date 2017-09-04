#include <string.h>
#include <iostream>
#include "caminho.h"

using namespace std;

Caminho::Caminho(){

    path.push_back('A');
    peso = 0;

}
string Caminho::getPath(){
    return path;
}
int Caminho::getPeso(){
    return peso;
}
void Caminho::setPath(string path){
    this->path = path;
}
void Caminho::setPeso(int peso){
    this->peso = peso;
}
void Caminho::addPath(char path){ // erro aqui
    this->path.push_back(path);
}
int Caminho::contido(char test){
    for(int i = 0 ; i < path.size() ; i++){
        if(path.at(i) == (char)test){
            return 1;
        }else{
            continue;
        }
    }
    return 0;
}

void Caminho::toDefault(){
    peso = 0;
    int i = 0;
    while(!path.empty()){
        path.erase(i);
    }
    path = "A";
}

void Caminho::addPeso(int i){
    peso += i;
}

void Caminho::printa(){
    cout << "Path: \t" << path << endl;
    cout << "Peso: \t" << peso << endl;
    cout << "______________________" << endl;
}

void Caminho::aplicaPeso(Grafo grafo){


    for(int i = 1; i < this->path.size(); i++){
       int atual = (int)path.at(i-1)-65;
       int prox = (int)path.at(i)-65;
       this->addPeso(grafo.getMatriz()[atual][prox]);
    }

}

