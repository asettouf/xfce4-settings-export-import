#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
struct file_setting{
	char* path;
	struct file_setting* next;
};


//check following file for keyboard shortcuts .config/xfce4/xfconf/xfce-perchannel-xml/xfce4-keyboard-shortcuts.xml  

//check this folder for most config file (where is window manager config files???) .config/xfce4/xfconf/xfce-perchannel-xml/

int set_filecpy(struct file_setting *fs){
	int fd_to, fd_from;
	ssize_t nread;
	char buf[2];
	fd_from = open(fs -> path, O_RDONLY);
	if(fd_from < 0){
		printf("cant open file src\n");
		return -1;
	}
	fd_to = open("/home/ado/test2", O_WRONLY | O_CREAT | O_EXCL , 0666);
	if(fd_to < 0){
		printf("cant open file dest\n");
		remove("/home/ado/test2");
	}
	fd_to = open("/home/ado/test2", O_WRONLY | O_CREAT | O_EXCL , 0666);
	
	while(nread = read(fd_from, buf, sizeof buf), nread > 0){
		char* out = buf;
		ssize_t nwritten;
		printf("%s\n", out);
		do{
			nwritten = write(fd_to, out, nread);

			if(nwritten >= 0){
				nread -= nwritten;
				out += nwritten;
			}
		} while(nread > 0);

	}
	return 0;
}
void populate_file(char* dirname, char* sfile, struct file_setting *fs){
	DIR *dir;
	dir = opendir(dirname);
	struct dirent *dent;
	fs -> path = malloc(strlen(dirname) + strlen(sfile) + 2);

	if(dir != NULL){
		while((dent = readdir(dir))){
			if(strcmp(dent -> d_name, sfile) == 0){
				strcpy(fs -> path, dirname);
				strcat(fs -> path, "/");
				strcat(fs -> path, dent -> d_name);
				printf("%s\n",fs -> path);
			}
		}
	} else{
		printf("DIR does not exist\n");
	}

}

void free_fs(struct file_setting *fs){
	free(fs -> path);
	free(fs -> next);
	free(fs);
	fs = NULL;
}

int main(int argc, char** args){
	struct file_setting *fs = malloc(sizeof(struct file_setting));
	if (!fs){
		printf("didn't allocate memory");
	}
	populate_file("/home/ado", "test", fs);
	set_filecpy(fs);
	free_fs(fs);
	return 0;
}
