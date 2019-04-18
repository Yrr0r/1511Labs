#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int count = 0;
	char ch = getchar();
	while(ch != EOF){
		if(argc == 1){
			putchar(ch);
		}else if(strcmp(argv[1], "--upper") == 0){
			if(ch >= 'a' && ch <= 'z'){
				ch -= ('a'-'A');
			}
			putchar(ch);
		}else if(strcmp(argv[1], "--lower") == 0){
			if(ch >= 'A' && ch <= 'Z'){
				ch += ('a'-'A');
			}
			putchar(ch);
		}else if(strcmp(argv[1], "--swap") == 0){
			if(ch >= 'A' && ch <= 'Z'){
				ch += ('a'-'A');
			} else if(ch >= 'a' && ch <= 'z'){
				ch -= ('a'-'A');
			}
			putchar(ch);
		}
		ch = getchar();
	}

}
