#ifndef UTILERIAS_H_INCLUDED
#define UTILERIAS_H_INCLUDED

#include <windows.h>

#define FLECHA_ARRIBA 72
#define FLECHA_IZQ 75
#define FLECHA_DER 77
#define FLECHA_ABAJO 80
#define ENTER 13
#define ESCAPE 27

int CapturaEntero(const char solicitud[]);
long double CapturarRealDoble(const char solicitud[]);

void borrador();

void color(int X);
// Estados del cursor
enum estadoCursor{APAGADO, ENCENDIDO};
// Modos del cursor
enum modoCursor{MINI = 5, NORMAL = 20, SOLIDO = 80};

//GOTOXY para las coordenadas
void gotoxy(unsigned short x, unsigned short y);
void CambiaCursor(estadoCursor estado, modoCursor modo = NORMAL);

#endif // UTILERIAS_H_INCLUDED
