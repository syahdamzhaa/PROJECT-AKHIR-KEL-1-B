#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>  
#include <ncurses/ncurses.h>


using namespace std;
char audiofile[]={"C:/Users/syahd/Downloads/dry-fart.wav"};
string audiofile2;

char mariobross[]={"C:/Users/syahd/Downloads/mariobross.wav"};
string mariobross2;

char mariodead[]={"C:/Users/syahd/Downloads/1211mariodead.wav"};
string mariodead2;
fstream fp;

int maxX,maxY,x,y;
bool game = true;
char arah = 'w';
int score = 0;
int fruitX,fruitY;
int tailLength = 1; 
int tailX[100],tailY[100];
int level = 1; // level awal agar bertambah trus
int speed = 200; // kecepatatan awal untuk level 1


void LoadingScreen() {
    clear();
    attron(A_BOLD);
    mvprintw(maxY / 2, (maxX / 2) - 11, "Loading ya sayangg<3...");
    attroff(A_BOLD);
    refresh();
    
    // Tambahkan delay untuk simulasi loading
    // Anda bisa menambahkan animasi loading yang lebih kompleks jika diperlukan
    Sleep(2000); // Contoh: Delay selama 2 detik (untuk simulasi)
}

void GameOverScreen() {
    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(2));
    mvprintw(maxY / 2 - 1, (maxX / 2) - 15 , "AKU MAU KITA LEBIH DARI TEMEN!");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
    refresh();
}

void NampilinSkorBaris() {
    mvprintw(1, 2, "Skor kamu sayang: %d", score); // ini ni unutk nampilin skor di posisi baris 1, kolom 2
    mvprintw(2, 2, "Level: %d", level); // namipilin level baris 2, kolom 2
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

void AwalMasukGame() {
    clear();
    fp.open(mariobross, ios::in);
    mariobross2 = mariobross;
	PlaySound(mariobross2.c_str(), NULL, SND_ASYNC);
	fp.close();

    attron(A_BOLD); // Mengaktifkan teks tebal
    mvprintw(maxY / 2 - 2, (maxX / 2) - 10, "Selamat Datang di Game 'ULAR SI STARBOY'");
    attroff(A_BOLD); // Menonaktifkan teks tebal
    mvprintw(maxY / 2, (maxX / 2) - 20, "Tekan 'S' untuk memulai permainan.");
    mvprintw(maxY - 2, 2, "Tekan 'X' untuk keluar.");
    refresh();
}

void StartGame() {
	LoadingScreen();
    clear(); // Membersihkan layar sebelum memulai permainan
    attron(A_BOLD); // Mengaktifkan teks tebal
    attron(COLOR_PAIR(1)); // Mengatur warna teks
    mvprintw(maxY / 2, (maxX / 2) - 24, "Tekan tombol apa aja untuk mulai gamenya sayang<3");
    attroff(COLOR_PAIR(1)); // Menonaktifkan warna teks
    attroff(A_BOLD); // Menonaktifkan teks tebal
    refresh();
    getch();
}

void About() {
    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(2));
    mvprintw(maxY / 2 - 2, (maxX / 2) - 18, "'Ular si starboy' adalah game ular sederhana ");
    mvprintw(maxY / 2 - 1, (maxX / 2) - 18, "'d' Agar ular ke kanan");
    mvprintw(maxY / 2 , (maxX / 2) - 18, "'a' Agar ular ke kiri");
    mvprintw(maxY / 2 + 1, (maxX / 2) - 18, "'w' Agar ular ke atas");
    mvprintw(maxY / 2 + 2, (maxX / 2) - 18, "'s' Agar ular ke bawah");
    mvprintw(maxY / 2 + 9, (maxX / 2) + 32, "Dibuat Oleh:");
    mvprintw(maxY / 2 + 10, (maxX / 2) + 32, "1.Feliza Mutira");
    mvprintw(maxY / 2 + 11, (maxX / 2) +32 , "2.Lifi Anasywa");
    mvprintw(maxY / 2 + 12, (maxX / 2) + 32, "3.Salsha Nabila");
    mvprintw(maxY /2 + 13, (maxX / 2) + 32, "4.Syahdam Rizky Firdaus");
    mvprintw(maxY - 2, 2, "Tekan tombol apapun untuk kembali ke menu.");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
    refresh();
    getch();
    clear();
}
void ExitGame() {
    endwin();
    exit(0);
}

