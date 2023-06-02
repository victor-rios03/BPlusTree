#include "FuncionesDeGestion.h"
#include "BPlusTree.h"
#include "math.h"
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int startMenu()
{

    char key;
    int x = 1;

    CambiaCursor(APAGADO);

    gotoxy(1, 1);

    system("color 0A");
    cout << "                                                                                                          " << endl;
    cout << "                 :::::::::                    ::::::::::: :::::::::  :::::::::: ::::::::::                " << endl;
    cout << "                 :+:    :+:     :+:               :+:     :+:    :+: :+:        :+:                       " << endl;
    cout << "                 +:+    +:+     +:+               +:+     +:+    +:+ +:+        +:+                       " << endl;
    cout << "                 +#++:++#+ +#++:++#++:++          +#+     +#++:++#:  +#++:++#   +#++:++#                  " << endl;
    cout << "                 +#+    +#+     +#+               +#+     +#+    +#+ +#+        +#+                       " << endl;
    cout << "                 #+#    #+#     #+#               #+#     #+#    #+# #+#        #+#                       " << endl;
    cout << "                 #########                        ###     ###    ### ########## ##########                " << endl;
    cout << "                                                                                                          " <<endl;

    cout << " > Insert key  " << endl;
    cout << "  Remove key  " << endl;
    cout << "  Search key  " << endl;
    cout << "  Print tree  " << endl;
    cout << "  Clear tree  " << endl;
    cout << "    DONNUT    " << endl;
    cout << "     Exit     " << endl;

    while(true)
    {
        if(kbhit())
        {
            key = getch();
            if(key == FLECHA_ABAJO && x < 7) x = x + 1;
            if(key == FLECHA_ARRIBA && x > 1) x = x - 1;

            if(x == 1)
            {
               gotoxy(1,10);
               cout << " > Insert key " << endl;
               cout << "  Remove key  " << endl;
            }
            if(x == 2)
            {
                gotoxy(1,10);
                cout << "  Insert key  " << endl;
                cout << " > Remove key " << endl;
                cout << "  Search key  " << endl;
            }
            if(x == 3)
            {
                gotoxy(1,11);
                cout << "  Remove key  " << endl;
                cout << " > Search key " << endl;
                cout << "  Print tree  " << endl;

            }
            if(x == 4)
            {
                gotoxy(1,12);
                cout << "  Search key  " << endl;
                cout << " > Print tree " << endl;
                cout << "  Clear tree  " << endl;
            }
            if(x == 5)
            {
                gotoxy(1,13);
                cout << "  Print tree  " << endl;
                cout << " > Clear tree " << endl;
                cout << "    DONNUT    " << endl;
            }
            if(x == 6)
            {
                gotoxy(1,14);
                cout << "  Clear tree  " << endl;
                cout << "  > DONNUT   " << endl;
                cout << "     Exit    " << endl;
            }
            if(x == 7)
            {
                gotoxy(1,15);
                cout << "    DONNUT    " << endl;
                cout << "  >   Exit    " << endl;
            }
            if(key == ENTER)
            {
                return x;
            }

        }

    }

}

template<typename T, int Order>
void insertElements(BPlusTree<T, Order> & t)
{
   char option;
   CambiaCursor(ENCENDIDO, NORMAL);

    do{
    system("cls");
    gotoxy(1,1);
    T key;

    gotoxy(1,1);
    cout << " Insert key: ";
    cin >> key;
    t.insert(key);

    gotoxy(1,10);
    t.print();

    do{

        gotoxy(1,4);
        cout << " Would you like to add another key? [Y/N]: ";
        string choice;
        cin >> choice;

        if (choice.length() != 1 || (choice[0] != 'Y' && choice[0] != 'y' && choice[0] != 'N' && choice[0] != 'n'))
        {
            cout << "Please select a valid option" << endl;
        }
        else
        {
            option = choice[0];
            break;
        }

    }while (true);

    cout << endl;
    continue;

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    }while(option == 'Y' || option == 'y');

    gotoxy(1,1);
    system("cls");

}

template<typename T, int Order>
void removeElements(BPlusTree<T, Order> & t)
{
    char option;
    CambiaCursor(ENCENDIDO, NORMAL);

    if(t.empty())
    {
        gotoxy(1,20);
        cout << "The tree has no elements" << endl;
        cout << "  ";
        system("Pause");
        system("cls");
        return;
    }

    do{
        T key;
        system("cls");
        gotoxy(1,1);
        cout << " Remove key: ";
        cin >> key;

    if(t.find(key)){
        gotoxy(1,3);
        cout << " Key found for remove " << endl;
        t.remove(key);
        Sleep(1300);

    }else{
        gotoxy(1,3);
        cout << " Key not found for remove" << endl;
        cout << endl;
        Sleep(1300);
        system("cls");
        return;
    }

    do{
        gotoxy(1,3);
        cout << " Would you like to remove another key? [Y/N]: ";
        string choice;
        cin >> choice;

        if (choice.length() != 1 || (choice[0] != 'Y' && choice[0] != 'y' && choice[0] != 'N' && choice[0] != 'n'))
        {
            cout << "Please select a valid option" << endl;
        }
        else
        {
            option = choice[0];
            break;
        }

    }while(true);

    cout << endl;
    continue;

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }while(option == 'Y' || option == 'y');

    gotoxy(1,1);
    system("cls");

}

template<typename T, int Order>
void findElements(BPlusTree<T, Order> & t)
{
    char option;
    CambiaCursor(ENCENDIDO, NORMAL);

    do{
    system("cls");
    gotoxy(1,1);
    T key;

    gotoxy(1,2);
    cout << " Search key: ";
    cin >> key;
    cout << endl;

    if(t.find(key)){
        gotoxy(1,3);
        cout << " Key found! :) " << endl;
        cout << endl;
        Sleep(500);
    }else{
        gotoxy(1,3);
        cout << " Key not founded! :(" << endl;
        cout << endl;
        Sleep(500);
    }

    do{

        cout << " Would you like to remove another key? [Y/N]: ";
        string choice;
        cin >> choice;

        if (choice.length() != 1 || (choice[0] != 'Y' && choice[0] != 'y' && choice[0] != 'N' && choice[0] != 'n'))
        {
            cout << "Please select a valid option" << endl;
        }
        else
        {
            option = choice[0];
            break;
        }

    }while(true);

    cout << endl;
    continue;

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }while(option == 'Y' || option == 'y');

    gotoxy(1,1);
    system("cls");
}

template<typename T, int Order>
void printTree(BPlusTree<T, Order> & t)
{
    CambiaCursor(APAGADO);
    system("cls");
    gotoxy(1,1);
    gotoxy(1,19);

    t.print();
}

template<typename T, int Order>
void clearTree(BPlusTree<T, Order> & t)
{
    if(t.empty()){
        system("cls");
        gotoxy(1,1);
        cout << "*>The Tree has no elements<*" << endl;
        Sleep(600);
        system("pause");
        system("cls");
        return;
    }

    t.clear();
    system("cls");
}

void gotoxy2(SHORT x, SHORT y)
{

    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);


}

void Donnut()
{
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];

    std::cout << "\x1b[2J";

    while(true) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        std::cout << "\x1b[H";
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00014;
            B += 0.00012;
        }
        gotoxy2(0,0);
    }
    return;
}
