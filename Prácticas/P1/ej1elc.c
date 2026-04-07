#include <stdio.h>
#include <dos.h>

unsigned char ctexto=1;

int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

void escribir_char_con_color(char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = 0 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
	return;
}

int main(){
    int tmp;
    printf("\nIndique el caracter a imprimir: ");
    tmp = mi_getchar();

	printf("\nIndique el color del texto (0-15): ");
    ctexto = mi_getchar() - '0'; // Lee el color del texto
    printf("\nImprimiendo caracter con color... \n");
	escribir_char_con_color((char)tmp); 

	return 0;
}