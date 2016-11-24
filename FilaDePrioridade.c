#include "FilaDePrioridade.h"


void fixUp(PFILA f, PONT atual);
void fixDown(PFILA f, PONT atual);


PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxRegistros = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  res->heap = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) {
    res->arranjo[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

void printPONT(PONT p){
	PONT atual = p;
    //printf("[%p:%i;%f;%i] ", atual, atual->id, atual->prioridade, atual->posicao);
    printf("[%i;%f;%i] ", atual, atual->id, atual->prioridade, atual->posicao);
}
bool exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
	printPONT(atual);
  }
  printf("\n\n");
}
int tamanho(PFILA f){
  /* completar */
	
  return f->elementosNoHeap;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  /* completar */
	PONT p = (REGISTRO*) malloc(sizeof(REGISTRO)); 
	int pos = f->elementosNoHeap;
	p->id = id;
	p->prioridade = prioridade;
	p->posicao = pos;
	//printf("Added: "); printPONT(p); printf("\n");
	f->heap[pos] = p;
	fixUp(f, p);
	f->elementosNoHeap += 1;		
	return true;
  return false;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  /* completar */
if (id < 0 || id >= f->maxRegistros)
  return false;

if (id > tamanho(f))
	return false;

if (f->heap[id]->prioridade >= novaPrioridade)
	return false;

f->heap[id]->prioridade = novaPrioridade;

return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  /* completar */
 if (id < 0 || id >= f->maxRegistros)
  return false;

if (id > tamanho(f))
	return false;

if (f->heap[id]->prioridade <= novaPrioridade)
	return false;


f->heap[id]->prioridade = novaPrioridade;

return true;
}

PONT removerElemento(PFILA f){
  /* completar */
PONT rs = NULL;
if (tamanho(f) != 0){
	rs = f->heap[0];
	f->heap[0] = NULL;
	f->elementosNoHeap -= 1;
	
}
  return rs;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  /* completar */
  return false;
}
void fixUp (PFILA f, PONT atual){
	PONT run = atual;
	while(run != NULL){
		//printf("run: "); printPONT(run); printf("\n");
		int pai = (run->posicao-1)/2;
		PONT paip = f->heap[pai];
		if (pai < 0) return;
		if (f->heap[pai]->prioridade < run->prioridade){
			troca(f, pai, run->posicao);
			run = f->heap[pai];
		}else{
			break;
		}
	}
}
void fixDown (PFILA f,
void troca(PFILA f, int from, in to){
	int indexTemp1 = f->heap[from]->posicao;
	PONT pontTemp1 = f->heap[from];

	int indexTemp2 = f->heap[to]->posicao;
	PONT pontTemp2 = to;

	// troca temp1 com temp2
	PONT temp = pontTemp1;

	f->heap[indexTemp1] = f->heap[indexTemp2];
	f->heap[indexTemp2] = temp;

	f->heap[indexTemp1]->posicao = indexTemp2;
	f->heap[indexTemp2]->posicao = indexTemp1;
}
