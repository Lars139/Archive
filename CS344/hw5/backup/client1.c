#include "ud_ucase.h"
#define HIT_RATE 0.8 

int play_tennis(float hit_rate){
	int hit = 0;
	int hr = hit_rate*100;
	if(rand()%100 < hr)
		hit = 1;
	else if(rand()%100 >= hr){
		hit = 0;
	}
	return hit;
}

int main(int argc, char* argv[]){
	struct sockaddr_un svaddr, claddr;
	int sfd;
	char hit[2] = "0";
	ssize_t err;
	char resp[BUF_SIZE];
	int go=0;
	char ping[3] = "999";
	int ping_z = 0;
	hit[1] = '\0';


	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sfd == -1){
		perror("Client socket()");
		exit(EXIT_FAILURE);
	}
	//Creating client socket
	memset(&claddr, 0 , sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;
	snprintf(claddr.sun_path, sizeof(claddr.sun_path), "/tmp/ud_ucase_cl.%ld", (long) getpid());

	if(bind(sfd, (struct sockaddr *) &claddr, sizeof(struct sockaddr_un)) == -1 ){
		perror("Client socket()");
		exit(EXIT_FAILURE);
	}

	//Estrablishing connection with server
	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	//FIXME: SV_SOCK_PATH(1 or 2)
	strncpy(svaddr.sun_path, SV_SOCK_PATH2, sizeof(svaddr.sun_path)-1);


	//Ping to indicate connection
	ping_z = 3;
	if(sendto(sfd,&ping, ping_z, 0, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) != ping_z){
		perror("Client ping sendto()");
		exit(EXIT_FAILURE);
	}

	//Sending the hit/miss info
	while(1){
		err= recvfrom(sfd,resp, BUF_SIZE, 0, NULL, NULL);
		if(err== -1){
			perror("Client recvfrom()");
			exit(EXIT_FAILURE);
		}
		go = atoi(resp);
		if(go==1){
			sprintf(hit,"%d",play_tennis(HIT_RATE));
			hit[1] = '\0';

			if(sendto(sfd,&hit, 1, 0, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) != 1){
				perror("Client sendto()");
				exit(EXIT_FAILURE);
			}
			go = 0;
		}else if(go==2){
			exit(EXIT_SUCCESS);
		}

	}
}
