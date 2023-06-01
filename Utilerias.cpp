#include <iostream>
#include <limits>

#include "Utilerias.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::numeric_limits;
//********************************************
long double CapturarRealDoble(const char solicitud[])
{
    long double numero;
    do {
        cout << solicitud;
        cin >> numero;

        if (cin.bad()) {
            throw "  P�rdida de datos en el flujo";
        }

        if (cin.fail()) {
            cout << "  Error: El dato introducido no es un n\243mero" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            continue;
        }

        // Verificar si hay caracteres no num�ricos en el b�fer
        string remainingInput;
        getline(cin, remainingInput);

        bool containsNonNumeric = false;
        for (char c : remainingInput) {
            if (!isdigit(c) && c != '-' && c != '.' && c != 'e' && c != 'E') {
                containsNonNumeric = true;
                break;
            }
        }

        if (containsNonNumeric) {
            cout << "  Error: El dato introducido no es un n\243mero" << endl << endl;
            continue;
        }

        break;
    } while (true);

    return numero;
}

int CapturaEntero(const char solicitud[])
{
    int numero;
    long double aux;

    do {
        aux = CapturarRealDoble(solicitud);
        numero = static_cast<int>(aux);
        if (numero != aux) {
            cout << "  Error: Debe ser un n\243mero entero" << endl << endl;
        }
    } while (numero != aux);

    return numero;
}

void borrador()
{
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;
    std::cout <<"                                                                                   " << std::endl;

}

void color(int X)
{
SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X);
}
//GOTOXY para las coordenadas
void gotoxy(unsigned short x, unsigned short y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { static_cast<SHORT>(x - 1), static_cast<SHORT>(y - 1) };
    SetConsoleCursorPosition(handle, coord);
}

//Alterna entre los estados del cursor(Visible/NoVisible/Tama�o)
void CambiaCursor(estadoCursor estado, modoCursor modo)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = modo;
    ConCurInf.bVisible = estado;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}

