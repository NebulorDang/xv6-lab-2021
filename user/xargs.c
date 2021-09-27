#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define NULL ((char*)0) 


char* readline(){
	char buf[512], c;
	int pos = -1;
	while(read(0, &c, sizeof(char))){
		if(c == '\n'){
			break;
		}else{
			buf[++pos] = c;
		}
	}
	if(pos == -1){
		return NULL;
	}
	//need to free
	char *p = malloc((pos+1) * sizeof(char));
	memmove(p, buf, pos+1);
	return p;
}	

int main(int argc, char *argv[]){
	if(argc < 3){
		fprintf(2, "Usage : xargs command args...\n");
		exit(1);
	}
	char *argv_new[MAXARG];
	for(int i = 1; i < argc; i++){
		argv_new[i-1] = argv[i];
	}
	char *r;
	while((r = readline()) != NULL){
		argv_new[argc-1] = r;
		if(fork() == 0){
			exec(argv_new[0], argv_new);
			free(r);
			exit(0);
		}else{
			wait(0);
		}
	}	
	exit(0);
}

