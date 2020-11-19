#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <cwchar>
#include <windows.h>
#include <time.h>

using namespace std;

#define fundal CYAN
#define windowWidth 900
#define windowHeight 700

int stanga;
int sus;
int width;
int height;
int latura;
int numar;
char nr_secret[6];
int x;
int y;

void player_vs_player();
void player_vs_computer();
void writeFeedback(int x, int y, char input[], char nr1[], int nr_mutare);
void writeFeedback(int x, int y, char input[], char nr1[]);
void instructions();
bool cifre_disticte(char sir[]);

void CreareButon(int x1, int y1, int x2, int y2, int borderc, int fillc) {
    setcolor(borderc);
    setlinestyle(SOLID_LINE, 0xFFFF, THICK_WIDTH);
    setfillstyle(SOLID_FILL, fillc);
    rectangle(x1, y1, x2, y2);
    floodfill((x1 + x2) / 2, (y1 + y2) / 2, borderc);
}

void CreareButonText(int x1, int y1, int x2, int y2, int borderc, int fillc, int textc, char text[]) {
    setcolor(borderc);
    setlinestyle(SOLID_LINE, 0xFFFF, THICK_WIDTH);
    setfillstyle(SOLID_FILL, fillc);
    rectangle(x1, y1, x2, y2);
    floodfill((x1 + x2)/2, (y1 + y2) / 2, borderc);
    setbkcolor(fillc);
    setcolor(textc);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy((x1 + x2)/2, (y1 + y2)/2, text);
}

void MeniuPrincipal() {
    setbkcolor(fundal);
    clearviewport();
    width = getmaxx();
    height = getmaxy();

    CreareButonText(300, 150, 600, 250, RED, LIGHTRED, BLACK, "Player vs Player");
    CreareButonText(300, 300, 600, 400, BLUE, LIGHTBLUE, BLACK, "Player vs computer");
    CreareButonText(300, 450, 600, 550, MAGENTA, LIGHTMAGENTA, BLACK, "Instructiuni");
    CreareButonText(350, 600, 550, 680, LIGHTBLUE, LIGHTGRAY, BLACK, "EXIT");

    while (true) {
        do {
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            delay(50);
        } while(!ismouseclick(WM_LBUTTONDOWN));

        if (x > 300 && y > 150 && x < 600 && y < 248) {
            clearviewport();
            player_vs_player();
        }
        else if (x > 300 && y > 300 && x < 600 && y < 400) {
            clearviewport();
            player_vs_computer();
        }
        else if (x > 300 && y > 450 && x < 600 && y < 550) {
            clearviewport();
            instructions();
        }
        else if (x > 350 && y > 600 && x < 550 && y < 680) {
            closegraph();
            exit(0);
        }
    }
}

void instructions() {
    setbkcolor(BLACK);
    setcolor(GREEN);
    clearviewport();

    char tmp[1000] = "5 CIFRE";
    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
    outtextxy(450, 50, tmp);
    setfillstyle(SLASH_FILL,WHITE);
    bar(320,60,580,65);

    settextstyle(COMPLEX_FONT,HORIZ_DIR,1);

    strcpy(tmp,"Acesta este unul dintre cele mai captivante jocuri rationale.“5 Cifre” este");      //150
    outtextxy(470,120, tmp);
    strcpy(tmp,"un joc de doi, in care calculatorul genereaza aleatoriu un numar de 5 cifre");
    outtextxy(428,140,tmp);
    strcpy(tmp,"distincte, iar acestia incearca sa il ghiceasca. Acesta poate fi jucat si de un");
    outtextxy(450,160,tmp);
    strcpy(tmp,"singur jucator, acesta incercand singur sa gaseasca acel numar.");
    outtextxy(362,180,tmp);
    strcpy(tmp,"Jocul se desfasoara astfel: Fiecare jucator va introduce numarul ales format");
    outtextxy(470,250,tmp);
    strcpy(tmp,"din 5 cifre distincte si pe ecran va fi afisata o combinatie de cifre “centrate”");
    outtextxy(455,270,tmp);
    strcpy(tmp,"si “mutate”.");
    outtextxy(80,290,tmp);
    strcpy(tmp,"De exemplu: numarul generat de calculator este 57902, iar numarul introdus ");
    outtextxy(465,310,tmp);
    strcpy(tmp,"de jucator este 14305. In acest caz cifra 0 se gaseste exact pe aceeasi pozitie");
    outtextxy(448,330,tmp);
    strcpy(tmp,"in numarul generat de calculator (este “centrata”), iar cifra 5 se gaseste pe ");
    outtextxy(440,350,tmp);
    strcpy(tmp,"alta pozitie fata de cea din numarul introdus de jucator. In acest caz pe ecran ");
    outtextxy(450,370,tmp);
    strcpy(tmp,"va fi afisata combinatia “1c+1m”.");
    outtextxy(193,390,tmp);
    strcpy(tmp,"Va castiga acel jucator care va reusi sa ghiceasca numarul generat de calcu-");
    outtextxy(470,460,tmp);
    strcpy(tmp,"lator. Daca jucatorii nu vor reusi sa gaseasca numarul din numarul lor limitat");
    outtextxy(440,480,tmp);
    strcpy(tmp,"de incercari, atunci castigator va fi considerat calculatorul.");
    outtextxy(352,500,tmp);
    settextstyle(COMPLEX_FONT,HORIZ_DIR,4);
    strcpy(tmp,"SPOR LA JOC!");
    outtextxy(455,570,tmp);


    char tmp1[] = "Meniu";
    setcolor(GREEN);

    CreareButonText(350, 600, 550, 680, LIGHTBLUE, BLUE, BLACK, tmp1);

    while (1) {
        do {
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            delay(50);
        } while(!ismouseclick(WM_LBUTTONDOWN));

        if (x > 350 && y > 600 && x < 550 && y < 680) {
            MeniuPrincipal();
            break;
        }
    }
}

