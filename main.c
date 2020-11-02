#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>

#define RL_BUFSIZE 1024 // Buffer Size for Read_Line
#define TOKEN_BUFSIZE 64 // Buffer Size for Parser
#define TOKEN_DELIM_STR " \n\t\r\a" //Creating a list of delimiters to pass to strtok().

//cd: change directory
//args[0] = "cd" args[1] = directory ; return 1 to continue executing
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    //chdir: a system function in <unistd.h> used to change current working directory
    //input parameter: directory path; returns 0 on success and -1 on error
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

/*
//ls: list directory
//args[0]: ls
int lsh_ls(void){
struct dirent **namelist ;
int n ;

//scandir: scans contents of directory and stores in *namelist(array of pointers to structures of type struct dirent ) 
//returns number of entries placed in *namelist.
n= scandir(".", &namelist, 0, alphasort());
if(n<0){
    perror("scandir");
}
else{
    while(n--){
        printf("%s\n",namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);
}
return 1;
}
*/



//exit : to exit the shell
int lsh_exit(char **args)
{
  exit(0);
}

char *read_line()
{
    int bufsize = RL_BUFSIZE; // creating a buffer 
    int pos = 0;
    char *buffer = malloc(sizeof(char) * bufsize); // allocating space for buffer
    int c;

    // Used to check if memory is allocated successfully
    if(!buffer)
    {
        fprintf(stderr, "Memory Allocation Error\n"); // fprintf used to print error to stderr
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        c = getchar(); // returns the character read as an unsigned char cast to an int or EOF on end of file 

        // If we hit EOF replace it with null character and return.
        if(c == EOF || c == '\n')
        {
            buffer[pos] = '\0';
            return buffer;
        }
        else
        {
            buffer[pos] = c;
        }
        pos++;

        //If we exceed buffer limit, dynamically reallocate.
        if(pos >= bufsize)
        {
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer,bufsize);
            if(!buffer)
            {
                fprintf(stderr, "Memory Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
char **parse_line(char *line)
{
    int bufsize = TOKEN_BUFSIZE, pos = 0;
    char **tokens = malloc(sizeof(char *) * bufsize);
    char *token;
    if(!tokens)
    {
        fprintf(stderr, "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }

    // strtok() is used to return pointers to the tokens in the string you give it and place '\0' at the end of each token
    token = strtok(line, TOKEN_DELIM_STR); // Begin tokenising. Returns a pointer to the first token.

    while(token != NULL)
    {
        tokens[pos] = token;
        pos++;

        // Reallocate memory if overflow occurs
        if(pos >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if(!tokens)
            {
                fprintf(stderr, "Memory Allocation Error");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DELIM_STR); 
    }
    tokens[pos] = NULL; // NUll terminate the list of tokens
    return tokens;
}
void loop_shell()
{
    char *line;
    char **args;
    int status = 0, i;
    do
    {
        printf("> ");
        line = read_line();
        args = parse_line(line);
        for(i = 0; i <= sizeof(args); i++)
        {
            printf(args[i]);
            printf("\n");
        }

        free(line);
        free(args);
    }while(status);

}
int main()
{
    
    loop_shell();
    return EXIT_SUCCESS;
}