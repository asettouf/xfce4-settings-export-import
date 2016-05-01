#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

struct file_setting{
	char* path;
	struct file_setting* next;
};


//check following file for keyboard shortcuts .config/xfce4/xfconf/xfce-perchannel-xml/xfce4-keyboard-shortcuts.xml  

//check this folder for most config file (where is window manager config files???) .config/xfce4/xfconf/xfce-perchannel-xml/

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


int main(int argc, char** args){
	struct file_setting *fs = malloc(sizeof(struct file_setting));
	if (!fs){
		printf("didn't allocate memory");
		return 1;
	}
	populate_file("/home/ado", "test", fs);

	return 0;
}
