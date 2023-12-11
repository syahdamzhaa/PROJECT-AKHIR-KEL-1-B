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
int level = 1; // level awal agar bertambah trus
int speed = 200; // kecepatatan awal untuk level 1

void GameOverScreen() {
    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(2));
    mvprintw(maxY / 2 - 1, (maxX / 2) - 10, "GAMEE GAJEELASSSSS!");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
    refresh();
}


void LoadingScreen() {
    clear();
    attron(A_BOLD);
    mvprintw(maxY / 2, (maxX / 2) - 11, "Loading ya sayangg<3...");
    attroff(A_BOLD);
    refresh();

    Sleep(3000); // ini untuk delay loadingnya 3 detik 
}

void AwalMasukGame() {
    clear();
    attron(A_BOLD); // ini untuk aktifin teks tebal
    mvprintw(maxY / 2 - 2, (maxX / 2) - 10, "Selamat Datang di Game 'ULAR SI MATA DUITAN'");
    attroff(A_BOLD); // ini non aktif teks tebal
    mvprintw(maxY / 2, (maxX / 2) - 20, "Tekan 'S' untuk memulai permainan.");
    mvprintw(maxY - 2, 2, "Tekan 'X' untuk keluar.");
    refresh();
}

void MengaturLevel() {//ini unutk mengatur keceptan level
    switch (level) {
        case 1:
            speed = 200;
            break;
        case 2:
            speed = 150;
            break;
        case 3:
            speed = 100;
            break;
        case 4:
        	speed = 50;
        	break;
        default:
            break;
        }
    }


void Console() {
    if (kbhit()) {


@@ -130,49 +111,47 @@

    
    if (x <= 0 || x >= maxX || y <= 0 || y >= maxY) {
        game = false;
    }
}
  if (score >= 3 && level == 1) { // contoh: naik level saat skor mencapai 6 pada level 1
        level = 2; 
		}
    if(score >= 6 && level == 2){
    	level = 3; 
		}
	if(score >= 9 && level ==3){
		level = 4;
	}
        MengaturLevel(); // Mengatur kecepatan sesuai level yang baru
}

int main() {
    // Initialize ncurses
    initscr();
    noecho();  // Don't display typed characters
    curs_set(0);  // Hide the cursor
    
    AwalMasukGame();
	int level = 1; // level awal
    int level = 1; // level awal
    int speed = 200; // kecepatan awa

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
    mvprintw(maxX/2),(maxX/2)-12,"Kamu ga salah kok,gamenya salah!!")
    
	refresh();
    getch();
    clear();
    GameOverScreen();
    mvprintw(maxY/2,(maxX/2)-19,"Score Kamu adalah : %d",score);
    refresh();
    getch();
    endwin();

    return 0;
}
