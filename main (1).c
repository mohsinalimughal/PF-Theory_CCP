#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. DEFINE THE API URL (Free source for rates)
// We use a simple API that returns JSON data
#define URL "https://api.exchangerate-api.com/v4/latest/USD"
#define DATA_FILE "rates.txt"

// Function to fetch live data using the system command line
void fetch_live_rates() {
    printf("Fetching live rates from the internet... please wait.\n");

    // This command uses 'curl' (built into Windows 10/11 and Linux) 
    // to download the data and save it to 'rates.txt'
    char command[256];
    sprintf(command, "curl -s %s > %s", URL, DATA_FILE);

    int status = system(command);

    if (status == 0) {
        printf("Success! Rates updated.\n\n");
    } else {
        printf("Error: Could not fetch rates. Check internet connection.\n");
    }
}

// Function to parse the text file and find a specific currency rate
float get_rate_from_file(char *target_currency) {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("Error: Could not open rate file. Run fetch first.\n");
        return -1;
    }

    char buffer[4096]; // Buffer to hold file content
    // Read the file (simplification: we assume the one line is enough for this API)
    fgets(buffer, 4096, file);
    fclose(file);

    // Create the search string, e.g., "EUR":
    char search_term[10];
    sprintf(search_term, "\"%s\":", target_currency);

    // Search for the string in the file content
    char *position = strstr(buffer, search_term);

    if (position != NULL) {
        // If found, move pointer past the currency name to the number
        // "EUR":0.92 -> we skip 6 characters to get to 0.92
        float rate = strtof(position + strlen(search_term), NULL);
        return rate;
    } else {
        return -1; // Currency not found
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

    // Optional: Fetch immediately on run so the user doesn't have to wait
    fetch_live_rates(); 

    do {
        // Wait for user to press enter before clearing (so they can read results)
        if(choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Consume newline
            getchar(); // Wait for input
        }

        system("clear"); // Clears the screen on Replit
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