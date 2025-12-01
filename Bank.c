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
    printf("We offer a range od service to meet your banking needs.\n");
    printf("Do you have a ACCOUNT with us?\n1. YES\n2. NO\n");
    scanf("%d", &account);

    if(account == 1)
    {
        printf("Welcome back! Please Login to your account.\n");
        login();
    }
    else 
    {
        printf("Great! Please proceed to create your account.\nFill in the necessary details.\n");
        creat_account();
    }
}


void creat_account()
{
    char name[50];
    char address[100];
    char phon[50];
    char email[50];
    char password[20];

    FILE *file = fopen("AC_file.txt", "a");
    if(file == NULL)
    {
        printf("ERROR opening file.\n");
        return;
    }

    printf("Enter your Name: ");
    scanf(" %[^\n]", name);

    printf("Enter your Address: ");
    scanf(" %[^\n]", address);

    printf("Enter your phon Number: ");
    scanf(" %[^\n]", phon);

    printf("Enter your Email: ");
    scanf(" %[^\n]", email);

    printf("Create a Password: ");
    scanf(" %[^\n]", password);

    fprintf(file, "Email: %s\nPassword: %s\n\n", email, password);

    printf("Account created successfully! You can now login to your account.\n");
    fclose(file);
}



void login()
{
    char email[50], password[20];

    printf("Enter your Email: ");
    scanf(" %[^\n]", email);

    printf("Enter your Account password: ");
    scanf(" %[^\n]", password);

    FILE *file = fopen("AC_file.txt", "r");
    if(file == NULL)
    {
        printf("ERROR opening file.\n");
        return;
    }

    char line[200];
    char file_email[50], file_password[20];
    int found = 0;

    while(fgets(line, sizeof(line), file))
    {
        if(sscanf(line, "Email: %49[^\n]", file_email) == 1)
        {
            fgets(line, sizeof(line), file);  
            sscanf(line, "Password: %19[^\n]", file_password);

            if(strcmp(email, file_email) == 0 && strcmp(password, file_password) == 0)
            {
                found = 1;
                break;
            }
        }
    }

    fclose(file);

    if(found)
    {
        printf("Login Successfully! Welcome back to your account.\n");
        isLoggedIn = 1;
    }
    else
    {
        printf("Login failed! Incorrect Email or Password.\n");
    }
}



void Bank_fetures()
{
    printf("What would you like to do today?\n");
    printf("1. Check Balance\n");
    printf("2. Deposite Funds\n");
    printf("3. Withdraw Funds\n");
    printf("4. Transfer Funds\n");
    printf("5. View transfer history\n");
    printf("6. Logout\n");
    printf("7. Shutdown the application.\n");
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
