#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
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
    bool vide = true;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (tab[i][j] == 0)
                vide = false;
    if (!vide) {
        int case_l, case_c;
        do {
            case_l = rand() % 4;
            case_c = rand() % 4;
        } while (tab[case_l][case_c] != 0);

        tab[case_l][case_c] = tireDeuxOuQuatre();
    }

    return tab;
}

/** déplace les tuiles d'un plateau vers la gauche et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la gauche
 **/
Plateau déplacementGauche(Plateau plateau, int& score) {

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
                if (position != 0 && column[position - 1] == plateau[i][j]) {
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
Plateau déplacement(Plateau plateau, int direction, int& score) {
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

void dessine(sf::RenderWindow& window, Plateau brd, int &scoreText)
{
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    //draw the rectangle for score part above the game
    sf::RectangleShape score(sf::Vector2f(160*4, 160));
    score.setFillColor(sf::Color(255, 250, 250));
    score.setPosition(0, 0);
    window.draw(score);
    //make the writing
    sf::Text stext;
    stext.setFont(font);
    stext.setString("Score :  " + to_string(scoreText));
    stext.setCharacterSize(160 / 4 + 40);
    stext.setFillColor(sf::Color(100, 117, 134));
    sf::FloatRect textBounds = stext.getLocalBounds();
    stext.setOrigin(textBounds.width /8 - 10, textBounds.height / 2 - 10); 
    stext.setPosition(160 /4 , 160 / 4); 
    window.draw(stext);


    //draw the tiles and color them
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sf::RectangleShape tile(sf::Vector2f(160, 160));
            tile.setPosition(j * 160, i * 160 + 160); //position after score rectangle
            int nr = brd[i][j];
            if (nr == 0) 
                tile.setFillColor(sf::Color(255, 250, 250));
            else 
                if(nr == 2)
                    tile.setFillColor(sf::Color(230, 230, 250));
                else
                    if (nr == 4)
                        tile.setFillColor(sf::Color(240, 248, 255));
                    else
                        if (nr == 8)
                            tile.setFillColor(sf::Color(240, 255, 240));
                        else
                            if (nr == 16)
                                tile.setFillColor(sf::Color(255, 182, 193));
                            else
                                if (nr == 32)
                                    tile.setFillColor(sf::Color(176, 224, 230));
                                else
                                    if (nr == 64)
                                        tile.setFillColor(sf::Color(221, 160, 221));
                                    else
                                        if (nr == 128)
                                            tile.setFillColor(sf::Color(135, 206, 250));
                                        else
                                            if (nr == 256)
                                                tile.setFillColor(sf::Color(255, 218, 185));
                                            else
                                                if (nr == 512)
                                                    tile.setFillColor(sf::Color(100, 149, 237));
                                                else
                                                    if (nr == 1024)
                                                        tile.setFillColor(sf::Color(255, 255, 224));
                                                    else
                                                        if (nr == 2048)
                                                            tile.setFillColor(sf::Color(255, 215, 0));
            window.draw(tile);
            //draw the numbers
            if (nr != 0) 
            {
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(nr));
                text.setCharacterSize(160 / 4);
                text.setFillColor(sf::Color::Black);
                sf::FloatRect textBounds = text.getLocalBounds();
                text.setOrigin(textBounds.width / 2, textBounds.height / 2 + 10);
                text.setPosition(j * 160 + 160 / 2, i * 160 + 160 / 2 + 160); //add 160 to i bcs of the score rectangle
                window.draw(text);
            }
        }
    }
    //draw the line separating the game and the score
    sf::RectangleShape shorizontal(sf::Vector2f(640, 7));
    shorizontal.setPosition(0, 160);
    shorizontal.setFillColor(sf::Color(119, 136, 153));
    window.draw(shorizontal);
    // draw the lines between tiles 
    for (int i = 1; i < 4; i++) 
    {
        sf::RectangleShape horizontal(sf::Vector2f(640, 7)); 
        horizontal.setPosition(0, i * 160 + 160); //same story
        horizontal.setFillColor(sf::Color(119, 136, 153));
        window.draw(horizontal);
        sf::RectangleShape vertical(sf::Vector2f(7, 640)); 
        vertical.setPosition(i * 160, 160); //same story
        vertical.setFillColor(sf::Color(119, 136, 153));
        window.draw(vertical);
    }
}

/** permet de savoir si une partie est terminée
 *  @param plateau un plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTerminé(Plateau plateau, Plateau plateau1) {
    if (plateau == plateau1) {
        int s1 = 0;
        if (déplacement(plateau, 0, s1) == plateau)
            return false;
        if (déplacement(plateau, 1, s1) == plateau)
            return false;
        if (déplacement(plateau, 2, s1) == plateau)
            return false;
        if (déplacement(plateau, 3, s1) == plateau)
            return false;

        return true;
    }
    return false;
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

int main()
{
    int s = 0;
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(4 * 160, 5 * 160), "2048 - par Bianca et Elena");
    Plateau t = plateauInitial();
    dessine(window, t,s);
    window.display();
    Plateau newgamet = plateauVide();
    Plateau newt = plateauVide();
    Plateau ancienPlateau = plateauVide();

    bool moved = false;  

    while (window.isOpen() && !estTerminé(t, ancienPlateau) && !estGagnant(t))
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && !moved)
            {
                ancienPlateau = t; 

                int dircurrent = -1;
                if (event.key.code == sf::Keyboard::Left)
                    dircurrent = 0;
                else if (event.key.code == sf::Keyboard::Right)
                    dircurrent = 1;
                else if (event.key.code == sf::Keyboard::Up)
                    dircurrent = 2;
                else if (event.key.code == sf::Keyboard::Down)
                    dircurrent = 3;

                if (dircurrent != -1)
                {
                    newt = déplacement(t, dircurrent, s);
                    newgamet = Nouvelletuille(newt);  
                    t = newgamet;  
                    window.clear();  
                    dessine(window, newgamet, s);  
                    window.display();  
                    moved = true; 
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                moved = false;  
            }
        }
    }

    return 0;
}

