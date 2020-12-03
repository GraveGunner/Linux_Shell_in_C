
void mkDir(char **args)
{
    ///if we just pass the name of folder, it is created in the same directory of current project;
    ///we can also pass the path, eg-->  D:/Movies/3 Idiots
    ///Note We can create only 1 folder,, not 5 folders inside a folder;
    ///Just use forward slash to move inside folders
    char *dirname = args[1];
    if (mkdir(dirname)==0)  ///mkdir returns 0 if directory is created
        printf("Directory created\n");
    else
        perror("\nError : ");
}


void rmDir(char **args)
{
    /// Removes  empty dirs  only

    char *dirname = args[1];
    if (rmdir(dirname)==0)
        printf("Directory deleted\n");
    else
        perror("\nError : ");

}

void cd(char **args)
{
    char *dirname = args[1];
    if(args[1]=="..")
    {
        DIR * d;

        char parent[200];
        snprintf(parent, sizeof(parent), "%s/..", dirname);/// snprintf is in <stdio.h>
        d = opendir(parent);

        if (d == NULL)
            {perror("Error ");}

    }

    ///Note Both else if's will give same result because in windows root and home dirs are same
    else if(strcmp(args[1],"/")==0)
    {
        dirname = "Computer";
    }
    else if(args[1]==NULL || strcmp(args[1],"~")==0)  /// if args[1]=="~" not working
    {
        dirname = "C:/Users";
    }

    if(chdir(dirname)!=0)
        perror("Error ");

}

void ls(char **args)
{
    char *dirname = args[1] ;
    DIR *files;
    struct dirent *dir;
    if(args[1]==NULL)
        dirname = ".";        ///"." corresponds to current directory

    ///Below 4 lines are not working
    /*else if(args[1]=="~")
    {
        dirname = "C:/Users";
    }*/

    else
        dirname = args[1];

    files = opendir(dirname);
    int count=1;
    if (files)
    {
        while ((dir = readdir(files)) != NULL)
        {
            printf("  %2d. %s\n",count, dir->d_name);
            count++;
        }
        closedir(files);
    }

    else
        perror("\nError : ");

}

void pwd(char **args)
{
    char arr[200];///i am assuming that current directory name will fit in array of 200 chars
    getcwd(arr,200);
    puts(arr);
}

void clear(char **args)
{
    system("cls");
    setup();
}



void mv(char **args)
{
    /// This function can also be implemented for folders !!!!!!!!!!!!!!
    /// SYNTAX  :  mv Source Destination
    char *dp1 = args[1], *dp2 = args[2];
    FILE *f1,*f2;

    f1=fopen(dp1,"r");
    if(!f1)
        printf("File not Present.");
    else
    {
        int ch;
        f2=fopen(dp2,"w");
        while((ch=fgetc(f1))!=EOF)
        {
            fseek(f2,0,SEEK_CUR);
            fputc(ch,f2);
        }
    }
    fclose(f1);
    fclose(f2);
    if(remove(dp1)==0)
        printf("File Moved Successfully.\n");
    else
        perror("Error ");
}

void rm(char **args)
{
    /// rmdir f1.txt removes f1.txt only
    /// rmdir f1.txt   f2.txt  f3.txt   will remove all the 3 files
    /// thats why it is looped

    int i=1;
    while(args[i]!=NULL)
    {
        char *dp = args[i];
        if(remove(dp)==0)
            printf("File Deleted.\n");
        else
            perror("Error ");
        i++;
    }

}


void touch(char **args)
{
    ///  touch f1.txt f2.txt f3.txt ; So it creates 3 new empty files
    ///  touch f1.txt ; So it create only 1 empty file
    int i=1;
    while(args[i]!=NULL)
    {
        char *dp = args[i];
        FILE *f;
        f=fopen(dp,"w");
        if(!f)
            printf("File not created.\n");
        else
            printf("File created Successfully.\n");
        fclose(f);
        i++;
    }

}

void cp(char **args)
{   /// cp source destination

    char *dp1, *dp2;
    dp1 = args[1];
    dp2 = args[2];
    FILE *f1,*f2;
    f1=fopen(dp1,"r");
    if(!f1)
        perror("Error ");
    else
    {
        int ch;

        f2=fopen(dp2,"w");                          //If File is not Present, It creates one.
        while((ch=fgetc(f1))!=EOF)
        {
            fseek(f2,0,SEEK_CUR);
            fputc(ch,f2);
        }
        printf("File copied Successfully.\n");


        fclose(f2);
    }
    fclose(f1);

}

void cat(char **args)
{
   /// This function creates, reads files, thats why i put a loop;
   /// This function can also concatenate data from 1 file to another ....or ....from 2 or more files to a new/old file

    int j=1,flag=0; /// j will be index of ">" in the args
    while(args[j]!=NULL)
    {
        if(strcmp(args[j],">")==0)      /// ">" this overwrites
            {flag = 1;break;}

        if(strcmp(args[j],">>")==0)        /// ">>" this appends
            {flag = 2;break;}

        j++;
    }


    if(flag!=0)
    {
        char mode[2];
        if(flag==1)
            strcpy(mode,"w");
        else
            strcpy(mode,"a+");

        char *dp = args[j+1];
        FILE *f;
        f = fopen(dp,mode);/// f will be the file in which contents of all previous files is concatenated
        if(!f)
        {printf("File not Present.\n");}

        else
        {
            int i=1,ch;
            FILE *f_temp;
            char newline = '\0';
            while(i<j)
            {
                char *dp2  = args[i];
                f_temp=fopen(dp2,"r");
                ch=getc(f_temp);
                while(ch!=EOF)
                {
                    fseek(f,0,SEEK_CUR);
                    fputc(ch,f);
                    ch=getc(f_temp);
                }
                    fprintf(f,"\n\n");
                fclose(f_temp);
                i++;
            }

        }
        fclose(f);
    }

    else
    {
            int i=1;
        while(args[i]!=NULL)
        {
            char* dp = args[i];
            FILE *f;
            f=fopen(dp,"r");
            if(!f)
            {
                printf("File not Present.\n");
            }
            else
            {
                printf("\n");
                int ch;
                while((ch=fgetc(f))!=EOF)
                {
                    printf("%c",ch);
                }
                printf("\n");
            }
            fclose(f);
            i++;
        }
    }
}

