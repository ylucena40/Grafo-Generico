#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct grafo{
	int vertice;
	struct grafo *adj;
}grafo;

grafo* criavertice();
void criacabeca(grafo *g[], int n);
void criaverticegrafo(grafo *g, int i);
void criagrafonaodirecionado(grafo *g[],int n);
int verificaaresta(grafo *g,int j);
void adicionaarestalista(grafo *g, int j);	
void removearesta(grafo *g, int j);
void limpalista(grafo *g[],int n);
void printalistaadj(grafo *g);
void printlista(grafo *g[], int n);
void gndirecionadom(int n,int **matriz);
void gdirecionadom(int n,int **matriz);
void gdirecionadomad(int i,int j,int **matriz);
void removevm(int v,int n,int **matriz);
void removeagdm(int i, int j,int **matriz);
void removeagndm(int i, int j,int **matriz);
void imprimem(int n, int **matriz);
void addarestagndm(int i, int j, int **matriz);
void addarestagdm(int i, int j, int **matriz);
void pesquisaarestam(int i, int j, int **matriz);
void pesquisaverticem(int v, int **matriz);
void resetavetores(int visitados[], int vetor[], int c[], int caux[], int n);
void caminho(int n, int a, int **matriz, int cont, int vetor[], int visitados[], int c[], int caux[], int final);
void mostracaminho(int c[]);
void existecaminho(int vetor[],int j);

