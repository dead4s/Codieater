#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 

int* memoryUsage[500]; 


int main(){
	//check memory usage
	
	for(int i = 0; 	i < 500; i++){
		memoryUsage[i] = (int*)malloc(1000'000); 
		for(int j = 0; j < 20; j++){
			memoryUsage[i][j] = j; 
		}
	}
	
	//check nproc
	//system("ls -al"); 
	printf("helloword!!"); 

	//check fileno
	/*int fd = open("foo.txt", O_RDWR, 0777);
    	if(fd == -1)
        	perror("open");
	*/
	return 0; 
}
