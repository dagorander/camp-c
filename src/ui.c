#include <ncurses.h>
#include <string.h>
// #include <unistd.h> // For sleep?
#include "time.h"

void ui_init()
{
    initscr();
    curs_set(0);
}

void ui_teardown()
{
    endwin();
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

// Assumes we want centering, fix later
void draw_text_box(int rows, int columns, char text[])
{
    int start_x = (((columns-strlen(text))/2)-2);
    int start_y = ((rows/2)-1);
    int end_x = (((columns-strlen(text))/2)+strlen(text)+1);
    int end_y = ((rows/2)+1);
    int text_start_x = (columns-strlen(text))/2;
    int text_start_y = rows/2;

    draw_rectangle(start_x, start_y, end_x, end_y);
    mvprintw(text_start_y, text_start_x, "%s", text);
}

void draw_delay_text_box(int rows, int columns, char text[])
{
    int start_x = (((columns-strlen(text))/2)-2);
    int start_y = ((rows/2)-1);
    int end_x = (((columns-strlen(text))/2)+strlen(text)+1);
    int end_y = ((rows/2)+1);
    int text_start_x = (columns-strlen(text))/2;
    int text_start_y = rows/2;
    
    draw_rectangle(start_x, start_y, end_x, end_y);
    refresh();

    int i;
    for (i = 0; i < strlen(text); i++) {
        mvaddch((start_y+1), (start_x+i+2), text[i]);
        refresh();
        // TODO: Skip sleep if next char is a space
        time_sleep(0, 100);
    }
}

void draw_multiline_delayed_text_box(int rows, int columns, char text[])
{
    /* The old defauly-to-center method doesn't work with this
     * function, especially not with longer lines.
     *
    int start_x = (((columns-strlen(text))/2)-2);
    int start_y = ((rows/2)-1);
    int end_x = (((columns-strlen(text))/2)+strlen(text)+1);
    int end_y = ((rows/2)+1);
    int text_start_x = (columns-strlen(text))/2;
    int text_start_y = rows/2;
     * 
     * Resettign to hardcoded values below.
     */

    int start_x = 10;
    int start_y = 10;
    
    // Understand how many lines we need before drawing the box
    // Assuming width of 18 letters for now
    int box_width = 22; // Should be taken as argument
    int newline_locations[strlen(text)];
    
    // Find spaces and check if they need to be a linebreak
    int i;
    int previous_breakpoint_index = 0;
    int linebreaks;
    int previous_space_index = 0;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] != ' ') {
            continue;
        }
        if (i < (previous_breakpoint_index + box_width)) {
            previous_space_index = i;
            continue;
        }
        if (i > (previous_breakpoint_index + box_width)) {
            newline_locations[linebreaks] = previous_space_index;
            linebreaks += 1;
            previous_breakpoint_index = previous_space_index;
            continue;
        }
        newline_locations[linebreaks] = i;
        previous_breakpoint_index = i;
        linebreaks += 1;
    }

    // Actually draw things
    draw_rectangle(start_x, start_y, (start_x + box_width + 3), (start_y + linebreaks + 2));
    refresh();

    int y_position = (start_y+1);
    int x_position = (start_x+2);
    int current_line = 0;
    
    for (i = 0; i < strlen(text); i++) {
        // if (x_position != (start_x + box_width + 6)){
        mvaddch(y_position, x_position, text[i]);
        // }

        refresh();
        x_position += 1;
        if (text[i+1] != ' ') {
            time_sleep(0, 10);
        }
        if (i != newline_locations[current_line]) {
            continue;
        }
        if (i == newline_locations[current_line]) {
            current_line += 1;
            y_position += 1;
            x_position = (start_x+2);
        }
    }
}

// Also prototypes some drawing routines
void ui_splash_screen() 
{
    char splash_message[]="Camp C";
    int rows, columns;

    getmaxyx(stdscr, rows, columns);

    // draw_text_box(rows, columns, splash_message);

    // This needs to go to a separate function with prepared vars for args
    /* draw_rectangle(
            (((columns-strlen(splash_message))/2)-2),
            ((rows/2)-1),
            (((columns-strlen(splash_message))/2)+strlen(splash_message)+1),
            ((rows/2)+1)
        ); */
    // mvprintw(rows/2, (columns-strlen(splash_message))/2, "%s", splash_message);
    // draw_rectangle(4, 4, 8, 8);

    // Make struct for text box configs to avoid repeating coords

    /*
    draw_text_box(rows, columns, splash_message);
    refresh();
    getch();

    char second_message[]="This is the second one.";
    clear();
    draw_text_box(rows, columns, second_message);
    refresh();
    getch();

    char third_message[]="Short one.";
    clear();
    draw_text_box(rows, columns, third_message);
    refresh();

    char delay_message[]="This should be typed out slowly.";
    clear();
    draw_delay_text_box(rows, columns, delay_message);
    */

    char multiline_message[]=
        "This should go slowly on multiple lines. " 
        "Preferably without breaking in weird ways. "
        "Let's see if it is ready for a longer one. "
        "Like this one. :D";
    clear();
    draw_multiline_delayed_text_box(rows, columns, multiline_message);

    getch();
    clear();

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
