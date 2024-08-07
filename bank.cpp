#include <bits/stdc++.h>

#define MAX_ACCOUNTS 10
#define HASH_TABLE_SIZE 20
using namespace std;

// Structure for a bank account
struct BankAccount
{
    char accountNumber[20];
    char name[100];
    float balance;
};

// Structure for a node in a binary search tree (BST)
struct BSTNode
{
    BankAccount account;
    BSTNode *left;
    BSTNode *right;
};

// Structure for the hash table
struct HashTable
{
    BSTNode *table[HASH_TABLE_SIZE];
};

// Function to initialize the hash table
HashTable* initializeHashTable()
{
    HashTable* hashTable = new HashTable();
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        hashTable->table[i] = nullptr;
    }
    return hashTable;
}

// Function to hash the account number
int hashFunction(const char accountNumber[])
{
    int sum = 0;
    for (int i = 0; accountNumber[i] != '\0'; ++i)
    {
        sum += accountNumber[i];
    }
    return sum % HASH_TABLE_SIZE;
}

// Function to insert a bank account into the hash table
void insertIntoHashTable(HashTable* hashTable, BankAccount acc)
{
    int index = hashFunction(acc.accountNumber);
    BSTNode* newNode = new BSTNode();
    newNode->account = acc;
    newNode->left = nullptr;
    newNode->right = nullptr;
    if (hashTable->table[index] == nullptr)
    {
        hashTable->table[index] = newNode;
    }
    else
    {
        BSTNode* temp = hashTable->table[index];
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        temp->right = newNode;
    }
}

// Function to search for a bank account by account number in the hash table
BSTNode* searchHashTable(HashTable* hashTable, const char accNum[])
{
    int index = hashFunction(accNum);
    BSTNode* temp = hashTable->table[index];
    while (temp != nullptr)
    {
        if (strcmp(temp->account.accountNumber, accNum) == 0)
        {
            return temp;
        }
        temp = temp->right;
    }
    return nullptr; // Account not found
}

// Function to display all accounts in the BST
void displayBSTAccounts(BSTNode* root)
{
    if (root != nullptr)
    {
        displayBSTAccounts(root->left);
        cout << "Account Number: " << root->account.accountNumber << ", Holder's Name: " << root->account.name << ", Balance: " << root->account.balance << std::endl;
        displayBSTAccounts(root->right);
    }
}

// Function to display all accounts in the hash table (including BST accounts)
void displayAllAccounts(HashTable* hashTable)
{
    cout << "\nAll Accounts:\n";
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        BSTNode* temp = hashTable->table[i];
        while (temp != nullptr)
        {
            cout << "Account Number: " << temp->account.accountNumber << ", Holder's Name: " << temp->account.name << ", Balance: " << temp->account.balance << std::endl;
            displayBSTAccounts(temp->left);
            temp = temp->right;
        }
    }
}

// Function to search for accounts by account holder's name
void searchByName(HashTable* hashTable, const char name[])
{
    cout << "\nAccounts with Holder's Name '" << name << "':\n";
    bool found = false;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        BSTNode* temp = hashTable->table[i];
        while (temp != nullptr)
        {
            if (strcmp(temp->account.name, name) == 0)
            {
                cout << "Account Number: " << temp->account.accountNumber << ", Holder's Name: " << temp->account.name << ", Balance: " << temp->account.balance << std::endl;
                found = true;
            }
            temp = temp->right;
        }
    }
    if (!found)
    {
        cout << "No accounts found with this name.\n";
    }
}

// Function to create a new bank account
BankAccount createAccount()
{
    BankAccount acc;
    cout << "Enter account number: ";
    cin >> acc.accountNumber;
    cout << "Enter account holder's name: ";
    cin >> acc.name;
    cout << "Enter initial balance: ";
    cin >> acc.balance;
    return acc;
}

// Function to deposit money into an account
void deposit(BankAccount* acc, float amount)
{
    acc->balance += amount;
    cout << "Amount " << amount << " deposited successfully.\n";
}

// Function to withdraw money from an account
void withdraw(BankAccount* acc, float amount)
{
    if (amount <= acc->balance)
    {
        acc->balance -= amount;
        cout << "Amount " << amount << " withdrawn successfully.\n";
    }
    else
    {
        cout << "Insufficient balance.\n";
    }
}

// Function to check account balance
void checkBalance(const BankAccount& acc)
{
    cout << "Account Number: " << acc.accountNumber << std::endl;
    cout << "Account Holder Name: " << acc.name << std::endl;
    cout << "Current Balance: " << acc.balance << std::endl;
}

int main()
{
    char choose;
    system("clear");
    HashTable* hashTable = initializeHashTable();
    int numAccounts = 0;
    int choice;
    cout << "*****************************************\n";
    cout << "* *\n";
    cout << "* WELCOME TO BANKING SYSTEM *\n";
    cout << "* *\n";
    cout << "*****************************************\n";

  
    do{
        cout << "\nBank Account Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Search Account by Name\n";
        cout << "6. Display All Accounts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (numAccounts < MAX_ACCOUNTS)
            {
                BankAccount newAcc = createAccount();
                insertIntoHashTable(hashTable, newAcc);
                numAccounts++;
            }
            else
            {
                cout << "Maximum accounts limit reached.\n";
            }
            break;
        case 2:
        {
            char accNum[20];
            float amount;
            cout << "Enter account number: ";
            cin >> accNum;
            BSTNode* accNode = searchHashTable(hashTable, accNum);
            if (accNode != nullptr)
            {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                deposit(&(accNode->account), amount);
            }
            else
            {
                cout << "Account not found.\n";
            }
            break;
        }
        case 3:
        {
            char accNum[20];
            float amount;
            cout << "Enter account number: ";
            cin >> accNum;
            BSTNode* accNode = searchHashTable(hashTable, accNum);
            if (accNode != nullptr)
            {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                withdraw(&(accNode->account), amount);
            }
            else
            {
                cout << "Account not found.\n";
            }
            break;
        }
        case 4:
        {
            char accNum[20];
            cout << "Enter account number: ";
            cin >> accNum;
            BSTNode* accNode = searchHashTable(hashTable, accNum);
            if (accNode != nullptr)
            {
                checkBalance(accNode->account);
            }
            else
            {
                cout << "Account not found.\n";
            }
            break;
        }
        case 5:
        {
            char searchName[100];
            cout << "Enter account holder's name to search: ";
            cin >> searchName;
            searchByName(hashTable, searchName);
            break;
        }
        case 6:
            displayAllAccounts(hashTable);
            break;
        case 7:
            cout << "Exiting...\n";
            delete hashTable;
            exit(0);
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
        cout<<"Do you want to continue:";
        cin >> choose;

    }while(choose == 'y'|| choose == 'Y');
    return 0;
}
