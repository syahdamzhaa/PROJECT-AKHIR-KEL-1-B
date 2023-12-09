#include <iostream>
#include <conio.h>
#include <windows.h>  
#include <ncurses/ncurses.h>

int maxY, maxX;
int x, y;
char arah = 'd';
int score = 0;
int tailLength = 1;
int tailX[100], tailY[100];
int fruitX, fruitY;
bool game = true;

void Console() {
    if (kbhit()) {
        switch (getch()) {
            case 'a': if(arah!='d')arah = 'a'; break;
            case 'w': if(arah!='s')arah = 'w'; break;
            case 's': if(arah!='w')arah = 's'; break;
            case 'd': if(arah!='a')arah = 'd'; break;
            case 'q': game = false; break;
        }
    }
}

void Draw() {
    clear();
    WINDOW *win = newwin(maxY, maxX, 0, 0);
    
    refresh();
    box(win, 0, 0);
    wrefresh(win);

    mvprintw(y, x, "o");
    mvprintw(fruitY, fruitX, "#");

    for (int i = 0; i < tailLength; i++) {
        mvprintw(tailY[i], tailX[i], "o");
    }

    refresh();
    Sleep(100);
}

void Algorithm() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if(arah=='a')x-=2;
    if(arah=='d')x+=2;
    if(arah=='s')y+=2;
    if(arah=='w')y-=2;   

    if (y - fruitY >= 0 && y-fruitY < 3) {//misal ular dan makanan selisih dari 3,misal di x=16 dan y=17 ,maka true //salsa
    	if (x - fruitX >=0 && x-fruitX < 3){
        fruitX = rand() % maxX;
        fruitY=1;
        score++;
        tailLength++;
    }
    }
    fruitY++;
    
    if(fruitY>maxY){
    	fruitY=1;
    	fruitX=rand() %maxX;
	}


    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            game = false;
        }
    }

    
    if (x <= 0 || x >= maxX || y <= 0 || y >= maxY) {
        game = false;
    }
}

int main() {
    // Initialize ncurses
    initscr();
    noecho();  // Don't display typed characters
    curs_set(0);  // Hide the cursor

    getmaxyx(stdscr, maxY, maxX);

    y = maxY / 2;
    x = maxX / 2;
    fruitX = rand() % maxX;
    fruitY = 1;

    do {
        Draw();
        Console();
        Algorithm();
    } while (game);
    clear();
    mvprintw(maxY/2,(maxX/2)-19,"Score anda adalah %d",score);
    refresh();
    getch();
    endwin();

    return 0;
}
