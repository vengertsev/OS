/*
  This program needs the file error.c and mydash.h to compile.
 */
#include    <sys/types.h>
#include    <sys/wait.h>
#include    <mydash.h>
#include    <unistd.h>
#include    <pwd.h>

int main(int argc, char *argv[])
{
    //char    buf[MAXLINE];
    pid_t   pid;
    int     status;

  	char *line;
  	char *prompt = "mydash>";
   
    int numTokens;
    const char *homedir;
   
   	using_history();
  
  
    // validate prompt
    if (getenv("DASH_PROMPT") != NULL) {
        prompt = getenv("DASH_PROMPT");
    }        

    // print version information
    if (argc > 1)
         if (strcmp(argv[1], "-v")==0) 
         {
             printf("%s Version 1: Revision %s (author: Dmitry Vengertsev DmitryVengertsev@u.boisestate.edu)\n", prompt, git_version());
             exit(EXIT_SUCCESS);
         }

  	while ((line = readline(prompt))) 
  	{          
        // add lines to history 
    		add_history(line);
    
        // exit 
        if((strcmp(line, "exit") == 0))
    				break;
        
        // check for line with only spaces 
        uint spaces = 0;
        size_t len = strlen(line);
        size_t idx; 
        for (idx=0;idx<len; ++idx)
           if (line[idx] == ' ')
              ++spaces;
            
        // check not empty line
        if ( (line[0] != '\0') & (spaces != len) )
        {        
            // parse line to get command with args
            char **cmd = parseInput(line, " ", &numTokens);
            cmd[numTokens] = NULL;

            if (numTokens <= MAXARGS) {
                // change directory
                if ((strcmp(*cmd, "cd")) == 0) {
                    // home dir case
               	    if (cmd[1] == NULL) 
                     {            
                        if ((homedir = getenv("HOME")) == NULL) 
                        {
                            homedir = getpwuid(getuid())->pw_dir;
                        }       
                            chdir(homedir);
                       	} else {          
                      		  if ((chdir(cmd[1])) != 0)													
                       			    fprintf (stderr, "ERR: Cannot change directory.\n");
                        }             
                 } else {
            
                    if ( (pid = fork()) < 0)
                        err_sys("fork error");  
                    else if (pid == 0) {        /* child */
                        execvp(cmd[0], cmd);
                        err_ret("couldn't execute: %s", line);
                        exit(EXIT_FAILURE);
                    }
                                
                    /* parent */
                    if ( (pid = waitpid(pid, &status, 0)) < 0)
                       err_sys("waitpid error");
                }
            } else {
              fprintf (stderr, "Number of arguments exceeds allowed number.\n");
            }
            free(cmd);
         } 
         free(line);
      }
    exit(EXIT_SUCCESS);
}

/* vim: set ts=4: */
