#include <iostream>
#include "ncurses.h"
#include "chrono"
#include "unistd.h"
#include <string>
#include <math.h>

//using namespace ncurses;

int main() {
    initscr();
    start_color();

    const int c16 = 16;
    const int c17 = 17;
    const int c18 = 18;
    const int c19 = 19;
    const int c20 = 20;
    const int c21 = 21;
    const int c22 = 22;
    const int c23 = 23;
    const int c24 = 24;
    const int c25 = 25;
/*
    init_color(c16, 200, 0, 1000);
    init_color(c17, 100, 100, 900);
    init_color(c18, 0, 200, 750);
    init_color(c19, 25, 300, 600);
    init_color(c20, 50, 450, 450);
    init_color(c21, 100, 700, 300);
    init_color(c22, 200, 700, 150);
    init_color(c23, 400, 500, 50);
    init_color(c24, 800, 300, 0);*/

    init_color(c16, 100, 0, 400);
    init_color(c17, 100, 100, 1000);
    init_color(c18, 400, 1000, 750);
    init_color(c19, 100, 800, 200);
    init_color(c20, 50, 450, 450);
    init_color(c21, 100, 1000, 300);
    init_color(c22, 1000, 700, 750);
    init_color(c23, 400, 1000, 500);
    init_color(c24, 900, 300, 1000);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, c17, COLOR_BLACK);
    init_pair(3, c18, COLOR_BLACK);
    init_pair(4, c19, COLOR_BLACK);
    init_pair(5, c20, COLOR_BLACK);
    init_pair(6, c21, COLOR_BLACK);
    init_pair(7, c22, COLOR_BLACK);
    init_pair(8, c23, COLOR_BLACK);
    init_pair(9, c24, COLOR_BLACK);

    double delay_seconds = 0.1;
    double zoom_level = 1000.0;
    unsigned int delay_micro_seconds = (unsigned int) (1000 * 1000 * delay_seconds);

    unsigned int frame_count = 0;
    long double max_iteration_count = 500.0;
    curs_set(0);

    long double sx = -1.41421;
    long double sy = 0;

    unsigned long current_frame_index = 1;
    do {
        int window_height;
        int window_width;
        getmaxyx(stdscr, window_height, window_width);

        const int ww = window_width;
        const int wh = window_height;
        //char* display = new char[wh][ww];
        char display[wh][ww];

        for (int y = 0; y < wh; y++) {
            for (int x = 0; x < ww; x++) {
                long double x_res = (x - (long double) ww / 1.5) / (5 * zoom_level) + sx;//0.74601;
                long double y_res = (y - (long double) wh / 2.0) / (2.5 * zoom_level) + sy;//0.1001;
                const long double cx = x_res;
                const long double cy = y_res;

                unsigned int iter_count = 0;
                for (; iter_count < max_iteration_count; iter_count++) {
                    if (!(std::abs((int) x_res) < 100 && std::abs((int) y_res) < 100))
                        break;
                    const double x_res_temp = x_res;
                    x_res = x_res * x_res - y_res * y_res + cx;
                    y_res = 2 * x_res_temp * y_res + cy;
                }
                int cond = (int) max_iteration_count / iter_count;
                switch (cond) {
                    case 0:
                        display[y][x] = '#';
                        break;
                    case 1:
                        display[y][x] = '@';
                        break;
                    case 2:
                        display[y][x] = '0';
                        break;
                    case 3:
                        display[y][x] = 'O';
                        break;
                    case 4:
                        display[y][x] = 'o';
                        break;
                    case 5:
                    case 6:
                        display[y][x] = '*';
                        break;
                    case 7:
                    case 8:
                        display[y][x] = '^';
                        break;
                    case 9:
                        display[y][x] = '.';
                        break;
                    default:
                        display[y][x] = ' ';
                        break;
                }
                /*if (iter_count > max_iteration_count * 0.9)
                    display[y][x] = 'O';
                else if (iter_count > max_iteration_count * 0.7)
                    display[y][x] = 'o';
                else if (iter_count > max_iteration_count * 0.5)
                    display[y][x] = '.';
                else
                    display[y][x] = ' ';*/
            }
        }

        clear();
        for (int row = 0; row < wh; row++) {
            for(int column = 0; column < ww; column++){
                switch (display[row][column]) {
                    case '#':
                        attron(COLOR_PAIR(1));
                        break;
                    case '@':
                        attron(COLOR_PAIR(2));
                        break;
                    case '0':
                        attron(COLOR_PAIR(3));
                        break;
                    case 'O':
                        attron(COLOR_PAIR(4));
                        break;
                    case 'o':
                        attron(COLOR_PAIR(5));
                        break;
                    case '*':
                        attron(COLOR_PAIR(6));
                        break;
                    case '^':
                        attron(COLOR_PAIR(7));
                        break;
                    case '.':
                        attron(COLOR_PAIR(8));
                        break;
                    default:
                        attron(COLOR_PAIR(9));
                        break;
                }
                addch(display[row][column]);
            }


            //addstr(display[row]);
            refresh();
        }

        //zoom_level *= 1.03;

        //max_iteration_count *= 1.005;
        current_frame_index++;
        // usleep(delay_micro_seconds);
        const long double shift = 2 * 1/zoom_level;
        char dir = getch();

        switch (dir){
            case 'h':
                sx -= shift;
                break;
            case 'j':;
                sy += shift;
                break;
            case 'k':
                sy -= shift;
                break;
            case 'l':
                sx += shift;
                break;
            case 'J':
                zoom_level /= 1.2;
                break;
            case 'K':
                zoom_level *= 1.2;
                break;
            case '+':
                max_iteration_count *= 1.1;
                break;
            case '-':
                max_iteration_count /= 1.1;
                break;
        }
    } while (!current_frame_index - frame_count < 1);


    endwin();
    return 0;
}