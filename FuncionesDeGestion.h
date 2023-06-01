#ifndef FUNCIONESDEGESTION_H_INCLUDED
#define FUNCIONESDEGESTION_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <new>
#include <limits>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include "Utilerias.h"
#include "BPlusTree.h"

#define ESCAPE 27
#define FLECHA_ARRIBA 72
#define FLECHA_ABAJO 80
#define ENTER 13

int startMenu();
void insertElements(BPlusTree<int,3>& t);
void removeElements(BPlusTree<int,3>& t);
void findElements(BPlusTree<int,3>& t);
void printTree(BPlusTree<int,3>& t);
void clearTree(BPlusTree<int,3>& t);
void Donnut();
void gotoxy2(SHORT x, SHORT y);








#endif // FUNCIONESDEGESTION_H_INCLUDED
