#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define YC "\x1b[33m"
#define SC "\x1b[38;05;67m"
#define NC "\x1b[0m"
#define CYAN "\x1b[36m"

int main(int argc, char** argv){
	int fd;
	size_t len;
	char *addr;
	int status;
	pid_t c_pid,pid;
	int s;
	struct stat sb;
	char *buff;

	fd = shm_open("./shared_mem", O_RDWR | O_CREAT, 0666);
	if(fd ==-1){
		perror("shm_open()");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(fd, 1024)==-1){
		perror("ftruncate()");
		exit(EXIT_FAILURE);
	}


	switch(c_pid = fork()){
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		case 0:
			printf(CYAN"###### \tIN CHILD PROC \t#####\n");

			pid = getppid();
			printf(SC"Parent ID:"NC" %d\n",pid);
			pid = getpid();
			printf(SC"My ID:"NC" %d\n",pid);

			addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, NULL);
			if(addr == MAP_FAILED){
				perror("mmap()");
				exit(EXIT_FAILURE);
			}
			printf(SC"Shared memory addr:"NC" %p\n",addr);

			if(fstat(fd,&sb)==-1){
				perror("fstat()");
				exit(EXIT_FAILURE);
			}
			printf(SC"Shared memory size:"NC" %lu\n",sb.st_size);
			read(fd, buff, sb.st_size);
	
			write(STDOUT_FILENO, buff, sb.st_size );
			exit(EXIT_SUCCESS);
		case 1:
			while(waitpid(c_pid, &status, 0) == -1){
				perror("waitpid");
				exit(EXIT_FAILURE);

			}
			break;
	}
	printf(CYAN"###### \tIN PARENT PROC \t#####\n");
	pid = getpid();
	printf(SC"My ID:"NC" %d\n",pid);
	printf(SC"Child ID:"NC" %d\n",c_pid);
	addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, NULL);
	if(addr == MAP_FAILED){
		perror("mmap()");
		exit(EXIT_FAILURE);
	}

	printf(SC"Shared memory addr:"NC" %p\n",addr);
	if(fstat(fd,&sb)==-1){
		perror("fstat()");
		exit(EXIT_FAILURE);
	}
	printf(SC"Shared memory size:"NC" %lu\n",sb.st_size);
	read(fd, buff, sb.st_size);
	if(close(fd) == -1){
		perror("close()");
		exit(EXIT_FAILURE);
	}

	write(STDOUT_FILENO, buff, sb.st_size );

	if(shm_unlink("./shared_mem") == -1){
		perror("shm_unlink()");
		exit(EXIT_FAILURE);
	}
	return 0;
}
