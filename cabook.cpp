#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
const string admin_pass="root123";
struct node{
    int data;
    node *next=NULL;
    node(int x){
        data=x;
    } 
};
class category{
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
        cout<<"\nRoutes & Buses\n\n";
        cout<<"1.Bus 1 : Delhi--->Jaipur--->Udaipur"<<endl;
        cout<<"2.Bus 2 : Delhi--->Punjab--->Chandigarh"<<endl;
    }
    void contact(){
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


class accounts{
    public:
    string fname;
    string lname;
    string  accountname;
    string password;
    string phone;
    string email;
void signup(){
    cout<<endl;
    cout<<"Enter your firstname : ";
    cin>>fname;
    cout<<"Enter your lastname : ";
    cin>>lname;
    cout<<"Enter Account Name : ";
    cin>>accountname;
    cout<<"Enter Password : ";
    cin>>password;
    do{
        cout<<"Enter your phone number (10 digits only): ";
        cin>>phone;
        if(phone.length() != 10){
            cout<<"Invalid phone number. Please try again."<<endl;
        }
    }while(phone.length() != 10);
    cout<<"Enter your email id : ";
    cin>>email;
    ofstream writer;
    writer.open("Details",ios::out|ios::app);
    writer<<accountname<<" "<<password<<" "<<fname<<" "<<lname<<" "<<phone<<" "<<email<<"\n";
    writer.close();
}


    //nothing prints in login when no account is found in file;
int login() {
    int flag = 0;
    string acc, pass;
    cout<<endl;
    cout << "Enter Account Name : ";
    cin >> acc;
    cout << "Enter Password : ";
    cin >> pass;

    fstream reader;
    reader.open("Details", ios::in);

    string check_accountname, check_password, check_fname, check_lname ,check_email;
    string check_phone;

    while(reader >> check_accountname >> check_password >> check_fname >> check_lname >> check_phone >> check_email ) {
        if (check_accountname == acc) {
            flag = 1;
            if (check_password == pass) {
                cout << "Access Granted.\n" << endl;
                accountname = check_accountname;
                password = check_password;
                fname = check_fname;
                lname = check_lname;
                phone = check_phone;
                email = check_email;
                reader.close();
                return 1;
            } else {
                cout << "Wrong Password\n" << endl;
            }
            break;
        }
    }

    if (flag == 0) {
        cout << "Account not found.\n" << endl;
        return -1;
    }

    reader.close();
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

    cout << "Account " << accToDelete << " deleted successfully.\n";
}

};



class book {
public:
    void makeBooking(string Name, int busNumber, int seatNumber) {
        ofstream writer("Bookings", ios::out | ios::app);
        if (writer) {
            time_t now = time(0);
            tm *ltm = localtime(&now);

            writer << Name << " "<<ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " "<< busNumber << " " << seatNumber << "\n";
            writer.close();
            cout << "Booking successful.\n";
        } else {
            cout << "Error opening 'Bookings' file for writing.\n";
        }
    }

    void viewBookings(string accountName) {
        ifstream reader("Bookings");
        if (!reader) {
            cout << "Error opening 'Bookings' file for reading.\n";
            return;
        }

        string line;
        while (getline(reader, line)) {
            if (line.find("Account Name: " + accountName) != string::npos) {
                // Display the booking information for the user
                cout << line << endl;
                for (int i = 0; i < 3; ++i) {
                    getline(reader, line);
                    cout << line << endl;
                }
                cout << endl;
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

class queued{
    public:
    node *head=NULL;
    void enque(int x){
        node *newnode=new node(x);
        if(head==NULL){
            head=newnode;
            return;
        }
        newnode->next=head;
        head=newnode;
        
    }
    void deque(){
        node *temp=head;
        head=head->next;
        delete temp;
    }
    int front(){return head->data;}
    bool isempty(){
        return (head==NULL);
    }
    void display(){
        node *curr=head;
        while(curr!=NULL){
            cout<<curr->data<<" ";
            curr=curr->next;
        }
        cout<<endl;
    }
};  

class payment{

public:
    void queuePayment(string accountName, double amount) {
        ofstream writer("PaymentQueue", ios::out | ios::app);
        if (writer) {
            writer << "Account Name: " << accountName << "\n";
            writer << "Amount: $" << amount << "\n\n";
            writer.close();
            cout << "Payment request queued successfully.\n";
        } else {
            cout << "Error opening 'PaymentQueue' file for writing.\n";
        }
    }

    void processPayments() {
        ifstream reader("PaymentQueue");
        if (!reader) {
            cout << "Error opening 'PaymentQueue' file for reading.\n";
            return;
        }

        queued paymentQueue;

        string line;
        while (getline(reader, line)) {
            if (line.find("Account Name: ") != string::npos) {
                // Enqueue payment request
                paymentQueue.enque(stoi(line.substr(14)));
                getline(reader, line); // Skip the "Amount" line
            }
        }

        reader.close();

        // Process payment requests from the queue
        cout << "Processing payment requests...\n";
        while (!paymentQueue.isempty()) {
            int accountNumber = paymentQueue.front();
            cout << "Processing payment for Account Number: " << accountNumber << "\n";
            // Add your payment processing logic here

            // Dequeue processed payment request
            paymentQueue.deque();
        }
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

int getHeight(Node* root) {
    if (root == nullptr)
        return 0;
    return root->height;
}

int getBalanceFactor(Node* root) {
    if (root == nullptr)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}
Node *balancetree(Node *root,int data){
     int balance = getBalanceFactor(root);

    if (balance > 1) {
        if (data < root->left->data) // Left-Left case
            return rightRotate(root);
        if (data > root->left->data) // Left-Right case
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (data > root->right->data) // Right-Right case
            return leftRotate(root);
        if (data < root->right->data) // Right-Left case
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

Node* insert(Node* root, int data) {
    if (root == nullptr)
        return new Node(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    balancetree(root,data);
    return root;
}
Node *maxNode(Node *root){
    if(root->right==NULL){
        return root;
    }
    maxNode(root->right);
}
Node* deleteNode(Node* root, int x) {
    if (root == nullptr)
        return root;

    if (x < root->data) {
        root->left = deleteNode(root->left, x);
    } else if (x > root->data) {
        root->right = deleteNode(root->right, x);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            Node* temp = maxNode(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data);
        }
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return balancetree(root, x);
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}
int main(){
    cout<<"########## CABOOK ##########";
    category obj;
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
        }
        else if(choice==3){

        }
        else if(choice==4){

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


