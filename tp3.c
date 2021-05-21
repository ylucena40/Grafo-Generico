#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TP.h"

grafo* criavertice(){
	grafo* g = (grafo*) calloc(sizeof(grafo),1);
	return g;
}

void criacabeca(grafo *g[], int n){
	int i=0;
	for(i=0;i<n;i++){
		g[i] = criavertice();
		g[i]->vertice = i;
		g[i]->adj = NULL;
	}
}

void criaverticegrafo(grafo *g, int i){
	if(g->adj == NULL){
		g->adj = criavertice();
		g = g->adj;
		g->vertice = i;
		g->adj = NULL;
	}
	else{
		while(g->adj != NULL)
			g = g->adj;
		g->adj = criavertice();
		g = g->adj;
		g->vertice = i;
		g->adj = NULL;
	}
}

void criagrafonaodirecionado(grafo *g[],int n){
	int i=0,j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i!=j)
				criaverticegrafo(g[i],j);
		}
	}
}

int verificaaresta(grafo *g,int j){
	int i=0;
	while(g->adj!=NULL){
		if(g->vertice == j)
			i = 1;
		g = g->adj;
	}
	if(g->vertice == j)
		i = 1;
	return i;
}

void adicionaarestalista(grafo *g, int j){
	int i=0;
	i = verificaaresta(g,j);
	if(i == 0)
		criaverticegrafo(g,j);
}

void removearesta(grafo *g, int j){
	while(g->adj != NULL){
		if(g->vertice == j)
			g->vertice = -1;
		g = g->adj;
	}
	if(g->vertice == j){
		g->vertice = -1;
	}
}

void limpalista(grafo *g[],int n){
	int i=0;
	grafo *ga;
	for(i=0;i<n;i++){
		while(g[i]->adj != NULL){
			ga = g[i];
			g[i] = g[i]->adj;
			free(ga);
		}
		ga = g[i];
		free(ga);
		ga=NULL;
		g[i]->vertice = -1;
	}
}

void printalistaadj(grafo *g){
	if(g->vertice >=0){
		while(g->adj!=NULL){
			if(g->vertice >= 0)
				printf("%d -> ",g->vertice);
			g = g->adj;
		}
		if(g->vertice >= 0){
			printf("%d->",g->vertice);
		}
		printf("NULL\n");
	}
}

void printlista(grafo *g[], int n){
	int i=0;
	printf("\n");
	for(i=0;i<n;i++){
		printalistaadj(g[i]);
	}
}


//matriz

void gndirecionadom(int n,int **matriz){
	int i=0, j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(j == i)
				matriz[i][j] = 0;
			else
				matriz[i][j] = 1;
		}
	}
}

void gdirecionadom(int n,int **matriz){
	int i=0, j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			matriz[i][j] = 0;
		}
	}
}

void gdirecionadomad(int i,int j,int **matriz){
	matriz[i][j] = 1;
}

void removevm(int v,int n,int **matriz){
	int i=0, j=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(j == v || i == v)
				matriz[i][j] = -1;
		}
	}
}

void removeagdm(int i, int j,int **matriz){
	matriz[i][j] = 0;
}

void removeagndm(int i, int j,int **matriz){
	matriz[i][j] = 0;
	matriz[j][i] = 0;
}

void imprimem(int n, int **matriz){
	int i=0,j=0;
	printf("\n");
	for(i=0;i<n;i++){
		if(matriz[i][i] >= 0){
			for(j=0;j<n;j++){
				if(matriz[i][j] >= 0)
					printf("%d",matriz[i][j]);
			}
			printf("\n");
		}
	}
}

void addarestagndm(int i, int j, int **matriz){
	matriz[i][j] = 1;	
	matriz[j][i] = 1;		
}

void addarestagdm(int i, int j, int **matriz){
	matriz[i][j] = 1;
}

void pesquisaarestam(int i, int j, int **matriz){
	if(matriz[i][j] == 1)
		printf("\nSIM\n");
	else
		printf("\nNAO\n");
}

void pesquisaverticem(int v, int **matriz){
	if(matriz[v][0] >= 0)
		printf("\nSIM\n");
	else
		printf("\nNAO\n");
}

void resetavetores(int visitados[], int vetor[], int c[], int caux[], int n){
	int i=0;
	for(i=0;i<n;i++){
		visitados[i]=0;
		vetor[i] = 0;
		c[i] = -1;
		caux[i] = -1;
	}
}

void caminho(int n, int a, int **matriz, int cont, int vetor[], int visitados[], int c[], int caux[], int final){
	int b=0;
	for(b=0;b<n;b++){
		if(matriz[a][b] == 1 && visitados[b] == 0){
			caux[cont-1] = b;
			visitados[b] = 1;
			vetor[b]=cont;
			if(b == final){
				int d;
				for(d=0;d<n;d++)
					c[d] = caux[d];
			}
			caminho(n,b,matriz,cont+1,vetor,visitados,c,caux,final);
		}
	}
	return;
}

void mostracaminho(int c[]){
	int i=0;
	printf("\nCaminho: ");
	while(c[i]!=-1){
		printf("%d ",c[i]);
		i++;
	}
	printf("\n");
}

void existecaminho(int vetor[],int j){
	if(vetor[j] == 0)
		printf("\nNAO\n");
	else
		printf("\nSIM\n");
}

