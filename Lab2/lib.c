#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>

void showId(char *userName){
	struct passwd *pw;
	pw=getpwnam(userName);
        printf("%d\t%s\n", pw->pw_uid, userName);
}

void showGroup(char *userName){
	
	struct group *grp;
	struct passwd *pw;
	gid_t *grpp;
	int n=2;
	
    grpp=malloc(n*sizeof(gid_t));
	pw=getpwnam(userName);				
	getgrouplist(userName, pw->pw_gid, grpp, &n);
	printf("%s\t [",userName);	
	for(int i=0; i<n; i++){
		grp=getgrgid(grpp[i]);
		printf(" %s ", grp->gr_name);
	}
	puts("]");
	free(grpp);
}
