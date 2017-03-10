#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmpx.h>
#include <grp.h>
#include <pwd.h>

//man getgrouplist
//man utmp
//man getutent
//man getpwnam

int main(int argc, char **argv){

        struct utmpx *entry;
	setutxent();
	entry=getutxent();

	int aflag=0, bflag=0, ret;
        while((ret=getopt(argc, argv, "ab"))!=-1)
                switch(ret){
                        case 'a': aflag=1; break;
                        case 'b': bflag=1; break;
			case '?': return 1;                        
			 default: abort();
                }

        if(!aflag && !bflag){
                while(entry!=NULL){
			if(entry->ut_type==7)                        
				printf("%s\n", entry->ut_user);
                        entry=getutxent();
                }
        }
        else if(aflag && !bflag){
		struct passwd *pw;
                while(entry!=NULL){
			pw=getpwnam(entry->ut_user);
			if(entry->ut_type==7)
                        	printf("%d\t%s\n", pw->pw_uid, entry->ut_user);
                        entry=getutxent();
                }
        }
        else if(aflag && bflag){
		struct group *grp;
		struct passwd *pw;
		gid_t *grpp;
		int n=2;
        	while(entry!=NULL){
			if(entry->ut_type==7){
				grpp=malloc(n*sizeof(gid_t));
				pw=getpwnam(entry->ut_user);				
				getgrouplist(entry->ut_user, pw->pw_gid, grpp, &n);
				printf("%s\t [",entry->ut_user);	
				for(int i=0; i<n; i++){
					grp=getgrgid(grpp[i]);
					printf(" %s ", grp->gr_name);
				}
				puts("]");
			}
			entry=getutxent();
		}
		endutxent();
		free(grpp);
	 }

return 0;
}
