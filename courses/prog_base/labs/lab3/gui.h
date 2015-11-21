#ifndef _INC_GUI
#define _INC_GUI

void JumpTo(int x, int y);
void printRect(int x1, int y1, int x2, int y2, char border, int color);
void printIntro(char* string);
void printMainString(char* str, int blink);
void changeSize();
void printInputField(char* string);
void refreshScreen(char* string, int blink, int color, char* message, int beepFq);
int executeCmd(char* cmd, char* string, int Ypos);

#endif
