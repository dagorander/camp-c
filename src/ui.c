#include <ncurses.h>
#include <string.h>

void init_ui()
{
    initscr();
    curs_set(0);
}

void draw_rectangle(int x1, int y1, int x2, int y2)
{
    // Here's some new functions found randomly on StackOverflow
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void splash_screen() 
{
    char splash_message[]="Camp C";
    int row, col;

    getmaxyx(stdscr, row, col);

    mvprintw(row/2, (col-strlen(splash_message))/2, "%s", splash_message);

    draw_rectangle(4, 4, 8, 8);
    refresh();
    getch();
}

void end_curses()
{
    endwin();
}

// TEMP TEST FUNCTIONS
void second_screen()
{
    char second_message[]="The place where people suffer";
    int row, col;

    getmaxyx(stdscr, row, col);

    mvprintw(row/2, (col-strlen(second_message))/2, "%s", second_message);

    mvprintw(1,1, "Number of rows:    %d", row);
    mvprintw(2,1, "Number of columns: %d", col);

    if (col < 80) {
        mvprintw(3,1, "Less than 80 column display!");
    }
    
    refresh();
    getch();
}
