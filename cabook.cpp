#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include<vector>
#include <sstream>
using namespace std;
const string admin_pass="root123";
struct node{
    int data;
    int id;
    node *next=NULL;
    node(int x){
        data=x;
    } 
};
class category{
    // consist of the menus and stored info which is used just to display
    public:
    void user(){
        cout<<"\n\n1.Admin"<<endl;
        cout<<"2.User\n"<<endl;
    }
    void start(){
        cout<<"\n\n1.login"<<endl;
        cout<<"2.signup\n"<<endl;
    }
    void admin_menu() {
    cout<<"\nADMIN MENU\n\n";
    cout<<"1. View Bookings\n";
    cout<<"2. Delete Account\n";
    cout<<"3. Cancel Booking\n";
    cout<<"4. Exit\n\n";
    }
    void menu(){
        cout<<"\nMENU\n\n";
        cout<<"1.Routes and Buses"<<endl;
        cout<<"2.Book a seat"<<endl;
        cout<<"3.Your Account"<<endl;
        cout<<"4.Support"<<endl;
        cout<<"5.Exit\n"<<endl;
    }
    void showroutes(){
        cout << "Routes:\n";
        cout << "BusNo    From       To    Duration(hr)    Fare(Rs)\n";
        cout<<"1       delhi     manali       5            2300\n";
        cout<<"2       mumbai     pune        7            4600\n";
        cout<<"3      lucknow    meerut       6            1800\n";
        cout<<"4       meerut    kanpur       5            2400\n";
        cout<<"5       cochin   banglore      7            3000\n";
        cout<<"6       indore     pune        10           2800\n";
        cout<<"7       mumbai     pune        8            3300\n";
        cout<<"8        pune     nagpur       4            2100\n";
        cout<<"9       meerut     agra        5            2900\n";
        cout<<"10      mumbai     pune        6            2400\n";
        cout<<"11      meerut    kanpur       9            2350\n";
        cout<<"12      delhi     meerut       5            2200\n";
        cout<<"13      delhi     manali       7            2100\n";
        cout<<"14     varanasi  ghaziabad     10           2200\n";
        cout<<"15      nagpur     pune        5            2400\n";
        
    }
    void contact(){
        cout<<"WELCOME TO SUPPORT ";
            cout<<"please enter your complaint(we will get back to you shortly)=>"<<endl;
            string h;
            cin>>h;
            ofstream writer;
            writer.open("complaints",ios::out|ios::app);
            writer<<h<<"\n";
            writer.close();
            //complaint will get written in the file 
            cout<<"if the problem continues";
        cout<<"\nCONTACT DETAILS\n\n";
        cout<<"1.Email id: cabookhelp@gmail.com "<<endl;
        cout<<"2.Mobile no. 9988776600:"<<endl;
        cout<<"Feel free to contact us any time\n"<<endl;
        
    }
    void showseats(){
        cout<<"\nSeats\n\n";
        cout<<"01  02  03  04  05"<<endl;
        cout<<"06  07  08  09  10"<<endl;
        cout<<"11  12  13  14  15"<<endl;
        cout<<"16  17  18  19  20"<<endl;
        cout<<"21  22  23  24  25"<<endl;
        cout<<"26  27  28  29  30"<<endl;
    }
    void showpayment(){
        cout<<"\nEnter Payment Method\n\n";
        cout<<"1.Credit or Debit card "<<endl;
        cout<<"2.UPI"<<endl;
    }
};
const int TABLE_SIZE = 128;
class HashNode {
public:
    string key;
    int value;
    HashNode* next;
    HashNode(string key, int value) {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
};

class HashTable {
private:
    HashNode** table;

public:
    HashTable() {
        table = new HashNode*[TABLE_SIZE]();
    }

    int hashFunction(string key) {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash + (int)key[i]) % TABLE_SIZE;
        }
        return hash;
    }

    void insert(string key, int value) {
        int hash = hashFunction(key);
        if (!table[hash]) {
            table[hash] = new HashNode(key, value);
        } else {
            HashNode* entry = table[hash];
            while (entry->next) {
                entry = entry->next;
            }
            entry->next = new HashNode(key, value);
        }
    }

    int search(string key) {
        int hash = hashFunction(key);
        if (table[hash]) {
            HashNode* entry = table[hash];
            while (entry) {
                if (entry->key == key) {
                    return entry->value;
                }
                entry = entry->next;
            }
        }
        return -1;
    }
};

class accounts {
private:
    HashTable passwordTable;
    string password;
    

public:
    string accountname;
    string fname;
    string lname;
    string phone;
    string email;

