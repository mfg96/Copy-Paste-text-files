//Muhammad Faraz Sohail
//CopyPaste(OS fundamentals)

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 255

int readLine (int fd, char *buff,int n)
{
	int i=0, m;                          //without exceeding buff size n 
  	
	  //reading character by character to even include spaces and next line characters to copy
	  while(i<n && (m=read(fd, &buff[i], 1))==1){
	    if(buff[i]=='\n') //at next line character reader stops and returns the line given to be written to file
	      return(i+1);
	    i++;
	  }
	  if(m == -1)    // Error reading file
	    return(-1);
	  else
	    return(i);   // number of characters read or 0 for EOF
}

int main(int argc, char *argv[]){
	
	int x,status=0;
	char buf[SIZE],src[SIZE],dest[SIZE]="output.txt";

//if there are less cmd arguments then perform this action to get file names
if( argc<2){
	printf("Please enter Source file name: ");
	scanf("%s",src);
	argv[1]=src;
	printf("Please enter Destination file name: ");
	scanf("%s",dest);
	argv[2]=dest;
}


//checks if the file is there or not
 if(argv[1]==NULL)
    {
        perror("Error! Missing Source file to copy from.\n");
        exit(1);
    }

	if(argv[2]==NULL)
	{
		argv[2]=dest;
	}

	
    int fd1=open(argv[1],O_RDONLY);

	if(fd1<0){
		perror("Error! Unable to open file to read.");
		exit(1);
	}

	int fd2=open(argv[2],O_WRONLY | O_APPEND | O_CREAT);

	if(fd2<0){
		perror("Error! Unable to open file to write.");
		exit(1);
	}
	
	
	
	
   
	
	while((x=readLine(fd1,buf,SIZE))>0){
		
		
		if(x<=0)
			break;
		
		

		  if(write(fd2,buf,x)!=x){
				  perror("Error! Unable to write to the file.");
				  exit(1);
			  }
		
	   
	    }
	    if(x==-1)
	      perror("Reading error ");
		
	close(fd1);
	close(fd2);
	exit(0);
}