int main()
{
	int n=0,i=0,j=0, inicio=0, final=0,na=0,escolha=0;
	char texto[20];
	int **matriz;
	
	FILE* arquivo = fopen("arquivo.txt","r");  

	fscanf(arquivo,"%s",texto);
	if(strcmp(texto,"Crie") == 0){
		fscanf(arquivo,"%s %s %s",texto,texto,texto);
		if(strcmp(texto,"direcionado") == 0){
			fscanf(arquivo,"%s %d %s",texto,&n,texto);
			escolha =1;
			
		}
		else if(strcmp(texto,"nao-direcionado") == 0){
			fscanf(arquivo,"%s %d %s",texto,&n,texto);
			escolha =2;
		}
	}
	
	grafo* g[n];
	int visitados[n] , vetor[n], c[n], caux[n];
			
	matriz = (int**) malloc (n*sizeof(int*));
	for ( j = 0; j < n; j++){
		matriz[j] = (int*) malloc (n*sizeof(int));
	}
	
	if(escolha == 1){
		gdirecionadom(n,matriz);
		criacabeca(g,n);
	}
	else{
		gdirecionadom(n,matriz);
		criacabeca(g,n);
		criagrafonaodirecionado(g,n);
	}
		
	while(!feof(arquivo)){
		fscanf(arquivo,"%s",texto);
		if(strcmp(texto,"Adicione") == 0){
			fscanf(arquivo,"%s",texto);
			if(strcmp(texto,"N") == 0){
				fscanf(arquivo,"%s",texto);
				fscanf(arquivo,"%d %s",&na,texto);
				int a1=0;


				for(a1=0;a1<na;a1++){
					fscanf(arquivo,"%d %d",&i,&j);
					if(escolha == 1){
						if(matriz[j][j] != -1){

							addarestagdm(i,j,matriz);
							adicionaarestalista(g[i],j);
						}
					}
					else{
						if(matriz[j][j] != -1){
							addarestagndm(i,j,matriz);
							adicionaarestalista(g[i],j);
							adicionaarestalista(g[j],i);
						}
					}
				}
			}
			else{
				fscanf(arquivo,"%s",texto);
				fscanf(arquivo,"%d %d",&i,&j);
				if(escolha == 1){
					if(matriz[j][j] != -1){
						addarestagdm(i,j,matriz);
						adicionaarestalista(g[i],j);
					}
				}
				else{
					if(matriz[j][j] != -1){
						addarestagndm(i,j,matriz);
						adicionaarestalista(g[i],j);
						adicionaarestalista(g[j],i);
					}
				}
			}
		}
		else if(strcmp(texto,"Existe") == 0){
			fscanf(arquivo,"%s %s",texto,texto);
			if(strcmp(texto,"vertice") == 0){
				fscanf(arquivo,"%d %s",&i,texto);
				pesquisaverticem(i,matriz);
			}
			else if(strcmp(texto,"aresta") == 0){
				fscanf(arquivo,"%d %d %s",&i,&j,texto);
				pesquisaarestam(i,j,matriz);
			}
			else if(strcmp(texto,"caminho") == 0){
				fscanf(arquivo,"%s %d %s %d %s",texto,&inicio,texto,&final,texto);
				resetavetores(visitados,vetor,c,caux,n);
				vetor[inicio]=1;
				visitados[inicio]=1;
				caux[0]=inicio;
				caminho(n,inicio,matriz,2,vetor,visitados,c,caux,final);
				existecaminho(vetor,j);
			}
		}
		else if(strcmp(texto,"Remova") == 0){
			fscanf(arquivo,"%s %s",texto,texto);
			if(strcmp(texto,"vertice") == 0){
				fscanf(arquivo,"%d",&i);
				removevm(i,n,matriz);
				int d=0;
				for(d=0;d<n;d++){
					if(d!=i)
						removearesta(g[d],i);
					removearesta(g[i],d);
				}
			}
			else if(strcmp(texto,"aresta") == 0){
				fscanf(arquivo,"%d %d",&i,&j);
				if(escolha == 1){
					removeagdm(i,j,matriz);
					removearesta(g[i],j);
				}
				else{
					removeagndm(i,j,matriz);
					removearesta(g[i],j);
					removearesta(g[j],i);
				}
			}
		}
		else if(strcmp(texto,"Imprima") == 0){
			fscanf(arquivo,"%s %s",texto,texto);
			if(strcmp(texto,"matriz") == 0)
				imprimem(n,matriz);
			else if(strcmp(texto,"listas") == 0)
				printlista(g,n);
			fscanf(arquivo,"%s %s",texto,texto);
		}
		else if(strcmp(texto,"Mostre") == 0){
			fscanf(arquivo,"%s %s %s %s",texto,texto,texto,texto);
			fscanf(arquivo,"%d %s %d",&inicio,texto,&final);
			fscanf(arquivo,"%s %s",texto,texto);
			resetavetores(visitados,vetor,c,caux,n);
			vetor[inicio]=1;
			visitados[inicio]=1;
			caux[0]=inicio;
			caminho(n,inicio,matriz,2,vetor,visitados,c,caux,final);
			mostracaminho(c);
		}
	}
	
	
	for(i=0;i<n;i++){
		free(matriz[i]);
	}
	
	
	
	free(matriz);
	matriz=NULL;
	
	
	limpalista(g,n);

	return 0;
}
