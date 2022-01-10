//
// Created by notoverflow on 28/12/2021.
//

#include "fonction.h"
#include "iostream"
#include <stdio.h>
#include <random>

using namespace std;

/**
 * create a new table
 * @param n number of lines
 * @param m number of columns
 * @return the table
 */
int **createTable(int n, int m)
{
    int * *p=new int *[n];
    for(int i=0;i<n;i++) p[i]=new int[m];
    return p;
}

/**
 * create a new matrix
 * @param n number of lines
 * @param m number of columns
 * @return the matrix
 */
matrix *createMatrix(int n, int m)
{
    matrix *p=new matrix ;
    p->line=n ;
    p->column=m ;
    p->T= createTable(n, m) ;
    return p;
}

/**
 * initialize all elements of matrix with 0
 * @param J matrix to initialize
 */
void initializeMatrix(matrix & J)
{
    for(int i=0;i<J.line; i++)
        for(int j=0;j<J.column; j++) J.T[i][j]=0 ;
}

/**
 * create a new matrix for games
 * @param n number of lines
 * @param m number of columns
 * @return the matrix
 */
matrix Int_Jeu(int n, int m, int &nbMine) {


    int difficult;

    do {

        cout << "level of difficult in % (0-100)";
        cin >> difficult;
    } while (difficult > 100 or difficult < 0);


    matrix *tableau = createMatrix(n, m);
    initializeMatrix(*tableau);

    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 100);// distribute results between 1 and 6 inclusive.


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {

            if (dist(gen) > difficult) {
                tableau->T[i][j] = 0;
            } else {
                tableau->T[i][j] = 2;
                nbMine++;
            }

        };
    }


    return *tableau;
}

/**
 * create a new matrix with the number of mine around
 * @param tableau the matrif of game
 * @return the matrix MineAround
 */
matrix mineAround(matrix *tableau){

    matrix *mineAround = createMatrix(tableau->line, tableau->column);
    initializeMatrix(*mineAround);

    int column = tableau->column;
    int line = tableau->line;


    //pour les coins
    mineAround->T[0][0] = int((tableau->T[0][1] + tableau->T[1][1] + tableau->T[1][0]) / 2);
    mineAround->T[0][column - 1] = int(
            (tableau->T[0][column - 2] + tableau->T[1][column - 2] + tableau->T[1][column - 1]) / 2);
    mineAround->T[line - 1][0] = int((tableau->T[line - 2][0] + tableau->T[line - 2][1] + tableau->T[line - 1][1]) / 2);

    mineAround->T[line - 1][column - 1] = int(
            (tableau->T[line - 1][column - 2] + tableau->T[line - 2][column - 2] + tableau->T[line - 2][column - 1]) /
            2);

    //pour les  colonne
    for (int col = 1; col < column; ++col) {

        mineAround->T[0][col] = int(
                (tableau->T[0][col - 1] + tableau->T[1][col - 1] + tableau->T[1][col] + tableau->T[1][col + 1] +
                 tableau->T[0][col + 1]) / 2);
        mineAround->T[line - 1][col] = int(
                (tableau->T[line - 1][col - 1] + tableau->T[line - 2][col - 1] + tableau->T[line - 2][col] + tableau->T[line - 2][
                        col + 1] + tableau->T[line - 1][col + 1]) / 2);

    }

    //pour les lignes

    for (int lin = 1; lin <line-1 ; ++lin) {


        mineAround->T[lin][0] = int(
                (tableau->T[lin + 1][0] + tableau->T[lin + 1][1] + tableau->T[lin][1] + tableau->T[lin - 1][1] +
                 tableau->T[lin - 1][0]) / 2);
        mineAround->T[lin][column - 1] = int(
                (tableau->T[lin + 1][column - 1] + tableau->T[lin + 1][column - 2] + tableau->T[lin][column - 2] +
                 tableau->T[lin - 1][
                         column - 2] + tableau->T[lin - 1][column - 1]) / 2);
    }


    for (int c = 1; c < column - 1; ++c) {
        for (int l = 1; l < line - 1; ++l) {

            mineAround->T[l][c] = int((tableau->T[l - 1][c - 1] + tableau->T[l - 1][c] + tableau->T[l - 1][c + 1] +
                                       tableau->T[l + 1][c - 1] + tableau->T[l + 1][c] + tableau->T[l + 1][c + 1] +
                                       tableau->T[l][c - 1] + tableau->T[l][c + 1]) / 2);

        }
    }

    return *mineAround;

}


