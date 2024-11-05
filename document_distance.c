#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_WORD_LEN 21
#define MAX_TITLE_LEN 7
#define MAX_FILES 100
#define MAX_INQUIRIES 100000

typedef struct Word {
    char word[MAX_WORD_LEN];
    int count;
    struct Word* nextword;
} Word;

typedef struct {
    char title[MAX_TITLE_LEN];
    Word* nullhead;
}Title;

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void stem(char *word) {
    int len = strlen(word);
    if (len > 3) {
        if (strcmp(&word[len-3], "ies") == 0) {
            strcpy(&word[len-3], "y");
        } else if (strcmp(&word[len-2], "es") == 0 || strcmp(&word[len-2], "ed") == 0) {
            word[len-2] = '\0';
        } else if (strcmp(&word[len-3], "ing") == 0) {
            word[len-3] = '\0';
        }
    }
}

void add(char* word,Title* file){
    to_lowercase(word);
    stem(word);
    Word* cur=file->nullhead;
    while(cur!=NULL){
        int result = strcmp(word,cur->word);
        if(result>0){
            if(cur->nextword==NULL||strcmp(((Word*)cur->nextword)->word,word)>0){
                Word* new_word=(Word*)malloc(sizeof(Word));
                new_word->nextword=cur->nextword;
                cur->nextword=new_word;
                strcpy(new_word->word,word);
                new_word->count=1;
                break;
            }
            else cur=cur->nextword;
        }
        else if (result == 0){cur->count++;
        break;
        }
        else{}
    }

}

double calculate(Title* file1,Title* file2){
    double result=0;
    double whole1=0,whole2=0;
    Word* node1=file1->nullhead;
    Word* node2=file2->nullhead;
    while(node1!=NULL||node2!=NULL){
        if(strcmp(node1->word,node2->word)==0){
            result+=node1->count*node2->count;
            whole1+=node1->count*node1->count;
            whole2+=node2->count*node2->count;
            node1=node1->nextword;
            node2=node2->nextword;
            }
        else if (strcmp(node1->word,node2->word)>0){
            whole2+=node2->count*node2->count;
            node2=node2->nextword;
            }
        else {
            whole1+=node1->count*node1->count;
            node1=node1->nextword;
        }
    }
    if(node1!=NULL){
        while(node1!=NULL){
            whole1+=node1->count*node1->count;
            node1=node1->nextword;
        }
    }
    if(node2!=NULL){
        while(node2!=NULL){
            whole2+=node2->count*node2->count;
            node2=node2->nextword;
        }
    }
    whole1=sqrt(whole1);
    whole2=sqrt(whole2);
    return result/(whole1*whole2);
}

int main(void){
    int N,n;
    scanf("%d",&N);
    getchar();
    Title* files[101];
    for(int i=0;i<N;i++){
        files[i]=(Title*)malloc(sizeof(Title));
        files[i]->nullhead=(Word*)malloc(sizeof(Word));
        strcpy(files[i]->nullhead->word,"\0");
        scanf("%s",files[i]->title);
        files[i]->nullhead->count=0;
        getchar();
        char word[25];
        scanf("%s",word);
        getchar();
        while(strcmp(word,"#")!=0){
            add(word,files[i]);
            scanf("%s",word);
            getchar();
        }
    }
    scanf("%d",&n);
    char name1[10],name2[10];
    int id_1=0,id_2=0;
    for(int i=0;i<n;i++){
        scanf("%s %s",name1,name2);
        getchar();
        for(int j=0;j<N;j++){
            if(strcmp(name1,files[j]->title)==0)id_1=j;
            if(strcmp(name2,files[j]->title)==0)id_2=j;
        }
        double dist=0;
        dist=calculate(files[id_1],files[id_2]);
        printf("Case %d: %.3f\n",i+1,acos(dist));
    }
    return 0;
}