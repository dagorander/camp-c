#include "ui.h"

int main()
{
    init_ui();

    splash_screen();

    second_screen();

    end_curses();
    
    return 0;
}
