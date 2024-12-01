# DES-encryption-algorithm-implementation
Implementing DES encryption algorithm in C++

# DES Encryption Algorithm in C++

This project is a C++ implementation of the **Data Encryption Standard (DES)**, a symmetric-key algorithm for secure data encryption. It is designed to provide a foundational understanding of encryption mechanisms and showcases how DES operates.

## Project Structure

```
DES_Cryptography/
├── example/
│   └── main.cpp           # Example program demonstrating library usage
├── include/
│   ├── DES_constants.h    # Constants for DES cryptography
│   ├── DES_functions.h    # Function declarations (public API)
│   └── DES_templates.h    # Templates
├── src/
│   └── DES_functions.cpp  # Function implementations 
├── CMakeLists.txt         # CMake build configuration
└── run.ps1                # PowerShell script to automate build
```

## Features

- **Encryption and Decryption:** Implements core DES functions for data encryption and decryption.
- **Modern C++ Standards:** Built with C++23, leveraging modern language features for clarity and performance.
- **Modular Design:** Organized with separate directories for headers and source files for better maintainability.
- **Designed as Library**: The project is structured to function as a reusable library.

## TODOs
- Add functionality to encrypt and decrypt strings.
- Handle file encryption.

## Prerequisites
CMake 3.10 or newer.
A C++23 compatible compiler.

