# ATM Simulator

## Overview

The ATM Simulator is a command-line application designed to mimic the functionality of an automated teller machine (ATM). It allows users to register, log in, perform transactions, and manage their accounts. This project demonstrates basic concepts of file handling, user authentication, and data management in C++.

## Features

- **User Registration**: Register new users with a name, account number, PIN, and initial balance.
- **Login**: Authenticate users using their account number and PIN.
- **Transactions**: Perform deposit and withdrawal transactions.
- **PIN Management**: Change user PIN.
- **Account Management**: View account details and balance.

## Project Structure

- `include/`
  - `ATM.h`: Class definition for the ATM.
  - `User.h`: Class definition for the User.
  - `utilities.h`: Function declarations for utility functions.
- `src/`
  - `ATM.cpp`: Implementation of the ATM class.
  - `User.cpp`: Implementation of the User class.
  - `utilities.cpp`: Implementation of utility functions.
  - `main.cpp`: Entry point of the application.
- `user_cred.csv`: Sample CSV file for storing user credentials.

## Dependencies

This project requires a C++ compiler that supports C++11 or later. It uses standard libraries such as `<iostream>`, `<fstream>`, `<sstream>`, and `<iomanip>`.

## Build and Run

### Building

To build the project, you can use a C++ compiler such as `g++`. Navigate to the root directory of the project and run the following command:

```sh
g++ -std=c++11 -o atm_simulator src/*.cpp
```

This command compiles all `.cpp` files in the `src/` directory and links them into an executable named `atm_simulator`.

### Running

After building the project, you can run the executable with:

```sh
./atm_simulator
```

### Sample CSV File

The `user_cred.csv` file should follow the format:

```
Name,Account Number,PIN,Balance
John Doe,123456789012,1234,1000.00
Jane Smith,987654321098,5678,1500.00
```

Make sure to update this file with initial user data before running the simulator.

## Usage

1. **Register**: Create a new user account by providing a name, PIN, and initial balance.
2. **Login**: Enter your account number and PIN to access your account.
3. **Perform Transactions**: Deposit or withdraw money, view your balance, and change your PIN.
4. **Logout**: End your session and return to the main menu.

## Contributing

Contributions to the project are welcome! If you have suggestions or improvements, please create a pull request or open an issue.

## License

This project is licensed under the MIT License. See the [MIT LICENSE](LICENSE) file for details.
