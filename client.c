
#include <stdio.h>
#include <sys/types.h>  //has definition of number of datatypes used in system calls
#include <sys/socket.h> //has number of definition of structures needed for sockets
#include <netinet/in.h> // contains constants and structures needed for internet domain address
#include <stdlib.h>     //contains several macros and various functions for performing general functions ex-atoi() string to int type(used to conver port number to int)
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdbool.h>
int option,currUserID;
typedef struct normaluser
{
    int userID;
	char name[30];
	char pass[10];
	int acc_no;
	float balance;
}nu;

typedef struct jointuser
{
    int userID;
	char name1[30];
    char name2[30];
	char pass[10];
	int acc_no;
	float balance;
}ju;

typedef struct admin{
	int userID;
	char name[30];
	char pass[10];
}au;

void NormalUserLogin(int sd);
void JointUserLogin(int sd);
void AdminLogin(int sd);
void main_menu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);

void choice_menu(int sock)
{
    
    write(1," --------------      Welcome To Laxmi Chit Fund     ----------------\n",70);
	write(1,"1 : Normal-User Login        \n",31);
	write(1,"2 : Joint Account-User Login \n",31);
	write(1,"3 : Admin Login              \n",31);
    write(1," ----------------------------\n",31);
	write(1,"Choose an option : ",20);
	scanf("%d",&option);
	printf("Option : %d\n",option);

	switch(option){
		case 1 :
			NormalUserLogin(sock);
			break;
		case 2 :
			JointUserLogin(sock);
			break;
		case 3 :
			AdminLogin(sock);
			break;
		default :
			write(1,"Invalid option!!\n\n",19);
			choice_menu(sock);
			break;
	}
	return;

}
void NormalUserLogin(int s)
{
    bool result;
    nu currUser; // create a struct for the user info
	write(1,"User ID : ",11);
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",12);
	scanf("%s",currUser.pass);

	//to the server
	write(s,&option,sizeof(int));
	write(s,&currUser,sizeof(nu));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",18);
		choice_menu(s);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",26);
	}
	return;

}
void JointUserLogin(int s)
{
    bool result;
	ju currUser;
	write(1,"User ID : ",11);
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",12);
	scanf("%s",currUser.pass);

	//to the server
	write(s,&option,sizeof(int));
	write(s,&currUser,sizeof(ju));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",18);
		choice_menu(s);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",26);
	}
	return;

}
void AdminLogin(int s)
{
    bool result;
	au currUser;
	write(1,"User ID : ",11);
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Password : ",12);
	scanf("%s",currUser.pass);

	//to the server
	write(s,&option,sizeof(int));
	write(s,&currUser,sizeof(au));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",18);
		choice_menu(s);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",26);
	}
	return;

}
void deposit(int s)
{
	float amt;
	int select=1;
	bool result;

	write(1,"Amount to Deposit : Rs.",24);
	scanf("%f",&amt);

	while(amt<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Deposit : Rs.",24);
		scanf("%f",&amt);
	}

	//to the server
	write(s,&select,sizeof(int));
	write(s,&amt,sizeof(float));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error depositing your money!!\n\n",32);
	}
	else{
		write(1,"Succesfully deposited!!\n\n",26);
	}
	main_menu(s);
	return;

}
void withdraw(int s)
{
	float amt;
	int select=2;
	bool result;

	write(1,"Amount to Withdraw : Rs.",25);
	scanf("%f",&amt);

	while(amt<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Withdraw : Rs.",25);
		scanf("%f",&amt);
	}

	//to the server
	write(s,&select,sizeof(int));
	write(s,&amt,sizeof(float));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error withdrawing your money, please check your balance!!\n\n",60);
	}
	else{
		write(1,"Succesfully withdrew!!\n\n",25);
	}
	main_menu(s);
	return;

}
void balanceEnq(int s)
{
	float amt;
	int select=3;
	int len;

	//to the server
	write(s,&select,sizeof(int));

	len=read(s,&amt,sizeof(float));	//from server

	write(1,"Available Balance :: Rs.",25);
	printf("%0.2f\n\n",amt);

	main_menu(s);
	return;

}
void cngPass(int s)
{
	int select=4;
	char nPassword[10];
	bool result;

	write(1,"Enter the new password(max 10 characters) : ",45);
	scanf("%s",nPassword);

	//to the server
	write(s,&select,sizeof(int));
	write(s,nPassword,sizeof(nPassword));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error changing your password!!\n\n",33);
	}
	else{
		write(1,"Succesfully changed your password!!\n\n",38);
	}
	main_menu(s);
	return;

}
void viewDetails(int s)
{
	int select=5;

	//to the server
	write(s,&select,sizeof(int));

	if(option==1){
		nu currUser1;
		read(s,&currUser1,sizeof(nu));

		printf("User ID : %d\n",currUser1.userID);
		printf("Name : %s\n",currUser1.name);
		printf("Account Number : %d\n",currUser1.acc_no);
		printf("Available Balance : Rs.%0.2f\n",currUser1.balance);
	}
	else if(option==2){
		ju currUser2;
		read(s,&currUser2,sizeof(ju));

		printf("User ID : %d\n",currUser2.userID);
		printf("Main Account Holder's Name : %s\n",currUser2.name1);
		printf("Other Account Holder's Name : %s\n",currUser2.name2);
		printf("Account Number : %d\n",currUser2.acc_no);
		printf("Available Balance : Rs.%0.2f\n",currUser2.balance);
	}
	main_menu(s);
	return;

}
void addAcc(int s)
{
	int select=1;
	int type;
	bool result;

	write(s,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",62);
	scanf("%d",&type);

	write(s,&type,sizeof(int));

	if(type==1){
		nu addUser1;
		write(1,"Name of the account holder : ",30);
		scanf(" %[^\n]",addUser1.name);
		write(1,"Password(max 10 characters) : ",31);
		scanf("%s",addUser1.pass);
		write(1,"Initial Deposit : Rs.",22);
		scanf("%f",&addUser1.balance);
		write(s,&addUser1,sizeof(nu));
	}

	if(type==2){
		ju addUser2;
		write(1,"Name of the primary account holder : ",38);
		scanf(" %[^\n]",addUser2.name1);
		write(1,"Name of the other account holder : ",36);
		scanf(" %[^\n]",addUser2.name2);
		write(1,"Password(max 10 characters) : ",31);
		scanf("%s",addUser2.pass);
		write(1,"Initial Deposit : Rs.",22);
		scanf("%f",&addUser2.balance);
		write(s,&addUser2,sizeof(ju));
	}

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error adding the account!!\n\n",29);
	}
	else{
		write(1,"Succesfully added the account!!\n\n",34);
	}
	main_menu(s);
	return;

}
void delAcc(int s)
{
	int select=2;
	int type,userID;
	bool result;

	write(s,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",62);
	scanf("%d",&type);

	write(s,&type,sizeof(int));

	write(1,"User ID : ",11);
	scanf("%d",&userID);
	write(s,&userID,sizeof(int));

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error deleting the account ,please re-check the User ID!!\n\n",60);
	}
	else{
		write(1,"Succesfully deleted the account!!\n\n",36);
	}
	main_menu(s);
	return;

}
void modifyAcc(int s)
{
	int select=3;
	int type;
	bool result;

	write(s,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",62);
	scanf("%d",&type);

	write(s,&type,sizeof(int));

	if(type==1){
		nu modUser1;
		write(1,"User ID : ",11);
		scanf("%d",&modUser1.userID);
		write(1,"Account Number : ",18);
		scanf("%d",&modUser1.acc_no);
		write(1,"New Name of the account holder : ",34);
		scanf(" %[^\n]",modUser1.name);
		write(1,"New Password(max 10 characters) : ",35);
		scanf("%s",modUser1.pass);
		write(1,"New Balance : ",15);
		scanf("%f",&modUser1.balance);
		write(s,&modUser1,sizeof(nu));
	}

	if(type==2){
		ju modUser2;
		write(1,"User ID : ",11);
		scanf("%d",&modUser2.userID);
		write(1,"Account Number : ",18);
		scanf("%d",&modUser2.acc_no);
		write(1,"New Name of the primary account holder : ",42);
		scanf(" %[^\n]",modUser2.name1);
		write(1,"New Name of the other account holder : ",42);
		scanf(" %[^\n]",modUser2.name2);
		write(1,"New Password(max 10 characters) : ",35);
		scanf("%s",modUser2.pass);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser2.balance);
		write(s,&modUser2,sizeof(ju));
	}

	read(s,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error modifying the account ,please re-check the User ID and Account No!!\n\n",76);
	}
	else{
		write(1,"Succesfully modified the account!!\n\n",37);
	}
	main_menu(s);
	return;

}
void searchAcc(int s)
{
	int select=4;
	int type,len;
	bool result;

	write(s,&select,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",62);
	scanf("%d",&type);

	write(s,&type,sizeof(int));

	if(type==1){
		nu searchUser1;
		int userID;
		write(1,"User ID : ",11);
		scanf("%d",&userID);
		write(s,&userID,sizeof(int));

		len=read(s,&searchUser1,sizeof(nu));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",32);
		}
		else{
			printf("User ID : %d\n",searchUser1.userID);
			printf("Name : %s\n",searchUser1.name);
			printf("Account Number : %d\n",searchUser1.acc_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
		}
	}

	if(type==2){
		ju searchUser2;
		int userID1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID1);
		write(s,&userID1,sizeof(int));

		len=read(s,&searchUser2,sizeof(ju));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",32);
		}
		else{
			printf("User ID : %d\n",searchUser2.userID);
			printf("Main Account Holder's Name : %s\n",searchUser2.name1);
			printf("Other Account Holder's Name : %s\n",searchUser2.name2);
			printf("Account Number : %d\n",searchUser2.acc_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.balance);
		}
	}
	main_menu(s);
	return;

}


