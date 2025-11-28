#include <stdio.h>
#include <string.h>

void welcome_message();
void creat_account_in_AC_file();
void login();

int isLoggedIn = 0;


int main()
{
    welcome_message();

    //working on!

}


void welcome_message()
{
     int account;
    printf("Welcome to daily C Bank\n");
    printf("Your trusted partner in financial service.\n");
    printf("We offer a range od service to meet your banking needs.\n");
    printf("Do you have a ACCOUNT with us?\n 1. YES\n 2.NO\n");
    scanf("%d", &account);
    if(account == 1)
    {
        printf("Welcome back! Please Login to your account.\n");
        login();
    }
    else 
    {
        printf("Great! Please proceed to create your account.\n Fill in the necessary details.\n");
        creat_account_in_AC_file();
    }
}

void creat_account_in_AC_file()
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
    scanf(" %[^\n]s", name);
    printf("Enter your Address: ");
    scanf(" %[^\n]s", address);
    printf("Enter your phon Number: ");
    scanf(" %[^\n]s", phon);
    printf("Enter your Email: ");
    scanf(" %[^\n]s", email);
    printf("Create a Password: ");
    scanf(" %[^\n]s", password);
    fprintf(file, "Name: %s\nAddress: %s\nPhon Number: %s\nEmail: %s\nPassword: %s\n\n", name, address, phon, email, password);
    printf("Account created successfully! You can now login to your account.\n");
    fclose(file);
}

void login()
{
    char email[50], password[20];
    printf("Enter your Email: ");
    scanf(" %[^\n]s", email);
    printf("Enter your Account password: ");
    scanf(" %[^\n]s", password);

    FILE *file = fopen("AC_file.txt", "r");
    if(file == NULL)
    {
        printf("ERROR opening file.\n");
        return;
    }
    char file_email[50], file_password[20];
    int found = 0;
    while(fscanf(file, "Name: %*[^\\n]\\nAddress: %*[^\\n]\\nPhon Number: %*[^\\n]\\nEmail: %49[^\n]\\nPassword: %19[^\n]\\n\n", file_email, file_password))
    {
        if(strcmp(email, file_email) == 0 & strcmp(password, file_password) == 0)
        {
            found = 1;
            break;
        }
    }

    if(found)
    {
        printf("Login successful! Welcome back to your account.\n");
        isLoggedIn = 1;
    }
    else
    {
        printf("Login failed! Incorrect Email or Password.\n");
    }
    fclose(file);
}

void logout()
{
    if(isLoggedIn)
    {
        isLoggedIn = 0;
        printf("You have been logged out SUCCESSFULLY.\n");
    }
    else
    {
        printf("You are not logged in.\n");
    }
}

void Bank_fetures()
{
    if(isLoggedIn)    
    {
        printf("What would you like to do today?\n\n\n");
        printf("1. Check Balance\n");
        printf("2. Deposite Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Transfer Funds\n");
        printf("5. View transfer history\n");
        printf("6. Logout\n");
    }
}

void check_balance_form_balance_file()
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

void deposite_funds_to_balance_file()
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

void withdraw_funds_from_balance_file()
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
            fclose(file);
        }
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
        scanf(" %[^\n]s", recipient_email);
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
        }
        else
        {
            balance -= amount;
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%.2f", balance);
            printf("Transferred $%.2f to %s SUCCESSFULLY. New balance: $%.2f\n", amount, recipient_email, balance);
            fclose(file);
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
        printf("Working on!");
    }
}