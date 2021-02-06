#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
   int acno;
   char name[50];
   int deposit;
   char type;

public:
   void create_account();
   void show_account();
   void modify();
   void dep(int);
   void draw(int);
   void report() const;
   int retacno() const;
   int retdeposit() const;
   char rettype() const;

};

void account:: create_account()
{
   cout<<"\nEnter account No. : ";
   cin>>acno;
   cout<<"\nEnter the name of account Holder : ";
   cin.ignore();
   cin.getline(name, 50);
   cout<<"\nEnter the type of account : ";
   cin>>type;
   type=toupper(type);
   cout<< "\nEnter the initial amount(>=500 for saving and>=1000 for current) :  ";
   cin>>deposit;
   cout<<"\n\n\nAccount Created.";
}

void account ::show_account()
{
   cout<< "\nAccount No. : "<<acno;
   cout<< "\nAccount Holder Name :";
   cout<< name;
   cout<< "\nType of Account :"<< type;
   cout<< "\nBalance amount : "<< deposit;

}

void account ::modify()
{
   cout<< "\nAccount No. : "<<acno;
   cout<<"\nModify Account Holder Name : ";
   cin.ignore();
   cin.getline(name,50);
   cout<<"\nModify Type of Account";
   cin>> type;
   type=toupper(type);
   cout<<"\nModify Balance amount :";
   cin>>deposit;

}

void account ::dep(int x)
{
   deposit +=x;
}

void account ::draw(int x)
{
   deposit -=x;
}

void account ::report() const
{
   cout<<"\n"<< acno<< setw(10) <<" "<<name<< setw(10)<<"             "<<type <<setw(6)<<"             "<<deposit<<endl;
}

int account ::retacno() const
{
   return acno;
}

int account :: retdeposit() const
{
   return deposit;
}

char account::rettype() const
{
   return type;
}



//*******************************
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();


//*********************
int main()
{
   char ch;
   int num;
   intro();
   do{
      system("cls");
      cout<< "\n\n\n\tMAIN MENU";
      cout<< "\n\n\t 01. NEW ACCOUNT";
      cout<< "\n\n\t 02. DEPOSIT AMOUNT";
      cout<< "\n\n\t 03. WITHDRAW AMOUNT";
      cout<< "\n\n\t 04. BALANCE ENQUIRY";
      cout<< "\n\n\t 05. ALLACCOUNT HOLDER LIST";
      cout<< "\n\n\t 06. CLOSE AN ACCOUNT";
      cout<< "\n\n\t 07. MODIFY AN ACCOUNT";
      cout<< "\n\n\t 08. EXIT\n\n";
      cin>>ch;
      system("cls");
      switch(ch)
      {
         case '1' : write_account();
                    break;

         case '2' : cout<<"\n\n\tEnter the account No. :";
                    cin>>num;
                    deposit_withdraw(num, 1);
                    break;

         case '3' : cout<<"\n\n\tEnter the account No. :";
                    cin>>num;
                    deposit_withdraw(num, 2);
                    break;

         case '4' : cout<<"\n\n\tEnter the account No. :";
                    cin>>num;
                    display_sp(num);
                    break;

         case '5' : display_all();
                    break;

         case '6' : cout<<"\n\n\tEnter the account No. :";
                    cin>>num;
                    delete_account(num);
                    break;

         case '7' : cout<<"\n\n\tEnter the account No. :";
                    cin>>num;
                    modify_account(num);
                    break;

         case '8' : cout<<"\n\n\tThanks for using bank management system";
                    break;

         default:cout<< "\a";
      }
      cin.ignore();
      cin.get();
   }while(ch !='8');
   return 0;
}

//*****************************
//    FUNTION TO WRITE IN FILE
//*****************************

void write_account()
{
   account ac;
   ofstream outfile;
   outfile.open("account.dat", ios::binary | ios::app);
   ac.create_account();
   outfile.write(reinterpret_cast<char*>(&ac), sizeof(account));
   outfile.close();
}
//*****************************
//    FUNTION TO READ IN FILE
//*****************************

