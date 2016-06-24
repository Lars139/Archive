#include "ud_ucase.h"
#define forever for(;;)

void print_score(int *score){
	for(int i = 0; i < 2; ++i){
		if(score[i] < 3){
			if(i==0)
			printf(YC"\tPlayer1 score: %d \t"NC, score[i]*15);
			else if(i==1)
			printf(YC"\tPlayer2 score: %d \n\n"NC, score[i]*15);
		}
		if(score[i] == 3){
			if(i==0)
			printf(YC"\tPlayer1 score: %d \t"NC, 40);
			else if(i==1)
			printf(YC"\tPlayer2 score: %d \n\n"NC, 40);
		}
		if(score[i] == 4){
			if(i==0)
			printf(YC"\tPlayer1 score: %d \t"NC, 60);
			else if(i==1)
			printf(YC"\tPlayer2 score: %d \n\n"NC, 60);
		}
	}
}

int* mk_soc(struct sockaddr_un *svaddr){
	int *sfd = (int*) malloc(sizeof(int)*2);

	sfd[0] = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sfd[0] == -1){
		perror("Sever socket()");
		exit(EXIT_FAILURE);
	}

	if(remove(SV_SOCK_PATH1) == -1 && errno != ENOENT){
		perror("Server remove()");
		exit(EXIT_FAILURE);
	}


	memset(svaddr, 0, sizeof(struct sockaddr_un));
	svaddr->sun_family = AF_UNIX;
	strncpy(svaddr->sun_path, SV_SOCK_PATH1, sizeof(svaddr->sun_path) -1 );

	if(bind(sfd[0], (struct sockaddr *) svaddr, sizeof(struct sockaddr_un)) == -1){
		perror("bind()");
		exit(EXIT_FAILURE);

	}

	/////////////////////////DIS IS SEC SOC //////////////
	sfd[1] = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sfd[1] == -1){
		perror("Sever socket()");
		exit(EXIT_FAILURE);
	}

	if(remove(SV_SOCK_PATH2) == -1 && errno != ENOENT){
		perror("Server remove()");
		exit(EXIT_FAILURE);
	}


	memset(svaddr, 0, sizeof(struct sockaddr_un));
	svaddr->sun_family = AF_UNIX;
	strncpy(svaddr->sun_path, SV_SOCK_PATH2, sizeof(svaddr->sun_path) -1 );

	if(bind(sfd[1], (struct sockaddr *) svaddr, sizeof(struct sockaddr_un)) == -1){
		perror("bind()");
		exit(EXIT_FAILURE);

	}


	return sfd;
}

int main(int argc, char **argv){
	struct sockaddr_un svaddr ;
	struct sockaddr_un claddr;
	struct sockaddr_un player[2];
	int *sfd = mk_soc(&svaddr);
	ssize_t numBytes = 2;
	socklen_t len;
	char go_permit[2] = "1";
	char release[2] = "2";
	char buf[BUF_SIZE];
	int connected[2] = {0,0};
	int hit_tracker[2] = {0,0};
	int score[2] = {0,0};

	len = sizeof(struct sockaddr_un);
	//Waiting for both of the client to connect
	do{
		//once the client connect keep track of its socket 
		numBytes = recvfrom(sfd[0], buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
		if(numBytes==-1){
			perror("recvform()");
			exit(EXIT_FAILURE);
		}
		if(numBytes<BUF_SIZE){
			buf[numBytes]='\0';
		}
		if(atoi(buf) == 999 && connected[0]==0){
			memset(&(player[0]),0,sizeof(struct sockaddr_un));
			player[0].sun_family = AF_UNIX;
			strncpy(player[0].sun_path, claddr.sun_path,sizeof(player[0].sun_path)-1);
			connected[0]= 1;
		}
		//the second client connect keep track of its socket 
		numBytes = recvfrom(sfd[1], buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
		if(numBytes==-1){
			perror("recvform()");
			exit(EXIT_FAILURE);
		}
		if(numBytes<BUF_SIZE){
			buf[numBytes]='\0';
		}
		if(atoi(buf) == 999 && connected[1]==0){
			memset(&(player[1]),0,sizeof(struct sockaddr_un));
			player[1].sun_family = AF_UNIX;
			strncpy(player[1].sun_path, claddr.sun_path,sizeof(player[0].sun_path)-1);
			connected[1]= 1;
		}
	}while(connected[0] == 0 || connected[1] == 0);
	printf("The game may now begin!\n");

	forever{
		//FIXME:Why is it not continuing in infinite loop? 
		//need a while-loop keeping track of hit/miss and score
		//Player 1
		if(sendto(sfd[0], go_permit, 2, 0, (struct sockaddr *) &(player[0]), len) != 2){
			perror("Player1 sendto()");
			exit(EXIT_FAILURE);
		}
		numBytes =  recvfrom(sfd[0], buf, BUF_SIZE, 0, NULL,NULL); 
		if(numBytes == -1){
			perror("recvform()");
			exit(EXIT_FAILURE);
		}
		if(numBytes<BUF_SIZE){
			buf[numBytes]='\0';
		}
		if(atoi(buf) == 1){
			(hit_tracker[0])++;
		}

//		printf("Server received %ld bytes from %s: %s\n", (long) numBytes, player[0].sun_path, buf);
		printf("  Player1 Hit: %s\n"NC,buf);

		//SECOND Plyaer hit
		if(sendto(sfd[1], go_permit, 2, 0, (struct sockaddr *) &(player[1]), len) != 2){
			perror("Playe2 sendto()");
			exit(EXIT_FAILURE);
		}
		//		numBytes =  recvfrom(sfd[1], buf, BUF_SIZE, 0, (struct sockaddr *) &(player[1]), &len); 
		numBytes =  recvfrom(sfd[1], buf, BUF_SIZE, 0, NULL,NULL); 
		if(numBytes == -1){
			perror("recvform()");
			exit(EXIT_FAILURE);
		}
		if(numBytes<BUF_SIZE){
			buf[numBytes]='\0';
		}
		if(atoi(buf) == 1){
			(hit_tracker[1])++;
		}
//		printf("Server received %ld bytes from %s: %s\n", (long) numBytes, player[1].sun_path, buf);
		printf("  Player2 Hit: %s\n"NC,buf);
		if(hit_tracker[0] - hit_tracker[1] == 1){
			hit_tracker[0] = 0;
			hit_tracker[1] = 0;
			(score[0])++;
			printf(CYAN"Player 1 won this ball\n"NC);
			print_score(score);
			//FIXME: break only when the score reach not the ball
		}else if(hit_tracker[1] - hit_tracker[0] ==1){
			hit_tracker[0] = 0;
			hit_tracker[1] = 0;
			(score[1])++;
			printf(CYAN"Player 2 won this ball\n"NC);
			print_score(score);
		}

		if(score[1] == 4 || score[0]==4){
			if(sendto(sfd[0], release, 2, 0, (struct sockaddr *) &(player[0]), len) != 2){
				perror("Playe1 sendto stop()");
				exit(EXIT_FAILURE);
			}
			if(sendto(sfd[1], release, 2, 0, (struct sockaddr *) &(player[1]), len) != 2){
				perror("Playe2 sendto stop()");
				exit(EXIT_FAILURE);
			}
			if(score[0]==4)
				printf(PC"\n\t\tPlayer 1 won the match!\n"NC);
			if(score[1]==4)
				printf(PC"\n\t\tPlayer 2 won the match!\n"NC);
			break;
		}

	}
	free(sfd);
}



