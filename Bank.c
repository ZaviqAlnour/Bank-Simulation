#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Platform-specific clear screen
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

void welcome_message();
void create_account();
void login();
void Bank_features();
void check_balance();
void deposit_funds();
void withdraw_funds();
void transfer_funds();
void view_transfer_history();
void logout();
void clear_screen();
void pause_screen();

int isLoggedIn = 0;
char acNumber[20];
int choice;

void clear_screen()
{
    system(CLEAR_SCREEN);
}

void pause_screen()
{
    printf("\nPress Enter to continue...");
    while(getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter key
}

int main()
{
    do {
        clear_screen();
        welcome_message();

        while(isLoggedIn == 1)
        {
            clear_screen();
            Bank_features();

            switch (choice)
            {
                case 1: 
                    clear_screen();
                    check_balance();
                    pause_screen();
                    break;
                case 2: 
                    clear_screen();
                    deposit_funds();
                    pause_screen();
                    break;
                case 3: 
                    clear_screen();
                    withdraw_funds();
                    pause_screen();
                    break;
                case 4: 
                    clear_screen();
                    transfer_funds();
                    pause_screen();
                    break;
                case 5:
                    clear_screen();
                    view_transfer_history();
                    pause_screen();
                    break;
                case 6:
                    clear_screen();
                    logout();
                    pause_screen();
                    break;
                case 7:
                    clear_screen();
                    printf("\n========================================\n");
                    printf("Thank you for using Daily C Bank!\n");
                    printf("Goodbye!\n");
                    printf("========================================\n");
                    return 0;
                default:
                    clear_screen();
                    printf("Invalid choice. Please select a valid option.\n");
                    pause_screen();
            }
        }
    } while(1);

    return 0;
}

void welcome_message()
{
    int account;

    printf("\n========================================\n");
    printf("     Welcome to Daily C Bank\n");
    printf("========================================\n");
    printf("Your trusted partner in financial service.\n");
    printf("We offer a range of services to meet your banking needs.\n\n");
    printf("Do you have an ACCOUNT with us?\n");
    printf("1. YES\n");
    printf("2. NO\n");
    printf("Enter your choice: ");

    if (scanf("%d", &account) != 1)
    {
        printf("Invalid input. Please enter 1 or 2.\n");
        while (getchar() != '\n');
        pause_screen();
        return;
    }

    if (account == 1)
    {
        clear_screen();
        printf("Welcome back! Please login to your account.\n\n");
        login();
        if(!isLoggedIn) pause_screen();
    }
    else if (account == 2)
    {
        clear_screen();
        printf("Great! Please proceed to create your account.\n");
        printf("Fill in the necessary details.\n\n");
        create_account();
        if(!isLoggedIn) pause_screen();
    }
    else
    {
        printf("Invalid choice. Please restart and choose 1 or 2.\n");
        pause_screen();
    }
}

void create_account()
{
    char name[50];
    char address[100];
    char phone[50];
    char email[50];
    char password[20];
    char acnum[10];
    int balance;

    FILE *file = fopen("AC_file.txt", "a");
    if (file == NULL)
    {
        printf("ERROR opening file.\n");
        return;
    }

    printf("---- Account Creation ----\n\n");
    printf("Enter your Name: ");
    scanf(" %[^\n]", name);

    printf("Enter your Address: ");
    scanf(" %[^\n]", address);

    printf("Enter your Phone Number: ");
    scanf(" %[^\n]", phone);

    printf("Enter your Email: ");
    scanf(" %[^\n]", email);

    printf("Create a Password: ");
    scanf(" %[^\n]", password);

    printf("Choose your Account Number (must be less than 8 characters): ");
    scanf(" %[^\n]", acnum);

    if (strlen(acnum) >= 8)
    {
        printf("\nAccount creation failed! Account number must be less than 8 characters.\n");
        fclose(file);
        return;
    }

    printf("Deposit at least $1000 to create your account: ");
    if(scanf("%d", &balance) != 1)
    {
        printf("\nInvalid amount entered.\n");
        fclose(file);
        while(getchar() != '\n');
        return;
    }

    if (balance < 1000)
    {
        printf("\nAccount creation failed! Minimum deposit is $1000.\n");
        fclose(file);
        return;
    }

    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Address: %s\n", address);
    fprintf(file, "Phone: %s\n", phone);
    fprintf(file, "Email: %s\n", email);
    fprintf(file, "Password: %s\n", password);
    fprintf(file, "Account Number: %s\n", acnum);
    fprintf(file, "Balance: %d\n\n", balance);
    fclose(file);

    FILE *file2 = fopen("acNandBalance.txt", "a");
    if (file2 == NULL)
    {
        printf("ERROR opening acNandBalance file.\n");
        return;
    }

    fprintf(file2, "AccountNumber: %s\nBalance: %d\n\n", acnum, balance);
    fclose(file2);

    strcpy(acNumber, acnum);

    clear_screen();
    printf("\n========================================\n");
    printf("   Account Created Successfully!\n");
    printf("========================================\n");
    printf("Account Number: %s\n", acnum);
    printf("Initial Balance: $%d\n", balance);
    printf("\nYou are now logged in!\n");
    printf("========================================\n");
    
    isLoggedIn = 1;
    pause_screen();
}

void login()
{
    char email[50], password[20], acnum_input[10];

    printf("---- Login ----\n\n");
    printf("Enter your Email: ");
    scanf(" %[^\n]", email);

    printf("Enter your Account password: ");
    scanf(" %[^\n]", password);

    printf("Enter your Account Number: ");
    scanf(" %[^\n]", acnum_input);

    FILE *file = fopen("AC_file.txt", "r");
    if (file == NULL)
    {
        printf("\nERROR opening file. No accounts found.\n");
        return;
    }

    char line[200];
    char file_email[50], file_password[20], file_acnum[10];
    int email_pass_ok = 0;
    int acnum_match = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Email: %49[^\n]", file_email) == 1)
        {
            if (fgets(line, sizeof(line), file) != NULL)
            {
                sscanf(line, "Password: %19[^\n]", file_password);
                
                if (fgets(line, sizeof(line), file) != NULL)
                {
                    sscanf(line, "Account Number: %9[^\n]", file_acnum);
                    
                    if (strcmp(email, file_email) == 0 &&
                        strcmp(password, file_password) == 0 &&
                        strcmp(acnum_input, file_acnum) == 0)
                    {
                        email_pass_ok = 1;
                        acnum_match = 1;
                        strcpy(acNumber, acnum_input);
                        break;
                    }
                }
            }
        }
    }

    fclose(file);

    if (email_pass_ok && acnum_match)
    {
        clear_screen();
        printf("\n========================================\n");
        printf("      Login Successful!\n");
        printf("========================================\n");
        printf("Account Number: %s\n", acNumber);
        printf("Welcome back to your account!\n");
        printf("========================================\n");
        isLoggedIn = 1;
        pause_screen();
    }
    else
    {
        printf("\nLogin failed! Incorrect Email, Password, or Account Number.\n");
        isLoggedIn = 0;
    }
}