    accounts(){
        ifstream reader("Passwords",ios::in);
        string account,pass;
        while(reader>>account>>pass){
            passwordTable.insert(account,stoi(pass));
        }
        reader.close();
    }

    void signup() {
        cout << endl;
        cout << "Enter your firstname : ";
        cin >> fname;
        cout << "Enter your lastname : ";
        cin >> lname;
        cout << "Enter Account Name : ";
        cin >> accountname;
        cout << "Enter Password : ";
        cin >> password;

        // Hash the password before storing it
        int hashedPassword = hashPassword(password);
        passwordTable.insert(accountname, hashedPassword);

        do {
            cout << "Enter your phone number (10 digits only): ";
            cin >> phone;
            if (phone.length() != 10) {
                cout << "Invalid phone number. Please try again." << endl;
            }
        } while (phone.length() != 10);

        cout << "Enter your email id : ";
        cin >> email;

        ofstream writer("Details", ios::out | ios::app);
        writer << accountname << " " << password << " " << fname << " " << lname << " " << phone << " " << email << "\n";
        writer.close();

        writer.open("Passwords",ios::out | ios::app);
        writer<<accountname<<" "<< hashPassword(password)<<"\n";
        writer.close();
    }

    int login() {
        int flag = 0;
        string acc, pass;
        cout << endl;
        cout << "Enter Account Name : ";
        cin >> acc;
        cout << "Enter Password : ";
        cin >> pass;        

        int storedPassword = passwordTable.search(acc);
        if (storedPassword != -1) {
            // Hash the entered password for comparison
            int hashedEnteredPassword = hashPassword(pass);

            if (hashedEnteredPassword == storedPassword) {
                cout << "Access Granted.\n" << endl;
                accountname = acc;
                password = pass;
                ifstream reader("Details");
                string check_accountname, check_password, check_fname, check_lname, check_email, check_phone;
                while (reader >> check_accountname >> check_password >> check_fname >> check_lname >> check_phone >> check_email) {
                    if (check_accountname == acc) {
                        fname=check_fname;
                        lname=check_lname;
                        phone=check_phone;
                        email=check_email;
                        break;
                    }       
                }
                return 1;
            } else {
                cout << "Wrong Password\n" << endl;
            }
        } else {
            cout << "Account not found. Please sign up.\n";
            return -1;
        }

        return 0;
    }

    void deleteAccount() {
        string accToDelete;
        cout << "Enter the account name to delete: ";
        cin >> accToDelete;

        ifstream inFile("Details");
        ofstream outFile("TempFile");
        if (!inFile || !outFile) {
            cout << "Error opening files.\n";
            return;
        }
        string check_accountname, check_password, check_fname, check_lname, check_email, check_phone;
        while (inFile >> check_accountname >> check_password >> check_fname >> check_lname >> check_phone >> check_email) {
            if (check_accountname == accToDelete) {
                // Skip the account to be deleted
                continue;
            }
            outFile << check_accountname << " " << check_password << " " << check_fname << " "
                    << check_lname << " " << check_phone << " " << check_email << "\n";
        }
        inFile.close();
        outFile.close();

        // Remove the original file and rename the temporary file
        remove("Details");
        rename("TempFile", "Details");

        // Remove the account from the hash table
        passwordTable.search(accToDelete); 
        // To remove from the hash table
        inFile.open("Passwords");
        outFile.open("TempFile");
        if (!inFile || !outFile) {
            cout << "Error opening files.\n";
            return;
        }
        string check_acc, check_pass;
        while (inFile >> check_acc >> check_pass ) {
            if (check_acc == accToDelete) {
                // Skip the account to be deleted
                continue;
            }
            outFile << check_acc << " " << check_pass << "\n";
        }
        inFile.close();
        outFile.close();

        // Remove the original file and rename the temporary file
        remove("Passwords");
        rename("TempFile", "Passwords");

        cout << "Account " << accToDelete << " Deleted successfully.Please run the code again to reflect changes.\n";
    }

private:
    // Replace this function with a secure hashing algorithm in a real-world application
    int hashPassword(const string& password) {
        int hash = 0;
        for (char ch : password) {
            hash += static_cast<int>(ch);
        }
        return hash;
    }
};


struct Node {
    int data;
    Node *left;
    Node *right;
    int height;
    Node(int d) {
        data = d;
        left = right = NULL;
        height = 1;
        }
};

