#include <ncurses.h>
#include <string.h>

void splash_screen() 
{
    char splash_message[]="Camp C";
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);

    mvprintw(row/2, (col-strlen(splash_message))/2, "%s", splash_message);
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
