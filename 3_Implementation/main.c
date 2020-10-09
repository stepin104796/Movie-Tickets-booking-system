#include "movieList.h"
#include "ticketList.h"

#define BUFFERSIZE 512
#define DELIM " \n\t"

void storeMovies( MovieList * movieList ) {
    // Function that saves movie list inside a file
    FILE * file = fopen("movieList.txt","w");
    MovieListPrint(movieList,file);
    fclose(file);
}
void reservation(int capacity)
{
        int *array;
        int i,j,k=1;
        int a[20];
		printf("\n                                SCREEN\n\n\n");
		for (i=1;i<=100;i++)
		{
			if (array[i]==0)
				printf("%d\t",i);
			else
				printf("%d\t",i);
			if(i%10==0)
				printf("\n\n");
		}
		while(capacity!=0)
        {
            printf("Select the %d seat you want : ",k);
            scanf("%d",&a[k]);
            if (j>100||j<1)
                {
                    printf("seat1 number is unavailable in this theater\n");
                    printf("Please re-enter seat number: ");
                    scanf("%d",&j);
                }
            if (array[j]==1)
                {
                    printf("Sorry, this ticket is already booked! Please choose another seat.\n");
                    scanf("%d",&j);
                }
            else
                array[j]=1;
            k++;
            capacity--;
        }
        for(k=1;k<=capacity;k++)
        {
            printf("Seat numbers are %d ",a[k]);
        }
}


void loadMovies( MovieList * movieList  ) {
    // Function that loads a movie list from a file
    FILE * file = fopen("movieList.txt","r");
    if ( file == NULL ) {
        perror("fopen r");
    }
    char buffer[BUFFERSIZE];
    memset(buffer,0,BUFFERSIZE);
    char * name;
    int price;
    int capacity;
    while( fgets(buffer,BUFFERSIZE,file) != NULL ) {
        // Ignore empty lines, spaces and tabs
        if ( *buffer == '\n' || *buffer == ' ' || *buffer == '\t') continue;

        name = strtok(buffer,"-");
        price = atoi( strtok(NULL,DELIM) );
        capacity = atoi( strtok(NULL,DELIM) );
        MovieListInsert(movieList,name,price,capacity);
        memset(buffer,0,BUFFERSIZE);

    }
    fclose(file);
}