void Bank_features()
{
    printf("\n========================================\n");
    printf("       Daily C Bank - Main Menu\n");
    printf("========================================\n");
    printf("Account: %s\n", acNumber);
    printf("========================================\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Funds\n");
    printf("3. Withdraw Funds\n");
    printf("4. Transfer Funds\n");
    printf("5. View Transaction History\n");
    printf("6. Logout\n");
    printf("7. Exit Application\n");
    printf("========================================\n");
    printf("Choose an option: ");
    
    if(scanf("%d", &choice) != 1)
    {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        choice = -1;
    }
}

void deposit_funds()
{
    if(isLoggedIn)
    {
        float amount;
        printf("\n========================================\n");
        printf("         Deposit Funds\n");
        printf("========================================\n");
        printf("Enter amount to deposit: $");
        if(scanf("%f", &amount) != 1 || amount <= 0)
        {
            printf("\nInvalid amount. Please enter a positive number.\n");
            while(getchar() != '\n');
            return;
        }

        FILE *file = fopen("acNandBalance.txt", "r");
        if(file == NULL)
        {
            printf("\nERROR opening balance file.\n");
            return;
        }

        typedef struct {
            char acNumber[20];
            float balance;
        } Account;

        Account accounts[100];
        int count = 0;
        char line[200];

        while(fgets(line, sizeof(line), file))
        {
            if(sscanf(line, "AccountNumber: %19[^\n]", accounts[count].acNumber) == 1)
            {
                if(fgets(line, sizeof(line), file))
                {
                    sscanf(line, "Balance: %f", &accounts[count].balance);
                    count++;
                }
            }
        }
        fclose(file);

        int found = 0;
        int found_index = -1;
        for(int i = 0; i < count; i++)
        {
            if(strcmp(accounts[i].acNumber, acNumber) == 0)
            {
                accounts[i].balance += amount;
                found = 1;
                found_index = i;
                printf("\n========================================\n");
                printf("      Deposit Successful!\n");
                printf("========================================\n");
                printf("Amount Deposited: $%.2f\n", amount);
                printf("New Balance: $%.2f\n", accounts[i].balance);
                printf("========================================\n");
                break;
            }
        }

        if(!found)
        {
            printf("\nAccount number not found.\n");
            return;
        }

        file = fopen("acNandBalance.txt", "w");
        if(file == NULL)
        {
            printf("\nERROR writing balance file.\n");
            return;
        }

        for(int i = 0; i < count; i++)
        {
            fprintf(file, "AccountNumber: %s\nBalance: %.2f\n\n", accounts[i].acNumber, accounts[i].balance);
        }
        fclose(file);

        char history_file[50];
        sprintf(history_file, "%s.txt", acNumber);
        FILE *history = fopen(history_file, "a");
        if(history != NULL)
        {
            fprintf(history, "Deposited $%.2f | New Balance: $%.2f\n", amount, accounts[found_index].balance);
            fclose(history);
        }
    }
    else
    {
        printf("\nPlease login to deposit funds.\n");
        login();
    }
}

