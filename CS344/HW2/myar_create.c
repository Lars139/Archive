#define C_POSIX_SOURCE 200809L
#define XOPEN_SOURCE 600

#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define CY "\x1b[33m"
#define NC "\x1b[0m"

typedef struct {
	char name[16];
	char time[12];
	char uid[6],gid[6];
	char mode[8];
	char size[10];
	char numintro[2];
	int desc;
}file;

///////////////////////////// FILE MANIPULATION ///////////////////////////
/*Func: open_file()
 * Open and return a file desciptor
 * It also take care of the error that might happen during file opening
 * type whether the file is arch or not, if the file is arch, type = 1;
 */
int open_file(char *filename,int type){
	char temp_file[16];
	int de_file=0;
	int w = 0;

	//if the file input doesn't have '\0'
	for(int i=0; i<16;++i){
		temp_file[i] = filename[i];
		if(filename[i] == '/')
			temp_file[i] = '\0';
	}
//////////////////////////////////////Special for first time open archeive file need to set !<arch>

	if((de_file = open(temp_file,O_RDWR | O_APPEND | O_CREAT | O_EXCL, 0666))!=-1 && type==1){
// Taking care of archeive set up
			w = write(de_file,"!<arch>\n",8);
			if(w==-1){
				perror("Archeive Write");
				printf(CY"Error: Cannot write to archeive file.\nProgram is now exiting!\n"NC);
				exit(EXIT_FAILURE);
			}
			return de_file;
	}

///////////////////////////////// Normal Trypical file opening
	de_file = open(temp_file,O_RDWR | O_APPEND | O_CREAT, 0666);
	if(de_file == -1){
		if(!type){
			perror("Open File");
			printf(CY"Error: Unable to open a file.\nProgram is now exiting!\n"NC);
			exit(EXIT_FAILURE);
		}else{
			perror("Open File");
			printf(CY"Error: Unable to open an archive file.\nProgram is now exiting!\n"NC);
			exit(EXIT_FAILURE);

		}
	}

	return de_file;	
}

/*Func: create_tempfile()
 * Create a temp file
 * Return a file descriptor of the temp file
 */
int create_tempfile(){
	int temp_f=0;
	char name_temp[]="./tempfileXXXXXX";
	temp_f = mkstemp(name_temp);
	if(temp_f == -1){
		printf(CY"Error: Unable to open a temporary file.\nProgram is now exiting!\n"NC);
		exit(EXIT_FAILURE);
	}
	return temp_f;
}

/*Func: null_str()
 * take in a string str with length of n
 * convert the string size of n to size of n+1 
 * and add the '\0' to the end of the sring
 * return the address of temp_str
 */

char* null_str(char* str, int n){
	char* temp_str = malloc(sizeof(char)*(n+1));
	for(int i = 0; i<n; ++i){
		temp_str[i] = ' ';
		temp_str[i] = str[i];
	}
	temp_str[n] = '\0';
	return temp_str;
}


/*Func: write_file_header()
 * write to a file header to a temp file
 * check the error 
 */
void write_file_header(int tempfile,file *info){
	//FIXME: Continue here
	char* str=0;
	str = null_str(info->name,16);
	write(tempfile,str,16);

	str = null_str(info->time,12);
	write(tempfile,str,12);

	str = null_str(info->uid,6);
	write(tempfile,str,6);

	str = null_str(info->gid,6);
	write(tempfile,str,6);

	str = null_str(info->mode,8);
	write(tempfile,str,8);

	str = null_str(info->size,10);
	write(tempfile,str,10);

	write(tempfile,"`\n",2);
	return ;
}

/*Func: write_file_content()
 * write the content of a given file name to a temp file
 */
void write_file_content(int tempfile, file *info){
	int size = atoi(info->size);
	char *str_buf = malloc(sizeof(char)*size);
	read(info->desc,str_buf, size);
	write(tempfile, str_buf, size);
	free(str_buf);
	return ;
}

/*Func: all_in_arch()
 * stuff EVERYTHING in temp file into archieve
 * and say good bye to the royal temp file
 */
void all_in_arch(int tempfile,int arch, file *info){
	int size = atoi(info->size)+60;
	char *str_buf = malloc(sizeof(char)*size);
	lseek(tempfile,0,SEEK_SET);
	read(tempfile,str_buf, size);
	write(arch, str_buf, size);

	if(size%2!=0)
		write(arch,"\n" ,1);

	return ;


}

