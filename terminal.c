#include <stdio.h>
#include <termios.h>
#include "terminal.h"

void disableBuffer() /* Function to disable terminal input buffering*/
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}
void enableBuffer() /* Function to enable terminal input buffering*/
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

