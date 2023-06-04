#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparadorMunicipio(const void *x, const void *y) {

  municipio dataRaiz = (*(municipio *)x);
  municipio dataAdd = (*(municipio *)y);
  // Latitude
  if (strcmp(dataRaiz.coordenada, dataAdd.coordenada)) {
    if (!(strcmp(dataAdd.coordenada, "LATITUDE"))) {
      return dataRaiz.latitude - dataAdd.latitude;
    } else { // Longitude
      return dataRaiz.longitude - dataAdd.longitude;
    }
  } else {
    if (!(strcmp(dataAdd.coordenada, "LATITUDE"))) {
      strcpy(dataAdd.coordenada, "LONGITUDE");
      return dataRaiz.longitude - dataAdd.longitude;
    } else {
      strcpy(dataAdd.coordenada, "LATITUDE");
      return dataRaiz.latitude - dataAdd.latitude;
    }
  }
  return 0;
}

int comparadorFastFood(const void *x, const void *y) {

  fastFood dataRaiz = (*(fastFood *)x);
  fastFood dataAdd = (*(fastFood *)y);

  // Latitude
  if (strcmp(dataRaiz.coordenada, dataAdd.coordenada)) {
    if (!(strcmp(dataAdd.coordenada, "LATITUDE"))) {
      return dataRaiz.latitude - dataAdd.latitude;
    } else { // Longitude
      return dataRaiz.longitude - dataAdd.longitude;
    }
  } else {
    if (!(strcmp(dataAdd.coordenada, "LATITUDE"))) {
      strcpy(dataAdd.coordenada, "LONGITUDE");
      return dataRaiz.longitude - dataAdd.longitude;
    } else {
      strcpy(dataAdd.coordenada, "LATITUDE");
      return dataRaiz.latitude - dataAdd.latitude;
    }
  }
  return 0;
}

void criarArvore(arvore *arvorekd,
                 int (*comparador)(const void *x, const void *y)) {
  arvorekd->raiz = NULL;
  arvorekd->comparador = comparador;
}

struct no *criarNo(void *data) {
  no *novoNo = (no *)malloc(sizeof(no));
  novoNo->data = data;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  return novoNo;
}

void inserirNo(arvore *arvorekd, void *data) {
  no **enderecoNo = &(arvorekd->raiz);
  no *raizArvore, *p, *q;
  raizArvore = *enderecoNo;

  q = raizArvore;
  while (q) {
    p = q;
    q = q->direita;
    if (arvorekd->comparador(raizArvore->data, data)) {
      enderecoNo = &(raizArvore->direita);
      raizArvore = *enderecoNo;
    } else {
      enderecoNo = &(raizArvore->esquerda);
      raizArvore = *enderecoNo;
    }
    q = raizArvore;
  }

  if (*(enderecoNo) == NULL) {
    *(enderecoNo) = criarNo(data);
  }
  return;
}

void percorrerArvoreM(struct no *raiz) {
  if (raiz) {

    percorrerArvoreM(raiz->esquerda);
    municipio *m = (municipio *)raiz->data;
    printf("%s\n", m->nome);
    percorrerArvoreM(raiz->direita);
  }
  return;
}

void percorrerArvoreF(struct no *raiz) {
  if (raiz) {
    percorrerArvoreM(raiz->esquerda);
    fastFood *f = (fastFood *)raiz->data;
    printf("%s\n", f->nome);
    percorrerArvoreM(raiz->direita);
  }
  return;
}

void lerArquivoM(arvore *arvoreMunicipio) {
  FILE *arquivoM;

  arquivoM = fopen("municipios.txt", "r");

  if (!arquivoM) {
    printf("Erro ao abrir o arquivo de municípios\n");
  }
  int x = 9;
  int cont = 0;
  while (x == 9) {
    municipio *m = malloc(sizeof(municipio));
    x = fscanf(arquivoM, "%d %[^\t] %f %f %d %d %d %d %[^\n]\n", &m->codigoIBGE,
               m->nome, &m->latitude, &m->longitude, &m->capital, &m->codigoUf,
               &m->siafi, &m->ddd, m->fusoHorario);
    if (cont % 2 == 0) {
      // printf("%s\n", "oi");
      strcpy(m->coordenada, "LATITUDE");
      inserirNo(arvoreMunicipio, m);
    } else {
      // printf("%s\n", "oi2");
      strcpy(m->coordenada, "LONGITUDE");
      inserirNo(arvoreMunicipio, m);
    }
    cont++;
  }
}

