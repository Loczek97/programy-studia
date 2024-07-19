#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

class Authenticator;

class userData {
    string password;
public:
    string login;

    userData(string p_login, string p_password) : login(p_login), password(p_password) {};
    userData() {};

    friend class Authenticator;
};


class Authenticator {
private:
    string databaseName;
    vector<userData> users;

    bool compareLoginData(userData userInput, userData user)
    {
        return userInput.login == user.login && userInput.password == user.password;
    };

    bool getUsersData() {
        users.clear();

        fstream file;

        file.open(databaseName, ios::in);

        if (!file.good()) {
            file.close();
            return false;
        }

        string login, password;
        while(file >> login >> password) {
            userData newUser(login, password);
            users.emplace_back(newUser);
        }

        file.close();

        return true;
    }

public:
    bool isDataGood;
    bool isUserLoggedIn;
    userData currentUser;

    Authenticator(string p_databaseName) {
        this->databaseName = p_databaseName;
        this->isUserLoggedIn = false;

        if (this->getUsersData())  this->isDataGood = true;
        else this->isDataGood = false;
    }

    ~Authenticator() {
        this->users.clear();
    }

    bool addUser(userData newUser) {
        fstream file;
        file.open(this->databaseName, ios::app);

        if (!file.good()) {
            file.close();
            return false;
        }

        file << newUser.login << " " << newUser.password << endl;

        file.close();

        this->users.push_back(newUser);

        return true;

    }

    bool loginUser(userData userInput) {
        for (auto &user : users) {
            if (this->compareLoginData(userInput, user)) {

                this->currentUser.login = user.login;
                this->currentUser.password = user.password;
                this->isUserLoggedIn = true;

                return true;
            }
        }
        return false;
    }

    void logout() {
        this->isUserLoggedIn = false;
    }


    void displayUsers() const {
        for (auto& user : this->users) {
            cout << "Login: " << user.login << " Password: " << user.password << endl;
        }
    }

    string getUserName() { return this->currentUser.login; };
};

int main()
{
    string dbname = "database.txt";

    Authenticator auth(dbname);

    if (!auth.isDataGood) {
        cout << "Cannot open database!" << endl;
        return 0;
    }


    int choice;

    while (true)
    {
        cout << "===========================================" << endl;
        cout << "    1. Login user" << endl;
        cout << "    2. Register user" << endl;
        cout << "    3. Logout" << endl;
        cout << "    4. Display users" << endl;
        cout << "    5. Show current user" << endl;
        cout << "    0. Close program" << endl;
        cout << "===========================================" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1: {
            string userLogin, userPassword;
            cout << "Login: ";
            cin >> userLogin;
            cout << "Password: ";
            cin >> userPassword;

            userData userToLogIn(userLogin, userPassword);

            if (auth.loginUser(userToLogIn)) cout << "User logged in properly!" << endl;
            else cout << "Login or password invalid." << endl;
            break;
        }
        case 2: {
            string userLogin, userPassword, confirmedPassword;
            cout << "Login: ";
            cin >> userLogin;
            cout << "Password: ";
            cin >> userPassword;
            cout << "Confirm password: ";
            cin >> confirmedPassword;

            if (userPassword != confirmedPassword) {
                cout << "Password not confirmed properly.";
                break;
            }

            userData newUser(userLogin, userPassword);

            if (auth.addUser(newUser)) cout << "User registered successfully!" << endl;
            else cout << "Cannot register user." << endl;
            break;
        }
        case 3: {
            if (auth.isUserLoggedIn) {
                auth.logout();
                cout << "User logged out." << endl;
            }
            else cout << "No user logged in." << endl;
            break;
        }
        case 4: {
            auth.displayUsers();
            break;
        }

        case 5: {
            if (auth.isUserLoggedIn) cout << "Current user login: " << auth.getUserName() << endl;
            else cout << "No user logged in." << endl;
            break;
        }
        case 0: {
            cout << "Program closing." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }


    cout << "Hello world!" << endl;
    return 0;
}
