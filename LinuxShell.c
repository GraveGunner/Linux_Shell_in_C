#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<unistd.h>
#define RL_BUFSIZE 1024 // Buffer Size for Read_Line
#define TOKEN_BUFSIZE 64 // Buffer Size for Parser
#define TOKEN_DELIM_STR " \n\t\r\a"

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
    tokens[pos] = NULL; // Null terminate the list of tokens
    return tokens;
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

int setup(char **args)
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

void loop_shell()
{
    char *line;
    char **args;
    int status = 0;
    setup(args);
    do
    {
        printf("> ");
        line = read_line();
        args = parse_line(line);

        free(line);
        free(args);
    }while(status);
}

int main()
{
    loop_shell();
    return EXIT_SUCCESS;
}