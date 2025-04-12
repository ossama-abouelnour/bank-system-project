# bank-system-project
A modular C++ console banking system built using object-oriented principles. Includes user authentication, transaction management, currency updates, and detailed user history tracking - all through interactive terminal screens.


# 💼 Banking System CLI (C++ OOP Project)

A modular, object-oriented **banking system** built in C++ for console use. It simulates core banking functions such as user authentication, client management, money transfers, and transaction history — all through a structured terminal interface.

---

## 🧩 Features

- ✅ User Authentication with login history
- ✅ Client Account Management (add, edit, delete)
- ✅ Transactions: Deposits, Withdrawals, Transfers
- ✅ Currency rate updates
- ✅ Admin-only user management
- ✅ Persistent storage via text files
- ✅ CLI interface via modular “Screen” classes

---
Ensure data files are present

Users.txt
Clients.txt
TransfersLog.txt
LoginHistory.txt
Currencies.txt

---

🔐 Default Login Credentials
For testing or demo purposes, use:

USERNAME: User1
PASSWORD: 1234

---

📁 Project Structure
Bank Project OOP.cpp – Main program file

cls*.h – Encapsulated screen logic and application modules

.txt files – Used for data storage

---

Example modules:
clsAddNewClient.h       → Create new clients
clsTransferScreen.h     → Internal money transfers
clsUpdateUserScreen.h   → Modify existing users
clsUsersLoginHistory.h  → View login timestamps
clsWithdrawScreen.h     → Withdraw money
clsUpdateCurrencyRate.h → Edit exchange rates

---

🧠 Concepts Demonstrated

C++ OOP: Inheritance, Encapsulation, Modularity

CLI navigation using “Screen” abstraction

File I/O and persistent storage (no external database)

Separation of business logic and UI screens

Admin vs standard user access control


⚠️ Limitations
❌ Simple encryption for stored data

❌ No concurrent user support (single-user CLI)

❌ Not intended for production banking systems

✅ Designed for educational or demonstrative purposes


📃 License
This project is licensed under the MIT License. You are free to use, modify, and distribute it.
