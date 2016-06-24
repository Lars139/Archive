#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define forever for(;;)
#define YC "\x1b[33m"
#define NC "\x1b[0m"
#define Cyan "\x1b[0;36m"
#define flush while((c=getchar()) != '\n' && c!= EOF)

/////////////////////////// Chinanigan funcions ///////////////

void quit(char* instr){
	if((!strcmp(instr,"logout"))||(!strcmp(instr,"exit"))){
		printf(YC"[myShell Existed]\n"NC);
		exit(EXIT_SUCCESS);
	}
	return ;
}


void prompt(char* instr){
	char c=0;
	printf(Cyan"%c: "NC,36);
	scanf("%[^\n]",instr);
	flush;
	quit(instr);
	return ;
}

int is_cd(char *instr ){
	char* dir = malloc(sizeof(char)* sysconf(_SC_ARG_MAX));
	int cd = -1;
	for(int i = 0; instr[i+2] != '\0'; ++i){
		if(instr[i] == 'c' && instr[i+1] == 'd' && instr[i+2] == ' '){
			cd = i;
		}

	}

	if(cd>=0){
		for(int j = 0; instr[j+cd+3] != '\0'; ++j){
			dir[j] = instr[j+cd+3];
		}
		if(!strcmp(dir,"~")){
			dir = getenv("HOME");
		}

		if(chdir(dir)==-1)
			perror("chdir");
	}

	return cd;
}



// instr < or | or > count if there is 1 of each
int is_pipe_redir(char* instr){
	int p=0, ro= 0, rc=0;
	int er=0;
	for(int i=0; instr[i]!='\0'; ++i){
		if(instr[i] == '<'){
			ro++;
			er=11;
			if(instr[i+1] == '>')
				er = 12;
		}
		if(instr[i] == '>'){
			rc++;
			er=21;
			if(instr[i+1] =='<' )
				er = 22;

		}
		if(instr[i] == '|'){
			p++;
			er=3;
		}
	}

	if(p!=0 && (ro!=0 || rc!=0)){
		printf(YC"myShell is now confused (Too many pipes)\n"NC);
		er =0;
	}

	if(p>1){
		printf(YC"myShell is now confused (Too many pipes)\n"NC);
		er=0;
	}
	return er;
}
//This fucntion token stuff into 2 thing one for commnad one for file
//only use whne it is pipe/redir
void  str_tok(char* command,char* pp_dest, char* pp_flag, int pp){
	char* temp;
	int cnt =0;
	int lct=0;
	int skp = 0;
	int f = 0;
	if(pp==3){
		cnt = 0;
		for(int i = 0; command[i]!='\0'; ++i){
			if(command[i] == '|')
				lct = i;
		}
		skp=0;
		f = 0;
		for(int i = lct+1; command[i] != '\0';++i){
			if(command[lct+1]== ' ' && f==0){
				skp++;
				f=1;
			}
			pp_dest[cnt] = command[i+skp];			
			cnt++;
		}
		pp_dest[cnt+1] = '\0';
		command[lct]='\0';

	}
	if(pp==21 || pp==22){
		cnt = 0;
		for(int i = 0; command[i]!='\0'; ++i){
			if(command[i] == '>' && lct ==0)
				lct = i;
		}
		skp=0;
		for(int i = lct; command[i] == ' ' || command[i]== '>';++i){
			skp++;
		}
		f = 0;
		for(int i = lct; command[i] != '\0';++i){
			pp_dest[cnt] = command[i+skp];			
			cnt++;
		}
		pp_dest[cnt+1] = '\0';
		command[lct]='\0';

		cnt = 0;
/*		for(int i = 0; command[i] != '\0'; ++i){
			if(command[i]== ' ' && f!=0)
				cnt++;
		}
		if(cnt>0){
			pp = 99;
	   		printf(YC"Too many file input"NC);
		}
		*/
	}
//FIXME: fix pp==1 or pp =2 so that it can handle << or >>
	if(pp==11 || pp==12){
		cnt = 0;
		temp = malloc(sizeof(char)*1024);
		for(int i = 0; command[i]!='\0'; ++i){
			if(command[i] == '<' && lct ==0)
				lct = i;

		}
		for(int i = 0; i < lct;++i){
			pp_dest[cnt] = command[i];			
			cnt++;
		}
		pp_dest[cnt-1] = '\0';
		skp = 0;
		for(int i = lct; command[i] == ' ' || command[i]== '<';++i){
			skp++;
		}
		cnt = 0;
		f=0;
		for(int i = 0; command[i+lct+1] != '\0';i++){
			command[i] = command[i+lct+skp];
			cnt++;
		}
	command[cnt]='\0';	
	}
	return ;
}

