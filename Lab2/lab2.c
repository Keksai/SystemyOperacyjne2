#include "dlfcn.h"
#include "utmpx.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

void (*showId)(char*);
void (*showGroup)(char*);

int main(int argc, char **argv){

	int aflag=0, bflag=0, ret;
	struct utmpx *entry;
	entry=getutxent();
	setutxent();
	
	void *handle=dlopen("./lib.so.0.1", RTLD_LAZY);
	if(!handle){
		puts("Error, library not found");
		goto jump;
	}
	else{
		
		if (showId=dlsym(handle, "showId")){;}
			else{
				puts("Error, show id not found");
                goto jump;
			}
		if(showGroup=dlsym(handle, "showGroup")){;}
			else{
				puts("Error, show grooup not found");
				goto jump;
			}

		while((ret=getopt(argc, argv, "ab"))!=-1)
                switch(ret){
                        case 'a': aflag=1; break;
                        case 'b': bflag=1; break;                        
			default: abort();
                }
		jump:
		if(!aflag && !bflag){
			while(entry!=NULL){
				if(entry->ut_type==7)                        
					printf("%s\n", entry->ut_user);
                       		entry=getutxent();
                	}
				dlerror();
       		}
		else if(aflag && !bflag){
			while(entry!=NULL){
				if(entry->ut_type==7)
					if(showId)
						showId(entry->ut_user);
				entry=getutxent();
			}
		}
		else if(aflag && bflag){	
			while(entry!=NULL){
				if(entry->ut_type==USER_PROCESS)
					if(showGroup)
						showGroup(entry->ut_user);
				entry=getutxent();
			}
		}
		if (handle)
			dlclose(handle);
	}
	endutxent();
return 0;
}
