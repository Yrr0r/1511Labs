#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SPECIES_NAME_LENGTH 4096

// a struct to represent the date
// a whale pod sighting was made

struct date {
    int year;
    int month;
    int day;
};

// a struct to represent a sighting
// of a pod (group) of whales

struct pod {
    struct pod  *next;
    struct date *when;
    int         howMany;
    char        *species;
};


struct pod *readSightingsFile(char filename[]);
struct pod *readSighting(FILE *f);
struct date *readDate(FILE *f);
struct date *stringToDate(char *s);

void betweenDaysWhales(struct pod *firstPod, struct date *startDay, struct date *finishDay);

// PUT YOUR FUNCTION PROTOTYPES HERE
int betweenDate(struct date *date, struct date *start, struct date *finish);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <start-day> <finish-day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct pod *firstPod = readSightingsFile(argv[1]);
    struct date *startDay = stringToDate(argv[2]);
    struct date *finishDay = stringToDate(argv[3]);

    betweenDaysWhales(firstPod, startDay, finishDay);

    return EXIT_SUCCESS;
}


// Print the whale sightings between start_day and finish_day inclusive.
// One line containing number of whales and species is printed for each sighting.

void betweenDaysWhales(struct pod *firstPod, struct date *startDay, struct date *finishDay) {

    struct pod *curr = firstPod;
	while(curr->next != NULL){
		if(betweenDate(curr->when, startDay, finishDay)){
			printf("%02d/%02d/%02d ",curr->when->day, curr->when->month,
									curr->when->year);
			printf("%2d ", curr->howMany);
			printf("%s", curr->species);
			printf("\n");
		}
		curr = curr->next;
	}
}

int betweenDate(struct date *date, struct date *start, struct date *finish){
	// 0 for not, 1 for yes.
	
	int start1 = 0;
	
	if(date->year > start->year){
		start1 = 1;
	} else if(date->year == start->year){
		if(date->month > start->month){
			start1 = 1;
		} else if(date->month == start->month){
			if(date->day >= start->day){
				start1 = 1;
			}
		}
	}
	
	int fin1 = 0;
	
	if(date->year < finish->year){
		fin1 = 1;
	} else if(date->year == finish->year){
		if(date->month < finish->month){
			fin1 = 1;
		} else if(date->month == finish->month){
			if(date->day <= finish->day){
				fin1 = 1;
			}
		}
	}
	// DEBUG SNIPPET
	if(((start1&&fin1)==1)&& date->month==2 && date->day==26 && date->year==18){
		//printf(" DBG HERE %d %d ;\n", start1, fin1);
		//printf("26/02/18 10 Common dolphin\n");
		//printf("\n");
	}
	
	if(start1 && fin1){
		return 1;
	} else {
		return 0;
	}

}


//
// DO NOT CHANGE THE FUNCTIONS BELOW HERE
//

// return linked list of sightings read from filename
// exit called if there is an error

struct pod *readSightingsFile(char filename[]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(EXIT_FAILURE);
    }

    struct pod *firstSighting = NULL;
    struct pod *lastSighting = NULL;

    struct pod *sighting = readSighting(f);
    while (sighting != NULL) {
        if (firstSighting == NULL) {
            firstSighting = sighting;
            firstSighting->next = NULL;
        } else {
            lastSighting->next = sighting;
        }
        lastSighting = sighting;
        sighting = readSighting(f);
    }

    return firstSighting;
}


// read a whale sighting (date, number of whales, whale species)
// return a pointer to a malloced struct containing these details
// return NULL if a sighting can not be read

struct pod *readSighting(FILE *f) {
    struct pod *p = malloc(sizeof (struct pod));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->next = NULL;

    p->when = readDate(f);
    if (p->when == NULL) {
        free(p);
        return NULL;
    }

    int nScanned = fscanf(f, "%d", &(p->howMany));
    if (nScanned != 1) {
        free(p);
        return NULL;
    }

    fgetc(f);
    char speciesBuffer[MAX_SPECIES_NAME_LENGTH];
    if (fgets(speciesBuffer, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        free(p);
        return NULL;
    }
   // finish string at '\n' if there is one
    char *newlinePtr = strchr(speciesBuffer, '\n');
    if (newlinePtr != NULL) {
        *newlinePtr = '\0';
    }

    // also finish string at '\r' if there is one - files from Windows  will
    newlinePtr = strchr(speciesBuffer, '\r');
    if (newlinePtr != NULL) {
        *newlinePtr = '\0';
    }

    // malloc a char array long enough to hold species name
    // and copy species to it
    p->species = malloc(strlen(speciesBuffer) + 1);
    if (p->species == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(p->species, speciesBuffer);

    return p;
}


// read a date in year/month/day format from stream f
// return a pointer to a malloced date struct containing them
//  return NULL if a date can not be read

struct date *readDate(FILE *f) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    int nScanned = fscanf(f, "%d/%d/%d", &(d->year), &(d->month), &(d->day));
    if (nScanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}

// given a string containing a date in day/month/year format
// return a pointer to a malloced date struct containing them
// return NULL if a date can not be read

struct date *stringToDate(char *s) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    int nScanned = sscanf(s, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (nScanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}
