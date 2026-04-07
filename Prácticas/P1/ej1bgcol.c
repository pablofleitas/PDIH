#include <stdio.h>
#include <dos.h>

int mi_getchar(){
   union REGS inregs, outregs;
   int caracter;

   inregs.h.ah = 0x08;
   int86(0x21, &inregs, &outregs);

   caracter = outregs.h.al;
   return caracter;
}

void put_char(char c){
	union REGS inregs, outregs;
	inregs.h.ah = 2;
	inregs.h.dl = c;    
	int86(0x21, &inregs, &outregs);
}

int leer_numero() {
    int num = 0;
    char c;

    while(1) {
        c = mi_getchar();
		put_char(c);

        if(c == 13)  // ENTER
            break;

        if(c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        }
    }

    return num;
}

unsigned char leer_color(){
	int c = leer_numero();

	if(c >= 0 && c <= 15) {
		return (unsigned char)c;
	} else {
		printf("Color inválido. Usando color por defecto (BLANCO).\n");
		return 7; // color blanco por defecto
	}
}

void escribir_char_con_color(char c, unsigned char color){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;    
	inregs.h.bl = color << 4 | 0;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
	return;
}
void avanzar(){
	union REGS inregs, outregs;
	unsigned char fila, col;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0;
    int86(0x10, &inregs, &outregs);

	fila = outregs.h.dh;
    col  = outregs.h.dl;

    col++;

    inregs.h.ah = 0x02;
    inregs.h.dh = fila;
    inregs.h.dl = col;
    int86(0x10, &inregs, &outregs);
}

int main(){
	unsigned char color;
	char c;
	int num;

	printf("Indique el color del fondo con el que desea escribir (0-15): ");
	color = leer_color();

	printf("\n");

	printf("Puede comenzar a escribir (presione ENTER para finalizar)...\n");
	while(1) {
		c = mi_getchar();

		if(c == 13)  // ENTER
			break;

		escribir_char_con_color(c, color);
		avanzar();
	}

	return 0;
}