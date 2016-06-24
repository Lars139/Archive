#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define YC "\x1b[33m"
#define PC "\x1b[38;05;199m"
#define SC "\x1b[38;05;67m"
#define NC "\x1b[0m"
#define CYAN "\x1b[36m"
#define forever for(;;)

int cntr=0;
int flags = 0;
int GO = 0;
int proc_thread = 0;
int wait_thread = 0;
pthread_cond_t cond_t;
pthread_mutex_t mtx;

typedef struct {
	int me;
	int opp;
	int hit;
	float hr;
	int pt;
}thread_info;

////////////////////////////// Function    ///////////////////////////////
//Func: play_tennis()
//This function random wether the playing is hitting or missing the ball
//targv->hit = 0 is a miss
void play_tennis(thread_info *targv){
	int hitrate =0;
	int hrm=1;
//	printf(PC"targv[%d]->hr: %.3f\n"NC,targv->me,targv->hr);
	hitrate = (targv->hr)*100;
	hrm = rand()%100;
	if(hrm <= hitrate){
		targv->hit = 1;
	}else{
		targv->hit = 0;
	}
	return;
}

int count_score(thread_info *targv, int *score, int *hit_tracker){
	int re = 1;
	//FIXME: make the tennis rules here
	if(targv[GO].hit == 1){
		(hit_tracker[GO])++;
	}
	if(hit_tracker[0] - hit_tracker[1] ==1){
		hit_tracker[0] = 0;
		hit_tracker[1] = 0;
		(score[0])++;
		printf(CYAN"Player 1 won this ball\n\n"NC);
	}else if(hit_tracker[1] - hit_tracker[0] ==1){
		hit_tracker[0] = 0;
		hit_tracker[1] = 0;
		(score[1])++;
		printf(CYAN"Player 2 won this ball\n\n"NC);
	}

	if(score[GO] < 3)
		targv[GO].pt = score[GO]*15;
	else if(score[GO] == 3)
		targv[GO].pt = 40;
	else if(score[GO] == 4)
		targv[GO].pt = 60;

	if(score[0] == 4 || score[1] == 4){
		if(score[0]==4)
		printf(PC"Player 1 won the match\n\n"NC);
		if(score[1]==4)
		printf(PC"Player 2 won the match\n\n"NC);

		re = 0;
	}
	return re;
}

void print_all(thread_info *targv){
	for(int i = 0; i<2; ++i){
		printf("Player%d score: %d\n",targv[i].me, targv[i].pt );
//		printf(SC"   Hit Rate: "NC"%.3f\n",targv[i].hr );
//		printf(SC"   Hit/Miss?: "NC"%d\n",targv[i].hit );
//		printf(SC"   Score: "NC"%d\n",targv[i].pt );
	}
	return; 
}

////////////////////////////// Thread Func ///////////////////////////////

//Func: in_thread()
//This is the task of each thread.
void* in_thread(void *in_targv){
	thread_info *targv = in_targv;
	if(GO == targv->me)
		play_tennis(targv);

	pthread_mutex_lock(&mtx);{
		cntr++;
		if(cntr== 3){
			GO = (GO+1)%2;
			pthread_cond_broadcast(&cond_t);
			flags = 1;
		}else{
			while(flags==0)
				pthread_cond_wait(&cond_t, &mtx);
		}
	}pthread_mutex_unlock(&mtx);

	if(GO == targv->me)
		play_tennis(targv);

	pthread_mutex_lock(&mtx);{
		cntr--;
		if(cntr==0){
			GO = (GO+1)%2;
			pthread_cond_broadcast(&cond_t);
			flags = 0;
		}else{
			while(flags==1)
				pthread_cond_wait(&cond_t, &mtx);
		}
	}pthread_mutex_unlock(&mtx);
	return NULL;
}

//Func: ini_thread()
//This function initialize value of each player
//me = index for the thread
//opp = index for the other player
//hti = 0 is not a miss.
void init_thread(thread_info *targv){
	(targv[0]).me = 0;
	(targv[0]).opp = 1;
	(targv[0]).hit = 0;
	(targv[0]).hr = 0.8;
	(targv[0]).pt= 0;
	(targv[1]).me = 1;
	(targv[1]).opp = 0;
	(targv[1]).hit = 0;
	(targv[1]).hr = 0.8;
	(targv[1]).pt= 0;
}

///////////////////////////// The main land ///////////////////////////

int main(int argc, char* argv[]){
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond_t, NULL);

	pthread_t pid[2] = {0,0};
	thread_info player[2];

	int err = 0;
	int re = 1;
	int score[2] = {0,0};
	int hit_tracker[2] = {0,0};

	init_thread(player);
	//This is the new thread
	forever{
		for(int i = 0; i < 2; ++i){
			err = pthread_create(&(pid[i]), NULL, in_thread, &(player[i]));
			if(err==-1){
				perror("pthread_create()");
				exit(EXIT_FAILURE);
			}
		}

		//FIXME: count score
		GO = 0;
		print_all(player);
		re = count_score(player, score, hit_tracker);
		if(!re)
			break;

		pthread_mutex_lock(&mtx);{
			cntr++;
			if(cntr== 3){
				pthread_cond_broadcast(&cond_t);
				flags = 1;
			}else{
				while(flags==0)
					pthread_cond_wait(&cond_t, &mtx);
			}
		}pthread_mutex_unlock(&mtx);

		//FIXME: count score
		GO = 1;
		print_all(player);
		re = count_score(player, score, hit_tracker);
		if(!re)
			break;

		pthread_mutex_lock(&mtx);{
			cntr--;
			if(cntr==0){
				pthread_cond_broadcast(&cond_t);
				flags = 0;
			}else{
				while(flags==1)
					pthread_cond_wait(&cond_t, &mtx);
			}
		}pthread_mutex_unlock(&mtx);
		pthread_join(pid[0],NULL);
		pthread_join(pid[1],NULL);

	}

	//////////end ref thread

	//FIXME: join the thread
	//FIXME: count score
	return 0;
}
