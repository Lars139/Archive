#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define forever for(;;)
#define YC "\x1b[33m"
#define PC "\x1b[38;05;199m"
#define SC "\x1b[38;05;67m"
#define NC "\x1b[0m"
#define CYAN "\x1b[36m"
#define VoG  6.67*pow(10,-11)
#define PI 3.14159265358978323846264338327950288
#define FLUSH while((c=getchar()) != '\n' && c!=EOF)

/////////////////////////////// Structs Declaration ///////////////////

typedef struct{
	float x, y, z; //printed location
	float sx, sy, sz; // new displacement
	float vx, vy, vz;
	float ax, ay, az;
	float fx, fy, fz;
	float tf;
	float theta, phi;

	double m;

}obj;

typedef struct{
	int idx;
	int group_size;
}thread_info;

typedef struct{
	int num_astr;
	obj *astr;
	thread_info *t_info;
	int t;
	suseconds_t proc_t;
}thread_argv;

pthread_barrier_t barrier;

////////////////////////////  Normal functions //////////////////////////
//Func: argv_handler
//Determine what flag is being called from argv
//flags = [t | n | p | v | c | q ]
void argv_handler(int argc, char **argv, int *flags){
	char c;
	char *str;
	for(int i = 0; i < 6; ++i){
		flags[i] = 0;
	}
	while((c = getopt(argc, argv, "t:n:p:cqv"))!= -1){
		//FIXME: getopt causing me problem
		switch(c){
			case 't':
				str = optarg;
				flags[0] = atoi(str);
				break;
			case 'n':
				str = optarg;
				flags[1] = atoi(str);
				break;
			case 'p':
				str = optarg;
				flags[2] = atoi(str);
				break;
			case 'v':
				flags[3] = 1;
				break;
			case 'c':
				flags[4] = 1;
				break;
			case 'q':
				flags[5] = 1;
				break;
			case '?':
				if(optopt == 't' || optopt =='n' || optopt =='p')
					fprintf(stderr,"-%c requires an argument.\n",optopt);
				return ;
			default:
				abort();
		}
	}
	if(flags[0] == 0 || flags[1] == 0 || flags[2] == 0){
		printf(YC"Error: Insufficient information\n"NC);
		printf(YC"Ex: ./sieve -t [time intev] -n [#obj] -p [#threads] [-cqv]\n"NC);
		exit(EXIT_FAILURE);
	}

	if(flags[0] <= 0 || flags[1] <= 0 || flags[2] <= 0){
		printf(YC"Error: #thread, #astr, #thread must not be a negative number\n"NC);
		printf(YC"Ex: ./sieve -t [time intev] -n [#obj] -p [#threads] [-cqv]\n"NC);
		exit(EXIT_FAILURE);
	}

	if(flags[2] > flags[1]){
		printf(YC"A number of particle must not be less than a number of threads\n"NC);
		exit(EXIT_FAILURE);

	}

	if(flags[3] == 0 && flags[5] ==0){
		flags[4] = 1;
	}

}


//Func: prompt()
//This funtion prompt for the values of num_thread and num_astr 
//Then allocate the momory for that many astr
//Also allocate the momory for thread info for that many thread
//flags = [t | n | p | v | c | q ]
void prompt(int *num_thread, int *num_astr, thread_info *t_info, obj **astr, int *flags, int *max_t){
	//int re = 1;
	(*num_thread) = flags[2];
	(*num_astr) = flags[1];
	(*max_t) = flags[0];
/*	do{
		if((*num_thread) <= 0){
			printf(CYAN"Number of thread: "NC);
			scanf("%d", num_thread);
			re = 0;
		}
		if((*num_astr) <= 0){
			printf(CYAN"Number of asteriod: ");
			scanf("%d", num_astr);
			re = 0;
		}
		if((*max_t) <= 0){
			printf(CYAN"Upper time limit: ");
			scanf("%d", max_t);
			re = 0;
		}

		if((*num_thread)<=0){
			printf(YC"\nNumber of thread must be greater than zero.\nPlease try again.");
			re = 1;
		}
		if((*num_astr)<=0){
			printf(YC"\nNumber of asteriod must be greater than zero.\nPlease try again.");
			re = 1;
		}
		if((*max_t)<0){
			printf(YC"\nUpper time be greater than zero.\nPlease try again.");
			re = 1;
		}
	}while(re);
*/
	(*astr) = malloc(sizeof(obj)* (*num_astr));
	t_info->idx = 0;
	t_info->group_size = (*num_astr)/(*num_thread);

	return ;
}

