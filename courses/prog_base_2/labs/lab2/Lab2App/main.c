#include "app.h"

int main(void) {
    stack_t stack = stack_new();
    printf("<<< Lab 2 V7 >>>\n");
    const char * dllName = chooseLib();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->check) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->reaction) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    srand(time(NULL));

    //stack_inputLoop(stack, dll->check, dll->reaction);
    while (1){
        char input[50];
        printf("%s"," >>> ");
		gets(input);
		if (input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = '\0';
		if (dll->check(stack, input)){
            dll->reaction(stack, input);
            continue;
		}
		char cmd[50];
		char value[50];
        sscanf(input, "%s", cmd);
        if (strcmp(cmd, "push")==0){
            sscanf(input, "%s %s", cmd, value);
            stack_push(stack, value);
            printf("Pushed: %s\n", value);
        }
        else if (strcmp(cmd, "pop") == 0){
            printf("Popped: %s\n", stack_pop(stack));
        }
        else if (strcmp(cmd, "count") == 0){
            printf("Strings on stack: %d\n", stack_getCount(stack));
        }
        else if (strcmp(cmd, "peek") == 0){
            printf("On peek: %s\n", stack_peek(stack));
        }
		else if (strcmp(input, "stop") == 0 || strcmp(input, "exit") == 0 ) return;
		else if (strlen(input)>0) printf("Sorry, unknown cmd.\n");
		fflush(stdin);
	}

    return 0;
}