int my_system(char *command){
	sigset_t  origMask;
	struct sigaction saOrigQuit, saOrigInt, saDefault;
	pid_t childPid;
	int status ;
	int cd=0;
	int pfd[2];
	int ex=0;
	int pp = 0;
	int file = 0;
	char* pp_dest = malloc(sizeof(char)*1024);
	char* pp_flag = malloc(sizeof(char)*1024);

	cd = is_cd(command);
	pp = is_pipe_redir(command);
	if(pp!=0)
		str_tok(command, pp_dest, pp_flag, pp);
/*	
	   printf("pp_dest: %s\n"NC,pp_dest);
	   printf("pp_flag: %s\n"NC,pp_flag);
	   printf("command: %s\n"NC,command);
*/	   

	//This secion handling normal execution that is not "cd ..."
	if(cd==-1 && pp==0){
		switch(childPid = fork()){ //creating child process
			case -1: //fail to create a child
				status = -1;
				break;
			case 0:  //in child process
				saDefault.sa_handler = SIG_DFL;
				saDefault.sa_flags = 0;
				sigemptyset(&saDefault.sa_mask);

				if(saOrigInt.sa_handler != SIG_IGN)
					sigaction(SIGINT, &saDefault, NULL);
				if(saOrigQuit.sa_handler != SIG_IGN)
					sigaction(SIGQUIT, &saDefault, NULL);
				sigprocmask(SIG_SETMASK, &origMask,NULL);


				ex = execl("/bin/sh","sh","-c",command, (char*) NULL);

				//This doesn't get the program out of ls | error
				if(ex==-1){
					_exit(EXIT_FAILURE);
				}

				if(pp==3){
					if(close(pfd[1]==-1)) //close the read end
						perror("Writing Pipe (Child proc)");
				}

				_exit(127);

			default: //in parents process
				while(waitpid(childPid, &status, 0) == -1){
					//wait for child
					if(errno != EINTR){
						status = -1;
						break;
					}
				}
				break;
		}

	}


	///////////////////This secion handling pipe in the shell

	if(cd == -1 && pp==3){
		if(pipe(pfd)==-1){
			perror("Pipe");
		}

		printf(YC"before first fork\n"NC);
		//		printf(YC"[myShell pipes]\n"NC);
		switch(fork()){
			case -1:
				status = -1;
				exit(EXIT_FAILURE);
				break;
			case 0:
				//	printf(YC"Child 1\n"NC);
				if(close(pfd[0]) == -1){
					perror("close - pfd[0] Child");
					exit(EXIT_FAILURE);

				}
				if(pfd[1] != STDOUT_FILENO){
					if(dup2(pfd[1],STDOUT_FILENO) == -1){
						perror("dup2 - pfd[1]");
						exit(EXIT_FAILURE);
					}
					/*		if(close(pfd[1]) == -1){
							perror("close1 - pfd[1]");
							exit(EXIT_FAILURE);
							}
							*/
				}
				//		printf(YC"#command: %s\n" NC,command);
				//execlp(command,command,(char*) NULL);
				execl("/bin/sh","sh","-c",command, (char*) NULL);
				perror("execlp first");

			default:
				break;
		}

		printf(YC"before second fork\n"NC);
		switch(fork())	{
			case -1:
				status = -1;
				exit(EXIT_FAILURE);
				break;

			case 0:
				//	printf(YC"Child 2\n"NC);
				if(close(pfd[1]) == -1){
					perror("close2 - pfd[1]");
					exit(EXIT_FAILURE);
				}
				if(pfd[0] != STDIN_FILENO){
					if(dup2(pfd[0], STDIN_FILENO) == -1){
						perror("dup2 - pfd[0]");
						exit(EXIT_FAILURE);
					}
					if(close(pfd[0])== -1){
						perror("close - pfd[0]");
						exit(EXIT_FAILURE);
					}
				}
				printf(YC"#pp_dest: %s\n"NC, pp_dest);
				printf(YC"#pfd[0]: %d\n"NC, pfd[0]);
				
				//execlp(pp_dest,pp_dest,pp_flag,(char*) NULL);
				execl("/bin/sh","sh","-c",pp_dest, (char*) NULL);
				perror("execlp second");

			default:
				break;
		}
		printf("I am here closing suttf in Parent");
		if(close(pfd[0]) ==-1){
			perror("Parent close 0");
			exit(EXIT_FAILURE);

		}
		if(close(pfd[1]) ==-1){
			perror("Parent close 1");
			exit(EXIT_FAILURE);
		}
		printf(YC"Here b4 wait1"NC);
		if(wait(NULL)==-1){
			perror("wait1");
			exit(EXIT_FAILURE);
		}
		printf(YC"Here after wait1"NC);
		if(wait(NULL)==-1){
			perror("wait2");
			exit(EXIT_FAILURE);
		}
		//	printf(YC"ENDING [myShell pipes]\n"NC);
	}
	/////////////////////This section dealing with redirecting

	if(cd == -1 && (pp==21 || pp==22 || pp==11 ||pp==12)){

		switch(fork()){
			case -1:
				perror("File dir pipe");
				exit(EXIT_FAILURE);
				break;
			case 0:
				//FIXME: continue from here P.575
				//need to open and pip-write to a file
				//command always executable, pp_dest is a file
				//also need to change pp=-1 at the end.
				//	execlp(command,command,(char*) NULL);
				if(pp==21 || pp == 11){
					file = open(pp_dest, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
					if(file != STDOUT_FILENO){
						dup2(file, STDOUT_FILENO);
						close(file);
					}
				}
				if(pp==22 || pp == 12){
					file = open(pp_dest, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
					if(file != STDOUT_FILENO){
						dup2(file, STDOUT_FILENO);
						close(file);
					}
				}
				execl("/bin/sh","sh","-c",command, (char*) NULL);
				perror("execlp first");

			default:
				break;

		}


	}
	return status;
}


///////////////////////////// MAIN ////////////////////////////
int main(int argc, char** argv){
	int arg_max = sysconf(_SC_ARG_MAX);
	char instr[arg_max];
	sigset_t blockMask, origMask;
	struct sigaction saIgnore, saOrigQuit, saOrigInt ;
	int savedErrno;




	forever{
		sigemptyset(&blockMask);
		sigaddset(&blockMask, SIGCHLD);
		sigprocmask(SIG_BLOCK, &blockMask, &origMask);

		saIgnore.sa_handler = SIG_IGN;
		saIgnore.sa_flags = 0;
		sigemptyset(&saIgnore.sa_mask);
		sigaction(SIGINT, &saIgnore, &saOrigInt);
		sigaction(SIGQUIT, &saIgnore, &saOrigQuit);



		prompt(instr);
		my_system(instr);

		savedErrno = errno;
		sigprocmask(SIG_SETMASK, &origMask, NULL);
		sigaction(SIGINT, &saOrigInt, NULL);
		sigaction(SIGQUIT, &saOrigQuit, NULL);
		errno = savedErrno;
		//	printf("%s", instr);
	}

	return 0;
}