//Func: ini_astr()
//This function set initial values for every asteroid
void ini_astr(int num_astr, obj *astr){
	for(int i = 0; i < num_astr; ++i){
		do{
			(astr[i]).m = rand()%(int) pow(10,rand()%7);
		}while((astr[i]).m == 0);
		(astr[i]).x = rand()%(int) pow(10,rand()%4);
		(astr[i]).y = rand()%(int) pow(10,rand()%4);
		(astr[i]).z = rand()%(int) pow(10,rand()%4);
		(astr[i]).sx = (astr[i]).x;
		(astr[i]).sy = (astr[i]).y;
		(astr[i]).sz = (astr[i]).z;
		(astr[i]).vx = 0;
		(astr[i]).vy = 0;
		(astr[i]).vz = 0;
		(astr[i]).ax = 0;
		(astr[i]).ay = 0;
		(astr[i]).az = 0;
		(astr[i]).fx = 0;
		(astr[i]).fy = 0;
		(astr[i]).fz = 0;
		(astr[i]).theta = 0;
		(astr[i]).phi = 0;

	}
}
//Func: print_all()
//This function print everything from the astr arr
void print_all(int num_astr, obj * astr, int t){
	printf(PC"Time: %d\n"NC,t);
	for(int i = 0; i < num_astr; ++i){
		printf(YC"astr[%d]\n"NC,i);
		printf(CYAN"Mass:"NC "  %3E\n", (astr[i]).m);
		printf(CYAN"Position:\n"NC);
		printf("  sx: %.3E\n",(astr[i]).x);
		printf("  sy: %.3E\n",(astr[i]).y);
		printf("  sz: %.3E\n",(astr[i]).z);
		printf(CYAN"Speed:\n"NC);
		printf("  vx: %.3E\n",(astr[i]).vx);
		printf("  vy: %.3E\n",(astr[i]).vy);
		printf("  vz: %.3E\n",(astr[i]).vz);
		printf(CYAN"Acceleration:\n"NC);
		printf("  ax: %.3E\n",(astr[i]).ax);
		printf("  ay: %.3E\n",(astr[i]).ay);
		printf("  az: %.3E\n",(astr[i]).az);
		printf(CYAN"Force:\n"NC);
		printf("  Fx: %.3E\n",(astr[i]).fx);
		printf("  Fy: %.3E\n",(astr[i]).fy);
		printf("  Fz: %.3E\n",(astr[i]).fz);
		printf(CYAN"Total Force with Angles:\n"NC);
		printf("  Fz: %.3E\n",(astr[i]).tf);
		printf("  Theta: %.3E\n",(astr[i]).theta);
		printf("  Phi  : %.3E\n",(astr[i]).phi);
		printf("\n");
	}
	return ;
}

void print_c(int num_astr, obj* astr, int t){

	printf(CYAN"Time: %d\n"NC,t);
	for(int i = 0; i < num_astr; ++i){
		printf(YC"  astr[%d]:\t"NC,i);
		printf(SC"m: "NC);
		printf("%.3E\t", (astr[i]).m);
		printf(SC"s: "NC);
		printf("< %.3E, %.3E, %.3E >\n", (astr[i]).x, (astr[i]).y, (astr[i]).z);

	}
	return ;
}

void print_q(int num_threads, thread_argv *targv, int t){
	printf(YC"Time step: %d\n"NC,t);
	printf(CYAN"N-body: %d\n"NC,targv->num_astr);
	printf(CYAN"Total number of thread: %d\n"NC,num_threads);
	printf(CYAN"(Time of each thread in usec)\n"NC);
	for(int i = 0; i < num_threads; ++i){
		printf(SC"\tthread#%d:"NC" %ld",i,targv[i].proc_t);
		if(i%3==0 )
			printf("\n");
	}
	printf("\n");

	return ;
}
///////////////////////////// Calculating Function ////////////////////

