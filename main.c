#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <io.h>
#include <process.h>
#include <conio.h>
#define RL_BUFSIZE 1024 // Buffer Size for Read_Line
#define TOKEN_BUFSIZE 64 // Buffer Size for Parser
#define TOKEN_DELIM_STR " \n\t\r\a" //Creating a list of delimiters to pass to strtok().

//function for making a directory(folder)
void mkDir(char *dirname)
{

    int check;
    check = mkdir(dirname);
    //checking if directory is created
    if (!check)
        printf("Directory created\n");
    else
    {
        printf("Unable to create directory\n");
        exit(1);
    }
    //system("dir/p");
    return;
}

//function for removing a directory(folder)
void rmDir(char *dirname)
{
    int cheack;
    //system("dir/p");

    cheack = rmdir(dirname);
    if (!cheack)
        printf("Directory deleted\n");
    else
    {
        printf("Unable to remove directory\n");
        getch();
    }
    return;
    getch();
}

char *builtin_str[] = {
    "cd",
    "setup",
    "exit"
};

int num_builtins()
{
    return (sizeof(builtin_str)/sizeof(char**));
}

int setup()
{
    int i;
    printf("\nSimple Linux Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++)
    {
        printf("%s\n", builtin_str[i]);
    }
    return 1;
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
    setup();
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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <io.h>
#include <process.h>
#include <conio.h>
#define RL_BUFSIZE 1024 // Buffer Size for Read_Line
#define TOKEN_BUFSIZE 64 // Buffer Size for Parser
#define TOKEN_DELIM_STR " \n\t\r\a" //Creating a list of delimiters to pass to strtok().

//function for making a directory(folder)
void mkDir(char *dirname)
{

    int check;
    check = mkdir(dirname);
    //checking if directory is created
    if (!check)
        printf("Directory created\n");
    else
    {
        printf("Unable to create directory\n");
        exit(1);
    }
    //system("dir/p");
    return;
}

//function for removing a directory(folder)
void rmDir(char *dirname)
{
    int cheack;
    //system("dir/p");

    cheack = rmdir(dirname);
    if (!cheack)
        printf("Directory deleted\n");
    else
    {
        printf("Unable to remove directory\n");
        getch();
    }
    return;
    getch();
}

char *builtin_str[] = {
    "cd",
    "setup",
    "exit"
};

int num_builtins()
{
    return (sizeof(builtin_str)/sizeof(char**));
}

int setup()
{
    int i;
    printf("\nSimple Linux Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++)
    {
        printf("%s\n", builtin_str[i]);
    }
    return 1;
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
    setup();
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
