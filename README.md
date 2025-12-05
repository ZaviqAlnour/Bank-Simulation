# Daily C Bank - C Console Banking Simulation

This is a **simple console-based banking system** written in C. It allows users to:

- Create accounts with personal details and initial deposit
- Login with email, password, and account number
- Check balance
- Deposit funds
- Withdraw funds
- Transfer funds between accounts
- View transaction history
- Logout and exit

---

## Project Overview

This project is a **human-AI collaborative effort**. While AI was used to assist in writing and structuring the code, the **design decisions, system features, and implementation were entirely conceived and reviewed by me**. Using AI in coding is not a shortcut — it is a **tool to help structure, optimize, and accelerate development** while keeping your vision and system design clear.

Key points about this project:

- Each user has a **unique account number** and a separate **transaction history file**.
- Balances are stored in `acNandBalance.txt`.
- Transaction history for deposits, withdrawals, and transfers is stored in **per-user files**.
- AI assistance was used to help write functions and structure the program, but **all logic, features, and design were manually reviewed and implemented**.
- This project demonstrates that coding is not just about syntax — it is about **system design, strong fundamentals, and keeping your vision alive**.

---

## Features

1. **Account Creation:** Users can create accounts with personal details, choose an account number (less than 8 characters), and deposit a minimum of $1000.  
2. **Login:** Users login with **email, password, and account number**.  
3. **Check Balance:** View the current balance.  
4. **Deposit Funds:** Deposit money into the account and record it in the user’s transaction history.  
5. **Withdraw Funds:** Withdraw money from the account and update the transaction history.  
6. **Transfer Funds:** Transfer money to another user’s account and record transactions for both sender and recipient.  
7. **View Transaction History:** Each user has a separate file recording all deposits, withdrawals, and transfers.  
8. **Logout:** Securely logout of the account.  

---

## Usage

1. **Clone the repository:**  
   ```bash
   git clone https://github.com/ZaviqAlnour/Bank-Simulation.git
Compile the code using a C compiler (e.g., gcc):

bash
Copy code
gcc main.c -o bank
Run the program:

bash
Copy code
./bank   # Linux / Mac
bank.exe # Windows
Follow the on-screen instructions to create an account, login, and use the banking features.

Philosophy
Using AI to assist in coding is a superpower. It allows you to:

Build complex systems faster

Focus on system design and strong fundamentals

Keep your vision alive while implementing features

Review and refine code before publishing

It’s not about just learning syntax — it’s about learning to design, create, and manage systems effectively.


Thank you for exploring this project. Remember, combining human creativity with AI assistance can help you build anything great while maintaining control over your system design and vision.