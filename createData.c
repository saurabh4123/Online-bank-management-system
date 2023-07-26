#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

typedef struct nu{
	int userID;
	char name[30];
	char password[10];
	int acc_no;
	float balance;
}normalUser;

typedef struct ju{
	int userID;
	char name1[30];
	char name2[30];
	char password[10];
	int acc_no;
	float balance;
}jointUser;

typedef struct admin{
	int userID;
	char username[30];
	char password[10];
}admin;

int getNewUserID1();
int getNewUserID2();
int getNewUserID3();

int getNewUserID1(){
	int fd=open("NormalUserData",O_RDONLY,0744);             // Normal User
	normalUser record;
	lseek(fd,-sizeof(normalUser),SEEK_END);
	read(fd,&record,sizeof(normalUser));
	close(fd);
	return record.userID+1;
}

int getNewUserID2(){
	int fd=open("JointUserData",O_RDONLY,0744);             // Joint User
	jointUser record;
	lseek(fd,-sizeof(jointUser),SEEK_END);
	read(fd,&record,sizeof(jointUser));
	close(fd);
	return record.userID+1;
}

int getNewUserID3(){
	int fd=open("AdminData",O_RDONLY,0744);             // Admin
	admin record;
	lseek(fd,-sizeof(admin),SEEK_END);
	read(fd,&record,sizeof(admin));
	close(fd);
	return record.userID+1;
}

int main(){
	int fd=open("AdminData",O_RDWR | O_CREAT,0744);
	int choice=0;
	admin newAdmin;
	printf("Please enter the name of the admin: ");
	scanf(" %[^\n]",newAdmin.username);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",newAdmin.password);
	newAdmin.userID=1000;
	printf("Your userID is : %d\n",newAdmin.userID);
	write(fd,&newAdmin,sizeof(admin));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Please enter the name of the admin: ");
		scanf(" %[^\n]",newAdmin.username);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",newAdmin.password);
		newAdmin.userID=getNewUserID3();
		printf("Your userID is : %d\n",newAdmin.userID);
		write(fd,&newAdmin,sizeof(admin));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("NormalUserData",O_RDWR | O_CREAT,0744);
	choice=1;
	normalUser newNUser;
	printf("Please enter the name of the normal user: ");
	scanf(" %[^\n]",newNUser.name);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",newNUser.password);
	newNUser.userID=1000;
	newNUser.balance=0;
	newNUser.acc_no=(newNUser.userID-1000)+100000;
	printf("Your userID is : %d\n",newNUser.userID);
	write(fd,&newNUser,sizeof(normalUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Please enter the name of the normal user: ");
		scanf(" %[^\n]",newNUser.name);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",newNUser.password);
		newNUser.userID=getNewUserID1();
		newNUser.balance=1000;
		newNUser.acc_no=(newNUser.userID-1000)+100000;
		printf("Your userID is : %d\n",newNUser.userID);
		write(fd,&newNUser,sizeof(normalUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("JointUserData",O_RDWR | O_CREAT,0744);
	choice=1;
	jointUser newJUser;
	printf("Please enter the main name of the joint user: ");
	scanf(" %[^\n]",newJUser.name1);
	printf("Please enter the second name of the joint user: ");
	scanf(" %[^\n]",newJUser.name2);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",newJUser.password);
	newJUser.userID=1000;
	newJUser.balance=0;
	newJUser.acc_no=(newJUser.userID-1000)+100000;
	printf("Your userID is : %d\n",newJUser.userID);
	write(fd,&newJUser,sizeof(jointUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Please enter the main name of the joint user: ");
		scanf(" %[^\n]",newJUser.name1);
		printf("Please enter the second name of the joint user: ");
		scanf(" %[^\n]",newJUser.name2);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",newJUser.password);
		newJUser.userID=getNewUserID2();
		newJUser.balance=0;
		newJUser.acc_no=(newJUser.userID-1000)+100000;
		printf("Your userID is : %d\n",newJUser.userID);
		write(fd,&newJUser,sizeof(jointUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);
	return 0;
}
