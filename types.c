#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//Kevin Thomas 132002474


int main(int argc, char *argv[])
{
    //handle when user gives no input
    if (argc < 2) {
        fprintf(stderr,"usage: path1 [path2 ...]\n");
        return 1;
    }
    //iterate through files provided
    int i=1;
    while(i < argc){
        char* filepath = argv[i];
        struct stat file_stats;
        //use lstat call to get information about file pointed to by filepath
        //lstat and not stat so we look at file directly and not follow any links
        if (lstat(filepath, &file_stats) == 0) {
            printf("%s: ", filepath);
            //check each file type
            if (S_ISREG(file_stats.st_mode)) {
                printf("regular file\n");
            } else if (S_ISDIR(file_stats.st_mode)) {
                printf("directory\n");
            }else if (S_ISCHR(file_stats.st_mode) || S_ISBLK(file_stats.st_mode) || S_ISFIFO(file_stats.st_mode) || S_ISSOCK(file_stats.st_mode)) {
                char* typeOfSpecial;
                if(S_ISCHR(file_stats.st_mode)){
                    typeOfSpecial = "character";
                }else if(S_ISBLK(file_stats.st_mode)){
                    typeOfSpecial = "block";
                }else if(S_ISFIFO(file_stats.st_mode)){
                    typeOfSpecial = "FIFO";
                }else if(S_ISSOCK(file_stats.st_mode)){
                    typeOfSpecial = "socket";
                }
                printf("%s special file\n",typeOfSpecial);
            } else if (S_ISLNK(file_stats.st_mode)) {
                printf("symbolic link\n");
            } 
        } else {
            printf("%s: path error\n", argv[i]);
        }
        i++;
    }

    return 0;
}
