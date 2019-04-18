//
// Starting code for CP1511 lab exercises
//

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

void speciesCount(char species[], struct pod *firstPod, int *nPods, int *nWhales);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <species>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *filename = argv[1];
    char *species = argv[2];

    struct pod *firstPod = readSightingsFile(filename);

    int podCount;
    int whaleCount;
    speciesCount(species, firstPod, &podCount, &whaleCount);
    printf("%d %s pods containing %d whales in %s\n", podCount, species, whaleCount, filename);

    return EXIT_SUCCESS;
}


// number of pods of the specified species assigned to *nPods
// total number of whales of the specified species assigned to *nWhales

void speciesCount(char species[], struct pod *firstPod, int *nPods, int *nWhales) {
    int cPod = 0;
    int cWhls = 0;
    struct pod *curr = firstPod;
    while(curr->next != NULL){
		if(strcmp(curr->species, species)==0){
			cPod++;
			cWhls = cWhls + curr->howMany;
		}
		curr = curr->next;
	}
    
    *nPods = cPod; // CHANGE ME
    *nWhales = cWhls; // CHANGE ME
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