///////////////////////////// FILE DOCUMENTING ////////////////////////////

/*Func: read_filename
 * This function read a filename from CLA and put it in the form of
 * 16 byte character array with '/' at the end of content
 * If the file name itself is less than 16 char, it will fill the rest with white space.
 * If the file name is longer than 16 char, the char after the 15th will be ignore
 * opt stand for options is called 
 * -q, opt = 0;
 * -x, opt = 2;
 * -d, opt = 4;
 */
int read_filename(char **argv, int *filecount, int opt, int *fcalled, file *info){
	int j=0;
	if( (*fcalled) < filecount[opt+1]){//if all of the name after -q has not been all called

		for(int i=0; i<16;++i)
			info->name[i] = ' ';

		for(; (argv[filecount[opt] + (*fcalled) + 1][j] != '\0') && j<16;++j){
			info->name[j] = argv[filecount[opt] + (*fcalled) +1][j]; 
		}

		if(j<15)
			info->name[j] = '/';
		else if(j==15)
			info->name[15] = '/';

	}
	return 0;
}

/*Func: read_time()
 * This fucntion read timestamp off of the stat()
 * Create a temp array to sture timestamp with \0
 * Set temp array to contain white spaces ' '
 * Copy the time stamp from int to temp_time
 * Set info->time[] to contain white spaces
 * Set the time
 */
void read_time(file *info, struct stat fileinfo){
	char temp_time[13];

	for(int i=0;i<13; ++i){
		temp_time[i] = ' ';
	}

	sprintf(temp_time,"%d",fileinfo.st_mtime);


	for(int i=0;i<12; ++i){
		info->time[i] = ' ';
	}

	for(int i=0;i<12; ++i){
		if(temp_time[i] != '\0')
			info->time[i] = temp_time[i];
	}

	//printf("time: %d\n", fileinfo.st_mtime);
	return ;
}

/*Func: read_ids()
 * This fucntion read user_id and group_id off of the stat()
 * Create a temp arrays to store uid and gid with '\0'
 * Set temp arrays to contain white spaces ' '
 * Copy the ids from int to temp_uid, temp_gid
 * Set info->uid[] and info->gid to contain white spaces
 * Set the uid and gid in the info struct
 */
void read_ids(file *info, struct stat fileinfo){
	char uid_temp[7];
	char gid_temp[7];

	for(int i=0;i<7; ++i){
		uid_temp[i] = ' ';
		gid_temp[i] = ' ';
	}

	sprintf(uid_temp,"%d",fileinfo.st_uid);
	sprintf(gid_temp,"%d",fileinfo.st_gid);

	for(int i=0;i<6; ++i){
		info->uid[i] = ' ';
		info->gid[i] = ' ';
	}

	for(int i=0;i<6; ++i){
		if(uid_temp[i] != '\0')
			info->uid[i] = uid_temp[i];

		if(gid_temp[i] != '\0')
			info->gid[i] = gid_temp[i];

	}

	printf("user id: %d\n", fileinfo.st_uid);
	printf("group id: %d\n", fileinfo.st_gid);
	return ;
}

/*Func: read_mode()
 * This fucntion read file mode off of the stat()
 * Create a temp arrays to store mode with '\0'
 * Set temp arrays to contain white spaces ' '
 * Copy the mode from int to temp_mode
 * Set info->mode to contain white spaces
 * Set the mode in the info struct
 */
void read_mode(file *info, struct stat fileinfo){
	char temp_mode[9];

	for(int i=0;i<9; ++i){
		temp_mode[i] = ' ';
	}

	sprintf(temp_mode,"%o",fileinfo.st_mode);

	for(int i=0;i<8; ++i){
		info->mode[i] = ' ';
	}

	for(int i=0;i<8; ++i){
		if(temp_mode[i] != '\0')
			info->mode[i] = temp_mode[i];
	}

	printf("mode: %o\n", fileinfo.st_mode);
	return ;
}

/*Func: read_size()
 * This fucntion read file size off of the stat()
 * Create a temp arrays to store size with '\0' at the end of string
 * Set temp arrays to contain white spaces ' '
 * Copy the size from int to temp_size
 * Set info->size to contain white spaces
 * Set the size in the info struct
 */
