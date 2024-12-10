#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

using Plateau = vector<vector<int>>;

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre()
{
    int random = rand() % 10;
    if (random < 9)
        return 2;
    else
        return 4;
}

/** génère un plateau de dimensions 4*4 ne contenant que des 0
 *  @return un plateau vide
 **/
Plateau plateauVide()
{
    Plateau a = { {0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0} };
    return a;
}

/** génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @return un plateau en début de jeu
 **/
Plateau plateauInitial()
{
    Plateau tab = plateauVide();
    int case1_l = rand() % 4;
    int case1_c = rand() % 4;
    tab[case1_l][case1_c] = tireDeuxOuQuatre();
    int case2_l, case2_c;
    do {
        case2_l = rand() % 4;
        case2_c = rand() % 4;
    } while (tab[case2_l][case2_c] != 0);
    tab[case2_l][case2_c] = tireDeuxOuQuatre();
    return tab;
}

/** génère un nombre sur une cases aléatoire du plateau
 *  @return le plateau de jeu
 **/
Plateau Nouvelletuille(Plateau tab)
{
    int case_l, case_c;
    do {
        case_l = rand() % 4;
        case_c = rand() % 4;
    } while (tab[case_l][case_c] != 0);
    tab[case_l][case_c] = tireDeuxOuQuatre();
    return tab;
}

/** permet de savoir si une partie est terminée
 *  @param plateau un plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTerminé(Plateau plateau, Plateau plateau1) {
    bool egal = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (plateau[i][j] != plateau1[i][j])
                egal = false;
        }
    }

    return egal;
}


/** permet de savoir si une partie est gagnée
 * @param plateau un plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (plateau[i][j] == 2048)
                return true;
    return false;
}



/** déplace les tuiles d'un plateau vers la gauche et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la gauche
 **/
Plateau déplacementGauche(Plateau plateau , int &score) {

    Plateau newBoard(4, vector<int>(4, 0));

    for (int i = 0; i < 4; i++) {
        vector<int> row(4, 0);
        int position = 0;

        for (int j = 0; j < 4; j++) {
            if (plateau[i][j] != 0) {
                if (position != 0 && row[position - 1] == plateau[i][j])
                {
                    row[position - 1] *= 2;
                    score = score + row[position - 1];
                }
                else {
                    row[position] = plateau[i][j];
                    position++;
                }
            }
        }
        newBoard[i] = row;
    }

    return newBoard;
}

/** déplace les tuiles d'un plateau vers la droite et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la droite
 **/
Plateau déplacementDroite(Plateau plateau, int& score) {
    Plateau newBoard(4, vector<int>(4, 0));

    for (int i = 0; i < 4; i++) {

        vector<int> row(4, 0);
        int position = 3;

        for (int j = 3; j >= 0; j--) {

            if (plateau[i][j] != 0) {
                if (position != 3 && row[position + 1] == plateau[i][j]) {
                    row[position + 1] *= 2;
                    score = score + row[position + 1];
                }
                else {
                    row[position] = plateau[i][j];
                    position--;
                }
            }
        }
        newBoard[i] = row;
    }
    return newBoard;
}

/** déplace les tuiles d'un plateau vers le haut et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers le haut
 **/
Plateau déplacementHaut(Plateau plateau, int& score) {
    Plateau newBoard(4, vector<int>(4, 0));

    for (int j = 0; j < 4; j++) {

        vector<int> column(4, 0);
        int position = 0;

        for (int i = 0; i < 4; i++) {

            if (plateau[i][j] != 0) {
                if (position != 0 && column[position - 1] == plateau[i][j]){
                    column[position - 1] *= 2;
                    score = score + column[position - 1];
                }
                else {
                    column[position] = plateau[i][j];
                    position++;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            newBoard[i][j] = column[i];
        }
    }
    return newBoard;
}

/** déplace les tuiles d'un plateau vers le bas et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers le bas
 **/
Plateau déplacementBas(Plateau plateau, int& score) {
    Plateau newBoard(4, vector<int>(4, 0));

    for (int j = 0; j < 4; j++) {
        vector<int> column(4, 0);
        int position = 3;

        for (int i = 3; i >= 0; i--) {
            if (plateau[i][j] != 0) {
                if (position != 3 && column[position + 1] == plateau[i][j]) {
                    column[position + 1] *= 2;
                    score = score + column[position + 1]; 
                }
                else {
                    column[position] = plateau[i][j];
                    position--;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            newBoard[i][j] = column[i];
        }
    }
    return newBoard;
}

/** déplace les tuiles d'un plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le plateau
 *  @param direction la direction
 *  @return le plateau déplacé dans la direction
 **/
Plateau déplacement(Plateau plateau, int direction, int &score) {
    Plateau tab;
    if (direction == 0)
        tab = déplacementGauche(plateau, score);
    else if (direction == 1)
        tab = déplacementDroite(plateau, score);
    else if (direction == 2)
        tab = déplacementHaut(plateau, score);
    else
        tab = déplacementBas(plateau, score);
    return tab;
}


/** affiche un plateau
 * @param p le plateau
 **/
string dessine(Plateau brd)
{
    string s;
    int ct = 0;
    s = s + "*****************************";
    s = s + '\n';
    for (int i = 0; i < 4; i++)
    {
        s = s + '*';
        for (int j = 0; j < 4; j++)
        {
            if (brd[i][j] == 0)
                s = s + "      ";
            if (brd[i][j] > 0)
            {
                int nraux = brd[i][j];
                string aux; //utilise aux pour transformer brd[i][j] en string
                aux = to_string(nraux);
                if (brd[i][j] < 10)
                {
                    s = s + "   ";
                    s = s + aux;
                    s = s + "  ";
                }
                else
                    if (brd[i][j] < 100)
                    {
                        s = s + "  ";
                        s = s + aux;
                        s = s + "  ";
                    }
                    else
                        if (brd[i][j] < 1000)
                        {
                            s = s + "  ";
                            s = s + aux;
                            s = s + " ";
                        }
                        else
                        {
                            s = s + " ";
                            s = s + aux;
                            s = s + " ";
                        }
            }
            s = s + '*';
        }
        s = s + '\n';
        s = s + "*****************************";
        s = s + '\n';
        ct++;
    }
    if (ct < 4)
        s = s + "*****************************";
    s = s + '\n';
    return s;
}

int main()
{
    int s = 0;
    srand(time(0));
    Plateau t = plateauInitial();
    cout << "Score: " << s;
    cout << endl << endl; 
    cout << dessine(t);
    char cdir[128];
    cdir['a'] = 0;
    cdir['d'] = 1;
    cdir['w'] = 2;
    cdir['s'] = 3;
    Plateau newgamet = plateauVide();
    Plateau newt = plateauVide();
    Plateau ancienPlateau = plateauVide();
    while (!estTerminé(t, ancienPlateau) && !estGagnant(t))
    {
        ancienPlateau = t;
        char c;
        cin >> c;
        int dircurrent = cdir[c];
        // cout << dircurrent << endl; //test wasd
        newt = déplacement(t, dircurrent, s);
        newgamet = Nouvelletuille(newt);
        system("cls");
        cout << "Score: " << s;
        cout << endl << endl;
        cout << dessine(newgamet);
        t = newgamet;
    }
    return 0;
}
