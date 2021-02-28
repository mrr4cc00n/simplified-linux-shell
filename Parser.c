#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1

char* myread(char* line)
{	
	char* prompt = "$\a ";

	char path[100];

	printf ("\033[31m");

	printf("%s\a",getcwd(path, 100));

	printf ("\033[32m");

	line = readline(prompt);

	if(strcmp(line," ") != 0)
	{	
		return line;
	}

	else
	{
		return NULL;
	}
}

int mysplit(char* line, char* delimiter, char* result[100])
{
	char* aux; 
	 
	result[0]= strtok(line,delimiter);

	int index=1;

	while(aux = strtok(NULL,delimiter))
	{
		result[index] = aux;

		index++;
    }

	return index;
}

int openfile(char* file, int flag, int flag1)
{
	char* aux = (char*)malloc(sizeof(file));

	int i = 0;

	while(file[i] != 0)
	{
		aux[i] = file[i];

		i++;
	}

	aux[i+1] = 0;

	int fd1;

	if (flag == 1)
	{
			FILE* fd  = fopen(aux,"w");

	        fclose(fd);

		 fd1 = open(aux,O_RDWR|O_CREAT|O_CLOEXEC,00700);

	}

	else if (flag == 0)
	{
		 fd1 = open(aux,O_RDWR|O_APPEND|O_CREAT|O_CLOEXEC,00700);	
	}

	else if(flag == -1)
	{
		fd1 = open(aux,O_RDONLY|O_CLOEXEC,00700);
	}

	if (fd1 == -1)
		{
		   return -1;
		}

	if(flag1 != 0)
	  {
	  	close(fd1);
	  }
	   	
  	return fd1;
}

void myexecv(char* instruction[], int lenght, int fd1, int pipelement, int in, int havepipes, int pos, char* copymenor, char filename[100], int first, int last)
{
	rename("temp1.txt","temp.txt");

	char* arguments[lenght + 1];

	int n,fd,fd2,fd3,fd4,status;

	int tunnel[2];

	pipe(tunnel);

	arguments[lenght] = 0;

	for (int i = 0; i < lenght; i++)
	{
		arguments[i] = instruction[i];
	}

	int id = fork();

	if(id == 0)
	{

	 if(pipelement < 0)
	 	{
		 	if (havepipes > 0)
		 	{
			 		if (pos == -3)
			 		{
						fd2 = open("temp.txt",O_RDWR|O_CREAT|O_CLOEXEC,00700);

						dup2(fd2,STDOUT_FILENO);

						if (in >= 3)
						{
							n = openfile(copymenor,-1,0);

							dup2(n,STDIN_FILENO);

							execvp(instruction[0],arguments);
						}
			 		}

			 		else if (pos == -2)
			 		{

						fd2 = open("temp.txt",O_RDWR|O_CREAT|O_CLOEXEC,00700);

						dup2(fd2,STDIN_FILENO);
			 		}

			 		else if (pos == -1)
			 		{

			 			fd2 = open("temp.txt",O_RDWR|O_CREAT|O_CLOEXEC,00700);

			 			fd3 = open("temp1.txt",O_RDWR|O_CREAT|O_CLOEXEC,00700);

			 			dup2(fd2,STDIN_FILENO);

			 			dup2(fd3,STDOUT_FILENO);
			 		}
	 		}

	 		else if(in >= 3)
			 	{
			 		if(first == 0)
			 		{
			 			char buffer;
			 		
			 			n = openfile(copymenor,-1,0);

			 			while(read(n,&buffer,1))
			 			{
			 				write(tunnel[1],&buffer,1);
			 			}

			 			exit(buffer);
			 		}

			 		else
			 		{
			 			if(last == 1)
			 				{
			 					FILE* fd  = fopen(copymenor,"w");
			 					fclose(fd);

			 					n = openfile(filename,-1,0);

			 				    fd4 = openfile(copymenor,1,0);

			 					dup2(n,STDIN_FILENO);

			 					dup2(fd4,STDOUT_FILENO);

			 					execvp(instruction[0],arguments);

			 					//printf("%s\n","sali" );
			 				}
			 			else if(last == 0)
			 				{
			 					n = openfile(filename,-1,0);

			 					 fd4 = openfile(copymenor,0,0);

			 					dup2(n,STDIN_FILENO);

			 					dup2(fd4,STDOUT_FILENO);

			 					execvp(instruction[0],arguments);
			 				}
			 		}
			 	}

	 			if(fd1 != 1)
		 	   	{
		 	   		int k = dup2(fd1, STDOUT_FILENO);
		 	   	}
		}

		if(in < 3)
     		execvp(instruction[0],arguments);
    }

    else
    {
	    waitpid(-1,&status,0);

    	if(in >= 3)
       		{

       			if(first != 0 )
       			{
       				close(fd4);

       				close(n);
       			}
       			close(tunnel[1]);
       			dup2(tunnel[0],STDIN_FILENO);
       			execvp(instruction[0],arguments);      			
       		}

	    if(fd1 != -1)
	    {
	    	close(fd1);
	    }
	}      
}


