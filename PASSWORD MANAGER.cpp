#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<math.h>
#include<cstdlib>

using namespace std;

string encrypt(string,int);
string decrypt(string,int);
void Login();
void UseOptions(string,int);
string generate_password();

long long int calculateHash(string str)
{
	int anyvalue = 101;
    long long hash=0;
    for (size_t i=0;i<str.length();i++)
        hash+=(str[i])*pow(anyvalue,i);
    return hash;
}

int genratekey()
{
	srand(static_cast<unsigned int>(time(NULL)));
	return rand()%50+1;
}

void create_Account(string Username)
{
	string password;
	ofstream write;
	write.open(Username.c_str());
	if(!write.is_open())
		cout<<"Error Occured\n";
	else if(write.is_open())
	{
		cout<<"Enter the password: ",cin>>password;
		cout<<"Account Created Successfully\n";
		write<<calculateHash(password)<<endl;
		write<<genratekey()<<endl;
		write.close();
		Login();
	}
}

void Login()
{
	system("cls");
	cout<<"LOGIN\n";
	string Username,password;
	int key;
	cout<<"Enter your Username: ",cin>>Username;
	cout<<"Enter your password: ",cin>>password;
	ifstream Read;
	Read.open(Username.c_str());
	string pass;
	bool check=false;
	if(Read)
	{
		long long int value;
		getline(Read,pass);
		istringstream ss(pass);
		ss>>value;
		if(calculateHash(password)==value)
		check=true;
		getline(Read,pass);
		istringstream s(pass);
		s>>key;
	}
	if(!check)
	{
		string Username;
		int choose;
		cout<<"No Credentials Stored with given UserName or Password.\n";
		cout<<"1.Create new Account\n2.Login Again!\n",cin>>choose;
		if(choose==1)
		{
			system("cls");
			cout<<"Sign-up\n";
			cout<<"Enter your Username: ";cin>>Username;
			create_Account(Username);
		}
		else
			Login();
	}

	if(check)
		UseOptions(Username,key);
}

void strength_checker(string password)
{
	int up=0,lw=0,dig=0,sp_ch=0,count=0;
	for(int i=0;i<password.length();i++)
	{
		if(islower(password[i]))
		lw++;
		else if(isdigit(password[i]))
		dig++;
		else if(isupper(password[i]))
		up++;
		else if(ispunct(password[i]))
		sp_ch++;
	}
	if(lw>0){count++;}
	if(up>0){count++;}
	if(dig>0){count++;}
	if(sp_ch>0){count++;}
	if(count==1)
		cout<<"WEAK\n";
	else if(count==2)
		cout<<"AVERAGE\n";
	else if(count==3)
		cout<<"GOOD\n";
	else if(count==4)
		cout<<"STRONG\n";
}

string encrypt(string Password,int key)
{
	string result;
	for(int i=0;Password[i]!='\0';i++)
	result+=(Password[i]+key);
	
	return result;
}

string decrypt(string Password,int key)
{
	string result;
	for(int i=0;Password[i]!='\0';i++)
	result+=(Password[i]-key);
	return result;
}

string generate_password()
{
	int length;
	cout<<"Enter the length of Password: ",cin>>length;
	const string charset="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[{]}|;:,<.>/?";
	string password;
	srand(time(NULL));
	 for (int i = 0; i < length; i++) {
        password += charset[rand() % charset.length()];
    }
	return password;
}

void UseOptions(string Username,int key)
{
		int choose;
		cout<<"\n                                              CHOOSE FROM BELOW OPTIONS\n";
		cout<<"Press 1 to See Stored Password.\nPress 2 to Store Password.\nPress 3 to Generate Password.\nPress 4 to check Password Strength.\n",cin>>choose;
		if(choose==1)
		{
			string pass;
			ifstream Read;
			Read.open(Username.c_str());
			getline(Read,pass);
			getline(Read,pass);
			bool a=true;
			while(Read)
			{
				getline(Read,pass);
				if(pass==""&&a)
				{
					cout<<"No Password Stored.\n";
					break;
				}
				a=false;
				pass=decrypt(pass,key);
				cout<<pass<<endl;
			}
			Read.close();
			getchar();		
			while(1)
			{
				cout<<"\nPress 1 to choose again!\nPress 0 to terminate\n",cin>>choose;
				if(choose==1)
				{
					system("cls");
					UseOptions(Username,key);
				}
				else if(choose==0)
				exit(0);
				else
				cout<<"Invailed Input!,Choose again\n";	
			}
		}
		else if(choose==2)
		{
			string pass;
			int numb;
			ofstream write;
			write.open(Username.c_str(),ios::app);
			cout<<"Enter Number of Password you want to Store: ",cin>>numb;
			for(int i=0;i<numb;i++)
			{
				cout<<"Enter Password: ",cin>>pass;
				pass=encrypt(pass,key);
				write<<pass<<endl;
			}
			cout<<"Passwords Stored\n";
			write.close();
			getchar();
			while(1)
			{
				cout<<"\nPress 1 to choose again!\nPress 0 to terminate\n",cin>>choose;
				if(choose==1)
				{
					system("cls");
					UseOptions(Username,key);
				}
				else if(choose==0)
				exit(0);
				else
				cout<<"Invailed Input!,Choose again\n";	
			}
		}
		else if(choose==3)
		{
			string Password=generate_password();
			cout<<"Generated Password: "<<Password;
			getchar();
			while(1)
			{
				cout<<"\nPress 1 to choose again!\nPress 0 to terminate\n",cin>>choose;
				if(choose==1)
				UseOptions(Username,key);
				else if(choose==0)
				exit(0);
				else
				cout<<"Invailed Input!,Choose again\n";	
			}
		}
		else if(choose==4)
		{
			string Password;
			cout<<"Enter Password to check: ",cin>>Password;
			strength_checker(Password);
			getchar();
			while(1)
			{
				cout<<"\nPress 1 to choose again!\nPress 0 to terminate\n",cin>>choose;
				if(choose==1)
				{
					system("cls");
					UseOptions(Username,key);
				}
				else if(choose==0)
				exit(0);
				else
				cout<<"Invailed Input!,Choose again\n";	
			}
		}	
}

main()
{
	cout<<"----------------------------------------------WELCOME TO PASSWORD MANAGERS--------------------------------------------\n";
	
	string Username,password;
	char choice;
	cout<<"\n                                              CHOOSE FROM BELOW OPTIONS\n1.Login		2.Sign-up\n";cin>>choice;
	if(choice=='1')
		Login();
	else if(choice=='2')
	{
		cout<<"Sign-up\n";
		cout<<"Enter your Username: ",cin>>Username;
		create_Account(Username);
	}
	else
	{
		cout<<"Invailed Input\n";
		main();
	}
	cout<<"--------------------------------------------THANK YOU FOR USING OUR SERVICE---------------------------------------------";
}
