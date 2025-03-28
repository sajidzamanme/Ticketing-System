// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structures and Global Variables
struct customer {
    char name[50];
    int age;
    char mobile[15];
    int numOfTicket;
    int seats[4];
};
struct customer cust[61];
int seatArrangment[31];
int custNum = 1;
int total = 30;
int booked = 0;
int deletedIDs[30];
int delpos = 0;

// Prototypes:
void titleScreen();
int menu();
void showSeats();
void takeBooking();
void editBooking();
void deleteBooking();
void showCustDetails(int id);
int depart();
void returnToMenu();
void showCustIdName();

// Start of Execution:
int main()
{
    titleScreen();
    for (int i = 1; i <= 30; i++) {
        seatArrangment[i] = i;
    }

    while(1)
    {
        if (menu() == 0) {
            break;
        }
    }

    return 0;
}

// Functions:
void titleScreen()
{
    printf("        --------------------------------------------------------------------------------\n");
    printf("        | _____ _      _        _   _               ____            _                  |\n");
    printf("        ||_   _(_) ___| | _____| |_(_)_ __   __ _  / ___| _   _ ___| |_ ___ _ __ ___   |\n");
    printf("        |  | | | |/ __| |/ / _ \\ __| | '_ \\ / _` | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\  |\n");
    printf("        |  | | | | (__|   <  __/ |_| | | | | (_| |  ___) | |_| \\__ \\ ||  __/ | | | | | |\n");
    printf("        |  |_| |_|\\___|_|\\_\\___|\\__|_|_| |_|\\__, | |____/ \\__, |___/\\__\\___|_| |_| |_| |\n");
    printf("        |                                   |___/         |___/                        |\n");
    printf("        --------------------------------------------------------------------------------\n");
    printf("\n");
}

int menu()
{
    printf("Menu:\n");
    printf("---------------------------\n");
    printf("1. Show seats\n");
    printf("2. Take booking\n");
    printf("3. Edit booking\n");
    printf("4. Delete booking\n");
    printf("5. Show Customer Details\n");
    printf("6. Depart the bus\n");
    printf("7. Exit\n");

    int opt, ID;

    printf("Enter your option: ");
    scanf("%d", &opt);
    getchar();
    printf("\n");

    switch(opt){
        case 1:
                showSeats();
                returnToMenu();
                return 1;
        case 2:
                takeBooking();
                returnToMenu();
                return 1;
        case 3:
                editBooking();
                returnToMenu();
                return 1;
        case 4:
                deleteBooking();
                returnToMenu();
                return 1;
        case 5:
                showCustIdName();
                printf("Enter Customer ID: ");
                scanf("%d", &ID);
                getchar();

                showCustDetails(ID);
                returnToMenu();

                return 1;
        case 6:
                int temp = depart();
                system("cls");
                return temp;
        case 7:
                return 0;
        default:
                printf("No such option\n");
                return 1;
    }

}

void showSeats()
{
    printf("Seat Arrangement & available seats:\n");
    printf("-----------------------------------\n    ");
    int cnt = 0;
    for (int i = 1; i <= 30; i++) {
        if (cnt == 1) {
            printf("\t");
        }
        else if (cnt == 3) {
            printf("\n    ");
            cnt = 0;
        }

        if (seatArrangment[i] != -1) {
            printf("%0.2d ", seatArrangment[i]);
            cnt++;
        }
        else {
            printf("XX ");
            cnt++;
        }
        if (i == 9) printf("    Total Seats: %d", total);
        else if (i == 15) printf("    Booked Seats: %d", booked);
        else if (i == 21) printf("    available Seats: %d", total - booked);
    }
    printf("\n\n");
}

