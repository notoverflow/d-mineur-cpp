#include <iostream>
#include "fonction.h"

using namespace std;

int main() {
/**

    matrix game = Int_Jeu(10, 10);
    matrix around = mineAround(&game);
    printerTable(&game,&around);

    cout << "ligne";

    int n = 0;
    cin>>  n;

    int m = 0;
    cin >> m;

    cout << game.T[n][m]<<"\n";
    int nbr = 10;

    dig(&game, &around, n, m, nbr);

    printerTable(&game,&around);
**/
//
//
//    cout << "welcome ! \n \n \n";
//
//    int nbLine;
//    int nbColumn;
//    int nbMine=0;
//    int mineFound = 0;
//
//    char action = 'd';
//    int line=0;
//    int column = 0;
//    bool mine;
//
//
//    cout << "number of lines ? ";
//    cin >> nbLine;
//    cout << "number of column ? ";
//    cin >> nbColumn;
//
//    matrix game = Int_Jeu(nbLine, nbColumn, nbMine);
//
//
//    matrix around = mineAround(&game);
//
//    while (mineFound != nbMine) {
//
//
//        printerTable(&game, &around);
//
//        cout << "what do you want make : \n f : put a flag \n t : take off a flaf \n d : dig a box \n";
//
//        do {
//
//            cin >> action;
//        } while (action != 'f' or action != 't' or action != 'd');
//        cout << "\n line ? \n";
//        cin >> line;
//        cout << "\n column ? \n";
//        cin >> column;
//        cout << "\n";
//
//
//        if (action == 'f') {
//            flagMine(&game, 0, line, column);
//        } else if (action == 't') {
//            flagMine(&game, 1, line, column);
//        } else if (action == 'd') {
//            mine = dig(&game, &around, line, column, mineFound);
//            if (!mine) {
//                cout << "G A M E    O V E R ";
//                return 0;
//            }
//        }
//
//    }
//
//


    cout << "welcome ! \n \n \n";

    int nbLine;
    int nbColumn;
    int nbMine=0;
    int mineFound = 0;

    char action = 'c';
    int line=0;
    int column = 0;
    bool mine;


    cout << "number of lines ? ";
    cin >> nbLine;
    cout << "number of column ? ";
    cin >> nbColumn;

    matrix game = Int_Jeu(nbLine, nbColumn, nbMine);

//    printerTableInit(&game);


    matrix around = mineAround(&game);
    cout << "\n\n\n";

    while (mineFound != nbLine*nbColumn- nbMine) {


        printerTable(&game, &around);

        cout << "what do you want make : \n f : put a flag \n t : take off a flaf \n d : dig a box \n";


        do {

            cin >> action;
        } while (action != 'f' and
        action != 't' and
        action != 'd');

        cout << "\n line ? \n";
        cin >> line;
        cout << "\n column ? \n";
        cin >> column;
        cout << "\n";


        if (action == 'f') {
            flagMine(&game, 0, line, column);
        } else if (action == 't') {
            flagMine(&game, 1, line, column);
        } else if (action == 'd') {
            mine = dig(&game, &around, line, column, mineFound);
            if (!mine) {
                cout << "G A M E    O V E R ";
                return 0;
            }
        }

    }

    cout <<"Y O U    W I N";


    return 0;
}