//
// Created by notoverflow on 28/12/2021.
//

#ifndef DEMINEUR__FONCTION_H
#define DEMINEUR__FONCTION_H


struct matrix
{
    int line ;
    int column ;
    int **T;
};

int **createTable(int n, int m);

matrix *createMatrix(int n, int m);

void initializeMatrix(matrix &J);

matrix Int_Jeu(int n, int m, int &nbMine);

void printerTable(matrix *tableau, matrix *mineAround);

matrix mineAround(matrix *tableau);

void flagMine(matrix *tableau, bool dp, int i, int j);

bool dig(matrix *table, matrix *mineAround, int i, int j, int &n);

int digRecursive(matrix *table, matrix *mineAround, int i, int j,int &n);

void printerTableInit(matrix *tableau);



#endif //DEMINEUR__FONCTION_H
