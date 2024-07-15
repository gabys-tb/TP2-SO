#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(2, "Usage: settickets <tickets>\n");
        exit(1);
    }
    
    int tickets = atoi(argv[1]);

    if(settickets(tickets) <1){
        printf("Invalid ticket number. Ticket number must be greater than one.\n");
    } else{
        printf("Actual process has now %d tickets\n", tickets);
    }
    return 0;
}
