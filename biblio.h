#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

typedef struct {
    int ordem;
    char mensagem[500];
} TItemMensagem;

typedef struct CelulaConversa* ApontadorM;
typedef struct CelulaLista* ApontadorL;

typedef struct CelulaConversa {
    TItemMensagem item;
    ApontadorM prox, ant;
} TConversa;

typedef struct {
    int par, envios;
    TCelulaConversa celula;
    ApontadorM primeiro, ultimo;
} TListaMenor;

typedef struct CelulaLista{
    TItemLista item;
    ApontadorL prox, ant;
} TCelulaLista;

typedef struct {
    ApontadorL primeiro, ultimo;
} TLista;

void criaListaVazia(TLista*);

void recebeLote(int* , TLista*);

void insereAntes(TItemMensagem, ApontadorM, TLista*);

#endif // BIBLIO_H_INCLUDED
