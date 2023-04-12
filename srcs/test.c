#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 


int main(int argc, char **argv)
{
	DIR				*dir_ptr = NULL;
	struct dirent	*file	= NULL;
	struct stat		buf;
	char			*filename;
	char			*pwd;

	/* 목록을 읽을 디렉토리명으로 DIR *를 return 받습니다. */
	if((dir_ptr = opendir("/Users/dongyshi/Desktop")) == NULL) 
	{
		fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", "aaaaa");
		return -1;
	}
	/* 디렉토리의 처음부터 파일 또는 디렉토리명을 순서대로 한개씩 읽습니다. */
	while((file = readdir(dir_ptr))) 
	{
		/*
		*   struct dirent *의 구조체에서 d_name 이외에는 
		*   시스템마다 항목이 없을 수 있으므로 무시하고 이름만 사용합니다.
		*/
		filename = strdup(file->d_name);
		if(stat(ft_strjoin(pwd, filename), &buf) == -1) /* 파일의 속성(파일의 유형, 크기, 생성/변경 시간 등)을 얻기 위하여 */
			continue ;
		if (S_ISDIR(buf.st_mode) == 1)
			printf("It is a directory : %s\n", file->d_name);
		else if(S_ISREG(buf.st_mode) == 1)
			printf("It is not a directory : %s\n", file->d_name);
	}
	closedir(dir_ptr);
	return 0;
}
