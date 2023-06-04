#include "estruturas.h"

int comparadorMunicipio(const void *x, const void *y);
int comparadorFastFood(const void *x, const void *y);

void criarArvore(arvore *arvorekd,
                 int (*comparador)(const void *x, const void *y));

struct no *criarNo(void *data);
void inserirNo(arvore *arvorekd, void *data);

void percorrerArvoreM(struct no *raiz);
void percorrerArvoreF(struct no *raiz);

void lerArquivoM(arvore *arvoreMunicipio);
void lerArquivoF(arvore *arvoreFastFood);

void encontrarSucessorMunicipio(struct no *raiz, float lat, float lon);
void encontrarSucessorFastFood(struct no *raiz, float lat, float lon);

void encontrarPredecessorMunicipio(struct no *raiz, float lat, float lon);
void encontrarPredecessorFastFood(struct no *raiz, float lat, float lon);

void liberarNoDaAvore(struct no *raiz);
void liberarArvoreRaiz(arvore *arvorekd);
