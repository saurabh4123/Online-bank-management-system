#include<stdio.h>
#include<sys/types.h>  //has definition of number of datatypes used in system calls
#include<sys/socket.h>  //has number of definition of structures needed for sockets
#include<netinet/in.h>  // contains constants and structures needed for internet domain address 
#include<stdlib.h> //contains several macros and various functions for performing general functions ex-atoi() string to int type(used to conver port number to int)
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdbool.h>


typedef struct normalUser{
	int userID;
	char name[30];
	char password[10];
	int account_no;
	float balance;
}normalUser;

typedef struct jointUser{
	int userID;
	char name1[30];
	char name2[30];
	char password[10];
	int account_no;
	float balance;
	//int active;
}jointUser;

typedef struct admin{
	int userID;
	char username[30];
	char password[10];
}admin;

normalUser getNormalUser(int ID){
	int i=ID-1000;
	normalUser currUser;
	int fd=open("NormalUserData",O_RDONLY,0744);

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

jointUser getJointUser(int ID){
	int i=ID-1000;
	jointUser currUser;
	int fd=open("JointUserData",O_RDONLY,0744);

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

admin getAdmin(int ID){
	int i=ID-1000;
	admin currUser;
	int fd=open("AdminData",O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     //nth record
	lock.l_len=sizeof(admin);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

bool checkNormalUser(normalUser currUser){
	int i=currUser.userID-1000;
	int fd=open("NormalUserData",O_RDONLY,0744);
	bool result;
	normalUser temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(normalUser));
	if(!strcmp(temp.password,currUser.password))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkJointUser(jointUser currUser){
	int i=currUser.userID-1000;
	int fd=open("JointUserData",O_RDONLY,0744);
	bool result;
	jointUser temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(jointUser));
	if(!strcmp(temp.password,currUser.password))
		result=true;
	else
		result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkAdmin(admin currUser){
	int i=currUser.userID-1000;
	int fd=open("AdminData",O_RDONLY,0744);
	bool result;
	admin temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     //nth record
	lock.l_len=sizeof(admin);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(admin));
	if(!strcmp(temp.password,currUser.password))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool depositMoney(int accType,int ID,float amt){
	int i=ID-1000;
	printf("hiii\n");
	if(accType==1){
		int fd=open("NormalUserData",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));

		    currUser.balance+=amt;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
	

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JointUserData",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointUser));

			currUser.balance+=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			result=true;
		// printf("hiii\n");
		sleep(10);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool withdrawMoney(int accType,int ID,float amt){
	int i=ID-1000;
	if(accType==1){
		int fd=open("NormalUserData",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));

		if(currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JointUserData",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointUser));

		if(currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float getBalance(int accType,int ID){
	int i=ID-1000;
	float result;
	if(accType==1){
		int i=ID-1000;
		int fd=open("NormalUserData",O_RDONLY,0744);
		normalUser temp;

		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    	     //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(normalUser));
		result=temp.balance;
		

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int i=ID-1000;
		int fd=open("JointUserData",O_RDONLY,0744);
		jointUser temp;

		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    	     //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(jointUser));
		result=temp.balance;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool alterPassword(int accType,int ID,char newPwd[10]){
	int i=ID-1000;
	if(accType==1){
		int fd=open("NormalUserData",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    //nth record
		lock.l_len=sizeof(normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		normalUser currUser;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(normalUser));

			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(normalUser));
			result=true;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JointUserData",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    //nth record
		lock.l_len=sizeof(jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		jointUser currUser;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(jointUser));

	
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(jointUser));
			result=true;
		
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool addNormalUser(normalUser record){
	int fd=open("NormalUserData",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser endUser;
	lseek(fd,(-1)*sizeof(normalUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(normalUser));

	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;

	int j=write(fd,&record,sizeof(normalUser));
	if(j!=0)	result=true;
	else	result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool addJointUser(jointUser record){
	int fd=open("JointUserData",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(jointUser);    //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser endUser;
	lseek(fd,(-1)*sizeof(jointUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(jointUser));

	record.userID=endUser.userID+1;
	record.account_no=endUser.account_no+1;

	int j=write(fd,&record,sizeof(jointUser));
	if(j!=0)	result=true;
	else	result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deleteNormalUser(int ID){
	int i=ID-1000;
	int fd=open("NormalUserData",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser currUser;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));


		currUser.balance=0;

		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR);
		int j=write(fd,&currUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deleteJointUser(int ID){
	int i=ID-1000;
	int fd=open("JointUserData",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser currUser;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointUser));

		currUser.balance=0;

		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR);
		int j=write(fd,&currUser,sizeof(jointUser));
		if(j!=0)	result=true;
		else		result=false;
	

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool modifyNormalUser(normalUser modUser){
	int i=modUser.userID-1000;
	int fd=open("NormalUserData",O_RDWR,0744);
	bool result=false;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    //nth record
	lock.l_len=sizeof(normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser currUser;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(normalUser));

	if( (modUser.account_no==currUser.account_no)){
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR);
		int j=write(fd,&modUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool modifyJointUser(jointUser modUser){
	int i=modUser.userID-1000;
	int fd=open("JointUserData",O_RDWR,0744);
	bool result=false;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    //nth record
	lock.l_len=sizeof(jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser currUser;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(jointUser));

	if( (modUser.account_no==currUser.account_no)){
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR);
		int j=write(fd,&modUser,sizeof(jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

void serverTask(int nsd){
	int msgLength,select,type,option,accType,currUserID;
	bool result;
	while(1){
		read(nsd,&option,sizeof(option));
		printf("Option : %d\n",option);

		if(option==1){
			normalUser currUser1;
			accType=1;
			msgLength=read(nsd,&currUser1,sizeof(normalUser));
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			currUserID=currUser1.userID;
			result=checkNormalUser(currUser1);
			write(nsd,&result,sizeof(result));
		}
		else if(option==2){
			jointUser currUser2;
			accType=2;
			msgLength=read(nsd,&currUser2,sizeof(jointUser));
			currUserID=currUser2.userID;
			printf("Username : %d\n",currUser2.userID);
			printf("Password : %s\n",currUser2.password);
			result=checkJointUser(currUser2);
			write(nsd,&result,sizeof(result));
		}
		else if(option==3){
			admin currUser3;
			accType=3;
			msgLength=read(nsd,&currUser3,sizeof(admin));
			currUserID=currUser3.userID;
			printf("Username : %d\n",currUser3.userID);
			printf("Password : %s\n",currUser3.password);
			result=checkAdmin(currUser3);
			write(nsd,&result,sizeof(result));
		}
		else{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	break;
	}

	while(1){
		read(nsd,&select,sizeof(int));
		if(option==1 || option==2){
			if(select==1){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=depositMoney(accType,currUserID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==2){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=withdrawMoney(accType,currUserID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==3){
				float amt;
				amt=getBalance(accType,currUserID);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4){
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				result=alterPassword(accType,currUserID,pwd);
				write(nsd,&result,sizeof(result));
			}
			else if(select==5){
				if(option==1){
					normalUser user1=getNormalUser(currUserID);
					write(nsd,&user1,sizeof(normalUser));
				}
				else if(option==2){
					jointUser user2=getJointUser(currUserID);
					write(nsd,&user2,sizeof(jointUser));
				}
			}
			else if(select==6)	break;
		}
		else if(option==3){
			read(nsd,&type,sizeof(int));
			if(select==1){
				if(type==1){
					normalUser newUser1;
					read(nsd,&newUser1,sizeof(normalUser));
					result=addNormalUser(newUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					jointUser newUser2;
					read(nsd,&newUser2,sizeof(jointUser));
					result=addJointUser(newUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==2){
				if(type==1){
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					result=deleteNormalUser(delUserID1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					result=deleteJointUser(delUserID2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==3){
				if(type==1){
					normalUser modUser1;
					read(nsd,&modUser1,sizeof(normalUser));
					result=modifyNormalUser(modUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					jointUser modUser2;
					read(nsd,&modUser2,sizeof(jointUser));
					result=modifyJointUser(modUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==4){
				if(type==1){
					normalUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=getNormalUser(userID1);
					write(nsd,&searchUser1,sizeof(normalUser));
				}
				else if(type==2){
					jointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=getJointUser(userID2);
					write(nsd,&searchUser2,sizeof(jointUser));
				}
			}
			else if(select==5)	break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

int main()
{
    char ser_mssg[250]="Congratulations!!You have connected to SAURABH'S server"; //sent to every client on successful connection
    
    //create server socket
    int ser_sock=socket(AF_INET,SOCK_STREAM,0); //create a socket/entrypoint for the server
    int clientLen,nsd;

    //socket()  creates  an  endpoint  for  communication  and returns a file descriptor that refers to that endpoint
    //now before connect we need to specify the port to connect to and we do that by using a structure
    //specify an address for the socket to connect to
    struct sockaddr_in server_address,client;
    server_address.sin_family=AF_INET;//specifying the type of addtess we are working with
    server_address.sin_port=htons(9001); //htons changes the format of port number to specific structure required format(using very high port since high chances its not being used by OS)
    //server_address.sin_addr.s_addr=inet_addr("192.168.159.72"); use this when connecting through wifi on different devices
    server_address.sin_addr.s_addr=INADDR_ANY;
    //sin addr is a structure itself therefore go inside that and fill field s_addr(real server address we'll be connecting to) 
    //inaddr_any is similar as connecting to 0.0.0.0

    //bind the socket to our specified IP and Port
    // using sockaddrr inplace of sockaddr_in bcz sockaddr is more generic whereas sockaddr_in specifies IPV4 address
    bind(ser_sock,(struct sockaddr *) & server_address,sizeof(server_address));

    //listen marks the socket referred to by sockfd as a passive socket, that is,as a socket that will be used to accept incoming connection requests using accept
    listen(ser_sock,5);//The  backlog  argument i.e. value 5 defines  the  maximum length to which the queue of pending connections for sockfd may grow.

    //accept the request
    //The  accept()  system  call  is used with connection-based socket types
   //  It  extracts  the  first   connection
    //   request  on  the queue of pending connections for the listening socket
    //return file descriptor for the accepted socket.    
    // int cli_sock=accept(ser_sock,NULL ,NULL);//first null is an argument which could have been used for storing client info like where's client connecting from and second null is size of that structure.

    // //accept is a blocking call which makes the server wait for client to connect

    // //now we can send the data
    // //The send() call may be used only when the  socket  is in  a  connected
    // // state(so  that the intended recipient is known).  The only difference
    // // between send() and write() is the presence  of  flags.   With  a  zero
    // //flags  argument, send() is equivalent to write()

    
    // //close the socket
    // close(ser_sock);
    while(1){
		clientLen = sizeof(client);
		nsd=accept(ser_sock,(struct sockaddr *)&client,&clientLen);
        //send(nsd,&ser_mssg,sizeof(ser_mssg),0);

		write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));
		if(!fork()){
			close(ser_sock);	// child doesn't require sd
			serverTask(nsd);
			exit(0);
		}
		else{
			close(nsd);	// child has nsd and parent doesn't require it
		}
	}
    return 0;
}