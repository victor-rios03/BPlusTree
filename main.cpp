#include <iostream>
#include "BPlusTree.h"
#include "Utilerias.h"

using namespace std;

int main()
{
    BPlusTree<int, 3> tInt;
    BPlusTree<char, 3> tChar;
    BPlusTree<double, 3> tDouble;
    int ListType = 0;          /**< 0:No hay tipo definido / 1:Enteros / 2:Caracteres / 3:Vectores */
    int menuOption;
    do {
        system("cls");
        cout << "----------------------------------------------------\n"
                "||>- SISTEMA DE PRUEBAS PARA EL USO DE UN ARBOL -<||\n"
                "----------------------------------------------------\n"
                "[01] Seleccionar tipo de arbol                       \n"            /**< Se crea una nueva lista (Se borrara la actual) */
                "[02] Agregar un nuevo elemento en el Arbol           \n"
                "[03] Eliminar un elemento del Arbol                \n"
                "[04] Imprimir el Arbol                 \n"
                "[05] Buscar un valor en el Arbol                    \n"
                "[06] Vaciar el Arbol                                 \n"
                "[07] Conocer si el arbol esta vacio                  \n"
                "[00] Salir del programa                              \n"
                "----------------------------------------------------\n"
                "> Seleccione una opcion: ";
        menuOption = CapturaEntero("");
        switch (menuOption) {
            case 1: {
                system("cls");
                int aux = 1;
                cout << "----------------------------------------------------\n"
                        "||>-              SELECCION DE ARBOL            -<||\n"
                        "----------------------------------------------------" << endl;
                if (ListType != 0) {
                    cout << "> ADVERTENCIA: Al hacer esta operacion, el arbol ac-\n"
                            "  tual desaparecera. Desea continuar? (1:Si|0:No): ";
                    aux = CapturaEntero("");
                    cout << "----------------------------------------------------" << endl;
                }
                if (aux == 1) {
                    cout << "> Seleccione el tipo de elmentos de su cola         \n"
                            "  [1] Enteros                                         \n"
                            "  [2] Caracteres                                      \n"
                            "  [3] Dobles                                        \n"
                            "----------------------------------------------------\n"
                            "> Seleccione una opcion: ";
                    aux = CapturaEntero("");
                    switch (aux) {
                        case 1:
                            cout << "> Arbol de enteros creado con exito." << endl;
                            ListType = 1;
                            tInt.clear();
                            break;
                        case 2:
                            cout << "> Arbol de caracteres creado con exito." << endl;
                            ListType = 2;
                            tChar.clear();
                            break;
                        case 3:
                            cout << "> Arbol de dobles creada con exito." << endl;
                            ListType = 3;
                            tDouble.clear();
                            break;
                        default:
                            cout
                                    << "> Respuesta invalida.\n  Anulando operacion por seguridad . . .\n  Operacion anulada con exito."
                                    << endl;
                    }
                } else if (aux == 0) {
                    cout << "> Operacion anulada con exito." << endl;
                } else {
                    cout
                            << "> Respuesta invalida.\n  Anulando operacion por seguridad . . .\n  Operacion anulada con exito."
                            << endl;
                }
                break;
            }
            case 2:
                system("cls");
                cout << "----------------------------------------------------\n"
                        "||>-         AGREGAR ELEMENTO A LA LISTA        -<||\n"
                        "----------------------------------------------------" << endl;
                cout << "> Ingresa la posicion de la lista en donde quieres \n"
                     << "  agregar el nuevo elemento: ";
                if (ListType == 1) {
                    int i;
                    cout << "> Ingrese el entero que desea ingresar: ";
                    i = CapturaEntero("");
                    tInt.insert(i);
                    cout << "> Elemento ingresado con exito." << endl;
                } else if (ListType == 2) {
                    char c;
                    cout << "> Ingrese el caracter que desea ingresar: ";
                    cin >> c;
                    tChar.insert(c);
                    cout << "> Elemento ingresado con exito." << endl;
                } else if (ListType == 3) {
                    double d;
                    cout << "> Ingrese la matriz que desea ingresar: ";
                    cin >> d;
                    tDouble.insert(d);
                    cout << "> Elemento ingresado con exito." << endl;
                } else {
                    cout << "> Aun no existe una lista." << endl;
                }
                break;
            case 3:
                system("cls");
                cout << "----------------------------------------------------\n"
                        "||>-        ELIMINAR ELEMENTO DEl Arbol       -<||\n"
                        "----------------------------------------------------" << endl;

                cout << "> Ingresa la posicion de la lista que quieras eliminar: ";
                index = CapturaEntero("");
                if (ListType == 1) {
                    int i;
                    cout << "> Ingrese el entero que desea eliminar: ";
                    cin >> i;
                    tInt.remove(i);
                    cout << "> Elemento " << i << " eliminado con exito.";
                } else if (ListType == 2) {
                    char c;
                    cout << "> Ingrese el caracter que desea eliminar: ";
                    cin >> c;
                    tChar.remove(c);
                    cout << "> Elemento " << c << " eliminado con exito.";
                } else if (ListType == 3) {
                    double d;
                    cout << "> Ingrese el real que desea eliminar: ";
                    cin >> d;
                    tDouble.remove(d);
                    cout << "> Elemento " << d << " eliminado con exito.";
                } else {
                    cout << "> Aun no existe un arbol." << endl;
                }
                break;
            case 4:
                system("cls");
                cout << "----------------------------------------------------\n"
                        "||>-            IMPRESION DEL ARBOL            -<||\n"
                        "----------------------------------------------------" << endl;
                if (ListType == 1) {
                    tInt.print();
                } else if (ListType == 2) {
                    tChar.print();
                } else if (ListType == 3) {
                    tDouble.print();
                } else {
                    cout << "> Aun no existe un arbol." << endl;
                }
                cout << endl;
                break;
            case 5:
                system("cls");
                cout << "----------------------------------------------------\n"
                        "||>-         BUSCAR UN VALOR EN EL ARBOL        -<||\n"
                        "----------------------------------------------------" << endl;
                if (ListType == 1) {
                    int i;
                    cout << "> Ingresa el entero que quieras buscar: ";
                    i = CapturaEntero("");
                    if (tInt.find(i)) cout << "> El entero " << i << " esta en el arbol " << endl;
                    else cout << "> El entero " << i << " no se encuentra en el arbol." << endl;
                } else if (ListType == 2) {
                    char c;
                    cout << "> Ingresa el caracter que quieras buscar: ";
                    cin >> c;
                    if (tChar.find(c)) cout << "> El caracter " << c << " esta en el arbol " << endl;
                    else cout << "> El caracter " << c << " no se encuentra en el arbol." << endl;
                } else if (ListType == 3) {
                    double d;
                    cout << "> Ingresa el doble que quieras buscar: ";
                    cin >> d;
                    if (tDouble.find(d)) cout << "> El real " << d << " esta en en arbol" << endl;
                    else cout << "> El real " << d << " no se encuentra en el arbol." << endl;
                } else {
                    cout << "> Aun no existe un arbol." << endl;
                }
                break;
            case 6:
                system("cls");
                cout << "----------------------------------------------------\n"
                        "||>-             VACIADO DEL ARBOL            -<||\n"
                        "----------------------------------------------------" << endl;
                if (ListType == 1) {
                    tInt.clear();
                    cout << "> Arbol de enteros vaciado con exito.";
                } else if (ListType == 2) {
                    tChar.clear();
                    cout << "> Arbol de caracteres vaciado con exito.";
                } else if (ListType == 3) {
                    tDouble.clear();
                    cout << "> Arbol de dobles vaciado con exito.";
                } else {
                    cout << "> Aun no existe un arbol." << endl;
                }
                break;
            case 7:
                system("cls");
                cout << "----------------------------------------------------\n"
                        "||>-                ¿ARBOL VACIO?               -<||\n"
                        "----------------------------------------------------" << endl;
                if (ListType == 1) {
                    if (tInt.empty()) {
                        cout << "> El arbol de enteros esta vacio.";
                    } else {
                        cout << "> El arbol de enteros NO esta vacio.";
                    }
                } else if (ListType == 2) {
                    if (tChar.empty()) {
                        cout << "> El arbol de caracteres esta vacio.";
                    } else {
                        cout << "> El arbol de caracteres NO esta vacio.";
                    }

                } else if (ListType == 3) {
                    if (tDouble.empty()) {
                        cout << "> El arbol de dobles esta vacio.";
                    } else {
                        cout << "> El arbol de dobles NO esta vacia.";
                    }

                } else {
                    cout << "> Aun no existe un arbol." << endl;
                }
                break;
            case 0:
                system("cls");
                cout << "> Saliendo del programa . . ." << endl;
                break;
            default:
                cout << "> Valor ingresado invalido, por favor vuelva a intentarlo." << endl;
        }
        cout << endl;
        system("pause");
    } while (menuOption != 0);
    system("cls");
    cout << "> Gracias por usar el programa, vuelva pronto. :d" << endl;
    system("pause");
    return 0;
}
