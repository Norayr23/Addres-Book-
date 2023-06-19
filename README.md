# Addres-Book-
Address book in c++
Compilation for Users

If you are a user and want to run the Address Book program, follow these steps to compile the source code:
Prerequisites

Compilation Steps

    Download the source code from the GitHub repository. You can do this by clicking on the green "Code" button and selecting "Download ZIP" or by      cloning the repository using Git:
    Download contacts.txt file and save it in same directory whith AdressBook.cpp

    shell

git clone https://github.com/your-username/address-book.git

Extract the downloaded ZIP file (if applicable) and navigate to the project directory:

shell

cd address-book

Compile the source code using a C++ compiler. Below are a few examples of common compilers:

    Using g++:

    shell

g++ AddressBook.cpp -o address-book

Using clang++:

shell

        clang++ AddressBook.cpp -o address-book

    After successful compilation, an executable file named address-book (or address-book.exe on Windows) will be created in the current directory.

Usage

Once you have compiled the Address Book program, follow these steps to run it:

    Open a terminal or command prompt.

    Navigate to the directory where the executable file address-book is located.

    Run the program by entering the following command:

    shell

    ./address-book

    The program will display the current list of contacts, if any.

    Choose one of the following options:
        Enter 1 to add a new contact.
        Enter 2 to delete a contact.
        Enter 3 to search for a contact.
        Enter 4 to modify an existing contact.
        Enter 5 to exit the program.

    Follow the prompts and provide the required information based on your chosen option.

    The program will save any changes to the "contacts.txt" file.
    Please note that the "contacts.txt" file  should not be modified   manually without using the program.

Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

