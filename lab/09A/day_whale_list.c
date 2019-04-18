#include <stdio.h>
//
// Starting code for CP1511 lab exercises
//
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

void dayWhales(struct pod *firstPod, struct date *day);
int datecmp(struct date *dateA, struct date *dateB);

// PUT YOUR FUNCTION DEFINITIONS HERE

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct pod *firstPod = readSightingsFile(argv[1]);
    struct date *day = stringToDate(argv[2]);

    dayWhales(firstPod, day);

    return EXIT_SUCCESS;
}


// Print the whale sightings, for the specified day.
// One line containing number of whales and species
// is printed for each sighting.

void dayWhales(struct pod *firstPod, struct date *day) {
	
	struct pod *curr = firstPod;
	while(curr->next != NULL){
		if(datecmp(curr->when, day)){
			printf("%d", curr->howMany);
			printf("%s", curr->species);
			printf("\n");
		}
		curr = curr->next;
	}
}

// PUT YOUR FUNCTIONS HERE
int datecmp(struct date *dateA, struct date *dateB){
	// 0 = DIFF, 1 = SAME.
	if(dateA->year != dateB->year){
		return 0; 
	}
	if(dateA->month != dateB->month){
		return 0;
	}
	if(dateA->day != dateB->day){
		return 0;
	}
	return 1;
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