/**
 * just a printer of matrix
 * @param tableau the matrix
 * @param mineAround matrix mineAround
 */
void printerTable(matrix *tableau, matrix *mineAround) {

    cout << "   ";
    for (int j = 0; j < tableau->column; ++j) {
        printf("%1d ", j );

    }
    cout << "\n";
    for (int i = 0; i < tableau->line; ++i) {
        printf("%2d ", i );
        for (int j = 0; j < tableau->column; ++j) {
            if (tableau->T[i][j] == 1) {
                cout << mineAround->T[i][j] << " ";
            } else if (tableau->T[i][j] == 3 or tableau->T[i][j] == 4) {
                cout << "\u2691 ";
            } else {
                cout << "\u25A0 ";
            }

        }
        cout << "\n";
    }

}

/**
 * a fonction to put/take of a flag
 * @param tableau matrix
 * @param dp 1: take of  \n  0: to put
 * @param i line
 * @param j column
 */
void flagMine(matrix *tableau, bool dp, int i, int j){
    dp?(tableau->T[i][j]==4?tableau->T[i][j]=2:tableau->T[i][j]=0):(tableau->T[i][j]==0?tableau->T[i][j]=3:tableau->T[i][j]=0);
}


/**
 * a function for dig a box
 * @param table the matrix
 * @param mineAround matrix for recurciity
 * @param i line of box
 * @param j column of box
 * @param n number of mine found
 * @return false if a mine, true else
 */
bool dig(matrix *table, matrix *mineAround, int i, int j, int &n) {

    if (table->T[i][j] == 2) {
        return false;

    }else if (i > table->line or j > table->column) {
        cout << "\n this box doesn't exist";
        return true;

    } else if (table->T[i][j] == 3 or table->T[i][j] == 4) {
        cout << "\n can't dig this box, there is a flag";
        return true;

    } else if (table->T[i][j] == 1) {
        cout << "\n can't dig this box, already dig";

    } else if (table->T[i][j] == 0) {
            digRecursive(table, mineAround, i+1, j,n);
        return true;

    }

    return false;

}


/**
 * a function dig recursive
 * @param table table of game
 * @param mineAround matrix of mineAround
 * @param i line
 * @param j column
 * @param n number of mine found
 * @return 0: if the box doesn't exist \n 1: if the box is flag \n 2: if the box is already dig \n 3: true \n 4:false
 */
int digRecursive(matrix *table, matrix *mineAround, int i, int j,int &n) {

    if (i < 0 or j < 0 or i >= table->line or j >= table->column) {
        return 0;
    } else if (table->T[i][j] == 3 or table->T[i][j] == 4) {
        return 1;
    } else if (table->T[i][j] == 1) {
        return 2;
    } else if(table->T[i][j]==0) {
        table->T[i][j]= 1;
        n++;
        if (mineAround->T[i][j] == 0) {


            digRecursive(table, mineAround, i - 1, j - 1, n);
            digRecursive(table, mineAround, i - 1, j, n);
            digRecursive(table, mineAround, i - 1, j + 1, n);
            digRecursive(table, mineAround, i, j + 1, n);
            digRecursive(table, mineAround, i + 1, j + 1, n);
            digRecursive(table, mineAround, i + 1, j, n);
            digRecursive(table, mineAround, i + 1, j - 1, n);
            digRecursive(table, mineAround, i, j - 1, n);
        }


    }


    return 3;
}

void printerTableInit(matrix *tableau){
    cout << "   ";
    for (int j = 0; j < tableau->column; ++j) {
        printf("%1d ", j );

    }
    cout << "\n";
    for (int i = 0; i < tableau->line; ++i) {
        printf("%2d ", i );
        for (int j = 0; j < tableau->column; ++j) {
            cout << tableau->T[i][j] << " ";
        }
        cout << "\n";
    }


}




/**
*0: s’il n’y pas de mine et la case n’est pas encore creusée
*1: s’il n’y pas  de mine et la case a été creusée
*2: s’il y a une mine
*3: s’il n’y pas de mine et un drapeau a été posé
*4: s’il y a une mine et un drapeau a été posé
 **/
