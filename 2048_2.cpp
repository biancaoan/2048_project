// 2048_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
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
    }
    while (tab[case2_l][case2_c] != 0);
    tab[case2_l][case2_c] = tireDeuxOuQuatre();
    return tab;
}


/** affiche un plateau
 * @param p le plateau
 **/
void dessine(Plateau brd)
{
    string s;
    int ct = 0;
    for (int i = 0; i < 25; i++)
        s = s + '*';
    s = s + '\n';
    for (int i = 0; i < 4; i++)
    {
        s = s + '*';
        for (int j = 0; j < 4; j++)
        {
            if (brd[i][j] == 0)
                s = s + "     ";
            if (brd[i][j] > 0)
            {
                string aux; //utilise aux pour transformer brd[i][j] en string
                aux = brd[i][j] + '0';
                if (brd[i][j] < 10)
                {
                    s = s + "  ";
                    s = s + aux;
                    s = s + "  ";
                }
                else
                    if (brd[i][j] < 100)
                    {
                        s = s + " ";
                        s = s + aux;
                        s = s + "  ";
                    }
                    else
                        if (brd[i][j] < 1000)
                        {
                            s = s + " ";
                            s = s + aux;
                            s = s + " ";
                        }
                        else
                            s = s + aux;
            }
            s = s + '*';
        }
        s = s + '\n';
        for (int i = 0; i < 25; i++)
            s = s + '*';
        s = s + '\n';
        ct++;
    }
    if (ct < 4)
        for (int i = 0; i < 25; i++)
            s = s + '*';
    s = s + '\n';
    cout << s;
}


int main()
{
  //  cout << tireDeuxOuQuatre();
    srand(time(0));
    cout << endl;
    Plateau t = plateauInitial();
    for (int i = 0;i < t.size();i++)
    {
        for (int j = 0;j < t[i].size();j++)
            cout << t[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    cout << endl;
    dessine(t);
    return 0;
}

