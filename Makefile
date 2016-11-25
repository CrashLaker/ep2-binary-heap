
CFLAGS= -g
(ALL): *
	gcc ${CFLAGS} usaFilaDePrioridade.c
	./a.out > output
	sdiff -w 200 output saida
	