void Draw(){
    WINDOW *win = newwin(maxY, maxX, 0, 0);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    mvprintw(y,x,"@");
    mvprintw(fruitY,fruitX,"<3");
    NampilinSkorBaris(); // Menampilkan skor dan status permainan 
    for(int i=0;i<tailLength;i++){
    	
    mvprintw(tailY[i],tailX[i],"o");
    }
    refresh();
    Sleep(speed);
}

void Console(){
    if(kbhit()){
        switch(getch()){
            case 'a' : if(arah!='d')arah = 'a';break;
            case 'd' : if(arah!='a')arah = 'd';break;
            case 'w' : if(arah!='s')arah = 'w';break;
            case 's' : if(arah!='w')arah = 's';break;
            case 'q' : game = false; break;
        }
    }
}

void Algorithm(){
 
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2,prevY2;
    tailX[0] = x;
    tailY[0] = y;

    for(int i=1;i<tailLength;i++){
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    if(arah=='a')x-=2;
    if(arah=='d')x+=2;
    if(arah=='s')y+=2;
    if(arah=='w')y-=2;   

    if (y - fruitY >= 0 && y-fruitY < 3) {//misal ular dan makanan selisih dari 3,misal di x=16 dan y=17 ,maka true //salsa
    	if (x - fruitX >=0 && x-fruitX < 3){
        fruitX = rand() % maxX;
        fruitY=1;
    fp.open(audiofile, ios::in);
	audiofile2 = audiofile;
	PlaySound(audiofile2.c_str(), NULL, SND_ASYNC);
	fp.close();
        score++;
        tailLength++;
    }
    }
    	fruitY++;
    	
    if(fruitY>maxY){
    	fruitY=1;
    	fruitX=rand() %maxX;
	}
    if(x <= 0 || y <=0 || x>=maxX || y>=maxY){
        game = false;
    }
    for(int i=0;i<tailLength;i++){
        if(x==tailX[i]&&y==tailY[i])game=false;
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

int main(){
    initscr();
    start_color(); // Mengaktifkan penggunaan warna
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // Pasangan warna untuk Start
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Pasangan warna untuk About

    noecho();
    curs_set(0);
    getmaxyx(stdscr, maxY, maxX);
    x = maxX / 2, y = maxY / 2;
    fruitX = rand() % maxX;
    fruitY = 1;
    
    AwalMasukGame();
    int level = 1; // level awal
    int speed = 200; // kecepatan awal
    int userInput;
    do {
        clear();
        mvprintw(maxY / 2 - 4, (maxX / 2)-18, "Welcome to the game 'Ular si mata buaya'");
        attron(COLOR_PAIR(1)); // Mengaktifkan warna teks
        mvprintw(maxY / 2 - 1, (maxX / 2) - 12, "Press 'S' to Start");
        attroff(COLOR_PAIR(1)); // Menonaktifkan warna teks
        attron(COLOR_PAIR(2));
        mvprintw(maxY / 2 , (maxX / 2) - 12, "Press 'A' for About");
        attroff(COLOR_PAIR(2));
        mvprintw(maxY / 2 + 1, (maxX / 2) - 12, "Press 'X' to Exit");
        refresh();

        userInput = getch();
        switch (userInput) {
            case 's':
            case 'S':
                StartGame();
                break;
            case 'a':
            case 'A':
                About();
                break;
            case 'x':
            case 'X':
                ExitGame();
                break;
            default:
                break;
        }
    } while (userInput != 's' && userInput != 'S');

    // Mulai permainan jika tidak keluar dari loop
    clear(); // Membersihkan layar sebelum memulai permainan
    do{
        Draw();
        Console();
        Algorithm();
    }while(game);//BAGIAN FELIZA
    fp.open(mariodead, ios::in);
    mariodead2 = mariodead;
	PlaySound(mariodead2.c_str(), NULL, SND_ASYNC);
	fp.close();
    mvprintw(maxY/2,(maxX/2)-12,"Kamu ga salah kok,gamenya salah!!");
   
    refresh();
    getch();
    clear();
    GameOverScreen();
    mvprintw(maxY/2-2,(maxX/2)-11,"Score Kamu adalah : %d",score);
    refresh();
    getch();
	endwin();
}
