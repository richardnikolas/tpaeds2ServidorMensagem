#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"

void criaListaVazia (TLista* lista) {
    lista->primeiro = (TCelulaLista *) malloc (sizeof(TCelulaLista));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    lista->primeiro->ant = NULL;
}

void recebeLote (int* numeroLote, TLista* lista) {
    char aux[700];
    int par;
    TItemMensagem temp;

        scanf("%[^\n]");
        *numeroLote++;
        while(1){
            scanf("%[^\n]", &aux);

            if(strcmp(aux,"Fim"))
                return;

            par = atoi(strtok(aux,";"));
            temp.ordem = atoi(strtok(NULL,";"));
            temp.mensagem[500] = (char*)strtok(NULL,"\n");

            TListaMenor novaMensagem;

            novaMensagem.par = par;
            novaMensagem.primeiro->item.ordem = temp.ordem;
            strcpy(novaMensagem.primeiro->item.mensagem,temp.mensagem);

            encontraCelula(novaMensagem, lista);
			ordenaConversa(novaMensagem, lista);
        }
}

void encontraCelula (TListaMenor conversa, TLista* lista) {
    ApontadorL aux = lista->primeiro;
    TListaMenor temp;

    while (aux->chat.par != conversa.par && aux->prox != NULL)
        aux = aux->prox;
    
    if(aux->chat.par == conversa.par){
        temp = aux->chat.primeiro;

        while(temp->item.ordem < conversa.celula.item.ordem && temp->prox != NULL){
            temp = temp->prox;
        }

		if(temp->item.ordem > conversa.celula.item.ordem){
			insereAntes(conversa.item, temp->celula->prox, *lista);
		}

        else if(conversa.primeiro->item.ordem > temp->ultimo->item.ordem){
            temp->ultimo->prox = conversa;
            conversa.celula.prox = NULL;
            temp->ultimo = conversa;
        }
		
    } 
	else {
        TListaMenor novoPar;
        novoPar.par = conversa.par;
        novoPar.primeiro->item.ordem = conversa.celula.item.ordem;
        strcpy(novoPar.primeiro->item.mensagem,conversa.celula.item.mensagem);
        novoPar.ultimo->prox = NULL;
		lista->ultimo = novoPar;
    }
}

void insereAntes (TItemMensagem celula, ApontadorM p, TLista* lista) {
    ApontadorM novo = (TConversa*) malloc (sizeof(TConversa));

    novo->item = celula;
    novo->ant = p->ant;
    novo->prox = p->ant->prox;
    p->ant->prox = novo;
    p->ant = novo;
	free(novo);
}

void insereDepois (TItemMensagem celula, ApontadorM p, TLista* lista) {
    ApontadorM novo = (TConversa*) malloc (sizeof(TConversa));

    novo->item = celula;
    novo->ant = p;
    novo->prox = p->prox;
    p->prox->ant = novo;
    p->prox = novo;
	free(novo);
}

void ordenaConversa (TConversa* celula, TLista* lista) {
    ApontadorM aux;

    while(celula->prox != NULL){
        aux = celula->prox->prox;
        if(celula->item.ordem > celula->prox->item.ordem){
            celula->prox = aux->prox;
            aux->prox = celula->prox;
            aux->ant = NULL;
            celula->ant = aux;
            aux->prox->ant = celula->prox;
        }

        celula = celula->prox;
    }
}

void liberaLista (TLista* lista, TCelulaLista* celula) {
    ApontadorM atual, anterior;

    atual = celula->primeiro->prox;
	anterior = atual;
    while(atual != NULL){
        atual->prox = celula->primeiro->prox;
        free(atual);
        atual = atual->prox;
    }
}

void printaListas (Tlista* lista, TListaMenor chat) {
	printf("Listas:\n");
	ApontadorL temp = lista->primeiro;

	while(temp != NULL){
		TListaMenor aux;
		aux = lista->primeiro->prox->item;
		while(aux->celula->prox != NULL){
			printf("Par_%d:[(%d, %s) ", aux.par, aux->celula->item.ordem, aux->celula->item.mensagem);
			aux = aux->celula->prox;
		}
		prinft("]\n");
		temp = temp->prox;	
	}
}