void read_size(file *info, struct stat fileinfo){
	char temp_size[11];

	for(int i=0;i<11; ++i){
		temp_size[i] = ' ';
	}

	sprintf(temp_size,"%d",fileinfo.st_size);

	for(int i=0;i<10; ++i){
		info->size[i] = ' ';
	}

	for(int i=0;i<10; ++i){
		if(temp_size[i] != '\0')
			info->size[i] = temp_size[i];
	}

	//printf("size: %d\n", fileinfo.st_size);
	return ;
}



/*Func: read_from_stat()
 * This fucnction create stat type struct
 * Read the information from stat()
 * Check to see if there is error
 * Calling functions to read info of the file:
 * 	timestamp
 * 	user_id, group_id
 * 	mode, size, numintro
 */
void read_from_stat(file *info){
	//FIXME
	int t=0;
	struct stat fileinfo;
	t = fstat(info->desc,&fileinfo);
	printf("file desc: %d\n",info->desc);
	//perror("File Stat");
	if(t==-1){
		printf(CY"Error: File stat cannot be read. \nProgram is now exiting!\n"NC);
		exit(EXIT_FAILURE);
	}
	read_time(info, fileinfo);
	read_ids(info, fileinfo);
	read_mode(info, fileinfo);
	read_size(info, fileinfo);

}


/*Func: read_header()
 * This function will read the header of a file put it in the correct format
 */
void read_header(int argc, char **argv, int *filecount, int opt, int *fcalled,file *info ){
	//FIXME: need to add opt var for the read_header func
	read_filename(argv, filecount,opt,fcalled, info);
	info->desc = open_file(info->name,0);
	read_from_stat(info);

/*	printf("info->time: %.12s\n", info->time);
	printf("info->uid: %.6s\n", info->uid);
	printf("info->gid: %.6s\n", info->gid);
	printf("info->mode: %.8s\n", info->mode);
	printf("info->size: %.10s\n", info->size);
	*/

	return ;
}

/////////////////////////////// FLAGS HANDLING ////////////////////////////

/*Func: opt_q()
 * If the -q has been specified, this function is called
 * Read from file in argv[n]; n is filecount[lq|cq]
 * Format the input and put the info. in temp file
 * Read from temp into arch
 */
int opt_q(int argc, char **argv,int arch, int *filecount, int *fcalled, file *info){
	int tempfile = 0;
	for((*fcalled) = 0; (*fcalled)<filecount[1];++(*fcalled)){
		tempfile = 0;
		read_header(argc,argv,filecount, 0, fcalled,info );
		tempfile = create_tempfile();
		write_file_header(tempfile, info);
		write_file_content(tempfile, info);
		all_in_arch(tempfile,arch, info);
		close(tempfile);
	}
	(*fcalled)=0;
	return 0;
}



///////////////////////  COMMAND LINE ARGUMENT HANDLING  ///////////////////

/*Func: cla_swap()
 * Swap a string of CLA so that q,x,d is right after the dash.
 * Also check if the following argument after -q,-x,-d is valid.
 */

void cla_swap(int argc, char **argv, int *filecount){
	char temp = '0';
	int cnt=0;
	for(int i=0; i<argc; ++i){
		if(argv[i][0]=='-'){
			for(int j=0;argv[i][j]!='\0';++j){
				if(argv[i][j]=='q' || argv[i][j]=='x'||argv[i][j]=='d'){
					cnt++;
				}
				//mark filecount to idicate that there is -t, -v, -A
				if(argv[i][j]=='t')
					filecount[6] = 1;
				if(argv[i][j]=='v')
					filecount[7] = 1;
				if(argv[i][j]=='A')
					filecount[8] =1;
			}
			if(cnt>1){
				printf(CY"Error: Options -q, -x, -d must not be grouped together.\nPlease separate them individually with '-' and a white space.\nProgram is now exiting!\n"NC);
				exit(EXIT_FAILURE);
			}else{
				for(int k=0;argv[i][k]!='\0';++k){
					if(argv[i][k]=='q' || argv[i][k]=='x'||argv[i][k]=='d'){
						temp = argv[i][1];
						argv[i][1] = argv[i][k];
						argv[i][k] = temp;
					}
				}
			}
		}
		cnt=0;
	}
}


/*Func: cla_count_files()
 * Count how many files are inputed with a specific options for options 
 * -q, -x, -d
 * Mark filecount wether -t, -v, - A has been used.
 */