void display_sp(int n)
{
   account ac;
   bool flag=false;
   ifstream infile;
   infile.open("account.dat", ios::binary);
   if(!infile)
   {
      cout<<"file could not be open !! press any key.";
      return;
   }
   cout<< "\nBalance DETails\n";
   while(infile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
   {
      if(ac.retacno()== n)
      {
         ac.show_account();
         flag=true;
      }
   }
   infile.close();
   if(flag==false)
      cout<< "\n\nAccount No. Does Not Exist";

}

//*****************************
//    FUNTION TO MODIFY RECORD OF FILE
//*****************************




void modify_account(int n)
{

   bool found=false;
   account ac;
   fstream File;
   File.open("account.dat", ios::binary | ios::in | ios::out);
   if(!File)
   {
      cout<< "File could not be Open !! press any key.";
      return;
   }
   while(!File.eof() && found==false)
   {
      File.read(reinterpret_cast<char*>(&ac), sizeof(account));
      if(ac.retacno() == n)
      {
         ac.show_account();
         cout<< "\n\nEnter the New Details of account"<<endl;
         ac.modify();
         int pos=(-1)*static_cast<int>(sizeof(account));
         File.seekp(pos, ios::cur);
         File.write(reinterpret_cast<char*>(&ac), sizeof(account));
         cout<<"\n\n\t Record updated";
         found=true;
       }
   }
   File.close();
   if(found==false)
      cout<<"\n\n Record Not FOund";
}

//*****************************
//    FUNTION TO Delete RECORD OF FILE
//*****************************

void delete_account(int n)
{
   account ac;
   ifstream inFile;
   ofstream outFile;
   inFile.open("account.dat",ios::binary);
   if(!inFile)
   {
      cout<<"File could not be Open !!press any key";
      return;
   }
    while(inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
   {
      if(ac.retacno()!= n)
      {
         outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
      }
   }
   inFile.close();
   outFile.close();
   remove("account.dat");
   rename("Temp.dat","account.dat");
   cout<<"\n\n\tRecord Deleted";
}

//*****************************
//    FUNTION TO Display all account deposit list
//*****************************

void display_all()
{
   account ac;
   ifstream inFile;
   inFile.open("account.dat", ios::binary);
   if(!inFile)
   {
      cout<<"File could not be Open !!press any key";
      return;
   }
   cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
   cout<<"==========================================\n";
   cout<<"A/c no.        NAME            TYPE          BALANCE \n";
   cout<<"==========================================";
    while(inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
   {
      ac.report();
   }
inFile.close();
}

void deposit_withdraw(int n, int option)
{
   int amt;
   bool found=false;
   account ac;
   fstream File;
   File.open("account.dat", ios::binary | ios::in | ios::out);
   if(!File)
   {
      cout<< "File could not be Open !! press any key.";
      return;
   }
   while(!File.eof() && found==false)
   {
      File.read(reinterpret_cast<char*>(&ac), sizeof(account));
      if(ac.retacno() == n)
      {
         ac.show_account();
         if(option==1)
         {
            cout<<"\n\n\tTo Deposit amount";
            cout<<"\n\nEnter the amount to be deposited";
            cin>>amt;
            ac.dep(amt);
         }
         if(option==2)
         {
            cout<<"\n\n\tTo Withdraw amount";
            cout<<"\n\nEnter the amount to be Withdraw";
            cin>>amt;
            int bal= ac.retdeposit()-amt;
            if((bal<500 &&ac.rettype()=='S')  || (bal<1000 && ac.rettype()=='C'))
            cout<<"insufficient balance";
            else
               ac.draw(amt);
         }
         int pos=(-1)*static_cast<int>(sizeof(account));
         File.seekp(pos, ios::cur);
         File.write(reinterpret_cast<char*>(&ac), sizeof(account));
         cout<<"\n\n\t Record updated";
         found=true;
       }
   }
   File.close();
   if(found==false)
      cout<<"\n\n Record Not FOund";
}

//*****************************
//   INTRODUCTION FUNTION
//*****************************

void intro()
{

   cout<<"\n\n\n\t BANK";
   cout<<"\n\n\t MANAGEMENT";
   cout<<"\n\n\t SYSTEM";
   cout<<"\n\n\t made by JASIM";
   cin.get();
}