void main_menu(int sock){
	int sel;//cboice for this menu
	if(option==1 || option==2){
		write(1," ------------------\n",21);
		write(1,"1 : Deposit\n",13);
		write(1,"2 : Withdraw\n",14);
		write(1,"3 : Balance Enquiry\n",21);
		write(1,"4 : Password Change\n",21);
		write(1,"5 : View Details\n",18);
		write(1,"6 : Exit\n",10);
		write(1," ------------------\n",21);

		write(1,"Choose an option : ",20);
		scanf("%d",&sel);
		printf("Option : %d\n",sel);

		switch(sel){
		case 1 :
			deposit(sock);
			break;
		case 2 :
			withdraw(sock);
			break;
		case 3 :
			balanceEnq(sock);
			break;
		case 4 :
			cngPass(sock);
			break;
		case 5 :
			viewDetails(sock);
			break;
		case 6 :
			write(sock,&sel,sizeof(int));
			write(1,"Thank you\n",11);
			exit(0);
		default :
			write(1,"Invalid option!!Try again\n\n",28);
			main_menu(sock);
			break;
		}
	}
	else if(option==3){
		write(1," ---------WELCOME ADMIN SAURABH-----------\n",44);
		write(1,"1 : Add Account    \n",21);
		write(1,"2 : Delete Account \n",21);
		write(1,"3 : Modify Account \n",21);
		write(1,"4 : Search Account \n",21);
		write(1,"5 : Exit \n",11);
		write(1," ------------------\n",21);

		write(1,"Choose an option : ",20);
		scanf("%d",&sel);
		printf("Option : %d\n",sel);

		switch(sel){
		case 1 :
			addAcc(sock);
			break;
		case 2 :
			delAcc(sock);
			break;
		case 3 :
			modifyAcc(sock);
			break;
		case 4 :
			searchAcc(sock);
			break;
		case 5 :
			write(sock,&sel,sizeof(int));
			write(1,"Thank you\n",11);
			exit(0);
		default :
			write(1,"Invalid option!!Try again!!\n\n",30);
			main_menu(sock);
			break;
		}
	}
    else;
}