void cla_count_files(int argc, char **argv,int *filecount){
	int fd=0, sd=0, t=0;
	cla_swap(argc, argv,filecount);

	for(int i=0;i<argc;++i){
		if(argv[i][0] == '-'||(i==argc-1)){
			t++;
			if(t%2==1) //toggle between first dash and second dash
				fd=i;
			else
				sd=i;
			if(i==(argc-1) && argv[i][0]!='-' )
				++sd;

			if(sd>fd){
				if((sd==fd+1)&&(argv[fd][1] == 'q'|| argv[fd][1] == 'x' || argv[fd][1] == 'd' )){
					printf(CY"Please provide filename(s) after -q, -x, or -d.\nProgram is now exiting!\n"NC);
					exit(EXIT_FAILURE);

				}else{
					if(argv[fd][1]=='q'){
						filecount[0] = fd;
						filecount[1] = sd-fd-1;
					}else if(argv[fd][1]=='x'){
						filecount[2] = fd;
						filecount[3] = sd-fd-1;
					}else if(argv[fd][1]=='d'){
						filecount[4] = fd;
						filecount[5] = sd-fd-1;
					}
					fd = i;
					t=1;
				}
			}

			if(argv[fd][1] == 'q'|| argv[fd][1] == 'x' || argv[fd][1] == 'd' ){

				if((fd==argc-1) ){//if the option is righ at the very end
					printf(CY"Please provide filename(s) after -q, -x, or -d.\nProgram is now exiting!\n"NC);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}


/*Func: cla_simp_check()
 * This function do simple CLA check
 * Check if there is at least 3 CLA
 * check if archive name has been specified
 */

void cla_simp_check(int argc, char **argv){
	if(argc < 3){ //exist if the user didn't provide enough CLA
		printf(CY"Error: Insufficient command line argument.\nProgram is now exiting!\n"NC);
		exit(EXIT_FAILURE);
	}

	if(argv[1][0] =='-'){ //exist if the user didn't provide enough CLA
		printf(CY"Error: No the archive name provided.\nProgram is now exiting!\n"NC);
		exit(EXIT_FAILURE);
	}

}

/*Func: cla_cp_archname()
 * cp archname from argv
 */
void cla_cp_archname(char **argv, char *archname){
	int i=0;
	for(;i!='\0';++i){
		archname[i]=argv[1][i];
	}
	archname[i+1]='\0';
	return ;
}


/*Func: cla_opt_switch()
 * Take the digested input from cla_opt_handle()
 * Create an struct which contains info. from file headers of files from CLA
 * Open archieve and add the <!arch> to the archive file
 * Then go through a switch-case to distingiush b/w options 
 * And pass the argc, agrv, filecount to the corresponding functions
 */
int cla_opt_switch(int argc, char **argv, int *filecount, char *archname){
	//FIXME
	int fcalled = 0;
	int arch = 0;
	file info;//creating a struct of file info, contianing header info
	arch = open_file(argv[1],1);


	opt_q(argc, argv, arch, filecount,  &fcalled,&info  );
	return 0;
}



/*Func: cla_opt_handle()
 * Digest the Commnad Line Argument.
 * Check if there is enough CLA to be valid
 * The function determine what are the options being passed in via CLA
 * The function then extract what file name goes with what option
 * (It counts how many file names are passed in option of -q, -x, -d)
 * NOTE: filecount is [lq|cq|lx|cx|ld|cd|t|v|A] 
 * (lq = the location index of where -q is placed in argv)
 * (cq = the number of files after -q is called subtract 1)
 */
int cla_opt_handle(int argc, char **argv, char *archname){
	int filecount[9]={0,0,0,0,0,0,0,0,0};
	cla_simp_check(argc,argv);
	cla_count_files(argc, argv, filecount);

	//To test filecount[]
	/*
	   for(int i=0;i<9;i++)
	   printf("%d\n",filecount[i]);
	   printf("\n");
	   */

	cla_cp_archname(argv, archname);
	cla_opt_switch(argc, argv, filecount, archname);
	return 0;
}

//////////////////////////////// MAIN LAND //////////////////////////////
int main(int argc, char **argv)
{
	char archname[261];
	errno = 0;
	cla_opt_handle(argc,argv,archname);
	return 0;
}
