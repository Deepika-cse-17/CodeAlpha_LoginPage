#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;
string getHiddenPassword();  

void registerUser()
 {
    string username, password;

    cout << "\n  Registration\n";
    cout << "Enter a username: ";
    cin >> username;

    // Check for duplicate username
    ifstream checkFile("users/" + username + ".txt");
    if (checkFile) {
        cout << " Username already exists. Try another.\n";
        return;
    }

    cout << "Enter a password: ";
    password = getHiddenPassword();

    // Save credentials
    ofstream userFile("users/" + username + ".txt");
    userFile << username << endl << password;
    userFile.close();

    cout << " Registration successful!\n";
}

void loginUser() {
    string username, password, storedUser, storedPass;

    cout << "\n  Login\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    password = getHiddenPassword();

    ifstream userFile("users/" + username + ".txt");
    if (!userFile) {
        cout << " No such user found.\n";
        return;
    }

    getline(userFile, storedUser);
    getline(userFile, storedPass);

    if (username == storedUser && password == storedPass) {
        cout << "  Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "  Invalid username or password.\n";
    }
}    
string getHiddenPassword() 
{
      string password;
      char ch;

      while (true)
      {
         ch = _getch(); // Read a character without echoing it

         if (ch == 13)
          { // Enter key
            cout << endl;
            break;
         }
          else if (ch == 8 && !password.empty()) 
           { // Backspace
            password.pop_back();
            cout << "\b \b";
           }
            else if (isprint(ch)) 
            {
            password += ch;
            cout << '*';
            }
      }

        return password;
 }

int main() {
    int choice;

    // Ensure 'users' folder exists (for basic usage, create it manually)
    system("mkdir users >nul 2>&1"); // Windows command, ignored if already exists

    while (true) {
        cout << "\n===== User System Menu =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}
