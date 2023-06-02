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

template<typename T, int Order>
void insertElements(BPlusTree<T, Order> &t);

template<typename T, int Order>
void removeElements(BPlusTree<T, Order> &t);

template<typename T, int Order>
void findElements(BPlusTree<T, Order> &t);

template<typename T, int Order>
void printTree(BPlusTree<T, Order> &t);

template<typename T, int Order>
void clearTree(BPlusTree<T, Order> &t);

void Donnut();

void gotoxy2(SHORT x, SHORT y);

#include "FuncionesDeGestion.tpp"

#endif // FUNCIONESDEGESTION_H_INCLUDED