int main()
{
    // creating a socket
    int nw_socket;                               // stores return value of socket sys call i.e file descriptor number
    nw_socket = socket(AF_INET, SOCK_STREAM, 0); // socket()  creates  an  endpoint  for  communication  and returns a file descriptor that refers to that endpoint
    // now before connect we need to specify the port to connect to and we do that by using a structure
    // specify an address for the socket to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;   // specifying the type of addtess we are working with(INET-IPV4)
    server_address.sin_port = htons(9001); // htons changes the format of port number to specific structure required format(using very high port since high chances its not being used by OS)
    // server_address.sin_addr.s_addr=inet_addr("192.168.159.72"); use this when connecting through wifi on different devices
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  //same machine  // If inet_addr is successful, it returns the address in network byte order.
    // sin addr is a structure itself therefore go inside that and fill field s_addr(real server address we'll be connecting to)
    // inaddr_any is similar as connecting to 0.0.0.0

    // now we can connect
    // using sockaddrr inplace of sockaddr_in bcz sockaddr is more generic whereas sockaddr_in specifies IPV4 address
    int conn_status = connect(nw_socket, (struct sockaddr *)&server_address, sizeof(server_address)); // return 0 on successful connection or binding else -1

    // check for error while connecting if any

    if (conn_status == -1)
        printf("Error while establishing connection.\n\n");

    // now we receive data from server if any
    //char ser_resp[500];
    //recv(nw_socket, &ser_resp, sizeof(ser_resp), 0);

    // printing data that we received from server
    //printf("Server response: %s\n", ser_resp);

    //calling customer menu function to display the menu and perform tasks
    choice_menu(nw_socket);
    main_menu(nw_socket);

    // close the connection
    close(nw_socket);
    return 0;
}