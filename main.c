#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define URL "https://api.exchangerate-api.com/v4/latest/USD"
#define DATA_FILE "rates.txt"

void fetch_live_rates() {
    printf("Fetching live rates from the internet... please wait.\n");

    char command[256];
    sprintf(command, "curl -s %s > %s", URL, DATA_FILE);

    int status = system(command);

    if (status == 0) {
        printf("Success! Rates updated.\n\n");
    } else {
        printf("Error: Could not fetch rates. Check internet connection.\n");
    }
}

float get_rate_from_file(char *target_currency) {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("Error: Could not open rate file. Run fetch first.\n");
        return -1;
    }

    char buffer[4096]; 
    
    fgets(buffer, 4096, file);
    fclose(file);

    char search_term[10];
    sprintf(search_term, "\"%s\":", target_currency);

    char *position = strstr(buffer, search_term);

    if (position != NULL) {
    
        float rate = strtof(position + strlen(search_term), NULL);
        return rate;
    } else {
        return -1; 
    }
}

void show_menu() {
    printf("==========================================\n");
    printf("   LIVE CURRENCY CONVERTER (Base: USD)    \n");
    printf("==========================================\n");
    printf("1. Update Live Rates\n");
    printf("2. Convert USD to PKR\n");
    printf("3. Convert USD to EUR\n");
    printf("4. Convert USD to GBP\n");
    printf("5. Convert USD to INR\n");
    printf("6. Custom Conversion (Enter Code)\n");
    printf("0. Exit\n");
    printf("==========================================\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    float amount, rate;
    char currency_code[4];

    fetch_live_rates(); 

    do {

        if(choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); 
            getchar(); 
        }

        system("clear"); 
        show_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                fetch_live_rates();
                break;

            case 2:
                rate = get_rate_from_file("PKR");
                if(rate != -1) {
                    printf("Enter amount in USD: ");
                    scanf("%f", &amount);
                    printf("--------------------------------\n");
                    printf("%.2f USD = %.2f PKR\n", amount, amount * rate);
                    printf("--------------------------------\n");
                }
                break;

            case 3:
                rate = get_rate_from_file("EUR");
                if(rate != -1) {
                    printf("Enter amount in USD: ");
                    scanf("%f", &amount);
                    printf("--------------------------------\n");
                    printf("%.2f USD = %.2f EUR\n", amount, amount * rate);
                    printf("--------------------------------\n");
                }
                break;

            case 4: // GBP
                 rate = get_rate_from_file("GBP");
                if(rate != -1) {
                    printf("Enter amount in USD: ");
                    scanf("%f", &amount);
                    printf("--------------------------------\n");
                    printf("%.2f USD = %.2f GBP\n", amount, amount * rate);
                    printf("--------------------------------\n");
                }
                break;

            case 5: // INR
                 rate = get_rate_from_file("INR");
                if(rate != -1) {
                    printf("Enter amount in USD: ");
                    scanf("%f", &amount);
                    printf("--------------------------------\n");
                    printf("%.2f USD = %.2f INR\n", amount, amount * rate);
                    printf("--------------------------------\n");
                }
                break;

            case 6:
                printf("Enter 3-letter Currency Code (e.g. JPY, CAD): ");
                scanf("%s", currency_code);
                rate = get_rate_from_file(currency_code);

                if (rate != -1) {
                    printf("Enter amount in USD: ");
                    scanf("%f", &amount);
                    printf("--------------------------------\n");
                    printf("%.2f USD = %.2f %s\n", amount, amount * rate, currency_code);
                    printf("--------------------------------\n");
                } else {
                    printf("Error: Currency code '%s' not found.\n", currency_code);
                }
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
