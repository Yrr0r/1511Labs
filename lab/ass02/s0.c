#define MAX_RULES 20
#define RULES_LENGTH 100
#define SEARCH_LENGTH 2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


// STRUCTS
struct rgb {
    double r;
    double g;
    double b;
};
typedef struct rgb Rgb;

struct strlist {
    char data;
    struct strlist *next;
};
typedef struct strlist Strlist;


// PROTOTYPES
Strlist *scanToList(Strlist *head);
Strlist *appendS(char data, Strlist *head);
Strlist *createNodeS(char data, Strlist *next);
Strlist *lastS(Strlist *head);


int main(int argc, char *argv[]){
    double lineLen;
    double iniDir;
    double angleInc;
    Rgb color;
    scanf("%lf%lf%lf", &lineLen, &iniDir, &angleInc);
    scanf("%lf%lf%lf", &color.r, &color.g, &color.b);
    // Do some error check here for first 3 vals.

    //Start String as LINKED LIST
    Strlist *firstList = NULL;
    // NB. IF malloc() FAILS, ADD FAILURE HANDLING.
    firstList = scanToList(firstList);

    char search[MAX_RULES][SEARCH_LENGTH] = {{'\0'}};
    char replace[MAX_RULES][RULES_LENGTH] = {{'\0'}};

    for(int i=0; i<20; i++){
        if(scanf("%s", search[i])!=1){
            break;
        }
        if(scanf("%s", replace[i]) != 1) {
            break;
        }
        for(int j=0; j< MAX_RULES; j++){
            if(replace[i][j] == '\n'){
                replace[i][j] = '\0';
            }
        }
        for(int j=0; j< SEARCH_LENGTH; j++){
            if (search[i][j] == '\n'){
                search[i][j] = '\0';
            }
        }
    }



    if(argc == 1){
        printf("Line Length: %.4lf \n", lineLen);
        printf("Initlal Direction: %.4lf \n", iniDir);
        printf("Angle Increment: %.4lf \n", angleInc);
        printf("Initial Color: RGB(%.4lf,%.4lf,%.4lf) \n", color.r, color.g, color.b);
        // Print String
        printf("Initial String: ");
        Strlist *curr = firstList;
        while(curr != NULL){
            putchar(curr->data);
            curr = curr->next;
        }
        printf("\n");
        printf("Rules:\n");
        for(int i=0; i<20; i++){
            if(search[i][0]=='\0'||replace[i][0]=='\0'){
                break;
            }
            printf("'%s' -> ",search[i]);
            printf("\"%s\"",replace[i]);
            printf("\n");
        }

    }
    

}

Strlist *scanToList(Strlist *head){
    Strlist *first = head;
    getchar();
    char ch = getchar();
    while(ch != '\n'){
        first = appendS(ch,first);
        ch = getchar();
    }
    return first;
}

Strlist *appendS(char data, Strlist *head){
    Strlist *newNode = createNodeS(data, NULL);
    if(head == NULL){
        return newNode;
    }
    Strlist *last = lastS(head);
    last->next = newNode;
    return head;
}

Strlist *createNodeS(char data, Strlist *next){
    Strlist *n = malloc(sizeof(Strlist));
    if(n == NULL){
        // ERROR FOR UNABLE TO MALLOC.
    }
    n->data = data;
    n->next = next;
    return n;
}

Strlist *lastS(Strlist *head){
    if(head == NULL){
        return NULL;
    }
    Strlist *n = head;
    while(n->next != NULL){
        n=n->next;
    }
    return n;
}