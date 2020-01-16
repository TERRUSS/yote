#include "utils.h"

void printLog(int importance, const char* message){

  switch(importance){
    case LOGGING_TASK:
      print_label("[INTERNAL]", BOLD);
      printf(" === %s ===\n", message);
    break;
    case LOGGING_STEP:
      print_label("[INTERNAL]", BOLD);
      printf("    %s\n", message);
    break;
    case STEP_ERROR:
      print_label("[INTERNAL ERROR]", ERROR);
      printf(" %s\n", message);
    break;
    case FINISHED_TASK:
      print_label("[INTERNAL]", BOLD);
      printf(" --- %s ---\n\n", message);
    break;
    case GAME_EVENT:
      print_label("[GAME]", BOLD);
      printf(" --- %s ---\n\n", message);
    break;
  }

  return;
}

void print_label(const char * label, int display){
  switch(display){
    case BOLD:
      printf("\033[1;32m%s\033[0m", label);
    break;
    case ERROR:
      printf("\033[1;31m%s\033[0m", label);
    break;
  }
}
