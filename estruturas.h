typedef struct municipio {
  int codigoIBGE;
  char nome[50];
  int codigoUf;
  int capital;
  float latitude;
  float longitude;
  int siafi;
  int ddd;
  char fusoHorario[50];
  char coordenada[15];
} municipio;

typedef struct fastFood {
  char address[50];
  char category[50];
  char city[50];
  char country[50];
  char name[50];
  int postalCode;
  char province[50];
  char website[100];
  float latitude;
  float longitude;
  char coordenada[15];
} fastFood;

typedef struct no {
  void *data;
  struct no *esquerda;
  struct no *direita;
  struct no *pai;
} no;

typedef struct arvore {
  no *raiz;
  int (*comparador)(const void *x, const void *y);
} arvore;
