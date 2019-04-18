// Read all comments before submit.
// And also add comment here.

#define MAX_RULES 20
#define RULES_LENGTH 100
#define SEARCH_LENGTH 2
#define REM_DEPTH 10
#define COLOR_INCR 0.1

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

struct stateMemory {
    struct coordinate resPos;
    struct rgb resColor;
    double resAngle;
    struct stateMemory *prev;
    struct stateMemory *next;
};
typedef struct stateMemory stateMem;


// PROTOTYPES
Strlist *scanToList(Strlist *head);
Strlist *appendS(char data, Strlist *head);
int countNode(Strlist *head);
Strlist *createNodeS(char data, Strlist *next);
Strlist *lastS(Strlist *head);
void putList(Strlist *firstList);
int drawAll(Strlist *list, double lineLen, double iniDir, double angleInc, Rgb color);
Strlist *iterate(Strlist *firstList, int iterations, char search[MAX_RULES][SEARCH_LENGTH], char replace[MAX_RULES][RULES_LENGTH]);
char readNext(Strlist *head, int next);
Strlist *searchReplace(Strlist *firstlist, char search[], char replace[]);
Strlist *strToList(Strlist *tail, char rpstring[]);
Strlist *skipToNode(Strlist *head, int next);
void freeAll(Strlist *head);
void freeSomeNodes(Strlist *head, int count);
stateMem *memNext(stateMem *curr);
stateMem *memPrev(stateMem *curr);
stateMem *moreTail(stateMem *lasttail);
stateMem *initList();
int stateMemFreeAll(stateMem *anyNode);

// Prototype End

int main(int argc, char *argv[]){
    double lineLen;
    double iniDir;
    double angleInc;
    Rgb color;
    // scan in first few lines
    if (scanf("%lf%lf%lf", &lineLen, &iniDir, &angleInc) != 3) {
        fprintf(stderr, "SYNTAX ERROR AT INPUT LINE 1");
        exit(0);
    }
    if( scanf("%lf%lf%lf", &color.r, &color.g, &color.b) != 3) {
        fprintf(stderr, "SYNTAX ERROR AT INPUT LINE 2");
        exit(0);
    }

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
        printf("Initial Direction: %.4lf \n", iniDir);
        printf("Angle Increment: %.4lf \n", angleInc);
        printf("Initial Colour: RGB(%.4lf,%.4lf,%.4lf) \n", color.r, color.g, color.b);
        // Print String
        printf("Start String: ");
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
        // Add input error check
        int iteration = atoi(argv[1]);
        // Do iterations before print for stage 2
        firstList = iterate(firstList,iteration, search, replace);
        
        drawAll(firstList, lineLen, iniDir, angleInc, color);
    }if(argc == 3){
        // Add input error check
        int iteration = atoi(argv[1]);
        if(strcmp(argv[2], "-s") == 0){
            printf("StartString: ");
            putList(firstList);
            printf("\n");
            firstList = iterate(firstList,iteration, search, replace);
            printf("After %d iterations: \n", iteration);
            putList(firstList);
            printf("\n");
        } else {
            fprintf(stderr, "Argument not understood.");
            exit(0);
        }
    }
    
    freeAll(firstList);

} // This close bracket ends main().

Strlist *iterate(Strlist *firstList, int iterations, char search[MAX_RULES][SEARCH_LENGTH], char replace[MAX_RULES][RULES_LENGTH]){
    int counter = MAX_RULES;
    Strlist * retr = firstList;
    for(int i=0; i<iterations; i++){
        for(int j=0; j<counter; j++){
            retr = searchReplace(firstList, search[j], replace[j]);
        }
    }
    return retr;
}

Strlist *searchReplace(Strlist *firstlist, char search[], char replace[]){
    if(search[0] == '\0'){
        return firstlist;
    }
    int sLen = strlen(search);
    int rLen = strlen(replace);
    char *cache = calloc(sLen+1, sizeof(char));

    Strlist *curr = firstlist;

    while(readNext(curr, sLen) != '\0'){
        for(int i=0; i<sLen; i++){
            cache[i] = readNext(curr,i+1);
        }
        if(strcmp(cache,search) == 0){
            // Begin replacement.
            Strlist *headofGarbage = curr -> next;
            
            if( countNode(curr) <= SEARCH_LENGTH ){
                curr->next = strToList(NULL, replace);
                freeAll(headofGarbage);
            } else {
                curr->next = strToList((skipToNode(curr, sLen) ->next) , replace);
                freeSomeNodes(headofGarbage, sLen); // Free some number of nodes (useless nodes)
            }
            

            curr = skipToNode(curr,rLen);
        } else {
            curr = curr->next;
        }
    } 
    
    free(cache);
    return firstlist;
}

