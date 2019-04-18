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
void writeSightingsFile(char filename[], struct pod *firstPod);
void writeSighting(FILE *f, struct pod *p);
void writeDate(FILE *f, struct date *d);
void freeSightings(struct pod *p);

struct pod * speciesDelete(char species[], struct pod *firstPod);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <old_file> <new_file> <species> \n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char * species = argv[3];

    struct pod *firstPod = readSightingsFile(argv[1]);
   
    firstPod = speciesDelete(species, firstPod);
     
    writeSightingsFile(argv[2], firstPod);

    freeSightings(firstPod);
    return EXIT_SUCCESS;
}


// delete the first occurrence of the given species from the list
// You should free the memory associated with the node you delete
// and return the start of the list

struct pod * speciesDelete(char species[], struct pod *firstPod) {
    struct pod *curr = firstPod;
    struct pod *prev = NULL;
    struct pod *needDel = NULL;
    while(strcmp(species, curr->species) != 0){
    	if(curr->next == NULL){
    		// NOT FOUND
    		return firstPod;
    	}
    	prev = curr;
    	curr = curr->next;
    }
    if(curr == firstPod){
    	struct pod *newhead = curr->next;
    	free(firstPod->when);
    	free(firstPod->species);
    	free(firstPod);
    	// free all malloced element in the node then free the node itself.
    	return newhead;
    } else {
    	prev->next = curr->next;
    	free(curr->when);
    	free(curr->species);
    	free(curr);
    	// same thing as the first one.
    	return firstPod;
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
        exit(EXIT_FAILURE);
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


// read a date in day/month/year format from stream f
// return a pointer to a malloced date struct containing them
//  return NULL if a date can not be read

struct date *readDate(FILE *f) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}

// print linked list of sightings to  filename

void writeSightingsFile(char filename[], struct pod *firstPod) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(EXIT_FAILURE);
    }

    struct pod *p = firstPod;
    while (p != NULL) {
        writeSighting(f, p);
        p = p->next;
    }
}


// print pod details to stream f

void writeSighting(FILE *f, struct pod *p) {
    writeDate(f, p->when);
    fprintf(f, " %2d %s\n", p->howMany, p->species);
}


// print date to  stream f

void writeDate(FILE *f, struct date *d) {
    fprintf(f, "%02d/%02d/%02d", d->day, d->month, d->year);
}

// free the list of sightings

void freeSightings(struct pod *p) {
    struct pod *curr = p;
    while (curr != NULL) {
        struct pod *next = curr->next;
        free(curr->species);
        free(curr->when);
        free(curr);
        curr = next;
    }
}
