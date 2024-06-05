#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <termios.h> /* For terminal input/output */

void disableBuffer();/* Function to disable terminal input buffering*/
void enableBuffer();/* Function to enable terminal input buffering*/

#endif /* TERMINAL_H_ */