int main( int argc, char * argv[] ) {

    enum modes{USER, ADMIN, MODERATOR};
    int mode = USER;

    if ( argc > 1 ) {
        if ( strcmp(argv[1],"-a") == 0) {
            mode = ADMIN;
        } else if ( strcmp(argv[1], "-m") == 0 ) {
            mode = MODERATOR;
        }
    }

    MovieList * movieList;
    MovieListCreate(&movieList);

    // Make sure that file exists
    FILE * file = fopen("movieList.txt","a");
    if ( file == NULL ) {
        perror("fopen a");
    }
    fclose(file);
    loadMovies(movieList);

    char name[BUFFERSIZE], username[BUFFERSIZE];
    char buffer[BUFFERSIZE];
    char buffer1[BUFFERSIZE];
    int price = 0 , capacity = 0;
    int loop = 1;
    TicketList * ticketList;


    switch(mode) {
        // Main switch depended on program mode
        case USER:
            TicketListCreate(&ticketList);
            printf("What is your username?\n");
            fgets(username,BUFFERSIZE,stdin);
            strtok(username,"\n");
            TicketListInput(ticketList,username);
            while(loop) {

                printf("--------------------------------\n");
                printf("1. View Movies\n");
                printf("2. Book a ticket\n");
                printf("3. View tickets\n");
                printf("4. Exit\n");
                printf("--------------------------------\n");

                int answer = 0;
                fgets(buffer,BUFFERSIZE,stdin);
                answer = atoi(buffer);

                switch ( answer ) {
                    case 1: // view movie list
                        MovieListPrint(movieList,stdout);
                        break;
                    case 2: // book movie
                        printf("Please enter the movie name you would like to book\n");
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("How many tickets would you like?\n");

                        int notValid = 1;
                        while ( notValid ) {
                            scanf(" %d", &capacity);
                            getchar();
                            notValid=0;
                            if ( capacity <= 0 ) {
                                printf("invalid input, try again.\n");
                                notValid=1;
                            }
                        }
                        reservation(capacity);
                        printf("Trying to book %s...\n", name);
                        int ret = MovieListBook(movieList,name,capacity);
                        if ( ret == -1 ) {
                            printf("Not enough seats available\n");
                        }
                        else if ( ret == 0 ) {
                            printf("Sorry, no such movie\n");
                        }
                         else {

                            TicketListInsert(ticketList,name,capacity);
                        }
                        break;
                    case 3: // ticket print
                        TicketListPrint(ticketList,capacity,username);
                        break;
                    case 4:
                        printf("Exiting application...\n");
                        TicketListOutput(ticketList,username);
                        TicketListDestroy(ticketList);
                        loop = 0;
                        break;
                    default:
                        printf("Unkown command\n");

                }
            }
            break; // end of admin
            break;

        case MODERATOR:

            while(loop) {

                printf("--------------------------------\n");
                printf("1. View Movies\n");
                printf("2  View user tickets\n");
                printf("3. Delete user ticket\n");
                printf("4. Exit\n");
                printf("--------------------------------\n");
                int answer = 0;
                fgets(buffer,BUFFERSIZE,stdin);
                answer = atoi(buffer);

                switch ( answer ) {
                    case 1: // view movie list
                        MovieListPrint(movieList,stdout);
                        break;
                    case 2: // user tickets
                        TicketListCreate(&ticketList);
                        printf("What is the username?\n");
                        fgets(username,BUFFERSIZE,stdin);
                        strtok(username,"\n");
                        TicketListInput(ticketList,username);
                        TicketListPrint(ticketList,capacity,username);
                        TicketListDestroy(ticketList);
                        break;
                    case 3: // ticket delete
                        TicketListCreate(&ticketList);
                        printf("What is the username?\n");
                        fgets(username,BUFFERSIZE,stdin);
                        strtok(username,"\n");
                        TicketListInput(ticketList,username);

                        printf("What is the movie name?\n");
                        memset(name,0,BUFFERSIZE);
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");

                        TicketListDelete(ticketList,name);
                        printf("Deletion complete!\n");
                        TicketListOutput(ticketList,username);
                        TicketListDestroy(ticketList);
                        break;
                    case 4:
                        printf("Exiting application...\n");
                        loop = 0;
                        break;
                    default:
                        printf("Unkown command\n");

                }
            }
            break;
        case ADMIN:

            while(loop) {
                printf("--------------------------------\n");
                printf("1. Create new movie\n");
                printf("2. Delete an existing movie\n");
                printf("3. View movies\n");
                printf("4. Exit\n");
                printf("--------------------------------\n");

                int answer = 0;
                fgets(buffer,BUFFERSIZE,stdin);
                answer = atoi(buffer);
                switch ( answer ) {
                    case 1: // new movie
                        printf("Please enter movie name\n");
                        memset(name,0,BUFFERSIZE);
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("What is the ticket price?\n");
                        scanf(" %d", &price);
                        printf("What is the capacity of the movie theater?\n");
                        scanf(" %d",&capacity);
                        MovieListInsert(movieList,name,price,capacity);
                        break;
                    case 2: // delete movie
                        printf("Please enter the movie name you would like to delete\n");
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("Trying to delete %s...\n", name);
                        MovieListDelete(movieList,name);
                        break;
                    case 3: // view movie
                        MovieListPrint(movieList,stdout);
                        break;
                    case 4:
                        printf("Exiting application...\n");
                        loop = 0;
                        break;
                    default:
                        printf("Unkown command\n");

                }
            }
            break; // end of admin

    }

    storeMovies(movieList);
    MovieListDestroy(movieList);

}
