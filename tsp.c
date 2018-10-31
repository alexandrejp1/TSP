#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

struct matriz {
    int numero_elementos;
    int** elementos;
};

struct nodo {
    int indice;
    int valor;
};

void ler_arquivo(struct matriz*, char*);
int calcular_custo(struct matriz, int*);
void tsp(struct matriz, int*);
void imprimir_caminho(int, int*);

void imprimir_matriz(struct matriz);


int main(int argc, char *argv[]) {
    struct matriz m;

    ler_arquivo(&m, "pcv04.txt");
    imprimir_matriz(m);

    int *solucao_inicial = malloc((m.numero_elementos + 1) * sizeof(int));
    tsp(m, solucao_inicial);
    printf("\nSolucao: ");
    imprimir_caminho(m.numero_elementos + 1, solucao_inicial);

    int custo_solucao_inicial = calcular_custo(m, solucao_inicial);
    printf("Custo: %d\n", custo_solucao_inicial);

    
}

void ler_arquivo(struct matriz* m, char* arquivo) {
    FILE* fp = fopen(arquivo, "r");

    fscanf(fp, "%d\n", &m->numero_elementos);

    m->elementos = malloc(m->numero_elementos * sizeof(int*));

    for(int i = 0; i < m->numero_elementos; i++) {
        m->elementos[i] = malloc(m->numero_elementos * sizeof(int));
        for(int j = 0; j < m->numero_elementos; j++) {
            fscanf(fp, "%d ", &m->elementos[i][j]);
        }
    }


    fclose(fp);
}

//calcular o custo do caminho
int calcular_custo(struct matriz m, int* caminho) {
    int custo = 0;

    for(int i = 0; i < m.numero_elementos; i++) {
        //custo de onde ta pra onde vai
        custo = custo + m.elementos[caminho[i]][caminho[i + 1]];
    }

    return custo;
}


void tsp(struct matriz m, int* caminho) {
    int *inseridos = malloc(m.numero_elementos * sizeof(int));

    for(int i = 0; i < m.numero_elementos; i++) { //iniciando os valores com FALSE (nao foi inserido)
        inseridos[i] = FALSE;
    }

    caminho[0] = 0;
    inseridos[0] = TRUE;

    for(int i = 0; i < m.numero_elementos; i++) {
        int valor_referencia = INT_MAX; //valor alto
        int vizinho_selecionado = 0; 

        for(int j = 0; j < m.numero_elementos; j++) {
           //se não tiver inserido e o valor de referencia que eu já tinha é maior, troca
            if(!inseridos[j] && valor_referencia > m.elementos[i][j]) { 
                //seleciona o vizinho e atualiza o valor de referencia
                vizinho_selecionado = j;
                valor_referencia = m.elementos[i][j];
            }
        }
        //o prox item a ser visitado é o que escolhi anteriormente
        caminho[i + 1] = vizinho_selecionado; 
        //adiciona no vetor de visitados
        inseridos[vizinho_selecionado] = TRUE;
    }
    //retornar a origem
    caminho[m.numero_elementos] = 0;

    free(inseridos);
}


void imprimir_matriz(struct matriz m) {
    printf("MATRIZ LIDA\n");

    for(int i = 0; i < m.numero_elementos; i++) {
        for(int j = 0; j < m.numero_elementos; j++) {
            printf("%d ", m.elementos[i][j]);
        }

        printf("\n");
    }

}


void imprimir_caminho(int n, int* caminho) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%d ", caminho[i]+1);
    }
    printf("\n");
}
