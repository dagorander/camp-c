#include "ui.h"

int main()
{
    ui_init();

    ui_splash_screen();

    second_screen();

    ui_teardown();
    return 0;
}
