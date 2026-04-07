#include <stdio.h>
#include <dos.h>

struct pareja {
    int a;
    int b;
};

struct pareja INVISIBLE = {0x20,0x00};
struct pareja NORMAL = {0x06,0x07};
struct pareja GRUESO = {0x04,0x07};

void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 0x00;
	 int86(0x21, &inregs, &outregs);
}

void cursortype(struct pareja modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	inregs.h.ch = modo.a;
	inregs.h.cl = modo.b;
	int86(0x10,&inregs,&outregs);
	return;
}

int main(){

	cursortype(INVISIBLE);

    printf("\nPulsa para aumentar el grosor del cursor\n");
    mi_pausa();

	cursortype(GRUESO);

    printf("\nPulsa para volver al cursor normal\n");
    mi_pausa();

	cursortype(NORMAL);

	return 0;
}
