#include <stdio.h>
#include <conio.h>
#include <string.h>

void CreatePrefix(char pattern[], int prefix[]);
void StringMatching(char pattern[], int prefix[], FILE* fp, char filename[]);

int main(){
	char pattern[100], ch, retry='y',filename[100];
	int prefix[100], p, t;
	
	printf("Enter Filename:");
	scanf("%s",&filename);
	FILE *fp = fopen(filename, "r");
	printf("\nText : ");
	while((ch = fgetc(fp)) != EOF){
		printf("%c", ch);
	}
	fclose(fp);
		
	CreatePrefix(pattern, prefix);
		
	
	//input
	printf("\nPattern : ");
	gets(pattern);
	fclose(fp);
	StringMatching(pattern, prefix, fp, filename);
	
	printf("\nDo you want to try again? (y/n) :");
	scanf(" %c",&retry);
	
	return 0;
}

void CreatePrefix(char pattern[], int prefix[]){
	int i = 0, j = 1, p = strlen(pattern), ctr = -1;
	prefix[0] = -1;
	while(j<p){
		if(pattern[i] == pattern[j]){
			prefix[j] = ++ctr;
			++i;
		}else{
			i = 0;
			prefix[j] = ctr = -1;
		}
		++j;
	}
}

void StringMatching(char pattern[], int prefix[], FILE* fp, char filename[]){
	fp = fopen(filename, "r");
	int i = 0, j = -1, match = 0, x, t, p = strlen(pattern);
	char ch, text[100];
	
	while((ch = fgetc(fp)) != EOF){
		text[i] = ch;	
		++i;
	}
	t = strlen(text);
	
	for(i=0; i<t; i++){
			if(pattern[j+1] == text[i]){
				++j;
				if(j+1 == p){
					match++;
					j = prefix[j];
				}
			}else if(j != -1){
				--i;
				j = prefix[j];
			}
	}
	fclose(fp);
	printf("\nNumber of matches : %d", match);
}
