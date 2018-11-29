#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"

int main() {
    int k, numeroLote = 0;
    TLista chat;

    criaListaVazia(&chat);
    scanf("%d", &k);
    recebeLote(&numeroLote, &chat);

    return 0;
}