void takeBooking()
{
    showSeats();

    printf("Enter details to book:\n");
    printf("----------------------\n");
    printf("Enter Name: ");
    fgets(cust[custNum].name, sizeof(cust[custNum].name), stdin);
    cust[custNum].name[strcspn(cust[custNum].name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &cust[custNum].age);
    getchar();
    
    printf("Enter Mobile Number: ");
    scanf("%s", cust[custNum].mobile);
    getchar();

    printf("How many tickets do you want to buy: ");
    scanf("%d", &cust[custNum].numOfTicket);
    getchar();

    for (int i = 0; i < cust[custNum].numOfTicket; i++) {
        printf("Select seat %d: ", i + 1);
        scanf("%d", &cust[custNum].seats[i]);
        getchar();
        if (seatArrangment[cust[custNum].seats[i]] != -1) {
            seatArrangment[cust[custNum].seats[i]] = -1;
            booked++;
        }
        else {
            printf("The seat %d is already booked. Please select another seat.\n", cust[custNum].seats[i]);
            i--;
        }
    }

    printf("\n***Please note down your Customer ID***\n");
    printf("\n***Your Customer ID is %d***\n\n", custNum);

    custNum++;
}

void editBooking()
{
    int ID;

    showCustIdName();
    printf("Enter Customer ID: ");
    scanf("%d", &ID);
    getchar();

    showCustDetails(ID);

    printf("What do you want to change: \n");
    printf("1. Name\n");
    printf("2. Age\n");
    printf("3. Mobile number\n");
    printf("4. Change booking\n");

    int opt;
    printf("Select option to edit: ");
    scanf("%d", &opt);
    getchar();

    if(opt == 1){
        printf("Enter Name: ");
        fgets(cust[ID].name, sizeof(cust[ID].name), stdin);
        cust[ID].name[strcspn(cust[ID].name, "\n")] = '\0';
    }
    else if(opt == 2){
        printf("Enter Age: ");
        scanf("%d", &cust[ID].age);
        getchar();
    }
    else if(opt == 3){
        printf("Enter Mobile Number: ");
        scanf("%s", cust[ID].mobile);
        getchar();
    }
    else if(opt == 4){
        for (int i = 0; i < cust[ID].numOfTicket; i++) {
            seatArrangment[cust[ID].seats[i]] = cust[ID].seats[i];
            booked--;
        }

        printf("\nHow many tickets do you want to buy: ");
        scanf("%d", &cust[ID].numOfTicket);
        getchar();

        showSeats();
        
        for (int i = 0; i < cust[ID].numOfTicket; i++) {
            printf("Select seat %d: ", i + 1);
            scanf("%d", &cust[ID].seats[i]);
            getchar();
            if (seatArrangment[cust[ID].seats[i]] != -1) {
                seatArrangment[cust[ID].seats[i]] = -1;
                booked++;
            }
            else {
                printf("The seat %d is already booked. Please select another seat.\n", cust[ID].seats[i]);
                i--;
            }
        }
    }
    printf("\n");
}

void deleteBooking()
{
    int temp;

    showCustIdName();
    printf("Enter Customer ID to delete booking: ");
    scanf("%d", &temp);
    getchar();
    deletedIDs[delpos] = temp;
    delpos++;

    for (int i = 0; i < cust[temp].numOfTicket; i++) {
        seatArrangment[cust[temp].seats[i]] = cust[temp].seats[i];
        booked--;
    }

    printf("Customer ID %d has been deleted.\n\n", temp);
}

void showCustDetails(int id)
{
    printf("Customer Details:\n");
    printf("-----------------\n");
    printf("Name: %s\n", cust[id].name);
    printf("Age: %d\n", cust[id].age);
    printf("Mobile Number: %s\n", cust[id].mobile);
    printf("Booked tickets: ");
    for (int i = 0; i < cust[id].numOfTicket; i++) {
        printf("%d ", cust[id].seats[i]);
    }
    printf("\n\n");
}

int depart()
{
    FILE *fp;
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Output File is missing\n");
        exit(0);
    }

    fprintf(fp, "Seat Arrangement & available seats:\n");
    fprintf(fp, "-----------------------------------\n    ");
    int cnt = 0;
    for (int i = 1; i <= 30; i++) {
        if (cnt == 1) {
            fprintf(fp, "\t");
        }
        else if (cnt == 3) {
            fprintf(fp, "\n    ");
            cnt = 0;
        }
        if (seatArrangment[i] != -1) {
            fprintf(fp, "%0.2d ", seatArrangment[i]);
            cnt++;
        }
        else {
            fprintf(fp, "XX ");
            cnt++;
        }
        if (i == 9) fprintf(fp, "    Total Seats: %d", total);
        else if (i == 15) fprintf(fp, "    Booked Seats: %d", booked);
        else if (i == 21) fprintf(fp, "    available Seats: %d", total - booked);
    }
    fprintf(fp, "\n-----------------------------------\n\n");
    fprintf(fp, "--------------------\n");
    fprintf(fp, "| Customer Details |\n");
    fprintf(fp, "--------------------\n");

    for (int i = 1; i < custNum; i++) {
        int flag = 1;
        for(int j = 0; j < delpos; j++) {
            if (i == deletedIDs[j]) {
                flag = 0;
                break;
            }
        }

        if (flag == 1) {
            fprintf(fp, "----------------------\n");
            fprintf(fp, "Customer ID: %d\n", i);
            fprintf(fp, "Name: %s\n", cust[i].name);
            fprintf(fp, "Age: %d\n", cust[i].age);
            fprintf(fp, "Mobile Number: %s\n", cust[i].mobile);
            fprintf(fp, "Booked seats: ");
            for (int j = 0; j < cust[i].numOfTicket; j++) {
                fprintf(fp, "%d ", cust[i].seats[j]);
            }
            fprintf(fp, "\n----------------------\n\n");
        }
    }

    seatArrangment[31];
    custNum = 1;
    total = 30;
    booked = 0;
    deletedIDs[30];
    delpos = 0;
    for (int i = 1; i <= 30; i++) {
        seatArrangment[i] = i;
    }

    fclose(fp);

    printf("Bus has been departed.\n");
    printf("Check the file \"Output.txt\" for customer details.\n\n");
    printf("Do you want to continue for another bus(y/n): ");
    char choice;
    scanf("%c", &choice);
    getchar();
    if (choice == 'y') {
        return 1;
    }
    else return 0;
}

void returnToMenu()
{
    printf("Press Enter to go back to Menu.");
    getchar();
    #ifdef _WIN32
      system("cls");  // Windows
    #else
      system("clear"); // Linux/macOS
    #endif
}

void showCustIdName()
{
    for (int i = 1; i < custNum; i++) {
        int flag = 1;
        for (int j = 0; j < delpos; j++) {
            if (i == deletedIDs[j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            printf("Customer ID %d: %s\n", i, cust[i].name);
        }
    }
    printf("\n");
}