char readNext(Strlist *head, int next){
    Strlist *curr = head;
    for(int i=0; i<next; i++){
        if (curr == NULL) {
            // Error
            return '\0';
        }
        curr = curr->next;
    }
    if (curr == NULL){
        // Error
        return '\0';
    }
    return (curr->data);
}

Strlist *skipToNode(Strlist *head, int next){
    Strlist *curr = head;
    for(int i=0; i<next; i++){
        curr = curr->next;
        if(curr == NULL){
            // for error
            return NULL;
        }
    }
    return curr;
}

int drawAll(Strlist *list, double lineLen, double iniDir, double angleInc, Rgb initColor){
    Strlist *curlist = list;
    double angle = iniDir;
    Coordinate curpos;
    curpos.x = 0; 
    curpos.y = 0;
    Rgb color = initColor;
    double colorInc = COLOR_INCR;

    // Bracket reserves
    stateMem *stateList = initList();
    
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
            // small 'f', inc place but no write, move only:
            curpos.x += lineLen * sin(angle);
            curpos.y += lineLen * cos(angle);
        }else if (ch == 'F'){

            // Color bound check
            if(color.r > 1){
                color.r = 1;
            } else if(color.r < 0){
                color.r = 0;
            }
            if(color.g > 1){
                color.g = 1;
            } else if(color.g < 0){
                color.g = 0;
            }
            if(color.b > 1){
                color.b = 1;
            } else if(color.b < 0){
                color.b = 0;
            }

            // big 'F', with prints.
            // Initial pos:
            printf("%lld %lld ", (long long)curpos.x, (long long)curpos.y);
            // Move:
            curpos.x += lineLen * sin(angle);
            curpos.y += lineLen * cos(angle);
            printf("%lld %lld ", (long long)curpos.x, (long long)curpos.y);
            printf("%lf %lf %lf \n", color.r, color.g, color.b);
        }
        else if (ch == '[') {
            stateList->resPos = curpos;
            stateList->resColor = color;
            stateList->resAngle = angle;
            stateList = memNext(stateList);
        }
        else if (ch == ']') {
            stateList = memPrev(stateList);
            curpos = stateList->resPos;
            color = stateList->resColor;
            angle = stateList->resAngle;
        }
        // If judge done, go to next element.
        curlist = curlist -> next;
    }
    stateMemFreeAll(stateList);
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
    first = appendS('`', first);
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
        fprintf(stderr, "ERROR: malloc returned NULL, check memory.");
        exit(0);
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
        if(curr->data != '`'){
            putchar(curr->data);
        }
        curr = curr->next;
    }
}

void freeAll(Strlist *head){
    Strlist *curr = head;
    Strlist *needFree = NULL;
    while(curr != NULL){
        needFree = curr;
        curr = curr->next;
        free(needFree);
    }
}

int countNode(Strlist *head) {
    int count = 0;
    Strlist *curr = head;
    while (curr != NULL) {
        count ++;
        curr = curr->next;
    }
    return count;
}

void freeSomeNodes(Strlist *head, int count) {
    Strlist *curr = head;
    Strlist *needFree = NULL;
    for(int i=0; i<count; i++){
        if(curr == NULL){
            break;
        }
        needFree = curr;
        curr = curr->next;
        free(needFree);
    }
}

// Added new func for new list

stateMem *memNext(stateMem *curr) {
    if(curr->next == NULL){
        moreTail(curr);
    }
    return curr->next;
}

stateMem *memPrev(stateMem *curr) {
    if(curr->prev != NULL){
        return curr->prev;
    } else {
        return curr;
    }
}

stateMem *moreTail(stateMem *lasttail) {
    if(lasttail->next != NULL){
        return lasttail->next;
    } else {
        stateMem *new = malloc(sizeof(stateMem));
        if(new == NULL){
            fprintf(stderr, "ERROR: malloc returned NULL, check memory.");
            exit(0);
        }
        new->prev = lasttail;
        new->next = NULL;
        lasttail->next = new;
        return lasttail->next;
    }
}

stateMem *initList() {
    stateMem *head = malloc(sizeof(stateMem));
    if(head == NULL){
        fprintf(stderr, "Unable to malloc.");
        exit(0);
    }
    head->prev = NULL;
    
    head->next = NULL;
    return head;
}

int stateMemFreeAll(stateMem *anyNode) {
    if(anyNode == NULL){
        return 1;
    }
    stateMem *curr = anyNode;
    // Find Head
    while(curr->prev != NULL){
        curr = curr->prev;
    }
    // Begin Free
    stateMem *needFree = NULL;
    while(curr != NULL){
        needFree = curr;
        curr = curr->next;
        free(needFree);
    }
    return 0;
}
