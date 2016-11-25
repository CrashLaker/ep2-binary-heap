#include "FilaDePrioridade.h"
#include "math.h"

PONT find(PFILA f, int id);
void troca(PFILA f, int from, int to);
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
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
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

PONT target = find(f, id);
if (target == NULL) return false;
if (target->prioridade >= novaPrioridade)
	return false;

target->prioridade = novaPrioridade;
fixUp(f, target);
fixDown(f, target);

return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  /* completar */
 if (id < 0 || id >= f->maxRegistros)
  return false;

PONT target = find(f, id);
if (target == NULL) return false;
if (target->prioridade <= novaPrioridade)
	return false;


target->prioridade = novaPrioridade;
fixUp(f, target);
fixDown(f, target);

return true;
}

PONT removerElemento(PFILA f){
  /* completar */
PONT rs = NULL;
if (tamanho(f) != 0){
	rs = f->heap[0];
	troca(f, 0, tamanho(f)-1);
	f->elementosNoHeap -= 1;
	PONT temp = f->heap[0];
	fixDown(f, temp);	
}
  return rs;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  /* completar */
if (id < 0 || id >= f->maxRegistros)
  return false;

PONT target = find(f, id);

if (target == NULL)
return false;


*resposta = target->prioridade;
return true;
}

PONT find(PFILA f, int id){
	PONT rs = NULL;
	int i;
	for (i = 0; i < tamanho(f); i++){
		if (f->heap[i]->id == id) {
			rs = f->heap[i];
			break;
		}
	}

	return rs;
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
void fixDown (PFILA f, PONT atual){
	PONT run = atual;
	while(run != NULL){
		if (run->posicao*2+1 < tamanho(f) && run->posicao*2+2 < tamanho(f)){
			PONT esq = f->heap[run->posicao*2+1];
			PONT dir = f->heap[run->posicao*2+2];
			if (run->prioridade > esq->prioridade && run->prioridade > dir->prioridade) break;
			else if (run->prioridade < esq->prioridade && run->prioridade > dir->prioridade){
				int from, to;
				from = run->posicao;
				to = esq->posicao;
				troca(f, from , to);
			}else if (run->prioridade > esq->prioridade && run->prioridade < dir->prioridade){
				int from , to;
				from = run->posicao;
				to = dir->posicao;
				troca(f, from , to);
			}else if (run->prioridade < esq->prioridade && run->prioridade < dir->prioridade){
				int from , to;
				from = run->posicao;
				if (esq->prioridade > dir->prioridade){
					to = esq->posicao;
				}else{
					to = dir->posicao;
				}
				troca(f, from, to);
			}else{
				break;
			}
		}else if (run->posicao*2+1 < tamanho(f)){
			PONT esq = f->heap[run->posicao*2+1];
			if (run->prioridade < esq->prioridade){
				int from, to;
				from = run->posicao;
				to = esq->posicao;
				troca(f, from , to);
			}
			break;
		}else if (run->posicao*2+2 < tamanho(f)){
			PONT dir = f->heap[run->posicao*2+2];
			if (run->prioridade < dir->prioridade){
				int from , to;
				from = run->posicao;
				to = dir->posicao;
				troca(f, from , to);
			}
			break;
		}else{
			break;
		}
	}
}
void troca(PFILA f, int from, int to){
	int indexTemp1 = f->heap[from]->posicao;
	PONT pontTemp1 = f->heap[from];

	int indexTemp2 = f->heap[to]->posicao;
	PONT pontTemp2 = f->heap[to];

	// troca temp1 com temp2
	PONT temp = pontTemp1;

	f->heap[indexTemp1] = f->heap[indexTemp2];
	f->heap[indexTemp2] = temp;

	f->heap[indexTemp1]->posicao = indexTemp1;
	f->heap[indexTemp2]->posicao = indexTemp2;
}
