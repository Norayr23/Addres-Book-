#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <thread>



class AddressBook {

     enum NumericChecking {

       Add = 1,
       Delete,
       Search,
       Change,
       Exit,
       PhoneLenght = 9,
       MaxNameLength = 16,
       MinEmailLength = 5,
       MaxEmailLenght = 100,
     };
     const std::string Cancel = "4";  

    class Contact {
    public:
      std::string name;
      std::string lastName;
      std::string phoneNumber;
      std::string email;
    };

    std::vector<Contact> contacts;

    void loadFromFile(const std::string& fileName) {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cout << "Failed to open file: " << fileName << std::endl;
            return;
        }
        if (file.peek() == std::ifstream::traits_type::eof()) {
           file.close();
           return;
        }  

        Contact contact;
        while (file >> contact.name >> contact.lastName >> contact.phoneNumber >> contact.email) {
            contacts.push_back(contact);
        }


        file.close();
    }

    void saveToFile() {
        std::ofstream file("contacts.txt");

        if (!file.is_open()) {
            std::cout << "Failed to open file: " << "contacts.txt" << std::endl;
            return;
        }
      
        for (const Contact& contact : contacts) {
            file << contact.name << " " << contact.lastName << " " << contact.phoneNumber << " " << contact.email << std::endl;
        }

        file.close();
    }

    void printContacts() {
        std::cout << "Address Book:\n" << std::endl;
        if (contacts.size() == 0) {
           return;
        }
        size_t nameWidth = 0, lastNameWidth = 0;
        for (const Contact& contact : contacts) {
            nameWidth = std::max(nameWidth, contact.name.length());
            lastNameWidth = std::max(lastNameWidth, contact.lastName.length());
        }
        nameWidth += lastNameWidth;

        std::cout << "Name";
        std::cout << std::string(nameWidth + (nameWidth - 4) + 1, ' ');
        std::cout << "Phone";
        std::cout << std::string(PhoneLenght, ' ');
        std::cout << "Email\n\n";

        for (const Contact& contact : contacts) {
            std::cout << contact.name << " " << contact.lastName;
            std::cout << std::string(nameWidth + (nameWidth - (contact.name.length() + contact.lastName.length() + 1)), ' ');
            std::cout << contact.phoneNumber;
            std::cout << std::string(5, ' ');
            std::cout << contact.email;
            std::cout << std::endl;
        }
    }

    bool isNameValid(const std::string& str) {
        if(str.length() > MaxNameLength) {
            return false;
        }
        for (char ch : str) {
            if ((ch < 'A' || ch > 'Z') && (ch < 'a' || ch > 'z')) {
                return false;
            }
        }
        return true;
    }

    bool isPhoneValid(const std::string& phone) {
        if (phone.length() != PhoneLenght) {
            return false;
        }
        for (char ch : phone) {
            if (ch < '0' || ch > '9') {
                return false;
            }
        }
        return true;
    }

    bool isEmailValid(const std::string& email) {
        if (email.length() < MinEmailLength || email.length() > MaxEmailLenght) {
            return false;
        }
        std::regex emailPattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
        return std::regex_match(email, emailPattern);
    }

    bool addContact() {
        Contact contact;
        std::cout << "For canceling the process, enter 4." << std::endl;
        std::string name;
        std::cout << "Enter contact name (maximum 16 characters): ";
        std::cin >> name;
        if (name == Cancel) {
            return false;
        }
        while (!isNameValid(name)) {
            std::cout << "Invalid name. Please try again: ";
            std::cin >> name;
            if (name == Cancel) {
                return false;
            }
        }
        contact.name = name;

        std::string lastName;
        std::cout << "Enter contact last name (maximum 15 characters): ";
        std::cin >> lastName;
        if (lastName == Cancel) {
            return false;
        }
        while (!isNameValid(lastName)) {
            std::cout << "Invalid last name. Please try again: ";
            std::cin >> lastName;
            if (lastName == Cancel) {
                return false;
            }
        }
        contact.lastName = lastName;

        std::string phone;
        std::cout << "Enter contact phone number (098......): ";
        std::cin >> phone;
        if (phone == Cancel) {
            return false;
        }
        while (!isPhoneValid(phone)) {
            std::cout << "Invalid phone number. Please try again: ";
            std::cin >> phone;
            if (phone == Cancel) {
                return false;
            }
        }
        contact.phoneNumber = phone;

        std::string email;
        std::cout << "Enter contact email: ";
        std::cin >> email;
        if (email == Cancel) {
            return false;
        }
        while (!isEmailValid(email)) {
            std::cout << "Invalid email. Please try again: ";
            std::cin >> email;
            if (email == Cancel) {
                return false;
            }
        }
        contact.email = email;

        contacts.push_back(contact);
        saveToFile();
        return true;
    }

    void deleteContact(std::string inputName = "") {
        std::string name;
       if (inputName  != "") {
          name = inputName;
       }
       else {
         std::cout << "Enter the name of the contact you want to delete: ";
         std::cin.ignore();
         std::getline(std::cin, name);
       }
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it -> name == name) {
               if (inputName != "") {
                  std::cout << "Do you want save changes " << name << " (y/n) :";
               }
               else {
                std::cout << "Do you want delete contact " << name << " (y/n) :";
               } 
                char answer;
                std::cin >> answer;
                if (answer == 'y') {
                contacts.erase(it);
                saveToFile();
                if (inputName != "") {
                   std::cout << "Contact changed successfully!" << std::endl;
                }
                else {
                std::cout << "Contact deleted successfully!" << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
                
                }
            }
        }

        std::cout << "Contact not found" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    void searchContact() {
         std::cout << "Please enter contact name : ";
         std::string name;
         std::cin.ignore();
         std::getline(std::cin, name);
         for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it -> name == name) {
                std::cout << it -> name << "  " << it -> lastName << "  " << it -> phoneNumber << "  " << it -> email << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
            
                            
         }
         std::cout << "Contact not found" << std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(1));
              

    }
    void changeContact() {
         std::cout << "Please enter contact name : ";
         std::string name;
         std::cin.ignore();
         std::getline(std::cin, name);
         for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it -> name == name) {
                std::cout << it -> name << "  " << it -> lastName << "  " << it -> phoneNumber << "  " << it -> email << std::endl;
                std::cout << std::endl;
                if (addContact()) {
                   deleteContact(name);
                }
                return;
            }
            
                            
         }
         std::cout << "Contact not found" << std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(1));

    }

public:
    void run() {
        loadFromFile("contacts.txt");

        while (true) {
            system("clear");
            printContacts();

            std::cout << "\n1: Add contact  2: Delete contact 3: Search contact 4: Change contact 5: Exit" << std::endl;
            int input;
            std::cin.clear();
            std::cin >> input;

            if (input == Exit) {
                std::string answer;
                std::cout << "Do you want to exit the program? (y/n): ";
                std::cin >> answer;
                if (answer == "y") {
                    break;
                }
                continue;
            }

            if (input == Add) {
                addContact();
            }

            else if (input == Delete) {
                deleteContact();
            }
            else if (input == Search) {
                searchContact();
            }
            else if (input == Change) {
               changeContact();
            }
            else {
                std::cout << "ivailid input" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        
    }
};

int main() {
    AddressBook addressBook;
    addressBook.run();

    return 0;
}