int resolvecd(char* result[])
{
	if(strcmp(result[1],".") == 0)
	{
		char* temp;		
		printf("%s\n",getcwd(temp, 100)); 
		return 0;
	}
	int error = chdir(result[1]);

	if(error == 0)
		return 0;

	return 1;
}

int save_history(char* line)
{
	int  fd1 = open("history.txt",O_RDWR|O_APPEND|O_CREAT|O_CLOEXEC,00700);

	write(fd1,line,strlen(line));

	write(fd1,"~",1);

	close(fd1);

	return 0;
}

int clean_history()
{
	FILE* fd  = fopen("history.txt","w");

	fclose(fd);
}

int load_history()
{
	FILE* fd = fopen("history.txt","r");

	int c = 0;

	c = fgetc(fd);

	printf("%c\n", c);

	while(c > EOF)
	{
		if(c != (int)'~')
		{
		  printf("%c", c);
		}
		else
			printf("%s\n"," " );

		c = fgetc(fd);

	}

	fclose(fd);

	return 0;
}

int resolvexpression(char* expresion, char* result[100], int havepipes, int pos)
{

	char* temp = (char*)malloc(sizeof(expresion));

	char* aux = (char*)malloc(sizeof(expresion));

	char filename [100];

	int first = 0;

	int last = -1;

	char* copymenor = (char*)malloc(sizeof(expresion));

	int status;

	int in = 0;

	int resultlenght = 0;

	for (int i = 0; i < strlen(expresion); i++)
	{
		temp[i] = (char)expresion[i];

		if((i+1) >= strlen(expresion))
		{
			temp[i+1] = 0;

			resultlenght = mysplit(temp, " ", result);

			if(strcmp(result[0],"cd") == 0)
			{
				resolvecd(result);

				free(temp); free(aux); free(copymenor);

				return 0;
			}

			else if (strcmp(result[0],"history") == 0)
			{
				load_history(result[0]);

				free(temp); free(aux); free(copymenor);

				return 0;
			}

			else if(strcmp(result[0],"clhistory") == 0)
			{
				clean_history();

				free(temp); free(aux); free(copymenor);

				return 0;
			}

			if (havepipes != 0)
			{
				myexecv(result,resultlenght,-1,-1,0,1,pos,aux,filename,first,last);

				free(temp); free(aux); free(copymenor);

				return 0;
			}

			else
			{
				myexecv(result,resultlenght,-1,1,0,0,pos,aux,filename,first,last);

				free(temp); free(aux); free(copymenor);

				return 0;
			}
		}

		else if ((char)expresion[i+1] == (char)'>' && (i+2) < strlen(expresion))
		{
			
			last = 1;

			if((char)expresion[i+2] == (char)'>')
				{
					last = 0;
				}

			temp[i+1] = 0;

			resultlenght = mysplit(temp," ", result);

			int index = 0;

			for (int j = i+2; j < strlen(expresion); j++)
			{
				if((char)expresion[j] != (char)' ' && (char)expresion[j] != (char)'>')
				   {
					   	aux[index] = (char)expresion[j];

					   	index++;
				   }

				if ((j+1) >= strlen(expresion))
				{
			      aux[index] = 0;

                  int fd1;

	              if (last == 1)
	              {
	              	fd1 = openfile(aux,1,0);

		            myexecv(result,resultlenght,fd1,-1, 0,havepipes,pos,aux,filename,first,last);
	              }

	              else if (last == 0)
                    {
                	  fd1 = openfile(aux,0,0);

		              myexecv(result,resultlenght,fd1,-1, 0,havepipes,pos,aux,filename,first,last);
                	}

					return 0;					
				}

				else if ((char)expresion[j+1] == (char)'>' && (char)expresion[j+2] == (char)'>')
				{
					aux[index] = 0;

					openfile(aux,last,1);

					j = j+3;

					index = 0;

					last = 0;

				}

				else if ((char)expresion[j+1] == (char)'>')
				{
					aux[index ] = 0;

					openfile(aux,last,1);

					j= j+2;

					index = 0;

					last = 1;
				}

				else if ((char)expresion[j+1] == (char)'<')
				{
					aux[index ] = 0;

					index = 0;

					j = j + 2;
				}
			}
		}

		else if((char)expresion[i+1] == (char)'<' && (i+2) < strlen(expresion))
		{       
				temp[i+1] = 0;

				last = -1;

				resultlenght = mysplit(temp," ", result);

				int index = 0;

				for (int j = i+2; j < strlen(expresion); j++)
				{
					if((char)expresion[j] != (char)' ')
					   {
					   	aux[index] = (char)expresion[j];

					   	index++;
					   }

					   if ((j+1) >= strlen(expresion))
					   {
					       aux[index] = 0;

		                   int fd1 = 1;

			               if (last == -1)
			               {
			               		int id = fork();

			               		if(id == 0)
				             		myexecv(result,resultlenght,1,-1,4,havepipes,pos,aux,filename,first,last);

				             	else
				             	{
				             		waitpid(-1,&status,0);

				             		return 0;
				             	}
			               }


			               else if (last == 1)
			               {
			               		int id = fork();

			               		if (id == 0)
			               		{
			               			myexecv(result,resultlenght,1,-1,4,havepipes,pos,aux,filename,first,last);
			               		}

			               		else
			               		{
				             		waitpid(-1,&status,0);

				             		return 0;			               			
			               		}
			               }

			               else if (last == 0)
			               {
			               	 	int id = fork();

			               		if (id == 0)
			               		{
			               			myexecv(result,resultlenght,1,-1,4,havepipes,pos,aux,filename,first,last);
			               		}

			               		else
			               		{
				             		waitpid(-1,&status,0);

				             		return 0;			               			
			               		}
			               }

						}

						else if ((char)expresion[j+1] == (char)'>' && first == 0)
						{
							aux[index] = 0;

							first = 1;

							int k = 0;

							while(aux[k])
							{
								filename[k] = aux[k];

								k++;
							}

							filename[k] = 0;
							
							if ((char)expresion[j+2] == (char)'>')
								{
									j=j+3;
									last = 0;
								}
							else
								{
									j=j+2;
									last = 1;
								}

							index = 0;

						}

						else if ((char)expresion[j+1] == (char)'>' && (char)expresion[j+2] == (char)'>')
						{
							aux[index] = 0;

							openfile(aux,last,1);

							j = j+3;

							index = 0;

							last = 0;

						}

						else if ((char)expresion[j+1] == (char)'>')
						{
							aux[index ] = 0;

							openfile(aux,last,1);

							j= j+2;

							index = 0;

							last = 1;
						}
				}
		}
	}

	return 0;
}

int resolve(char* expresion, char* result[100])
{
	int count_process = mysplit(expresion,"|",result);

	int havepipes = count_process -1;

	int pos = 1;

	char* operations[100];

	if(count_process-1 > 0)
	{
		for (int i = 0; i < count_process; i++)
		{
			if (i == 0)
			{
				resolvexpression(result[i],operations,havepipes,-3);
			}

			else if ((i+1) >= count_process)
			{
				resolvexpression(result[i],operations,havepipes,-2);
			}

			else if (i > 0 && (i+1) < count_process)
			{
				resolvexpression(result[i],operations,havepipes,-1);
			}
		}
	}

	else
		resolvexpression(result[0],operations,0,3);

	return 0;
}

int main(int argc, char const *argv[])
{
	char* line;

	char*result[100];

	while(strcmp(line = myread(line),"exit") != 0)
    {   
    	if(line[0] != ' ' && strlen(line) > 1)
    	   save_history(line);

    	if(strlen(line) > 1)
            resolve(line,result);
    }

   return 0;
}