class BinaryTree {
public:
    Node *root;
//binery tree class with all the functions 
    int getHeight(Node *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node *node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node *balanceTree(Node *node, int data) {
        int balance = getBalanceFactor(node);

        if (balance > 1) {
            if (data < node->left->data) // Left-Left case
                return rightRotate(node);
            if (data > node->left->data) // Left-Right case
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balance < -1) {
            if (data > node->right->data) // Right-Right case
                return leftRotate(node);
            if (data < node->right->data) // Right-Left case
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    Node *insert(Node *node, int data) {
        if (node == nullptr)
            return new Node(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        return balanceTree(node, data);
    }

    Node *maxNode(Node *node) {
        if (node->right == nullptr) {
            return node;
        }
        return maxNode(node->right);
    }

    Node *deleteNode(Node *node, int x) {
        if (node == nullptr)
            return node;

        if (x < node->data) {
            node->left = deleteNode(node->left, x);
        } else if (x > node->data) {
            node->right = deleteNode(node->right, x);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node *temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                Node *temp = maxNode(node->left);
                node->data = temp->data;
                node->left = deleteNode(node->left, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        return balanceTree(node, x);
    }

    void inorderTraversal(Node *node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
    void readFromFile(const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file " << filename << endl;
            return;
        }

        int id;
        while (file >> id) {
            root = insert(root, id);
        }

        file.close();
    }
    void writeIntoFile(Node* node, ofstream& file) {
        if (node) {
            writeIntoFile(node->left, file);
            file << node->data << " ";
            writeIntoFile(node->right, file);
        }
    }

    void writeToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file " << filename << " for writing.\n";
            return;
        }

        writeIntoFile(root, file);

        file.close();
        cout << "Data written to file successfully.\n";
    }
    Node *getmaxnode(Node *node){
        if(node==NULL){
            return node;
        }
        if(node->right==NULL){
            return node;
        }
        return (node->right);
    }
};



class book {
public:
int generateid() {
//helps generate the booking id 
    int id;
    fstream file("Booking_ids", ios::in | ios::out | ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file!" << std::endl;
        return -1;
    }

    BinaryTree obj;
    obj.readFromFile("Booking_ids");

    if (obj.root == nullptr) {
        // File is empty, set id to 1
        id = 1;
    } else {
        Node *node = obj.root;
        Node *maxi = obj.getmaxnode(node);
        id = (maxi->data) + 1;
    }

    file.close();
    return id;
}


    void makeBooking(int id,string Name, int busNumber, int seatNumber) {
        ofstream writer("Bookings", ios::out | ios::app);
        if (writer) {
            time_t now = time(0);
            tm *ltm = localtime(&now);
//provides confirmation of the booking along with  the important information

            writer << id << Name << " "<<ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " "<< busNumber << " " << seatNumber << "\n";
            writer.close();
            cout << "Booking successful.\n";
        } else {
            cout << "Error opening 'Bookings' file for writing.\n";
        }
    }

    void viewBookings(string accountName) {
    // 
        ifstream reader("Bookings");
        if (!reader) {
            cout << "Error opening 'Bookings' file for reading.\n";
            return;
        }

        string line;
        while (getline(reader, line)) {
            if (line.find(accountName) != string::npos) {
                // Display the booking information for the user
                cout << line << endl;
            }
        }

        reader.close();
    }
};

class seats {
public:
    string busSeats[15][30];

// Constructor to initialize seat data from a file
seats() {
    ifstream reader("Bus_Seats");

    if (!reader) {
        cout << "The file 'Bus_Seats' does not exist or cannot be opened. Creating a new seat data file." << endl;

        // Create a new seat data file with initial values (assuming all seats are initially available)
        ofstream writer("Bus_Seats");
        if (writer) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 30; j++) {
                    writer << "0 "; // Assuming '0' means the seat is available
                }
                writer << endl;
            }
            writer.close();
        } else {
            cout << "Error creating a new seat data file. Please check file permissions." << endl;
        }
    } else {
        // File exists, so read seat data
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 30; j++) {
                reader >> busSeats[i][j];
            }
        }
        reader.close();
    }
}

    // Book a seat on a specific bus by bus number (0-14) and seat number (1-30)
    bool book(int busNumber, int seatNumber) {
        if (busNumber < 0 || busNumber >= 15) {
            cout << "Invalid bus number. Please enter a number between 0 and 14." << endl;
            return false;
        }
        if (seatNumber < 1 || seatNumber > 30) {
            cout << "Invalid seat number. Please enter a number between 1 and 30." << endl;
            return false;
        }
        if (busSeats[busNumber-1][seatNumber - 1] == "0") {
            busSeats[busNumber-1][seatNumber - 1] = "1"; // Mark the seat as booked
            updateSeatsFile();
            cout << "Seat " << seatNumber << " on Bus " << busNumber << " booked successfully." << endl;
            return true;
        } else {
            cout << "Seat " << seatNumber << " on Bus " << busNumber << " is already booked." << endl;
            return false;
        }
    }

    // Display booked seats for a specific bus
    void booked(int busNumber) {
        if (busNumber < 0 || busNumber >= 15) {
            cout << "Invalid bus number. Please enter a number between 0 and 14." << endl;
            return;
        }
        cout << "Booked Seats for Bus " << busNumber << ": ";
        for (int i = 0; i < 30; i++) {
            if (busSeats[busNumber][i] == "1") {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }

    // Display available seats for a specific bus
    void available(int busNumber) {
        if (busNumber < 0 || busNumber >= 15) {
            cout << "Invalid bus number. Please enter a number between 0 and 14." << endl;
            return;
        }
        cout << "Available Seats for Bus " << busNumber << ": ";
        for (int i = 0; i < 30; i++) {
            if (busSeats[busNumber][i] == "0") {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }

void viewBusBookings() {
    // Display booked seats for all buses
    for (int i = 0; i < 15; i++) {
        cout << "Booked Seats for Bus " << i << ": ";
        for (int j = 0; j < 30; j++) {
            if (busSeats[i][j] == "1") {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
}

void cancelBooking() {
    int busNumber, seatNumber;
    cout << "Enter bus number: ";
    cin >> busNumber;

    // Display booked seats for the specified bus
    cout << "Booked Seats for Bus " << busNumber << ": ";
    for (int i = 0; i < 30; i++) {
        if (busSeats[busNumber][i] == "1") {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    cout << "Enter seat number to cancel booking: ";
    cin >> seatNumber;

    // Code to cancel booking for the specified seat on the specified bus
    if (seatNumber >= 1 && seatNumber <= 30) {
        if (busSeats[busNumber][seatNumber - 1] == "1") {
            busSeats[busNumber][seatNumber - 1] = "0"; // Mark the seat as available
            updateSeatsFile();
            cout << "Booking for Seat " << seatNumber << " on Bus " << busNumber << " canceled successfully.\n";
        } else {
            cout << "Seat " << seatNumber << " on Bus " << busNumber << " is not booked.\n";
        }
    } else {
        cout << "Invalid seat number. Please enter a number between 1 and 30.\n";
    }
}

private:
    // Update the seat information in the file
    void updateSeatsFile() {
        ofstream writer("Bus_Seats");
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 30; j++) {
                writer << busSeats[i][j] << " ";
            }
            writer << endl;
        }
        writer.close();
    }
};
class Linkedlist {
    node* head;
    public:
    Linkedlist() { 
        head = NULL; }

    void insertNode(int data,int d){
    node* newNode = new node(data);
    newNode->id=d;
    if (head == NULL) {
        head = newNode;
        return;
    }
    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
        temp->next = newNode;
    }

    node *getTail(node *curNode) {
        while (curNode != nullptr && curNode->next != nullptr) {
            curNode = curNode->next;
        }
        return curNode;
    }

    node *partition(node *low, node *high, node **newLow, node **newHigh) {
        int pivot = high->data;
        node *i = nullptr;

        for (node *j = low; j != high; j = j->next) {
            if (j->data <= pivot) {
                if (i == nullptr) {
                    i = low;
                } else {
                    i = i->next;
                }
                swap(i->data, j->data);
            }
        }

        if (i == nullptr) {
            i = low;
        } else {
            i = i->next;
        }
        swap(i->data, high->data);

        if (i == nullptr) {
            *newLow = low;
        } else {
            *newLow = i;
        }
        *newHigh = i;

        return i;
    }

    void quicksortUtil(node *low, node *high) {
        if (high != nullptr && low != high && low != high->next) {
            node *newLow = nullptr;
            node *newHigh = nullptr;
            node *pivot = partition(low, high, &newLow, &newHigh);

            if (newLow != nullptr && newLow != pivot) {
                quicksortUtil(newLow, pivot);
            }

            if (newHigh != nullptr && newHigh != pivot) {
                quicksortUtil(pivot->next, newHigh);
            }
        }
    }

    void quicksort() {
        head = getTail(head);
        quicksortUtil(head, nullptr);
    }

    void printlist(){
        node *ptr;
        ptr=head;
        cout<<"Bus No. -"<<"Fare";
        while(ptr!=NULL){
            cout<<ptr->id<<" "<<ptr->data<<" ";
            ptr=ptr->next;
        }
        cout<<endl;
    }
};

class routes{
    public:
    void getroute(){
        ifstream file("routes");

        if (!file.is_open()) {
            cerr << "Error opening file\n";
            return;
        }

        string line;
        cout << "Routes:\n";
        cout << "BusNo    From    To    Duration(hr)    Fare(Rs)\n";
        while (getline(file, line)) {
            cout << line << "\n";
        }

        file.close();
    }
void sortroutefare(int rn) {
        fstream reader("routes");

        if (!reader) {
            cerr << "Error opening file\n";
            return;
        }
        int routeno,busno,duration,fare;
        string from,to;
        Linkedlist l1;
        while(reader>>routeno>>busno>>from>>to>>duration>>fare){
            if(routeno==rn){
                l1.insertNode(fare,busno);
            }
        }
        l1.quicksort();
        l1.printlist();
        reader.close();
    }
    void sortrouteduration(int rn){
        fstream reader("routes");

        if (!reader) {
            cerr << "Error opening file\n";
            return;
        }
        int routeno,busno,duration,fare;
        string from,to;
        Linkedlist l1;
        while(reader>>routeno>>busno>>from>>to>>duration>>fare){
            if(routeno==rn){
                l1.insertNode(duration,busno);
            }
        }
        l1.quicksort();
        l1.printlist();
        reader.close();
    }//according to duration
};


void payment() {
    int choice;

        // Display menu options
        cout << "\n#######payment window opening#######\n";
        cout << "1. Bank Transfer\n";
        cout << "2. UPI\n";
        cout << "Enter your choice=";
        cin >> choice;

        // Process user choice
        if (choice==1){
                cout << "Option 1: Bank Transfer selected.\n";
                int x,y;
                cout<<"enter bank acc no.=>\n";
                cin>>x;
                cout<<"enter pin=>\n";
                cin>>y;
            }
       else{
                cout << "Option 2: UPI selected.\n";
                int x,y;
                cout<<"enter phone no.=>\n";
                cin>>x;
                cout<<"enter pin=>\n";
                cin>>y;
        }
        cout<<"amt to be paid=2300\n";
        cout<<"confirm the payment(y/n)=>";
        char t;
        cin>> t;
        if (t=='y' || t=='Y'){
            cout<<"payment successful\n";
        }
        else{
            cout<<"payment cancelled\n";
        }
}




int main(){
    cout<<"########## CABOOK ##########";
    category obj;
    routes r;
    int choice,seatno,busno;
    accounts a;
    seats s;
    l0:
    obj.user();
    cout<<"Enter option number :";
    cin>>choice;
    string admin;
    if(choice==1){
        cout<<"Enter password :";
        cin>>admin;
        if(admin==admin_pass){
            cout<<"Access Granted."<<endl;
        }
        else{
            cout<<"Access Denied."<<endl;
            goto l0;
        }
        while (1){
        obj.admin_menu();
        int c;
        cout<<"\nenter the choice=>\n";
        cin>>c;
        if (c==1){
            cout<<"seats are as follows=>\n";
            s.viewBusBookings();
        }
        else if (c==2){
            a.deleteAccount();
        }

        else if(c==3){
            s.cancelBooking();
        }

        else {
            break;
        }
        }
    }
    else if(choice==2){
        l1:
        obj.start();
        cout<<"Enter option number :";
        cin>>choice;
        if(choice==1){
            if(a.login()==-1){
                goto l1;
            }
        }
        else if(choice==2){
            a.signup();
        }
        else{
            cout<<"\nEnter correct option.";
            goto l1;
        }
        l2:
        obj.menu();
        cout<<"Enter option number :";
        cin>>choice;
        if(choice==1){
            obj.showroutes();
            goto l2;
        }
        else if(choice==2){
            l3:
            cout<<"Enter bus number :";
            cin>>busno;
            if(busno<1 || busno>10){
                cout<<"\nEnter correct bus number.";
                goto l3;        
            }
            l4:
            obj.showseats();
            s.booked(busno);
            s.available(busno);
            cout<<"Enter seat number :";
            cin>>seatno;
            if(seatno<1 || seatno>30){
                cout<<"\nEnter correct seat number.";
                goto l4;        
            }
            s.book(busno,seatno);
            payment();
            goto l2;

        }
        else if(choice==3){
           cout << "Account Details:\n";
                    cout << "Name: " << a.fname << " " << a.lname << endl;
                    cout << "Account Name: " << a.accountname << endl;
                    cout << "Phone: " << a.phone << endl;
                    cout << "Email: " << a.email << endl;
                    goto l2;
        }
        else if(choice==4){
            obj.contact();
            goto l2;
        }
        else if(choice==5){
            return 0;
        }
        else{
            cout<<"\nEnter correct option.";
            goto l2;
        } 
    }
    else{
        cout<<"\nEnter correct option.";
        goto l0;
    }

    return 0;
}
