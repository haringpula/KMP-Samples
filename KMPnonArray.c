/*  PROGRAM NAME : Knutt-Morris-Pratt Algorithm
	SUBMITTED BY : Kyle Andre Celonez and King Red Sanchez
                   BSCS 2-3
	NOTE : This program can read any length of text as it doesn't
		   use arrays to store text from file.
		   However, patterns and filenames have a limit of 20 
		   characters. If a longer pattern or filename is needed, 
		   corresponding adjustments must be made on the code.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int Input(char filename[], char pattern[]);
void Prefix(char pattern[], int prefix[]);
void Matching(char filename[], char pattern[], int prefix[]);
void SmallCaps(char ans[]);

int main(){
	char pattern[20], filename[20], ans[3];
	int  prefix[20], flag;
	
	do{
		system("cls");
		flag = Input(filename, pattern);
		if(flag != -1){
			Prefix(pattern, prefix);
			Matching(filename, pattern, prefix);			
		}
		printf("\n\nDo you want to continue? [yes/no]: ");
		gets(ans);
		SmallCaps(ans);
	}while(strcmp(ans, "yes") == 0);
	
	return;
}

int Input(char filename[], char pattern[]){
	FILE *fp;
	int i = 0;
	char ch;
	printf("file name : ");
	gets(filename);
	if((fp = fopen(filename, "r")) == NULL){
		printf("\n\"%s\" not found!!!", filename);
		return -1;	
	}
	printf("\nText : ");
	while((ch = fgetc(fp)) != EOF)
		printf("%c", ch);
	fclose(fp);
	
	printf("\npattern : ");
	gets(pattern);
}

void Prefix(char pattern[], int prefix[]){
	int plen = strlen(pattern);
	int i = 0, j = 1, ctr = -1;	
	prefix[0] = -1;
	while(j < plen){
		if(pattern[i] == pattern[j]){
			prefix[j] = ++ctr;
			++i;
		}else{
			i = 0;
			prefix[j] = ctr = -1;
		}
		++j;
	}
	printf("\nprefix : ");
	for(i=0; i<plen; i++)
		printf("%d ", prefix[i]);
}

void Matching(char filename[], char pattern[], int prefix[]){
	FILE *fp = fopen(filename, "r");
	int plen = strlen(pattern);
	int i = 0, j = -1, match = 0, flag = 0;
	char ch;
	while((ch = fgetc(fp)) != EOF){
		do{
			if(pattern[j+1] == ch){
				flag = 0;
				++j;
				if(j + 1 == plen){
					match++;
					j = prefix[j];
				}
			}else if(j != -1){
				flag = 1;
				j = prefix[j];
			}else flag = 0;
		}while(flag);
	}
	fclose(fp);
	printf("\nmatches : %d", match);
}

void SmallCaps(char ans[]){
	int i, alen = strlen(ans);
	for(i=0; i<alen; i++)
		ans[i] = tolower(ans[i]);
}