void check_balance()
{
    if(isLoggedIn)
    {
        FILE *file = fopen("acNandBalance.txt", "r");
        if(file == NULL)
        {
            printf("\nERROR opening balance file.\n");
            return;
        }

        char file_acNumber[20];
        char line[200];
        float balance;
        int found = 0;

        while(fgets(line, sizeof(line), file))
        {
            if(sscanf(line, "AccountNumber: %19[^\n]", file_acNumber) == 1)
            {
                if(fgets(line, sizeof(line), file))
                {
                    sscanf(line, "Balance: %f", &balance);
                    
                    if(strcmp(file_acNumber, acNumber) == 0)
                    {
                        printf("\n========================================\n");
                        printf("        Account Balance\n");
                        printf("========================================\n");
                        printf("Account Number: %s\n", acNumber);
                        printf("Current Balance: $%.2f\n", balance);
                        printf("========================================\n");
                        found = 1;
                        break;
                    }
                }
            }
        }

        if(!found)
        {
            printf("\nAccount number not found. Please check your account.\n");
        }

        fclose(file);
    }
    else
    {
        printf("\nPlease login to your account to check balance.\n");
        login();
    }
}

void withdraw_funds()
{
    if(isLoggedIn)
    {
        float amount;
        printf("\n========================================\n");
        printf("        Withdraw Funds\n");
        printf("========================================\n");
        printf("Enter amount to withdraw: $");
        if(scanf("%f", &amount) != 1 || amount <= 0)
        {
            printf("\nInvalid amount. Please enter a positive number.\n");
            while(getchar() != '\n');
            return;
        }

        FILE *file = fopen("acNandBalance.txt", "r");
        if(file == NULL)
        {
            printf("\nERROR opening balance file.\n");
            return;
        }

        typedef struct {
            char acNumber[20];
            float balance;
        } Account;

        Account accounts[100];
        int count = 0;
        char line[200];

        while(fgets(line, sizeof(line), file))
        {
            if(sscanf(line, "AccountNumber: %19[^\n]", accounts[count].acNumber) == 1)
            {
                if(fgets(line, sizeof(line), file))
                {
                    sscanf(line, "Balance: %f", &accounts[count].balance);
                    count++;
                }
            }
        }
        fclose(file);

        int found = 0;
        for(int i = 0; i < count; i++)
        {
            if(strcmp(accounts[i].acNumber, acNumber) == 0)
            {
                found = 1;
                if(amount > accounts[i].balance)
                {
                    printf("\n========================================\n");
                    printf("     Insufficient Funds!\n");
                    printf("========================================\n");
                    printf("Requested Amount: $%.2f\n", amount);
                    printf("Available Balance: $%.2f\n", accounts[i].balance);
                    printf("========================================\n");
                }
                else
                {
                    accounts[i].balance -= amount;
                    printf("\n========================================\n");
                    printf("     Withdrawal Successful!\n");
                    printf("========================================\n");
                    printf("Amount Withdrawn: $%.2f\n", amount);
                    printf("New Balance: $%.2f\n", accounts[i].balance);
                    printf("========================================\n");
                    
                    char history_file[50];
                    sprintf(history_file, "%s.txt", acNumber);
                    FILE *history = fopen(history_file, "a");
                    if(history != NULL)
                    {
                        fprintf(history, "Withdrew $%.2f | New Balance: $%.2f\n", amount, accounts[i].balance);
                        fclose(history);
                    }
                }
                break;
            }
        }

        if(!found)
        {
            printf("\nAccount number not found.\n");
            return;
        }

        file = fopen("acNandBalance.txt", "w");
        if(file == NULL)
        {
            printf("\nERROR opening balance file for writing.\n");
            return;
        }
        for(int i = 0; i < count; i++)
        {
            fprintf(file, "AccountNumber: %s\nBalance: %.2f\n\n", accounts[i].acNumber, accounts[i].balance);
        }
        fclose(file);
    }
    else
    {
        printf("\nPlease login to your account to withdraw funds.\n");
        login();
    }
}

