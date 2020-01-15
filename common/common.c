#include "common.h"
#include "dirent.h"
#include "stdio.h"
#include "string.h"

//extern int files_count = 0;
const char *to_search = "./testcase/";

int getAllTestcase(char filename[][256])
{
	DIR *dp;
    int i = 0;
    int files_count = 0;
    struct dirent *dirp;
    char endpart[256];
    if((dp = opendir(to_search)) == NULL) return 0;
    while((dirp = readdir(dp)) != NULL){
        for(int j = 0; j < strlen(dirp->d_name); j++){
            if(dirp->d_name[j] == '.'){
                memset(endpart, '\0', 256);
                strncpy(endpart, &dirp->d_name[j+1], strlen(dirp->d_name)-j-1);
                endpart[strlen(dirp->d_name)-j] = '\0';
                if(strncmp(endpart, "cminus", 6) == 0){
                    strcpy(filename[i++],dirp->d_name);
                    //printf("filename:%s\n", filename[i-1]);
                    files_count++;}
            }
        }
    }
    closedir(dp);
    printf("IN common.c file_count:%d\n", files_count);
    return files_count;
}