void player_vs_computer() {
    setbkcolor(fundal);
    clearviewport();
    outtextxy(200, 50, "Introduceti numarul:");
    CreareButon(60, 80, 840, 150, LIGHTRED, RED);
    setcolor(BLACK);

    CreareButon(200, 200, 250, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(450/2, 450/2 + 5, "1");

    CreareButon(250, 200, 300, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(550/2, 450/2 + 5, "2");

    CreareButon(300, 200, 350, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(650/2, 450/2 + 5, "3");

    CreareButon(350, 200, 400, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(750/2, 450/2 + 5, "4");

    CreareButon(400, 200, 450, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(850/2, 450/2 + 5, "5");

    CreareButon(450, 200, 500, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(950/2, 450/2 + 5, "6");

    CreareButon(500, 200, 550, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1050/2, 450/2 + 5, "7");

    CreareButon(550, 200, 600, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1150/2, 450/2 + 5, "8");

    CreareButon(600, 200, 650, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1250/2, 450/2 + 5, "9");

    CreareButon(650, 200, 700, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1350/2, 450/2 + 5, "0");

    int x = mousex();
    int y = mousey();
    int nr_cifre_introduse = 0;

    int player_x = 450;
    int player_y = 350;

    for (int nr_mutari = 1; nr_mutari <= 15; ++nr_mutari) {
        char input[6] = "";

        while (strlen(input) != 5) {
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
            do {
                clearmouseclick(WM_LBUTTONDOWN);
                x = mousex();
                y = mousey();
                delay(50);
            } while(!ismouseclick(WM_LBUTTONDOWN));

            if (x >= 200 && x <= 250 && y >= 200 && y <= 250) {
                strcat(input, "1");
                nr_cifre_introduse++;
            }
            if (x >= 250 && x <= 300 && y >= 200 && y <= 250) {
                strcat(input, "2");
                nr_cifre_introduse++;
            }
            if (x >= 300 && x <= 350 && y >= 200 && y <= 250) {
                strcat(input, "3");
                nr_cifre_introduse++;
            }
            if (x >= 350 && x <= 400 && y >= 200 && y <= 250) {
                strcat(input, "4");
                nr_cifre_introduse++;
            }
            if (x >= 400 && x <= 450 && y >= 200 && y <= 250) {
                strcat(input, "5");
                nr_cifre_introduse++;
            }
            if (x >= 450 && x <= 500 && y >= 200 && y <= 250) {
                strcat(input, "6");
                nr_cifre_introduse++;
            }
            if (x >= 500 && x <= 550 && y >= 200 && y <= 250) {
                strcat(input, "7");
                nr_cifre_introduse++;
            }
            if (x >= 550 && x <= 600 && y >= 200 && y <= 250) {
                strcat(input, "8");
                nr_cifre_introduse++;
            }
            if (x >= 600 && x <= 650 && y >= 200 && y <= 250) {
                strcat(input, "9");
                nr_cifre_introduse++;
            }
            if (x >= 650 && x <= 700 && y >= 200 && y <= 250) {
                strcat(input, "0");
                nr_cifre_introduse++;
            }

            setcolor(WHITE);
            setbkcolor(RED);

            outtextxy(450, 125, input);
            setcolor(WHITE);
            setbkcolor(RED);

            if (strlen(input) == 5) {
                if (!cifre_disticte(input)) {
                    char sir[] = "Numar incorect!";
                    outtextxy(450, 125, sir);
                    delay(1500);
                    CreareButon(60, 80, 840, 150, LIGHTRED, RED);
                }
                else {
                    delay(100);
                    CreareButon(60, 80, 840, 150, LIGHTRED, RED);
                    writeFeedback(player_x, player_y, input, nr_secret);
                    player_y += 25;
                }
                strcpy(input, "");
                nr_cifre_introduse = 0;
            }
        }
    }

}

void validareNumar(char nr1[], char nr2[], int &c, int &m) {
    c = 0;
    m = 0;
    int h1[10] = {0};
    int h2[10] = {0};
    for (int i = 0; i < 5; ++i) {
        h1[nr1[i] - '0']++;
        h2[nr2[i] - '0']++;
        c += (nr1[i] == nr2[i]);
    }
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (nr1[i] == nr2[j] && i != j)
                m++;
}

void writeFeedback(int x, int y, char input[], char nr1[], int nr_mutare) {
    int c = 0;
    int m = 0;
    validareNumar(nr1, input, c, m);

    if (c == 5) {
        setbkcolor(BLUE);
        setcolor(WHITE);
        CreareButon(250, 600, 600, 700, LIGHTBLUE, LIGHTBLUE);
        clearviewport();
        if (nr_mutare % 2 == 1)
            outtextxy(850/2, 1300/2, "Player1 a castigat!");
        else
            outtextxy(850/2, 1300/2, "Player2 a castigat!");
        delay(2500);
        clearviewport();
        clearmouseclick(WM_LBUTTONDOWN);
        MeniuPrincipal();
    }

    char cc[6];
    strcpy(cc, itoa(c, cc, 10));
    char mm[6];
    strcpy(mm, itoa(m, mm, 10));
    char sol[25] = "";
    strcat(sol, cc);
    strcat(sol, " c + ");
    strcat(sol, mm);
    strcat(sol, " m");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    setbkcolor(CYAN);
    if (c != 5)
        outtextxy(x, y, sol);
}

void writeFeedback(int x, int y, char input[], char nr1[]) {
    int c = 0;
    int m = 0;
    validareNumar(nr1, input, c, m);

    if (c == 5) {
        setbkcolor(BLUE);
        setcolor(WHITE);
        CreareButon(250, 600, 600, 700, LIGHTBLUE, LIGHTBLUE);
        clearviewport();
        outtextxy(850/2, 1300/2, "Ai castigat!");
        delay(2500);
        clearviewport();
        clearmouseclick(WM_LBUTTONDOWN);
        MeniuPrincipal();
    }

    char cc[6];
    strcpy(cc, itoa(c, cc, 10));
    char mm[6];
    strcpy(mm, itoa(m, mm, 10));
    char sol[25] = "";
    strcat(sol, cc);
    strcat(sol, " c + ");
    strcat(sol, mm);
    strcat(sol, " m");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    setbkcolor(CYAN);
    if (c != 5)
        outtextxy(x, y, sol);
}

bool cifre_disticte(char sir[]) {
    if (strlen(sir) < 2 || sir[0] == '0')
        return true;
    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 5; ++j)
            if (sir[i] == sir[j])
                return false;
    return true;
}

bool numar_corect(int nr) {
    char sir[6];
    int idx = 0;

    while (nr > 0) {
        sir[idx++] = (nr % 10) + '0';
        nr /= 10;
    }

    return cifre_disticte(sir);
}

void generareNumarSecret() {
    srand(time(NULL));
    int x = 10000 + rand() % 100000;

    while (!numar_corect(x) || x > 99999)
        x = 10000 + rand() % 100000;

    int idx = 0;
    while (x > 0) {
        nr_secret[idx++] = x % 10 + '0';
        x /= 10;
    }

    for (int i = 0; i <= 2; ++i) {
        int tmp = nr_secret[i];
        nr_secret[i] = nr_secret[4 - i];
        nr_secret[4 - i] = tmp;
    }
}

void player_vs_player() {
    setbkcolor(CYAN);
    clearviewport();
    outtextxy(200, 50, "Introduceti numarul:");
    CreareButon(60, 80, 840, 150, LIGHTRED, RED);
    setcolor(BLACK);

    CreareButon(200, 200, 250, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(450/2, 450/2 + 5, "1");

    CreareButon(250, 200, 300, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(550/2, 450/2 + 5, "2");

    CreareButon(300, 200, 350, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(650/2, 450/2 + 5, "3");

    CreareButon(350, 200, 400, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(750/2, 450/2 + 5, "4");

    CreareButon(400, 200, 450, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(850/2, 450/2 + 5, "5");

    CreareButon(450, 200, 500, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(950/2, 450/2 + 5, "6");

    CreareButon(500, 200, 550, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1050/2, 450/2 + 5, "7");

    CreareButon(550, 200, 600, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1150/2, 450/2 + 5, "8");

    CreareButon(600, 200, 650, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1250/2, 450/2 + 5, "9");

    CreareButon(650, 200, 700, 250, BLUE, LIGHTBLUE);
    setbkcolor(LIGHTBLUE);
    outtextxy(1350/2, 450/2 + 5, "0");

    int x = mousex();
    int y = mousey();
    int nr_cifre_introduse = 0;
    int nr_mutari = 1;

    int player_1_x = 300;
    int player_1_y = 300;

    int player_2_x = 600;
    int player_2_y = 300;

    for (int nr_mutari = 1; nr_mutari <= 15; ++nr_mutari) {
        char input[6] = "";

        while (strlen(input) != 5) {
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
            do {
                clearmouseclick(WM_LBUTTONDOWN);
                x = mousex();
                y = mousey();
                delay(50);
            } while(!ismouseclick(WM_LBUTTONDOWN));

            if (x >= 200 && x <= 250 && y >= 200 && y <= 250) {
                strcat(input, "1");
                nr_cifre_introduse++;
            }
            if (x >= 250 && x <= 300 && y >= 200 && y <= 250) {
                strcat(input, "2");
                nr_cifre_introduse++;
            }
            if (x >= 300 && x <= 350 && y >= 200 && y <= 250) {
                strcat(input, "3");
                nr_cifre_introduse++;
            }
            if (x >= 350 && x <= 400 && y >= 200 && y <= 250) {
                strcat(input, "4");
                nr_cifre_introduse++;
            }
            if (x >= 400 && x <= 450 && y >= 200 && y <= 250) {
                strcat(input, "5");
                nr_cifre_introduse++;
            }
            if (x >= 450 && x <= 500 && y >= 200 && y <= 250) {
                strcat(input, "6");
                nr_cifre_introduse++;
            }
            if (x >= 500 && x <= 550 && y >= 200 && y <= 250) {
                strcat(input, "7");
                nr_cifre_introduse++;
            }
            if (x >= 550 && x <= 600 && y >= 200 && y <= 250) {
                strcat(input, "8");
                nr_cifre_introduse++;
            }
            if (x >= 600 && x <= 650 && y >= 200 && y <= 250) {
                strcat(input, "9");
                nr_cifre_introduse++;
            }
            if (x >= 650 && x <= 700 && y >= 200 && y <= 250) {
                strcat(input, "0");
                nr_cifre_introduse++;
            }

            setcolor(WHITE);
            setbkcolor(RED);

            outtextxy(450, 125, input);
            setcolor(WHITE);
            setbkcolor(RED);

            if (strlen(input) == 5) {
                if (!cifre_disticte(input)) {
                    char sir[] = "Numar incorect!";
                    outtextxy(450, 125, sir);
                    delay(1500);
                    CreareButon(60, 80, 840, 150, LIGHTRED, RED);
                }
                else {
                    delay(100);
                    CreareButon(60, 80, 840, 150, LIGHTRED, RED);

                    if (nr_mutari % 2 == 1) {
                        writeFeedback(player_1_x, player_1_y, input, nr_secret, nr_mutari);
                        player_1_y += 25;
                    }
                    else {
                        writeFeedback(player_2_x, player_2_y, input, nr_secret, nr_mutari);
                        player_2_y += 25;
                    }
                    break;
                }
                strcpy(input, "");
                nr_cifre_introduse = 0;
            }
        }
    }
}

int main() {
    initwindow(windowWidth, windowHeight, "5 CIFRE");
    generareNumarSecret();
    std::cout << nr_secret;
    MeniuPrincipal();
    return 0;
}
