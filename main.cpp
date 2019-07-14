#include <iostream>
#include "ncurses.h"
#include "chrono"
#include "unistd.h"
#include <string>
#include <math.h>
#include <random>


//using namespace ncurses;

int main(int argc, char *argv[]) {
    srand(time(0));

    initscr();
    start_color();

    std::string jul_arg = "--julia";
    std::string rand_col_arg = "--random-colors";
    std::string auto_rotate_arg = "--auto-rotate";

    bool julia = false;
    bool random_colors = false;
    bool auto_rotate = false;

    for (int i = 0; i < argc; i++) {
        if (jul_arg.compare(argv[i]) == 0)
            julia = true;
        if (rand_col_arg.compare(argv[i]) == 0)
            random_colors = true;
        if (auto_rotate_arg.compare(argv[i]) == 0) {
            auto_rotate = true;
            julia = true;
        }
    }


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


    init_color(c16, 1000, 400, 0);
    init_color(c17, 0, 100, 1000);
    init_color(c18, 600, 600, 0);
    init_color(c19, 0, 800, 500);
    init_color(c20, 500, 450, 1000);
    init_color(c21, 1000, 300, 300);
    init_color(c22, 300, 1000, 750);
    init_color(c23, 400, 1000, 600);
    init_color(c24, 0, 400, 1000);

//
//    init_color(c16, 100, 0, 400);
//    init_color(c17, 100, 100, 1000);
//    init_color(c18, 400, 1000, 750);
//    init_color(c19, 100, 800, 200);
//    init_color(c20, 50, 450, 450);
//    init_color(c21, 100, 1000, 300);
//    init_color(c22, 1000, 700, 750);
//    init_color(c23, 400, 1000, 500);
//    init_color(c24, 900, 300, 1000);
//

    for (int i = 16; i < 26; i++) {
        if (random_colors) {
            int st_col = 333 + rand() % 778;
            int nd_col = 333 + rand() % 778;
            int lst_col = 1500 - (st_col + nd_col);

            int colors[] = {st_col, nd_col, lst_col};

            for (int x = 0; x < 3; x++) {
                int ind_a, ind_b;
                ind_a = rand() % 3;
                ind_b = rand() % 3;
                int temp = colors[ind_a];
                colors[ind_a] = colors[ind_b];
                colors[ind_b] = temp;
            }

            init_color(i, colors[0], colors[1], colors[2]);
        }
    }

    init_pair(1, c16, COLOR_BLACK);
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
    if (julia) {
        max_iteration_count = 30;
        zoom_level = 10.0;
    }

    curs_set(0);

    long double sx = -1.41421;
    long double sy = 0;

    if (julia)
        sx = 0;

    if (auto_rotate) {
        max_iteration_count = 115;
        zoom_level = 11;//11;
        sx = 0;
        sy = 0;
    }
    long double jul_x = 0.0;
    long double jul_y = -0.0;
    double rot_src = 0;

    int black_counter = 0;
    unsigned long current_frame_index = 1;
    int color_id = 1;
    do {
        if (auto_rotate) {
            max_iteration_count = 116 - (int) (50.0 / ((black_counter / 5000.0) + 1.0));
        }
        black_counter = 0;
        color_id++;
        if (0) {
            int id = color_id;
            init_pair(1, 16 + (id + 0) % 9, COLOR_BLACK);
            init_pair(2, 16 + (id + 1) % 9, COLOR_BLACK);
            init_pair(3, 16 + (id + 2) % 9, COLOR_BLACK);
            init_pair(4, 16 + (id + 3) % 9, COLOR_BLACK);
            init_pair(5, 16 + (id + 4) % 9, COLOR_BLACK);
            init_pair(6, 16 + (id + 5) % 9, COLOR_BLACK);
            init_pair(7, 16 + (id + 6) % 9, COLOR_BLACK);
            init_pair(8, 16 + (id + 7) % 9, COLOR_BLACK);
            init_pair(9, 16 + (id + 8) % 9, COLOR_BLACK);
        }
        int window_height;
        int window_width;
        getmaxyx(stdscr, window_height, window_width);

        const int ww = window_width;
        const int wh = window_height;
        //char* display = new char[wh][ww];
        char display[wh][ww];
        //X:0.000000 Y:0.000000 iter.:100.000000 Zoom:10.000000x jX:0.515129 jY:0.615067
        std::string txt = "X:" + std::to_string(sx) + " Y:" + std::to_string(sy) + " iter.:" +
                          std::to_string(max_iteration_count) + " Zoom:" + std::to_string(zoom_level) + "x jX: " +
                          std::to_string(jul_x) + " jY:" + std::to_string(jul_y) + "                              ";

        for (int y = 0; y < wh; y++) {
            for (int x = 0; x < ww; x++) {
                if (y == 0 && x < 85) {

                    display[y][x] = txt[x];
                    continue;
                }
                long double x_res = (x - (long double) ww / 2.0) / (5 * zoom_level) + sx;//0.74601;
                long double y_res = (y - (long double) wh / 2.0) / (2.5 * zoom_level) + sy;//0.1001;
                long double cx = x_res;
                long double cy = y_res;
                if (julia) {
                    cx = jul_x;
                    cy = jul_y;
                }

                unsigned int iter_count = 0;
                for (; iter_count < max_iteration_count; iter_count++) {
                    if (!(std::abs((int) x_res) < 1000 && std::abs((int) y_res) < 1000))
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
            }
        }

        clear();
        for (int row = 0; row < wh; row++) {
            for (int column = 0; column < ww; column++) {
                switch (display[row][column]) {
                    case '#':
                        attron(COLOR_PAIR(1));
                        break;
                    case '@':
                        black_counter++;
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
                if (row == 0 && column < 85) {
                    const int c99 = 99;
                    const int c98 = 98;
                    const int c97 = 97;
                    const int c96 = 96;
                    init_color(c99, 1000, 200, 700);
                    init_color(c98, 800, 300, 900);
                    init_color(c97, (short) zoom_level / 10000, 1000 - zoom_level / 10000, 100);
                    init_color(c96, 700, 700, 100);
                    init_pair(99, c99, COLOR_BLACK);
                    init_pair(98, c98, COLOR_BLACK);
                    init_pair(97, c97, COLOR_BLACK);
                    init_pair(96, c96, COLOR_BLACK);

                    attron(COLOR_PAIR(99));
                    if (column < 54)
                        attron(COLOR_PAIR(98));
                    if (column < 38)
                        attron(COLOR_PAIR(97));
                    if (column < 22)
                        attron(COLOR_PAIR(96));
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
        const long double shift = 2 * 1 / zoom_level;
        if (auto_rotate) {

            jul_x = sin(rot_src) / 1.1 + sin(rot_src / 33) / 10;
            jul_y = cos(rot_src + rot_src / 13) / 1.3 + sin(rot_src / 66) / 10;
            // 20 fps
            usleep(1000 * 50);
            rot_src = (rot_src + 0.02);
        } else {
            char dir = getch();

            switch (dir) {
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
                case 'w':
                    jul_y -= 1.0 / 100;
                    break;
                case 's':
                    jul_y += 1.0 / 100;
                    break;
                case 'a':
                    jul_x -= 1.0 / 100;
                    break;
                case 'd':
                    jul_x += 1.0 / 100;
                    break;
            }
        }

    } while (!current_frame_index - frame_count < 1);


    endwin();
    return 0;
}