#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subs(int ch, char dict[]);

int main(int argc, char *argv[]){
	if(strlen(argv[1]) != 26){
		printf("FATAL : Inputing a inconsistent dictionary is not fair.");
		exit(1);
	}
	char dict[27];
	strcpy(dict, argv[1]); // Last char may be '\0'
	char ch = getchar();
	while(ch != EOF){
		putchar(subs(ch, dict));
		ch = getchar();
	}
}

int subs(int ch, char dict[]){
	int sktp = ch;
	int counter = 0;
	if(sktp>='a' && sktp <= 'z'){
		while(dict[counter] != sktp){
			counter++;
		}
		return counter + 'a' ;
	} else if(sktp>='A' && sktp<='Z'){
		sktp = sktp + ('a' - 'A');
		while(dict[counter] != sktp){
			counter++;
		}
		return counter + 'A';
	} 
	return ch;
}
