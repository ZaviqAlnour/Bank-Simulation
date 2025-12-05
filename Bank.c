#include <stdio.h>
#include <string.h>

void welcome_message();
void creat_account();
void login();
void Bank_fetures();
void check_balance();
void deposite_funds();
void withdraw_funds();
void trasfer_funds_between_accounts();
void view_transfer_history();

int isLoggedIn = 0;
int acNumber;
int choice;


int main()
{
    welcome_message();

    if(isLoggedIn == 1)
    {
        Bank_fetures();

        switch (choice)
        {
            case 1: check_balance();
                break;
            case 2: deposite_funds();
                break;
            case 3: withdraw_funds();
                break;
            case 4: trasfer_funds_between_accounts();
                break;
        }
    }

    return 0;
}


void welcome_message()
{
    int account;

    printf("Welcome to daily C Bank\n");
    printf("Your trusted partner in financial service.\n");
    printf("We offer a range of services to meet your banking needs.\n");
    printf("Do you have an ACCOUNT with us?\n");
    printf("1. YES\n");
    printf("2. NO\n");
    printf("Enter your choice: ");

    // Validate input
    if (scanf("%d", &account) != 1)
    {
        printf("Invalid input. Please enter 1 or 2.\n");
        // clear buffer
        while (getchar() != '\n');
        return;
    }

    if (account == 1)
    {
        printf("Welcome back! Please login to your account.\n");
        login();
    }
    else if (account == 2)
    {
        printf("Great! Please proceed to create your account.\n");
        printf("Fill in the necessary details.\n");
        creat_account();
    }
    else
    {
        printf("Invalid choice. Please restart and choose 1 or 2.\n");
    }
}



void creat_account()
{
    char name[50];
    char address[100];
    char phon[50];
    char email[50];
    char password[20];
    char acnum[10];      // account number (must be < 8 chars)
    int balance;         // initial deposit

    FILE *file = fopen("AC_file.txt", "a");
    if (file == NULL)
    {
        printf("ERROR opening file.\n");
        return;
    }

    printf("Enter your Name: ");
    scanf(" %[^\n]", name);

    printf("Enter your Address: ");
    scanf(" %[^\n]", address);

    printf("Enter your Phone Number: ");
    scanf(" %[^\n]", phon);

    printf("Enter your Email: ");
    scanf(" %[^\n]", email);

    printf("Create a Password: ");
    scanf(" %[^\n]", password);

    // New Feature: Account Number
    printf("Choose your Account Number (must be less than 8 characters): ");
    scanf(" %[^\n]", acnum);

    if (strlen(acnum) >= 8)
    {
        printf("Account creation failed! Account number must be less than 8 characters.\n");
        fclose(file);
        return;
    }

    // New Feature: Minimum Initial Deposit
    printf("Deposit at least $1000 to create your account: ");
    scanf("%d", &balance);

    if (balance < 1000)
    {
        printf("Account creation failed! Minimum deposit is $1000.\n");
        fclose(file);
        return;
    }

    // Save all personal information
    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Address: %s\n", address);
    fprintf(file, "Phone: %s\n", phon);
    fprintf(file, "Email: %s\n", email);
    fprintf(file, "Password: %s\n", password);
    fprintf(file, "Account Number: %s\n", acnum);
    fprintf(file, "Balance: %d\n\n", balance);

    fclose(file);

    // Save account number + balance in second file
    FILE *file2 = fopen("acNandBalance.txt", "a");
    if (file2 == NULL)
    {
        printf("ERROR opening acNandBalance file.\n");
        return;
    }

    fprintf(file2, "AccountNumber: %s\nBalance: %d\n\n", acnum, balance);
    fclose(file2);

    // Store in global variable
    strcpy(acNumber, acnum);

    printf("Account created successfully! You can now login to your account.\n");
}





