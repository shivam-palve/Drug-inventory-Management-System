#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Class to represent a pharmaceutical drug
class Drug {
public:
    string name;
    string manufacturer;
    int quantity;
    string expiryDate;

    // Constructor
    Drug(string name, string manufacturer, int quantity, string expiryDate)
        : name(name), manufacturer(manufacturer), quantity(quantity), expiryDate(expiryDate) {}

    // Display drug information
    void display() {
        cout << "Name: " << name << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Expiry Date: " << expiryDate << endl;
    }
};

// Function to add a new drug to the inventory
void addDrug(vector<Drug>& inventory) {
    string name, manufacturer, expiryDate;
    int quantity;

    cout << "Enter Drug Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Manufacturer: ";
    getline(cin, manufacturer);

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Expiry Date (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, expiryDate);

    Drug newDrug(name, manufacturer, quantity, expiryDate);
    inventory.push_back(newDrug);

    cout << "Drug added to the inventory successfully!" << endl;
}

// Function to display all drugs in the inventory
void viewInventory(const vector<Drug>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    cout << "Inventory List:" << endl;
    for (const Drug& drug : inventory) {
        drug.display();
        cout << "-----------------------" << endl;
    }
}

// Function to save inventory data to a file
void saveInventoryToFile(const vector<Drug>& inventory, const string& filename) {
    ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const Drug& drug : inventory) {
            outFile << drug.name << "," << drug.manufacturer << ","
                    << drug.quantity << "," << drug.expiryDate << endl;
        }

        outFile.close();
    } else {
        cout << "Error: Unable to open the file for writing." << endl;
    }
}

// Function to load inventory data from a file
void loadInventoryFromFile(vector<Drug>& inventory, const string& filename) {
    ifstream inFile(filename);

    if (inFile.is_open()) {
        inventory.clear();

        string line;
        while (getline(inFile, line)) {
            string name, manufacturer, expiryDate;
            int quantity;

            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            name = line.substr(0, pos1);
            manufacturer = line.substr(pos1 + 1, pos2 - pos1 - 1);
            quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            expiryDate = line.substr(pos3 + 1);

            Drug drug(name, manufacturer, quantity, expiryDate);
            inventory.push_back(drug);
        }

        inFile.close();
    } else {
        cout << "Error: Unable to open the file for reading." << endl;
    }
}

int main() {
    vector<Drug> inventory;

    // Load inventory data from file (if available)
    loadInventoryFromFile(inventory, "inventory.txt");

    int choice;
    do {
        cout << "Pharmaceutical Inventory Management System" << endl;
        cout << "1. Add Drug" << endl;
        cout << "2. View Inventory" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addDrug(inventory);
                break;
            case 2:
                viewInventory(inventory);
                break;
            case 3:
                // Save inventory data to file before exiting
                saveInventoryToFile(inventory, "inventory.txt");
                cout << "Exiting the program. Inventory data saved." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 3);

    return 0;
}