//Func: void calc_f()
//Calculate the total force of all particle acting upon a particle
//This function takes care of it for all particle in the array
// To make it only calc a set of num_astr change the i-for-loop to match the group_size  AND make i = idx
void calc_f(int num_astr, obj *astr, thread_info t_info ){
	for(int i = t_info.idx; i < (t_info.group_size) + (t_info.idx); ++i){
		for(int j = 0; j < num_astr; ++j){
			if(i!=j){
				//F = Gm1m2 / r^2
				// X-axis
				if((astr[i]).x > (astr[j]).x){
					(astr[i]).fx += (-1) * ((VoG) * (astr[i]).m * (astr[j]).m)/pow((astr[i]).x - (astr[j]).x,2);
				}
				if((astr[i]).x < (astr[j]).x){
					(astr[i]).fx += ((VoG) * (astr[i]).m * (astr[j]).m)/pow((astr[i]).x - (astr[j]).x,2);
				}

				// Y-axis
				if((astr[i]).y > (astr[j]).y){
					(astr[i]).fy += (-1) * ((VoG) * (astr[i]).m * (astr[j]).m)/pow((astr[i]).y - (astr[j]).y,2);
				}
				if((astr[i]).y < (astr[j]).y){
					(astr[i]).fy += ((VoG) * (astr[i]).m * (astr[j]).m)/pow((astr[i]).y - (astr[j]).y,2);
				}

				// Z-axis
				if((astr[i]).z > (astr[j]).z){
					(astr[i]).fz += (-1) * ((VoG) * (astr[i]).m * (astr[j]).m)/pow((astr[i]).z - (astr[j]).z,2);
				}
				if((astr[i]).z < (astr[j]).z){
					(astr[i]).fz += ((VoG) * (astr[i]).m * (astr[j]).m)/pow((astr[i]).z - (astr[j]).z,2);
				}

				//In case obj locate on the same plane, there is not force exert from the axis of the plane
				if((astr[i]).x == (astr[j]).x){
					(astr[i]).fx += 0;
				}
				if((astr[i]).y == (astr[j]).y){
					(astr[i]).fy += 0;
				}
				if((astr[i]).z == (astr[j]).z){
					(astr[i]).fz += 0;
				}
			}
		}
	}
	return;
}

//Func: total_f()
//This function takes value from stuct *astr (fx,fy,fz) 
//And find the Total force along with its direction
//For a given set of num_astr = group_size (if needed)
void total_f(int num_astr, obj *astr, thread_info t_info){
	float rad_theta = 0, rad_phi = 0;
	for(int i = t_info.idx; i < (t_info.group_size) + (t_info.idx); ++i){
		(astr[i]).tf = pow((pow((astr[i].fx),2) + pow((astr[i]).fy,2) + pow((astr[i]).fz,2))  ,(float)1/ (float) 2);
		rad_theta = (-1) * atan((astr[i]).x / (astr[i]).y);
		rad_phi = atan( (astr[i]).z /  pow((pow((astr[i].fx),2) + pow((astr[i]).fy,2)),(float)1/ (float) 2)   );

		(astr[i]).theta = 180*rad_theta*PI;
		(astr[i]).phi = 180*rad_phi*PI;
	}
}
//Func: calc_acc()
//This funciton takes value from *astr (fx, fy, fz)
//And find the acceleration in each component
//For a givne set of num_astr = group_size (if needed)
void calc_acc(int num_astr, obj *astr, thread_info t_info){
	for(int i = t_info.idx; i < (t_info.group_size) + (t_info.idx); ++i){
		//a = F/m
		(astr[i]).ax = (astr[i]).fx / (astr[i]).m;
		(astr[i]).ay = (astr[i]).fy / (astr[i]).m;
		(astr[i]).az = (astr[i]).fz / (astr[i]).m;
	}
}

//Func: calc_velo()
//This fucntion takes value from *astr (ax, ay, az)
//And find the velocity in each component
//For a given set of num_astr = group_size (if needed)
void calc_velo(int num_astr, obj *astr, thread_info t_info, int t){
	for(int i = t_info.idx; i < (t_info.group_size) + (t_info.idx); ++i){
		//v = a*t
		(astr[i]).vx += (astr[i]).ax * t;
		(astr[i]).vy += (astr[i]).ay * t;
		(astr[i]).vz += (astr[i]).az * t;
	}
}

//Func: calc_s()
//This function takes value from *astr (ax, ay, az, vx, vy, vz)
//And find the displacement in each component
//For a given set of num_astr = group_size (if needed)
void calc_s(int num_astr, obj *astr, thread_info t_info, int t){
	for(int i = t_info.idx; i < (t_info.group_size) + (t_info.idx); ++i){
		// x = ut + 1/2at^2
		(astr[i]).sx += ((astr[i]).vx * t) + (0.5)*((astr[i]).ax)*t*t;
		(astr[i]).sy += ((astr[i]).vy * t) + (0.5)*((astr[i]).ay)*t*t;
		(astr[i]).sz += ((astr[i]).vz * t) + (0.5)*((astr[i]).az)*t*t;
	}
}

//Func: update_loc()
//This fucntion takes value from *astr (sx, sy, sz) 
//And put it to *astr (x, y, z)
//For a given set of num_astr = group_size (if needed)
void update_loc(int num_astr, obj *astr, thread_info t_info){
	for(int i = t_info.idx; i < (t_info.group_size) + (t_info.idx); ++i){
		(astr[i]).x = (astr[i]).sx;
		(astr[i]).y = (astr[i]).sy;
		(astr[i]).z = (astr[i]).sz;

	}
}

