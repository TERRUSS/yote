#pragma once

#include <stdio.h>
#include <stdlib.h>

enum {LOGGING_TASK, LOGGING_STEP, FINISHED_TASK, STEP_ERROR, GAME_EVENT};
enum {BOLD, ERROR};

void printLog(int importance, const char* message);
void print_label(const char * label, int display);
