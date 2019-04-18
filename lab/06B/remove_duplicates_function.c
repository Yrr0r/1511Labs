
static int testdup(int length, int des[length], int num);

int remove_duplicates(int length, int source[length], int destination[length]){
	int descount = 0;
	for(int i=0; i<length; i++){ //This i is src count.
		if(testdup(length, destination, source[i]) == 0){
			destination[descount] = source[i];
			descount ++;
		}
	}
	return descount;
}

static int testdup(int length, int des[length], int num){
	for(int i=0; i<length; i++){
		if(des[i] == num){
			return 1; // FOUND DUPLICATE
		}
	}
	return 0; // NOT FOUND DUPLICATE
}
