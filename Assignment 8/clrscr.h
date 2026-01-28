#ifndef CLRSCR_H
#define CLRSCR_H
// Clear screen functionality for Windows, Linux, and macOS: clear_screen();
#ifdef _WIN32
#define clear_screen() system("@cls||clear");
#else
#define clear_screen() printf("\e[1;1H\e[2J")
#endif
#endif