void lerArquivoF(arvore *arvoreFastFood) {
  FILE *arquivoF;

  arquivoF = fopen("restaurantes.txt", "r");

  if (!arquivoF) {
    printf("Erro ao abrir o arquivo de restaurantes\n");
  }
  int x = 9;
  int cont = 0;
  while (x == 9) {
    fastFood *f = malloc(sizeof(fastFood));
    x = fscanf(arquivoF, "%[^\n] %[^\t] %[^\t] %[^\t] %f %f %[^\t] %d %[^\t]",
               f->address, f->category, f->city, f->country, &f->latitude,
               &f->longitude, f->name, &f->postalCode, f->province);
    if (cont % 2 == 0) {
      // printf("%s\n", "oi");
      strcpy(f->coordenada, "LATITUDE");
      // printf("%s\n", f->address);
      inserirNo(arvoreFastFood, f);
    } else {
      // printf("%s\n", "oi2");
      strcpy(f->coordenada, "LONGITUDE");
      inserirNo(arvoreFastFood, f);
    }
    cont++;
  }
}

void encontrarSucessorMunicipio(struct no *raiz, float lat, float lon) {
  struct no *atual = raiz;
  struct no *sucessor = NULL;

  while (atual != NULL) {
    struct municipio *municipio = (struct municipio *)atual->data;
    if (lat < municipio->latitude ||
        (lat == municipio->latitude && lon < municipio->longitude)) {
      sucessor = atual;
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }

  struct municipio *municipioSuc = (struct municipio *)sucessor->data;
  printf("////////////////////////////////////////////\n");
  printf("Código IBGE: %d\n", municipioSuc->codigoIBGE);
  printf("Nome: %s\n", municipioSuc->nome);
  printf("Código UF: %d\n", municipioSuc->codigoUf);
  printf("Capital: %d\n", municipioSuc->capital);
  printf("Latitude: %f\n", municipioSuc->latitude);
  printf("Longitude: %f\n", municipioSuc->longitude);
  printf("Siafi: %d\n", municipioSuc->siafi);
  printf("DDD: %d\n", municipioSuc->ddd);
  printf("Fuso Horário: %s\n", municipioSuc->fusoHorario);
  printf("Coordenada: %s\n", municipioSuc->coordenada);
  printf("////////////////////////////////////////////\n");
  return;
}

void encontrarSucessorFastFood(struct no *raiz, float lat, float lon) {
  struct no *atual = raiz;
  struct no *sucessor = NULL;

  while (atual != NULL) {
    struct fastFood *fastFood = (struct fastFood *)atual->data;
    if (lat < fastFood->latitude ||
        (lat == fastFood->latitude && lon < fastFood->longitude)) {
      sucessor = atual;
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }

  struct fastFood *fastFoodSuc = (struct fastFood *)sucessor->data;
  printf("////////////////////////////////////////////\n");
  printf("Endereço: %s\n", fastFoodSuc->address);
  printf("Categoria: %s\n", fastFoodSuc->category);
  printf("Cidade: %s\n", fastFoodSuc->city);
  printf("País: %s\n", fastFoodSuc->country);
  printf("Nome: %s\n", fastFoodSuc->name);
  printf("Código Postal: %d\n", fastFoodSuc->postalCode);
  printf("Província: %s\n", fastFoodSuc->province);
  printf("Website: %s\n", fastFoodSuc->website);
  printf("Latitude: %f\n", fastFoodSuc->latitude);
  printf("Longitude: %f\n", fastFoodSuc->longitude);
  printf("Nome: %s\n", fastFoodSuc->nome);
  printf("Coordenada: %s\n", fastFoodSuc->coordenada);
  printf("////////////////////////////////////////////\n");
  return;
}

void encontrarPredecessorMunicipio(struct no *raiz, float lat, float lon) {

  struct no *atual = raiz;
  struct no *predecessor = NULL;

  while (atual != NULL) {
    struct municipio *municipio = (struct municipio *)atual->data;
    if (municipio->latitude < lat ||
        (municipio->latitude == lat && municipio->longitude < lon)) {
      predecessor = atual;
      atual = atual->direita;
    } else {
      atual = atual->esquerda;
    }
  }

  if (predecessor == NULL) {
    printf("Sem predecessor\n");
    return; // Não há predecessor
  }

  struct municipio *municipioPred = (struct municipio *)predecessor->data;
  printf("////////////////////////////////////////////\n");
  printf("Código IBGE: %d\n", municipioPred->codigoIBGE);
  printf("Nome: %s\n", municipioPred->nome);
  printf("Código UF: %d\n", municipioPred->codigoUf);
  printf("Capital: %d\n", municipioPred->capital);
  printf("Latitude: %f\n", municipioPred->latitude);
  printf("Longitude: %f\n", municipioPred->longitude);
  printf("Siafi: %d\n", municipioPred->siafi);
  printf("DDD: %d\n", municipioPred->ddd);
  printf("Fuso Horário: %s\n", municipioPred->fusoHorario);
  printf("Coordenada: %s\n", municipioPred->coordenada);
  printf("////////////////////////////////////////////\n");
  return;
}
void encontrarPredecessorFastFood(struct no *raiz, float lat, float lon) {

  struct no *atual = raiz;
  struct no *predecessor = NULL;

  while (atual != NULL) {
    struct fastFood *fastFood = (struct fastFood *)atual->data;
    if (fastFood->latitude < lat ||
        (fastFood->latitude == lat && fastFood->longitude < lon)) {
      predecessor = atual;
      atual = atual->direita;
    } else {
      atual = atual->esquerda;
    }
  }

  if (predecessor == NULL) {
    printf("Sem predecessor\n");
    return; // Não há predecessor
  }

  struct fastFood *fastFoodPred = (struct fastFood *)predecessor->data;
  printf("////////////////////////////////////////////\n");
  printf("Endereço: %s\n", fastFoodPred->address);
  printf("Categoria: %s\n", fastFoodPred->category);
  printf("Cidade: %s\n", fastFoodPred->city);
  printf("País: %s\n", fastFoodPred->country);
  printf("Nome: %s\n", fastFoodPred->name);
  printf("Código Postal: %d\n", fastFoodPred->postalCode);
  printf("Província: %s\n", fastFoodPred->province);
  printf("Website: %s\n", fastFoodPred->website);
  printf("Latitude: %f\n", fastFoodPred->latitude);
  printf("Longitude: %f\n", fastFoodPred->longitude);
  printf("Nome: %s\n", fastFoodPred->nome);
  printf("Coordenada: %s\n", fastFoodPred->coordenada);
  printf("////////////////////////////////////////////\n");
  return;
}

void liberarNoDaAvore(struct no *raiz) {
  if (raiz) {
    liberarNoDaAvore(raiz->esquerda);
    liberarNoDaAvore(raiz->direita);
    free(raiz->data);
    free(raiz);
  }
}

void liberarArvoreRaiz(arvore *arvorekd) {
  liberarNoDaAvore(arvorekd->raiz);
  arvorekd->raiz = NULL;
}

int main(void) {
  int op;
  arvore arvorekd, arvoreF;
  criarArvore(&arvorekd, &comparadorMunicipio);
  criarArvore(&arvoreF, &comparadorFastFood);
  lerArquivoM(&arvorekd);
  lerArquivoF(&arvoreF);
  do {
    printf("Escolha uma opção\n");
    printf("Municípios\n");
    printf("1 - Buscar predecessor\n2 - Buscar sucessor\n");
    printf("Restaurantes\n");
    printf("3 - Buscar predecessor\n4 - Buscar sucessor\n");
    printf("5 - Sair\n");
    scanf("%d", &op);

  if (op == 1) {
      float lat, lon;
      printf("Informe a latitude e a longitude\n");
      scanf("%f %f", &lat, &lon);
      encontrarPredecessorMunicipio(arvorekd.raiz, lat, lon);
    } else if (op == 2) {
      float lat, lon;
      printf("Informe a latitude e a longitude\n");
      scanf("%f %f", &lat, &lon);
      encontrarSucessorMunicipio(arvorekd.raiz, lat, lon);
    } else if (op == 3) {
      float lat, lon;
      printf("Informe a latitude e a longitude\n");
      scanf("%f %f", &lat, &lon);
      encontrarPredecessorFastFood(arvorekd.raiz, lat, lon);
    } else if (op == 4) {
      float lat, lon;
      printf("Informe a latitude e a longitude\n");
      scanf("%f %f", &lat, &lon);
      encontrarSucessorFastFood(arvorekd.raiz, lat, lon);
    }
  } while (op != 5);

  liberarNoDaAvore(arvorekd.raiz);
  liberarNoDaAvore(arvoreF.raiz);
  liberarArvoreRaiz(&arvorekd);
  liberarArvoreRaiz(&arvoreF);

  return 0;
}
