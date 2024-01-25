#include<iostream>									
#include<fstream>
#include<time.h>
#include<string.h>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;
int ucount=0;
class Bank{
	public:	
	char name[100],cnic[15],id[15],dob[20];
	int age,password;
	long balance=0;
	void showuser();
	void admin();
	void adduser();
	void deleteuser();
	void operations();
	char * getcnic(){ return cnic; }
	int getpass(){ return password; }
	int getbal(){ return balance; }
	void countuser();
	void reduce(int amount){
	balance-=amount;}
	void increment(int a){
	balance+=a;	
	}
	void header();
	void listview();
	void search();
}b;
void heading();
void Bank::header(){
	cout<<left<<setw(18)<<"CNIC "<<setw(20)<<"Name "<<setw(17)<<"Year of birth "<<setw(5)<<"Age ";
	cout<<setw(9)<<"Balance "<<endl;
	for(int i=1; i<=67; i++)
	cout<<"=";
	cout<<endl;
}
void Bank::listview(){
	cout<<left<<setw(18)<<cnic<<left<<setw(20)<<name <<left<<setw(17)<<dob<<left<<setw(5)<<age;
	cout<<left<<setw(9)<<balance<<endl;
}
void viewuser(){
	system("cls");
	system("color 70");
	cout<<"\n\n\n";
	heading();
	ifstream fin("Users.txt");
	int rec=0;
	while(fin.read((char*)&b,sizeof(b))){
	if(rec<1)
	b.header();
	b.listview();
	rec++;}
	fin.close();
	cout<<"\nTotal "<<rec<<" records in the file so far \n";
}
void Bank::showuser(){
	cout<<"\n\n";
	cout<<"Name is                 : "<<name<<endl;
	cout<<"CNIC is                 : "<<cnic<<endl;
	cout<<"Age is                  : "<<age<<endl;
	cout<<"Year of birth is        : "<<dob<<endl;
	cout<<"Bank balance is         : "<<balance<<endl;
}
void Bank::search(){
	bool b1=false;
	system("cls");
	system("color 70");
	cout<<"\n\n\n";
	heading();
	ifstream fin("Users.txt");
	char id[15];
	cout<<"Enter cnic you want to search : ";
	cin.ignore();
	cin.getline(id,15);
	while(fin.read((char*)&b,sizeof(b))){
	if(strcmp(id,b.getcnic())==0){
	b.showuser();
	b1=true;
	cout<<"\n";
	system("pause");
	break;	
	}}
	if(b1==false){
	cout<<"User not found\n";   
	system("pause");}
}
void drawline(char ch){							                    			
	for(int i=1; i<=70; i++){
	if(i<=48)
	cout<<" ";
	else
	cout<<ch;}
	cout<<endl;
}
void heading(){									                   			//Prints Library Management
	drawline('*');
	cout<<"\t\t\t\t\t\tBank Management System\n";
	drawline('*');
	cout<<endl;
}
void addcash(){
	system("cls");
	system("color 70");
	cout<<"\n\n\n";
	heading();
	bool b1=false;
	fstream f("Users.txt",ios::out | ios::in);
	char id[15];
	int pass,balance,pos;
	cin.ignore();
	cout<<"Enter your id : ";
	cin.getline(id,15);
	cout<<"Enter your password : ";
	cin>>pass;
	while(f.read((char*)&b,sizeof(b))){
	if((strcmp(id,b.getcnic())==0) && (pass==b.getpass())){
	pos=f.tellg();
	f.seekg(pos-sizeof(b));	
	cout<<"Enter amount you want to deposit : ";
	cin>>balance;
	b.increment(balance);
	f.write((char*)&b,sizeof(b));	
	b1=true;
	break;}
	else{
	cout<<"User not found";
	break;}
	}
	if(b1==true){
	cout<<"Amount "<<balance<<" has been credited in your bank account\n";	
	}
	f.close();
}
void withdraw(){
	system("cls");
	system("color 70");
	cout<<"\n\n\n";
	heading();
	fstream f("Users.txt",ios::out | ios::in);
	int value,pass;
	bool b1=0,b2=0;
	char id[15];
	cout<<"\nEnter your cnic : ";
	cin.ignore();
	cin.getline(id,15);
	cout<<"Enter password : ";
	cin>>pass;
	cout<<"Enter amount you want to withdraw (100 to 100000) : ";
	cin>>value;
	while(value<=0 or value>100000 or (value%100)!=0){
	cout<<"Enter amount again, it'd be a multiple of 100 : ";
	cin>>value;}
	while(f.read((char*)&b,sizeof(b))){
	if((strcmp(id,b.getcnic())==0) && (pass==b.getpass())){
	b1=true;	
	if(value<b.getbal()){
	b2=true;
	int pos=f.tellg();
	f.seekg(pos-sizeof(b));	
	b.reduce(value);
	f.write((char*)&b,sizeof(b));}}}
	if(b1==true && b2==true){
	cout<<"Amount "<<value<<" has been withdrawn from your bank account\n";
	system("pause");	
	}
	else if(b1==true && b2==false){
	cout<<"Insufficient balance\n";
	system("pause");}		
	else if(b1==false){
	cout<<"User not found\n";
	system("pause");}
	f.close();	
}
void Bank::countuser(){
	ucount=0;
	ifstream fin("Users.txt");
	while(fin.read((char*)&b,sizeof(b))){
	ucount++;}
}
void Bank::deleteuser(){
	system("cls");
	system("color 70");
	cout<<"\n\n\n";
	heading();
	char op,id[15];
	int pass;
	fstream reading,writing;
	reading.open("Users.txt",ios::in);
	writing.open("temp.txt",ios::app);
	cin.ignore();
	cout<<"\n\n\nEnter cnic without hyphens : ";
	cin.getline(id,15);
	cout<<"Enter password : ";
	cin>>pass;
	while(reading.read((char*)&b,sizeof(b))){
		if((strcmp(id,b.getcnic())==0) && (pass==b.getpass())){
		b.showuser();
		cout<<"\nUser found,do you want to delete this record (y/n)??? ";
		cin>>op;
		if(op=='y' or op=='Y'){
		cout<<"User deleted\n";
		system("pause");}  
		else{
		cout<<"User is not deleted\n";
		writing.write((char*)&b,sizeof(b));
		system("pause");}}
		else{
		writing.write((char*)&b,sizeof(b));
		}}
		reading.close();
		writing.close();
		remove("Users.txt");
		rename("temp.txt","Users.txt");
		b.countuser();
}
void Bank::adduser(){
	fstream fin("Users.txt",ios::in);
	fstream fout("Users.txt",ios::app);	
	system("cls");
	system("color 70");
	cout<<"\n\n\n";
	heading();
	bool b1=0;
	char id[15];
	cout<<"\nEnter your cnic without hyphens : ";
	cin.ignore();
	cin.getline(id,15);
	while(fin.read((char*)&b,sizeof(b))){
	if(strcmp(id,b.getcnic())==0){
	b1=true;
	cout<<"User already exists\n";
	return;
	}}
	if(b1==false){
	cout<<"Enter name : ";
	cin.getline(name,100);
	strcpy(cnic,id);
	cout<<"Enter your year of birth : ";
	cin.getline(dob,20);
	if(2023-atoi(dob)<18){
	cout<<"Minimum age should be 18\n";
	return;		
	}
	age=2023-atoi(dob);
	cout<<"Enter your login password : ";
	cin>>password;
	balance=0;
	fout.write((char*)&b,sizeof(b));}
	fout.close();
	fin.close();
	b.countuser();
}
void menu(){
	int ch;
	while(ch!=6){
	start:
	system("cls");	
	time_t t=time(NULL);
	cout<<endl<<endl<<endl;
	cout<<ctime(&t);	
	system("color B0");
	heading();
	cout<<"\n  0-> Add a new user (Total users : "<<ucount<<" )\n\n";
	cout<<"  1-> Delete user\n\n"<<"  2-> Show users\n\n"<<"  3-> Cash withdrawl\n\n"<<"  4-> Cash deposit\n\n";
	cout<<"  5-> Search user\n\n";
	cout<<"  6-> Exit\n\n  ";
	cin>>ch;
	system("cls");
	switch(ch){
		case 0:
		b.adduser();
		system("pause");
		break;
		case 1:
		b.deleteuser();
		break;
		case 2:
		viewuser();
		system("pause");
		break;	
		case 3:
		withdraw();
		break;
		case 4:
		addcash();	
		system("pause");
		break;
		case 5:
		b.search();
		break;	
		case 6:
		break;
		default:
		goto start;	
	}
}}
int main(){
	b.countuser();
	menu();
}
