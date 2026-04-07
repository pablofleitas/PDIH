#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

void pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}

int mi_getchar(){
   union REGS inregs, outregs;
   int caracter;

   inregs.h.ah = 1;
   int86(0x21, &inregs, &outregs);

   caracter = outregs.h.al;
   return caracter;
}

int leer_numero() {
    int num = 0;
    char c;

    while(1) {
        c = mi_getchar();

        if(c == 13)  // ENTER
            break;

        if(c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        }
    }

    return num;
}

void modovideo(BYTE modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

void pixel(int x, int y, BYTE C){
   union REGS inregs, outregs;
   inregs.x.cx = x;
   inregs.x.dx = y;
   inregs.h.al = C;
   inregs.h.ah = 0x0C;
   int86(0x10, &inregs, &outregs);
}

/*#################################################################################*/
int main(){
   int i;
   int valx , valy ;
   int color;

   printf("\nIndique el valor de la coordenada x: ");
   valx = leer_numero();

   printf("\nIndique el valor de la coordenada y: ");
   valy = leer_numero();

   printf("\nIndique el color (0-15): ");
   color = leer_numero();

   modovideo(MODOGRAFICO); //gráfico

   pixel(valx, valy, (BYTE)color); //poner un pixel en la coordenada (valx,valy) de color "color"

   pausa();
   modovideo(MODOTEXTO); //texto

	return 0;
}