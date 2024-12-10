#include "modele.hpp"
#include <curses.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

using Plateau = vector<vector<int>>;

int main() {

    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    int height = 20, width = 20, start_y = 0, start_x = 0;
    WINDOW *win = newwin(height, width, start_y, start_x);
    wrefresh(win);
    
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); 
    attron(COLOR_PAIR(1));

    int s = 0;
    srand(time(0));
    Plateau plateau = plateauInitial();
    printw("%d", s);
    printw("%s", dessine(plateau).c_str());
    refresh();   

    Plateau newt = plateauVide();
    Plateau ancienPlateau = plateauVide();

    while (!estTerminé(plateau, ancienPlateau) && !estGagnant(plateau))
    {
        int c = getch();
        
        if (c == KEY_LEFT) {
            newt = déplacement(plateau,0,s);  
        } else if (c == KEY_RIGHT) {
            newt = déplacement(plateau,1,s); 
        } else if (c == KEY_UP) {
            newt = déplacement(plateau,2,s); 
        } else if (c == KEY_DOWN) {
            newt = déplacement(plateau,3,s); 
        }
                
        ancienPlateau = plateau;
        plateau = Nouvelletuille(newt);
                
        clear();
        printw("%d", s);
        printw("%s", dessine(plateau).c_str());
        refresh(); 
    } 

    delwin(win);
    endwin();
    return 0;
}
