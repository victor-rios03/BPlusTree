#include <iostream>
#include "FuncionesDeGestion.h"
#include "Utilerias.h"
#include "BPlusTree.h"

using namespace std;

int main()
{

    int option;

    BPlusTree<int, 3> bPT;

    enum options {
        INSERT_ELEMENTS = 1, REMOVE_ELEMENTS, SEARCH_ELEMENTS, PRINT_TREE, CLEAR_TREE, DONNUT, EXIT
    };

    do {
        option = startMenu();
        switch (option) {
            case INSERT_ELEMENTS:
                insertElements(bPT);
                break;

            case REMOVE_ELEMENTS:
                removeElements(bPT);
                break;

            case SEARCH_ELEMENTS:
                findElements(bPT);
                break;

            case PRINT_TREE:
                printTree(bPT);
                break;

            case CLEAR_TREE:
                if (bPT.empty()) {
                    cout << "The Tree is alredy empty." << endl;
                }
                clearTree(bPT);
                break;

            case DONNUT:
                system("cls");
                gotoxy(1, 1);
                Donnut();
                break;

            case EXIT:
                system("cls");
                gotoxy(1, 1);
                bPT.clear();
                return 0;
        }
    } while (option != EXIT);

    cout << endl;
}