////////////////////////////  Threads fuctions ///////////////////////
//Then blah, look in the book to see how to make pthread(); and barrier
//fix the input to not intake the char 

//Func: in_thread()
//This function is used in the call for pthread_create()
//it calls other function and set up a mission for each thread
void* in_thread(void *in_targv){
	struct timeval t_start;
	struct timeval t_end;
	thread_argv *ad_targv = in_targv;
	thread_argv targv = *ad_targv;
	gettimeofday(&t_start,NULL);
	update_loc(targv.num_astr, ad_targv->astr, *(targv.t_info));
	calc_f(targv.num_astr, ad_targv->astr, *(targv.t_info));
	total_f(targv.num_astr, ad_targv->astr, *(targv.t_info));
	calc_acc(targv.num_astr, ad_targv->astr, *(targv.t_info));
	calc_velo(targv.num_astr, ad_targv->astr, *(targv.t_info), targv.t);
	calc_s(targv.num_astr, ad_targv->astr, *(targv.t_info), targv.t);
	// mutex_lock pls - I like to live dangerously
	gettimeofday(&t_end,NULL);
	ad_targv->proc_t = t_end.tv_usec - t_start.tv_usec;
	pthread_barrier_wait(&barrier);
	return NULL;
}

//Func set_t_infor()
//This function creats array of thread_info struct 
//Moreover, it also sets the idx and group_size of each thread_info
//Lastly, point the t_info in the struct to the created array
void set_t_info(int num_thread,thread_argv *targv){

	for(int k=0; k<num_thread; ++k){
		//FIXME
		if(k != num_thread-1){
			targv[k].t_info->group_size = targv[k].num_astr/num_thread; 
			targv[k].t_info->idx = k * targv[k].t_info->group_size;
		}
		if(k == num_thread-1){
			targv[k].t_info->idx = k * targv[k].num_astr/num_thread; 
			if(targv[k].num_astr%num_thread == 0)
				targv[k].t_info->group_size = targv[k].num_astr/num_thread;
			else
				targv[k].t_info->group_size = targv[k].num_astr - ((k) * targv[k].num_astr/num_thread);
		}

		targv[k].proc_t = 0;
	}

	return ;
}
//////////////////////////// WARNING: ZERG DETECTED /////////////////////////////
//Func: hive()
//This function spawn threads and give them missions
//The spawn of all things
pthread_t *hive(int num_thread, thread_argv *targv){
	int creep=0;
	pthread_t *th = malloc(sizeof(pthread_t)*(num_thread));
	set_t_info(num_thread, targv);
	for(int zerglings = 0; zerglings < num_thread; zerglings++){
		//	printf(PC"hive(): zerglings: %d \n"NC, zerglings);
		//	printf(PC"hive(): group_size: %d \n"NC, targv[zerglings].t_info->group_size);
		creep = pthread_create(&(th[zerglings]), NULL, in_thread,&(targv[zerglings]));
		if(creep == -1){
			perror("Spawn more Overlords");
			exit(EXIT_FAILURE);
		}
	}


	return th;
}

////////////////////////////// The main land //////////////////////////////
int main(int argc, char* argv[]){
	int flags[6] = {0,0,0,0,0,0};
	//flags = [t | n | p | v | c | q ]
	int num_thread=0, num_astr=0 ;
	obj *astr;
	thread_info t_info;
	int t = 1; // t is a preiod of time measure in a second
	int max_t=1000;
	thread_argv *targv;
	pthread_t *t_id;

	argv_handler(argc, argv, flags);
	prompt(&num_thread, &num_astr, &t_info, &astr, flags, &max_t);
	ini_astr(num_astr, astr);
	targv = malloc(sizeof(thread_argv)*num_thread);
	for(int a = 0; a < num_thread; a++){
		targv[a].num_astr = num_astr;
		targv[a].astr = astr;
		targv[a].t_info = malloc(sizeof(thread_info));
		targv[a].t = t;
	}
	//FIXME: while time steps goes here
	for(int time = 0; time < max_t; time++){
		pthread_barrier_init(&barrier, NULL, num_thread);
		t_id = hive(num_thread, targv );
		for(int k=0; k<num_thread; ++k){
			if(pthread_join(t_id[k],NULL)!=0){
				perror("The Hive Cluster is under attcked");
				exit(EXIT_FAILURE);
			}
		}
		pthread_barrier_destroy(&barrier);
		if(time == 0 || time == max_t-1){
			if(flags[3]==1)
				print_all(num_astr, astr, time);
			if(flags[4]==1)
				print_c(num_astr, astr, time);
			if(flags[5]==1)
				print_q(num_thread, targv,time);
		}

	}


	return 0;
}
