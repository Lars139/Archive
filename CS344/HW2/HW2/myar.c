#define C_POSIX_SOURCE 200809L
#define XOPEN_SOURCE 600

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>

#define CY "\x1b[33m"
#define NC "\x1b[0m"

typedef struct {
	char name[16];
	char time[12];
	char uid[6],gid[6];
	char mode[8];
	char size[10];
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

	if(type==1){
		if((de_file = open(temp_file,O_RDWR | O_APPEND | O_CREAT | O_EXCL, 0666))!=-1){ 
			// Taking care of archeive set up
			w = write(de_file,"!<arch>\n",8);
			if(w==-1){
				perror("Archeive Write");
				printf(CY"Error: Cannot write to archeive file.\nProgram is now exiting!\n"NC);
				exit(EXIT_FAILURE);
			}
			return de_file;
		}
	}

	///////////////////////////////// Normal Trypical file opening
	de_file = open(temp_file,O_RDWR  );
	if(de_file == -1){
		if(!type){
			perror("Open File");
			printf(CY"Error: Unable to open a file (\"%s\").\nProgram is now exiting!\n"NC,temp_file);
			exit(666);
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
	char name_temp[]="/tmp/tempfileXXXXXX";
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

/*Func: shrt_str()
 * take null string and get rid of the white space
 */
char* shrt_str(char* str){
	char* temp_str;
	int not_white = 0;
	for(int i = 0; str[i]!='\0'; ++i){
		if(str[i]=='/')
			str[i] = ' ';
		if(str[i]!=' ')
			not_white++;
	}
	temp_str = malloc(sizeof(char)*not_white);
	for(int i = 0; i<not_white;++i){
		temp_str[i] = str[i];
	}
	temp_str[not_white] = '\0';
	return temp_str;
}

/*Func: write_file_header()
 * write to a file header to a temp file
 * check the error 
 */
void write_file_header(int tempfile,file *info){
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

/*Func: write_file_header2()
 * write to a file header to a temp file
 * check the error 
 */
void write_file_header2(int tempfile,char* name,file *info){
	char* str=0;
	str = null_str(name,16);
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
void all_in_arch(int tempfile,int arch,int *fcalled, file *info){
	int size = atoi(info->size)+60;
	char *str_buf = malloc(sizeof(char)*size);
	lseek(tempfile,0,SEEK_SET);
	read(tempfile,str_buf, size);
	if(*fcalled==0)
		lseek(arch,8,SEEK_SET);
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
	int t=0;
	struct stat fileinfo;
	t = fstat(info->desc,&fileinfo);
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
	read_filename(argv, filecount,opt,fcalled, info);
	info->desc = open_file(info->name,0);
	read_from_stat(info);

	return ;
}

/*Func: put_header()
 * This function will read headers off of arch and put it in the info struct
 */
void put_header(int arch,file* info){
	read(arch,info->time,12);	
	read(arch,info->uid,6);	
	read(arch,info->gid,6);	
	read(arch,info->mode,8);	
	read(arch,info->size,10);	

}

/*Func: iter_arch()
 * Iterate from the second file name to the next file name
 * NOTE: This function assume the lseek() is currently at the first filename in the arch
 */
void iter_arch(int arch,int *fbyte,file *info){
	//make this into its own iter func
	lseek(arch,32,SEEK_CUR);
	read(arch, info->size, 10);
	lseek(arch,atoi(info->size)+2,SEEK_CUR);
	if(atoi(info->size)%2!=0){
		lseek(arch,1,SEEK_CUR);
		(*fbyte)++;
	}
	(*fbyte) += 60+atoi(info->size);
}

/*Func: print_mode()
 * print mode in a single line
 */
void print_mode(file *info){
	char *mode = null_str(info->mode,8);
	mode = shrt_str(mode);
	printf( (strtol(mode,NULL,8) & S_IRUSR) ? "r":"-");
	printf( (strtol(mode,NULL,8) & S_IWUSR) ? "w":"-");
	printf( (strtol(mode,NULL,8) & S_IXUSR) ? "x":"-");
	printf( (strtol(mode,NULL,8) & S_IRGRP) ? "r":"-");
	printf( (strtol(mode,NULL,8) & S_IWGRP) ? "w":"-");
	printf( (strtol(mode,NULL,8) & S_IXGRP) ? "x":"-");
	printf( (strtol(mode,NULL,8) & S_IROTH) ? "r":"-");
	printf( (strtol(mode,NULL,8) & S_IWOTH) ? "w":"-");
	printf( (strtol(mode,NULL,8) & S_IXOTH) ? "x":"-");

}
/////////////////////////////// FLAGS HANDLING ////////////////////////////

/*Func: opt_q()
 * If the -q has been specified, this function is called
 * Read from file in argv[n]; n is filecount[lq|cq]
 * Format the input and put the info. in temp file
 * Read from temp into arch
 */
void opt_q(int argc, char **argv,int arch, int *filecount, int *fcalled, file *info){
	int tempfile = 0;
	for((*fcalled) = 0; (*fcalled)<filecount[1];++(*fcalled)){
		tempfile = 0;
		read_header(argc,argv,filecount, 0, fcalled,info );
		tempfile = create_tempfile();
		write_file_header(tempfile, info);
		write_file_content(tempfile, info);
		all_in_arch(tempfile,arch,fcalled ,info);
		close(tempfile);
	}
	(*fcalled)=0;
	return ;
}

/*Func: opt_x()
 * lseek 8 bytes from the beginning of arc
 * read the file name from argv and ready to search
 * find the file name from CLA
 * read each header file and store it in info strct
 * create a file by using open(info->name,RDWR_0|CREATE_O,0666)
 * set header of a new file 
 * copy and paste the rest of the content from arch (use info->size)
 */
void opt_x(int argc, char **argv,int arch, int *filecount, int *fcalled, file *info){
	char cur_name[16];
	char *null_cur_name;
	char *null_info_name;
	int newfile=0;
	int fbyte_max=120;
	int fbyte=0;
	struct stat archinfo;
	fstat(arch,&archinfo);

	fbyte_max = archinfo.st_size;	

	for((*fcalled) = 0; (*fcalled)<filecount[3];++(*fcalled)){
		fbyte = 0;

		lseek(arch,8,SEEK_SET);
		read_filename(argv,filecount,2,fcalled,info);//get name from CLA
		for(fbyte_max ; fbyte < fbyte_max; fbyte++ ){ 
			//for the end of file	
			read(arch, cur_name,16); //get name of the file from arch

			null_cur_name = null_str(cur_name,16);//turn both of the name into
			null_cur_name = shrt_str(null_cur_name);
			null_info_name = null_str(info->name,16);//null terminated strings
			null_info_name = shrt_str(null_info_name);
			if(!strcmp(null_cur_name, null_info_name)){
				put_header(arch, info);
				remove(null_info_name);
				newfile = open(null_info_name, O_RDWR|O_CREAT,0666);
				info->desc = arch;
				lseek(arch,2,SEEK_CUR);
				write_file_content(newfile, info);
				if(atoi(info->size)%2!=0)
					lseek(arch,1,SEEK_CUR);
				utime(null_info_name, atoi(info->time));
				chmod(null_info_name, strtol(info->mode,NULL,8));
				break;
			}else{
				iter_arch(arch,&fbyte,info);
			}
		}//where the for EOF ends
		if(fbyte>=fbyte_max)
			printf(CY"Warning: File(\"%s\") doesn't documented in archeive.\nThe other file has successfully extract\n"NC,null_info_name);
	}
	/*	printf("info->name: %.16s\n",info->name);
		printf("info->time: %.12s\n",info->time);
		printf("info->uid: %.6s\n",info->uid);
		printf("info->gid: %.6s\n",info->gid);
		printf("info->mode: %.8s\n",info->mode);
		printf("info->size: %.10s\n",info->size);
		*/

	return;
}

/*Func: opt_t()
 * When the -t is called
 */

void opt_t(int argc, char **argv,int arch, int *filecount, int *fcalled, file *info){
	int fbyte_max=1;
	int fbyte=0;
	char cur_name[16];
	char *null_cur_name;
	struct stat archinfo;
	fstat(arch,&archinfo);

	fbyte_max = archinfo.st_size;
	fbyte = 0;
	lseek(arch,8,SEEK_SET);

	for(fbyte=0; fbyte < fbyte_max; fbyte++){
		read(arch,cur_name,16);
		null_cur_name = null_str(cur_name,16);
		null_cur_name = shrt_str(null_cur_name);
		iter_arch(arch,&fbyte,info);
		if(fbyte < fbyte_max)
			printf("%.16s\n",null_cur_name);
	}

}

/*Func: opt_v()
 * When the -t is called
 */

void opt_v(int argc, char **argv,int arch, int *filecount, int *fcalled, file *info){
	int fbyte_max=1;
	int fbyte=0;
	char cur_name[16];
	char *null_cur_name;
	struct stat archinfo;
	fstat(arch,&archinfo);

	fbyte_max = archinfo.st_size;
	fbyte = 0;
	lseek(arch,8,SEEK_SET);

	for(fbyte=0; fbyte < fbyte_max; fbyte++){
		read(arch,cur_name,16);
		null_cur_name = null_str(cur_name,16);
		null_cur_name = shrt_str(null_cur_name);
		(fbyte) += 60+atoi(info->size);



		if(fbyte < fbyte_max){
			put_header(arch,info);
			lseek(arch,atoi(info->size)+2,SEEK_CUR);
			print_mode(info);
			printf("%.6s",info->uid);
			printf("/%.6s",info->gid);
			printf("%.10s",info->size);
			//null_time= null_str(info->time,12);
			//null_time= shrt_str(null_time);
			//strftime(null_time,12,"%c",info->time);
			printf("%.12s",info->time);
			printf("%.16s",null_cur_name);
			printf("\n");
			if(atoi(info->size)%2!=0){
				lseek(arch,1,SEEK_CUR);
				(fbyte)++;
			}
		}
	}

}


/*Func: opt_d()
 * When the -d is called
 */

void opt_d(int argc, char **argv,int *arch, int *filecount, int *fcalled, file *info){
	int fbyte_max=1;
	int fbyte=0;
	int size = 0;
	int tsize = 0;
	int tempfile=0;
	int temparch =0;
	char cur_name[16];
	char *null_cur_name;
	char *null_info_name;
	char *str_buf;
	struct stat archinfo;
	struct stat temparch_info;


	fstat((*arch),&archinfo);

	temparch = open_file("temp_arch",1);

	fbyte_max = archinfo.st_size;
	//for fcalled goes here
	fbyte = 0;
	lseek((*arch),8,SEEK_SET);
	read_filename(argv,filecount,4,fcalled,info);

	for(fbyte=0; fbyte < fbyte_max; ){
		read((*arch),cur_name,16);
		null_cur_name = null_str(cur_name,16);
		null_cur_name = shrt_str(null_cur_name);
		null_info_name= null_str(info->name,16);
		null_info_name = shrt_str(null_info_name);

		(fbyte) += 60+atoi(info->size);

		if(fbyte < fbyte_max){
			if(!strcmp(null_cur_name,null_info_name)){//equal
				iter_arch((*arch), &fbyte, info);
				(fbyte) -= 60+atoi(info->size);
			}else{
				tempfile = 0;
				put_header((*arch), info);
				lseek((*arch),2,SEEK_CUR);

				/*printf("\ninfo->name: %.16s\n",info->name);
				  printf("cur name: %.16s\n",cur_name);
				  printf("info->time: %.12s\n",info->time);
				  printf("info->uid: %.6s\n",info->uid);
				  printf("info->gid: %.6s\n",info->gid);
				  printf("info->mode: %.8s\n",info->mode);
				  printf("info->size: %.10s\n",info->size);
				  */

				//so now the header are read correctly
				//Time to put info in files
				tempfile = create_tempfile();
				write_file_header2(tempfile,cur_name,info);
				info->desc = (*arch);
				write_file_content(tempfile,info);
				all_in_arch(tempfile,temparch,fcalled,info);

				if(tsize%2!=0){
					write(temparch,"\n",1);
				}

				(*fcalled)++;
				close(tempfile);
				if(atoi(info->size)%2!=0)
					lseek((*arch),1,SEEK_CUR);

			}
		}
	}
	//FIXME: the temp_arch has the correct info but when copy to arch itself has wrong info.	
	fstat(temparch,&temparch_info);
	size = temparch_info.st_size;
	printf("temparch.size: %d\n",size);
	str_buf = malloc(sizeof(char)*size);
	read(temparch,str_buf,size);
	//ftruncate((*arch),(sizeof(char))*size);
	lseek((*arch),0,SEEK_SET);
	write((*arch),str_buf,size);
	free(str_buf);
	close(temparch);
	//remove("temp_arch");
}

void opt_A(int argc, char **argv,int arch, int *filecount, int *fcalled, file *info){
	char path[1024];
	getcwd(path,1024);
	DIR *dir;
	struct dirent *ele;
	struct stat unknown;
	int totalfile = 0;
	char **argv_q;
	int j=2;
//	printf("cur dir: %s\n",path);

	if((dir = opendir(path)) != NULL){
		// S_IFREG undeclare?
		while((ele = readdir(dir))!=NULL){
			stat(ele->d_name,&unknown);
			if(unknown.st_mode & S_IFREG){//Is a file?
				if(!((!strcmp(ele->d_name,".")) ||(!strcmp(ele->d_name,"..")) ||(!strcmp(ele->d_name,"myar"))||(!strcmp(ele->d_name,argv[1])))){// Is not a "." ".." "myar" or archive itself
				//	printf("%s\n",ele->d_name);
					totalfile++;
				}
			}
		}
		closedir(dir);
	}
	//////////////////////Create 2D argv_q
	argv_q =(char**) malloc((totalfile+3)*sizeof(char*));
	for(int i=0; i<totalfile+3;i++){
		argv_q[i] = malloc(200*sizeof(char));
	}
	/////////////////////////////

	/////////////////////Inputing argv_q with fake file name and dash
	//copy ./myar and archive name
	for(int i=0; i<2;i++){
		strcpy(argv_q[i],argv[i]);
	}
	strcpy(argv_q[2],"-q\0");
	filecount[0] = 2;
	filecount[1] = totalfile;


	if((dir = opendir(path)) != NULL){
		while((ele = readdir(dir))!=NULL){
			stat(ele->d_name,&unknown);
			if(unknown.st_mode & S_IFREG){//Is a file?
				if(!((!strcmp(ele->d_name,".")) ||(!strcmp(ele->d_name,"..")) ||(!strcmp(ele->d_name,"myar"))||(!strcmp(ele->d_name,argv[1])))){// Is not a "." ".." "myar" or archive itself

					strcpy(argv_q[++j],ele->d_name);
				}
			}
		}
		closedir(dir);
	}

	opt_q(argc, argv_q, arch, filecount, fcalled, info );

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
				if((argv[i][j]=='q' || argv[i][j]=='x'||argv[i][j]=='d')&&(argv[i][0]=='-')){
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
	int fcalled = 0;
	int arch = 0;
	file info;//creating a struct of file info, contianing header info
	arch = open_file(argv[1],1);
	if(filecount[0]!=0){
		remove(argv[1]);
		arch = open_file(argv[1],1);
		opt_q(argc, argv, arch, filecount, &fcalled, &info );
	}
	if(filecount[2]!=0)
		opt_x(argc, argv, arch, filecount, &fcalled, &info);
	if(filecount[4]!=0)
		opt_d(argc, argv, &arch, filecount, &fcalled, &info);
	if(filecount[6]!=0 && filecount[7]==0)
		opt_t(argc, argv, arch, filecount, &fcalled, &info);
	if(filecount[6]!=0 && filecount[7]!=0)
		opt_v(argc, argv, arch, filecount, &fcalled, &info);
	if(filecount[8]==1)
		opt_A(argc, argv, arch, filecount,&fcalled, &info);

	//FIXME: More options opt_A need to find the file name from arch (cont here)
	close(arch);
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

void format_input(int argc,char **argv, char ***argv_f){
	int num_dash =0;
	int cur=2;
	int qxd =0;
	int st=1;

	//creating 2D array
	(*argv_f) =(char**) malloc((argc)*sizeof(char*));
	for(int i=0; i<argc;i++){
		(*argv_f)[i] = malloc(260*sizeof(char));
	}

	//counting total number of dashes and count if there are -q, -x, -d all togehter
	for(int i=0;i<argc;++i){
		if(argv[i][0]=='-'){
			num_dash++;
			for(int j=0;argv[i][j]!='\0';j++){
				if(argv[i][0]=='-' && (argv[i][j]=='x' || argv[i][j]=='q' || argv[i][j]=='d')){
					qxd++;
				}
			}
		}
	}

	if(qxd>1){
		printf(CY"Error:-q, -x, -d can only be used one at a time.\nProgram is now exiting!\n"NC);
		exit(EXIT_FAILURE);
	}

	//filling in argv_f in the order of the program
	strcpy((*argv_f)[0],argv[0]); //copy ./myar over
	strcpy((*argv_f)[1],argv[num_dash+1]); //copy arch to be the first

	//managing the options
	if(qxd>=1){
		//FIXME
		for(int i=0;i<num_dash;++i){
			if(argv[i+1][0]=='-'){
				for(int j=0;argv[i+1][j]!='\0';j++){
					if(argv[i+1][0]=='-' && (argv[i+1][j]=='x' || argv[i+1][j]=='q' || argv[i+1][j]=='d')){

						strcpy((*argv_f)[num_dash+1],argv[i+1]);
						st=0;
					}else{
						strcpy((*argv_f)[cur],argv[i+1]);
						st=1;
					}
				}
				if(st){
						cur++;
						st=1;
				}
			}
		}

	}else if(qxd==0){
		for(int z=0;z<num_dash;z++){
			strcpy((*argv_f)[2+z],argv[z+1]);
		}
	}
	strcpy((*argv_f)[1],argv[num_dash+1]); //copy arch to be the first
	//fill in the rest of the file names
	for(int i=num_dash+2;i<argc;i++){
		strcpy((*argv_f)[i],argv[i]);
	}

	for(int i=0;i<argc;++i){
		printf("argv_f: %s\n",(*argv_f)[i]);
	}
}

//////////////////////////////// MAIN LAND //////////////////////////////
int main(int argc, char **argv)
{
	char archname[261];
	char **argv_f;
	errno = 0;
	format_input(argc,argv,&argv_f);
	cla_opt_handle(argc,argv_f,archname);
	return 0;
}
