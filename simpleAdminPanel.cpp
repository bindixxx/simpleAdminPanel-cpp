#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <cstdlib>
#include <windows.h> 

using namespace std;

struct User {
    string username;
    string password;

    User(const string& user, const string& pass) : username(user), password(pass) {
        cout << "User created: " << username << endl;
    }

    ~User() {
        cout << "User deleted: " << username << endl;
    }
};

class AdminPanel {
private:
    vector<User> users;

public:
    AdminPanel() {
        cout << "Admin panel initialized!" << endl;
    }

    ~AdminPanel() {
        cout << "Admin panel shutting down..." << endl;
    }

    void addUser(const string& username, const string& password) {
        users.push_back(User(username, password));
        cout << "User added: " << username << endl;
    }

    void removeUser(const string& username) {
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].username == username) {
                users.erase(users.begin() + i);
                cout << "User removed: " << username << endl;
                return;
            }
        }
        cout << "User not found: " << username << endl;
    }

    void listUsers() const {
        if (users.empty()) {
            cout << "No users available." << endl;
        }
        else {
            cout << "List of users:" << endl;
            for (const auto& user : users) {
                cout << "Username: " << user.username << endl;
            }
        }
    }

    bool login(const string& username, const string& password) const {
        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                cout << "Login successful!" << endl;
                return true;
            }
        }
        cout << "Invalid username or password." << endl;
        return false;
    }

    string getDesktopPath() {
        char* desktopPath = nullptr;
        size_t len = 0;

        _dupenv_s(&desktopPath, &len, "USERPROFILE");
        string path(desktopPath);
        free(desktopPath);

        path += "\\Desktop\\";
        return path;
    }

    void createFileOnDesktop(const string& filename) {
        string desktopPath = getDesktopPath() + filename;

        ofstream file(desktopPath);
        if (file.is_open()) {
            file << "This is a test file created by Admin Panel." << endl;
            file.close();
            cout << "File created on Desktop: " << filename << endl;
        }
        else {
            cout << "Unable to create file." << endl;
        }
    }
};

int main() {
    AdminPanel adminPanel;
    int choice;
    string username, password, filename;

    do {
        cout << "\nAdmin Panel Menu:\n";
        cout << "1. Add User\n";
        cout << "2. Remove User\n";
        cout << "3. List Users\n";
        cout << "4. Login\n";
        cout << "5. Create File on Desktop\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            adminPanel.addUser(username, password);
            break;
        case 2:
            cout << "Enter username to remove: ";
            cin >> username;
            adminPanel.removeUser(username);
            break;
        case 3:
            adminPanel.listUsers();
            break;
        case 4:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            adminPanel.login(username, password);
            break;
        case 5:
            cout << "Enter filename to create on Desktop: ";
            cin >> filename;
            adminPanel.createFileOnDesktop(filename);
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
