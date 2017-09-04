#ifndef LIB_H
#define LIB_H

char toChar(int i);
void printaPopulacao(vector<Caminho> populacao);
void bubbleSort(vector<Caminho> *populacao);
void crossover(vector<Caminho> *buffer, Grafo grafo);
void esvazia(vector<Caminho> *vetor);
vector<Caminho> seleciona(vector<Caminho> populacao);
vector<Caminho> popula(Grafo *grafo);
vector<Caminho> cruzamento(vector<Caminho> populacao, Grafo grafo);
vector<Caminho> muta(vector<Caminho> populacao, int i, Grafo grafo);
bool contidoPopulacao(vector<Caminho> populacao, Caminho buffer);
string invertePath(string cromossomo);
bool contidoRandom(vector<int> vetor, int rand1);
void copiaPop(vector<Caminho> *pop1, vector<Caminho> *pop2);


#endif // LIB_H