void transfer_funds()
{
    if(isLoggedIn)
    {
        char recipient_acNumber[20];
        float amount;

        printf("\n========================================\n");
        printf("        Transfer Funds\n");
        printf("========================================\n");
        printf("Enter recipient's Account Number: ");
        scanf(" %[^\n]", recipient_acNumber);

        printf("Enter amount to transfer: $");
        if(scanf("%f", &amount) != 1 || amount <= 0)
        {
            printf("\nInvalid amount. Please enter a positive number.\n");
            while(getchar() != '\n');
            return;
        }

        FILE *file = fopen("acNandBalance.txt", "r");
        if(file == NULL)
        {
            printf("\nERROR opening balance file.\n");
            return;
        }

        typedef struct {
            char acNumber[20];
            float balance;
        } Account;

        Account accounts[100];
        int count = 0;
        char line[200];

        while(fgets(line, sizeof(line), file))
        {
            if(sscanf(line, "AccountNumber: %19[^\n]", accounts[count].acNumber) == 1)
            {
                if(fgets(line, sizeof(line), file))
                {
                    sscanf(line, "Balance: %f", &accounts[count].balance);
                    count++;
                }
            }
        }
        fclose(file);

        int sender_index = -1, recipient_index = -1;
        for(int i = 0; i < count; i++)
        {
            if(strcmp(accounts[i].acNumber, acNumber) == 0)
                sender_index = i;
            if(strcmp(accounts[i].acNumber, recipient_acNumber) == 0)
                recipient_index = i;
        }

        if(sender_index == -1)
        {
            printf("\nYour account number not found.\n");
            return;
        }
        if(recipient_index == -1)
        {
            printf("\nRecipient account number not found.\n");
            return;
        }
        if(strcmp(acNumber, recipient_acNumber) == 0)
        {
            printf("\nCannot transfer to the same account.\n");
            return;
        }
        if(amount > accounts[sender_index].balance)
        {
            printf("\n========================================\n");
            printf("     Insufficient Funds!\n");
            printf("========================================\n");
            printf("Requested Amount: $%.2f\n", amount);
            printf("Available Balance: $%.2f\n", accounts[sender_index].balance);
            printf("========================================\n");
            return;
        }

        accounts[sender_index].balance -= amount;
        accounts[recipient_index].balance += amount;

        file = fopen("acNandBalance.txt", "w");
        if(file == NULL)
        {
            printf("\nERROR writing balance file.\n");
            return;
        }
        for(int i = 0; i < count; i++)
        {
            fprintf(file, "AccountNumber: %s\nBalance: %.2f\n\n", accounts[i].acNumber, accounts[i].balance);
        }
        fclose(file);

        printf("\n========================================\n");
        printf("     Transfer Successful!\n");
        printf("========================================\n");
        printf("Amount Transferred: $%.2f\n", amount);
        printf("To Account: %s\n", recipient_acNumber);
        printf("Your New Balance: $%.2f\n", accounts[sender_index].balance);
        printf("========================================\n");

        char history_file[50];
        sprintf(history_file, "%s.txt", acNumber);
        FILE *history = fopen(history_file, "a");
        if(history != NULL)
        {
            fprintf(history, "Transferred $%.2f to %s | New Balance: $%.2f\n",
                    amount, recipient_acNumber, accounts[sender_index].balance);
            fclose(history);
        }
        
        sprintf(history_file, "%s.txt", recipient_acNumber);
        history = fopen(history_file, "a");
        if(history != NULL)
        {
            fprintf(history, "Received $%.2f from %s | New Balance: $%.2f\n",
                    amount, acNumber, accounts[recipient_index].balance);
            fclose(history);
        }
    }
    else
    {
        printf("\nPlease login to your account to transfer funds.\n");
        login();
    }
}

void view_transfer_history()
{
    if(isLoggedIn)    
    {
        char history_file[50];
        sprintf(history_file, "%s.txt", acNumber);

        FILE *file = fopen(history_file, "r");
        if(file == NULL)
        {
            printf("\n========================================\n");
            printf("   No Transaction History Found\n");
            printf("========================================\n");
            printf("You haven't made any transactions yet.\n");
            printf("========================================\n");
            return;
        }

        char line[200];
        printf("\n========================================\n");
        printf("     Transaction History\n");
        printf("========================================\n");
        printf("Account: %s\n", acNumber);
        printf("========================================\n");
        while(fgets(line, sizeof(line), file))
        {
            printf("%s", line);
        }
        printf("========================================\n");

        fclose(file);
    }
    else
    {
        printf("\nPlease login to view your transfer history.\n");
        login();
    }
}

void logout()
{
    if(isLoggedIn)
    {
        isLoggedIn = 0;
        strcpy(acNumber, "");
        printf("\n========================================\n");
        printf("     Logged Out Successfully\n");
        printf("========================================\n");
        printf("Thank you for using Daily C Bank.\n");
        printf("Your account is secure.\n");
        printf("========================================\n");
    }
    else
    {
        printf("\nYou are not logged in.\n");
    }
}