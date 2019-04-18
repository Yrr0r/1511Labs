// Read all comments before submit.
// And also add comment here.

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

struct coordinate {
    double x;
    double y;
};
typedef struct coordinate Coordinate;


// PROTOTYPES
Strlist *scanToList(Strlist *head);
Strlist *appendS(char data, Strlist *head);
Strlist *createNodeS(char data, Strlist *next);
Strlist *lastS(Strlist *head);
void putList(Strlist *firstList);
int drawAll(Strlist *list, double lineLen, double iniDir, double angleInc, Rgb color);


// Prototype End

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

    // ALL Inputs are done by now.

    if(argc == 1){
        // Just printing, nothing else.
        printf("Line Length: %.4lf \n", lineLen);
        printf("Initlal Direction: %.4lf \n", iniDir);
        printf("Angle Increment: %.4lf \n", angleInc);
        printf("Initial Color: RGB(%.4lf,%.4lf,%.4lf) \n", color.r, color.g, color.b);
        // Print String
        printf("Initial String: ");
        putList(firstList);
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
    if(argc == 2){
        int iteration = atoi(argv[1]);
        // Do iterations before print for stage 2
        drawAll(firstList, lineLen, iniDir, angleInc, color);
    }
    

} // This close bracket ends main().

int drawAll(Strlist *list, double lineLen, double iniDir, double angleInc, Rgb initColor){
    Strlist *curlist = list;
    double angle = iniDir;
    Coordinate curpos;
    curpos.x = 0; 
    curpos.y = 0;
    Rgb color = initColor;
    double colorInc = 0.1;
    
    while(curlist != NULL){
        char ch = curlist->data;
        // non-drawing operations are easy, do first.
        if(ch == '+'){
            angle += angleInc;
        }else if(ch == '-'){
            angle -= angleInc;
        }else if(ch == 'R'){
            color.r += colorInc;
        }else if(ch == 'r'){
            color.r -= colorInc;
        }else if(ch == 'G'){
            color.g += colorInc;
        }else if(ch == 'g'){
            color.g -= colorInc;
        }else if(ch == 'B'){
            color.b += colorInc;
        }else if(ch == 'b'){
            color.b -= colorInc;
        }else if(ch == 'f'){
            // small 'f', inc place but no write
            // Move:
            curpos.x += lineLen * cos(angle);
            curpos.y += lineLen * sin(angle);
        }else if (ch == 'F'){

            // Add color bound limit to make all color stays in range 0 to 1. # Important!

            // big 'F', with prints.
            // Initial pos:
            printf("%.0lf %.0lf ", curpos.x, curpos.y);
            // Move:
            curpos.x += lineLen * sin(angle);
            curpos.y += lineLen * cos(angle);
            printf("%.0lf %.0lf ", curpos.x, curpos.y);
            printf("%lf %lf %lf \n", color.r, color.g, color.b);
        }
        // If judge done, go to next element.
        curlist = curlist -> next;
    }
    return 0;
}


Strlist *strToList(Strlist *tail, char rpstring[]){
    int charCount = strlen(rpstring);
    // Create a list of string.
    Strlist *newlist = NULL;
    for(int i=0; i<charCount; i++){
        newlist = appendS(rpstring[i], newlist);
    }
    lastS(newlist) -> next = tail;
    return newlist;
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
        // ERROR CHK FOR UNABLE TO MALLOC.
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

void putList(Strlist *firstList){
    Strlist *curr = firstList;
    while(curr != NULL){
        putchar(curr->data);
        curr = curr->next;
    }
}
