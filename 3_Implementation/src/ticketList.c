#include "ticketList.h"

#define BUFFERSIZE 512

void TicketListCreate(TicketList ** ticketList ) {
    (*ticketList) = malloc(sizeof(TicketList) );
    if ( (*ticketList) == NULL ) {
        perror("malloc");
    }
    (*ticketList)->length =0;
    (*ticketList)->head = NULL;
}

void TicketListDestroy(TicketList * ticketList ) {

    Ticket * ticket = NULL;
    while ( ticketList->length ) {
        ticket = ticketList->head;
        ticketList->head = ticketList->head->next;
        ticketList->length--;
        free(ticket->movie);
        free(ticket);
    }
    free(ticketList);

}

void TicketListInsert( TicketList * ticketList, char * movie, int seats) {
    Ticket * ticket = malloc(sizeof(Ticket));
    if ( ticket == NULL ) {
        perror("malloc");
    }
    ticket->movie = malloc(sizeof(char) * strlen(movie) + 1 );
    if ( ticket->movie == NULL ) {
        perror("malloc");
    }
    int pending=0;
    char buffer1[BUFFERSIZE];
    printf("The price is : Rs%d\n", seats*100 );
    fgets(buffer1,BUFFERSIZE,stdin);
    pending = atoi(buffer1);
    strcpy(ticket->movie,movie);
    ticket->seats = seats;
    ticket->next = ticketList->head;
    ticket->pending = pending;
    ticketList->head = ticket;
    ticketList->length++;
}

void TicketListDelete( TicketList * ticketList, char * movie ) {
    int found = 0;
    char buffer[BUFFERSIZE];
    if ( ticketList->length == 0 ) {
        printf("Sorry, list is empty\n");
    } else {

        Ticket * ticket = ticketList->head;
        Ticket * prevTicket = ticketList->head;
        for (int i = 0; i < ticketList->length; i++){
            if ( strcmp(ticket->movie, movie) == 0 ) {
                if ( ticket->pending ) {
                    printf("Confirm local payment by pressing enter\n");
                    fgets(buffer,BUFFERSIZE,stdin);
                    if ( buffer[0] != '\n') {
                        printf("Payment failed\n");
                        return;
                    }
                }
                if ( i == 0 ) {
                    ticketList->head = ticket->next;
                } else {
                    prevTicket->next = ticket->next;
                }
                free(ticket);
                ticketList->length--;
                found = 1;
                break;
            }
            ticket = ticket->next;
            if ( i == 0 ) continue;
            prevTicket = prevTicket->next;
        }
    }
    if (!found ) {
        printf("Sorry, movie not found.\n");
    }
}

void TicketListPrint( TicketList * ticketList ,int capacity,char *username) {
    if ( ticketList->length == 0) {
        printf("No tickets available.\n");
    } else {
        Ticket * ticket = ticketList->head;
        for ( int i = 0; i < ticketList->length; i++ ) {
           	printf("\n\n");
        printf("\t\t\t-----------------Movie Tickets Booking----------------\n");
        printf("\t===========================================================================\n");
        printf("\t\t\t\tShow Name : %s\n",ticket->movie);
        printf("\t Customer  : %s\n",username);
        printf("\t                                              Time            : 09:00pm\n");
        printf("\t                                              Hall            : 03\n");
        printf("\t                                              No of tickets.  : %d  \n",ticket->seats);
        printf("\t                                              price .         : %d  \n\n",100*capacity);
        printf("\t===========================================================================\n");
            ticket = ticket->next;
        }
    }
}

void TicketListOutput(TicketList * ticketList, char * name ) {
    char filename[256];
    memset(filename,0,256);
    strcat(filename,"./Users/");
    strcat(filename,name);
    strcat(filename,".txt");
    // ./Users/username.txt
    FILE * file = fopen(filename,"w");
    if ( file == NULL ) {
        perror("fopen");
    }
    Ticket * ticket = ticketList->head;
    for ( int i = 0; i < ticketList->length; i++ ) {
        fprintf(file,"%s-%d %d\n", ticket->movie,ticket->seats, ticket->pending);
        ticket = ticket->next;
    }
    fclose(file);
}

void TicketListInput(TicketList * ticketList, char * name ) {
    char filename[256];
    memset(filename,0,256);
    strcat(filename,"./Users/");
    strcat(filename,name);
    strcat(filename,".txt");
    // ./Users/username.txt
    FILE * file = fopen(filename,"a");
    fclose(file);
    file = fopen(filename,"r");
    if ( file == NULL ) {
        perror("fopen read");
    }
    char buffer[BUFFERSIZE];
    memset(buffer,0,BUFFERSIZE);
    char * movie;
    int seats, pending;
    while( fgets(buffer,BUFFERSIZE,file) != NULL ) {
        if ( *buffer == '\n' || *buffer == ' ' || *buffer == '\t') continue;
        movie=strtok(buffer,"-");
        seats = atoi(strtok(NULL," \t\n"));
        pending = atoi(strtok(NULL," \t\n"));
        TicketListInsert(ticketList,movie,seats);
        memset(buffer,0,BUFFERSIZE);
    }

    fclose(file);

}
