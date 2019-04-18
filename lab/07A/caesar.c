#include <stdio.h>
#include <stdlib.h>

int encrypt(int character, int shift);
int shiftLetter(char ch, int shift, int lb, int hb);

int main(int argc, char *argv[]){
	int shift = atoi(argv[1])%26;
	//printf("%d\n", shift);
	char ch = getchar();
	while(ch != EOF){
		putchar(encrypt(ch, shift));
		ch = getchar();
	}
}

int encrypt(int character, int shift){
	int sktp = character;
	if(sktp >= 'A' && sktp <= 'Z'){
		int retr = shiftLetter(sktp, shift, 'A', 'Z');
		return retr;
	}else if(sktp >= 'a' && sktp <= 'z'){
		int retr = shiftLetter(sktp, shift, 'a', 'z');
		return retr;
	}else{
		return sktp; // NO SHIFT
	}	
}

int shiftLetter(char ch, int shift, int lb, int hb){
	int sktp = ch; //sktp means schetchpad.
	int range = 26;
	sktp = shift + sktp;
	if(sktp > hb){
		sktp = sktp - range;
	}
	if(sktp < lb){
		sktp = sktp + range;
	}
	return sktp;
}