void login()
{
    char email[50], password[20], acnum_input[10];

    printf("Enter your Email: ");
    scanf(" %[^\n]", email);

    printf("Enter your Account password: ");
    scanf(" %[^\n]", password);

    printf("Enter your Account Number: ");
    scanf(" %[^\n]", acnum_input);

    FILE *file = fopen("AC_file.txt", "r");
    if (file == NULL)
    {
        printf("ERROR opening file.\n");
        return;
    }

    char line[200];
    char file_email[50], file_password[20];
    int email_pass_ok = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "Email: %49[^\n]", file_email) == 1)
        {
            if (fgets(line, sizeof(line), file) != NULL)
            {
                sscanf(line, "Password: %19[^\n]", file_password);

                if (strcmp(email, file_email) == 0 &&
                    strcmp(password, file_password) == 0)
                {
                    email_pass_ok = 1;
                    break;
                }
            }

            fgets(line, sizeof(line), file); // skip blank line
        }
    }

    fclose(file);

    // If email+password failed  deny login immediately
    if (!email_pass_ok)
    {
        printf("Login failed! Incorrect Email or Password.\n");
        isLoggedIn = 0;
        return;
    }

    FILE *file2 = fopen("acNandBalance.txt", "r");
    if (file2 == NULL)
    {
        printf("ERROR opening acNandBalance file.\n");
        return;
    }

    char file_acnum[10];
    int balance;
    int acnum_ok = 0;

    while (fgets(line, sizeof(line), file2))
    {
        if (sscanf(line, "AccountNumber: %9[^\n]", file_acnum) == 1)
        {
            fgets(line, sizeof(line), file2); // Balance line
            sscanf(line, "Balance: %d", &balance);

            if (strcmp(acnum_input, file_acnum) == 0)
            {
                acnum_ok = 1;
                break;
            }
        }
    }

    fclose(file2);

    if (!acnum_ok)
    {
        printf("Login failed! Incorrect Account Number.\n");
        isLoggedIn = 0;
        return;
    }

    strcpy(acNumber, acnum_input);  // store globally

    printf("Login Successfully! Welcome back to your account.\n");
    isLoggedIn = 1;
}


void Bank_fetures()
{
    printf("What would you like to do today?\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Funds\n");
    printf("3. Withdraw Funds\n");
    printf("4. Transfer Funds\n");
    printf("5. View Transfer History\n");
    printf("6. Logout\n");
    printf("7. Shutdown the Application\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
}

void check_balance()
{
    if(isLoggedIn)
    {
        FILE *file = fopen("balance_file.txt", "r");
        if(file == NULL)
        {
            printf("ERROR opening balance file.\n");
            return;
        }
        float balance;
        fscanf(file, "%f", &balance);
        printf("Your current balance is: $%.2f\n", balance);
        fclose(file);
    }
    else
    {
        printf("Please login to your account to check balance.\n");
        login();
    }
}


void deposite_funds()
{
    if(isLoggedIn)
    {
        float amount;
        printf("Enter amount to deposite: ");
        scanf("%f", &amount);

        FILE *file = fopen("balance_file.txt", "r+");
        if(file == NULL)
        {
            printf("ERROR opening balance file.\n");
            return;
        }

        float balance;
        fscanf(file, "%f", &balance);

        balance += amount;

        fseek(file, 0, SEEK_SET);
        fprintf(file, "%.2f", balance);

        printf("Deposited $%.2f SUCCESSFULLY. New balance: $%.2f\n", amount, balance);

        fclose(file);
    }
}


void withdraw_funds()
{
    if(isLoggedIn)
    {
        float amount;
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);

        FILE *file = fopen("balance_file.txt", "r+");
        if(file == NULL)
        {
            printf("ERROR opening balance file.\n");
            return;
        }

        float balance;
        fscanf(file, "%f", &balance);

        if(amount > balance)
        {
            printf("Insufficient funds. Your current balance is: $%.2f\n", balance);
        }
        else
        {
            balance -= amount;
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%.2f", balance);
            printf("Withdrew $%.2f SUCCESSFULLY. New balance: $%.2f\n", amount, balance);   
        }

        fclose(file);
    }
    else
    {
        printf("Please login to your account to withdraw funds.\n");
        login();
    }
}


void trasfer_funds_between_accounts()
{
    if(isLoggedIn)
    {
        char recipient_email[50];
        float amount;

        printf("Enter recipient's Email: ");
        scanf(" %[^\n]", recipient_email);

        printf("Enter amount to transfer: ");
        scanf("%f", &amount);

        FILE *file = fopen("balance_file.txt", "r+");
        if(file == NULL)
        {
            printf("ERROR opening balance file.\n");
            return;
        }

        float balance;
        fscanf(file, "%f", &balance);

        if(amount > balance)
        {
            printf("Insufficient funds. Your current balance is: $%.2f\n", balance);
            fclose(file);
            return;
        }

        balance -= amount;
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%.2f", balance);
        fclose(file);

        printf("Transferred $%.2f to %s SUCCESSFULLY. New balance: %.2f\n", amount, recipient_email, balance);

        FILE *history = fopen("history.txt", "a");
        if(history != NULL)
        {
            fprintf(history, "Transferred $%.2f to %s | New Balance: %.2f\n", amount, recipient_email, balance);
            fclose(history);
        }
        else
        {
            printf("ERROR writing to history file.\n");
        }
    }
    else 
    {
        printf("Please login to your account to transfer funds.\n");
        login();
    }
}


void view_transfer_history()
{
    if(isLoggedIn)    
    {
        //Working on
    }
}
