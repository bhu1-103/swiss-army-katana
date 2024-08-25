#include <cstdlib>
#include <iostream>
#include <string>
#include <ncurses.h>

void print_centered(WINDOW* win, int row, const std::string& message, int color_pair = 1) {
    int width = getmaxx(win);
    int start_x = (width - message.length()) / 2;
    wattron(win, COLOR_PAIR(color_pair));
    mvwprintw(win, row, start_x, "%s", message.c_str());
    wattroff(win, COLOR_PAIR(color_pair));
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

    WINDOW* input_win = newwin(10, 50, 10, 10);
    box(input_win, 0, 0);
    refresh();
    wrefresh(input_win);

    std::string input_file, output_file;

    print_centered(input_win, 1, "FFmpeg Video Converter", 1);
    wrefresh(input_win);

    wattron(input_win, COLOR_PAIR(2));
    mvwprintw(input_win, 3, 2, "Enter input file: ");
    wattroff(input_win, COLOR_PAIR(2));
    wrefresh(input_win);
    echo();
    char input_buf[256], output_buf[256];
    wgetnstr(input_win, input_buf, 255);
    input_file = input_buf;

    wattron(input_win, COLOR_PAIR(2));
    mvwprintw(input_win, 5, 2, "Enter output file: ");
    wattroff(input_win, COLOR_PAIR(2));
    wrefresh(input_win);
    wgetnstr(input_win, output_buf, 255);
    output_file = output_buf;
    noecho();

    wclear(input_win);
    box(input_win, 0, 0);
    print_centered(input_win, 1, "Processing...", 1);
    wrefresh(input_win);

    std::string command = "ffmpeg -i " + input_file + " -vcodec libx264 -b:v 750k -s 480x272 "
                          "-aspect 16:9 -profile:v main -level:v 2.1 -x264-params ref=3:bframes=1 "
                          "-acodec aac -b:a 128k -ac 2 -movflags +faststart " + output_file;

    int result = std::system(command.c_str());

    wclear(input_win);
    box(input_win, 0, 0);
    if (result == 0) {
        print_centered(input_win, 1, "Conversion successful!", 3);
    } else {
        print_centered(input_win, 1, "Error: FFmpeg command failed.", 4);
    }
    wrefresh(input_win);

    print_centered(input_win, 3, "Press any key to exit...", 2);
    wrefresh(input_win);
    getch();

    delwin(input_win);
    endwin();

    return 0;
}
