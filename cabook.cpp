#include <iostream>
using namespace std;
struct node{
    int data;
    node *next=NULL;
    node(int x){
        data=x;
    }
};
class category{
    public:
    void start(){
        cout<<"####### CABOOK ######\n\n";
        cout<<"1.login"<<endl;
        cout<<"2.signup\n"<<endl;
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
    }

    reader.close();
    return 0;
}
};

class queue{
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


int main(){
    return 0;
}
/*
class linkedlist{
    public:
    node *head=NULL;
    void insertnode(int x){
        node *temp=new node(x);
        if(head==NULL){
            head=temp;
            return;
        }
        node *curr=head;
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next=temp;
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
*/