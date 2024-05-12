#include<log.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET_NEWLINE   "\x1b[0m\n"


void info(char* string,...){
    va_list ap;
    
    char formatted_str[strlen(string) +  12];
    strcat(strcat(strcat(formatted_str,ANSI_COLOR_BLUE),string),ANSI_COLOR_RESET_NEWLINE);

}