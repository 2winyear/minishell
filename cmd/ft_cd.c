#include "../include/minishell.h"

int start_find(char *command)
{
	int idx;

	idx = 0;
	while (command[idx] != ' ')
		idx++;
	return (idx + 1);
}

int find_dir(char* str)
{
	DIR *dir;
	int i;
	struct dirent *ent;

    dir = opendir ("./");
	if(dir == NULL)
		printf("error");
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
        printf ("%s\n", ent->d_name);
    }
	i = 0;
	while (str[i] && ((ent = readdir (dir)) != NULL))
	{
		if (str[i] != ent->d_name[i])
			return (0);
	}
    closedir (dir);
	return (1);
}

void ft_cd(char* command, char* abs_path)
{
	DIR *dir;
	struct dirent *ent;
	char *curr_pwd;
	char **curr_pwd_split;
	char **command_split;
	int start;
	int idx;
	int command_num;

	command_num = ft_strlen(command);
	start = start_find(command);
	printf("start_find: %d\n", start);
	
	//상대경로 일때
	if(command[start] != '/')
	{
		curr_pwd = getcwd(NULL, BUFSIZ);
		printf("상대경로: %s\n",curr_pwd);
	}
	// 절대경로 일때
	else
	{
		printf("절대경로: %s\n", abs_path);
		chdir("/");
	}
	printf("start: %s\n", &command[start]);
	curr_pwd_split = ft_split(curr_pwd, '/');
	idx = 0;
	dir = opendir("./");
	if(dir == NULL)
		printf("error");
	command_split = ft_split(&command[start], '/');
	idx = 0;
	//command_split 출력
	while (command_split[idx] != NULL)
	{
		printf("command: %s\n", command_split[idx]);
		if (find_dir(command_split[idx]))
		{
			printf("good\n");
			chdir(command_split[idx]);
			printf("바뀐경로: %s\n", getcwd(NULL, BUFSIZ));
		}
		else
			printf("디렉토리가 없습니다.");
		idx++;
	}


	closedir(dir);
}

char *find_abs_path(char **env)
{
	char *pwd;
	int i;

	i = 0;
	while(env[++i])
	{
		if (ft_strnstr(env[i], "PWD", ft_strlen("PWD")))
			pwd=&env[i][4];
		i++;
	}
	return (pwd);
}

int main(int argc, char **argv, char **env)
{
	char *command = "cd test";
	char *command1 = "cd ..";
	char *command2 = "cd /Users/seungyel/Downloads/minishell 2/minishell/";
	char *abs_path;
	abs_path = find_abs_path(env);
	ft_cd(command, abs_path);
	ft_cd(command1, abs_path);
	ft_cd(command2, abs_path);
}

// 시작!
// char *curr_pwd;
// if (처음에 '/' 있는지 (있음))
//     변수 선언 -> 절대 경로 파악 -> 찾아보세요
// else
//     변수 선언 -> getpwd => 현재 경로 파악
// 커멘드 변수 = 스플릿(/)
// 디렉토리의 구조체 열기
// while (커멘드 변수)
//     현재 경로 변수의 디렉토리의 파일, 디렉토리 읽어오기
// 	if( 디렉토리 있으면 ) -> 파일이다? -> X
// 		경로 바꾸기
// 	else 하나라도 없으면.
// 		error
// 디렉토리의 구조체 닫기
// 끝!!!

// cd download/minishell/minishell.c
//  -> Not a directory

// opendir
// DIR * => 무슨 구조체 (어떻게 생겨먹었는지 확인)

// readdir
// typedef struct DIR_type
// {
//     ino_t          d_ino;       /* inode 번호 */
//     off_t          d_off;       /* offset to the next dirent */
//     unsigned short d_reclen;    /* length of this record */
//     unsigned char  d_type;      /* type of file; not supported
//                                    by all file system types */
//     char           d_name[256]; /* filename */
// }   DIR_type;



/*
#include <dirent.h>

DIR *opendir(const char *name);
Directory정보 구조체인 DIR* 반환
error NULL 반환

struct dirent *readdir(DIR *dir_name);
디렉토리 내에 파일, 디렉토리를 하나씩 읽어온다.
전부 읽었을 때 NULL반환

int closedir(DIR *dir);
open된 Directory정보를 close

int chdir(const char *path);
경로를 바꾸는데에 사용된다.
*/


// return

