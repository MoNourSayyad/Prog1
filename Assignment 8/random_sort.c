/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/


#include <stdio.h>
#include "../prog1lib/lib/base.h"
#include <math.h>

//template code

int compares = 0;

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;


struct Car{
	char* brand;
	int year;
	int km;
	double price;
};

typedef struct Car Car;

//print car information
void print_car(Car* car){
	printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);	
}

//print carArray
void print_car_array(Car* car_park, int car_count){
	for(int i = 0; i < car_count; i++){
		print_car(car_park + i);
	}
}


// Creates an array with random cars. Returns a pointer to the array.
Car* create_car_park(int car_count){
	//next statement is part of the following lectures. Don't worry.
	Car* car = (Car*) xmalloc(sizeof(Car) * car_count);
	
	//fill the array with random cars
	for(int i = 0; i < car_count; i++){
		int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

		car[i].brand = brands[random_brand_index];
		int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
		car[i].year = random_year;
		
		int random_km = 0;
		// On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
		if(RAND_MAX == 32767){
			random_km = (i_rnd(max_km >> 16) << 16 ) | i_rnd(max_km); //dirty hack
		}else{
			random_km = i_rnd(max_km); 
		}
		car[i].km = random_km; //max 250.000km
		
		car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) + 20000.00 * pow(0.75, random_km / 10000.0)  ; // car price max 50.000 Euro
	}
	return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
}

//end of template code

//(a) TODO: implement compare function--------------------------------------
int compare(Car car1, Car car2) {
	compares++;

    // compare by year first
    if (car1.year > car2.year) {
        return 1;   // car1 is younger
    }
    if (car1.year < car2.year) {
        return -1;  // car1 is older
    }

    // same year → compare brands lexicographically
    int brand = strcmp(car1.brand, car2.brand);

    if (brand > 0) {
        return 1;
    }
    if (brand < 0) {
        return -1;
    }

    // same year and same brand
    return 0;
}



// (b) TODO: write compare test function---------------------------------------
void compare_test(void) {
    Car a;
    Car b;

    // 1) car1 younger than car2 -> return 1
    a.year = 2010;
    a.brand = "BMW";
    b.year = 2000;
    b.brand = "BMW";
    test_equal_i(compare(a, b), 1);

    // 2) car1 older than car2 -> return -1
    a.year = 1995;
    a.brand = "Audi";
    b.year = 2005;
    b.brand = "Audi";
    test_equal_i(compare(a, b), -1);

    // 3) same year, brand lexicographically smaller -> return -1
    a.year = 2010;
    a.brand = "Audi";
    b.year = 2010;
    b.brand = "BMW";
    test_equal_i(compare(a, b), -1);

    // 4) same year, brand lexicographically larger -> return 1
    a.year = 2010;
    a.brand = "VW";
    b.year = 2010;
    b.brand = "Fiat";
    test_equal_i(compare(a, b), 1);

    // 5) same year and same brand -> return 0
    a.year = 2010;
    a.brand = "Dacia";
    b.year = 2010;
    b.brand = "Dacia";
    test_equal_i(compare(a, b), 0);
}


// (c) TODO: implement sorted function
bool sorted(Car* a, int length){
	 for (int i = 0; i < length - 1; i++) {
        if (compare(a[i], a[i + 1]) > 0) {
            return false;
        }
    }
    return true;
}

// (d,e) TODO: implement random_sort function------------------
int random_sort(Car* a, int length) {
	compares = 0;
    int swaps = 0;

    while (!sorted(a, length)) {
        int i = i_rnd(length);
        int j = i_rnd(length);

        Car x = a[i];
        a[i] = a[j];
        a[j] = x;

        swaps++;
    }

    return swaps;
}

//2E-------------------------------------------------------------
	/*
	Wenn das Array schon sortiert ist, wird sorted() von random_sort()
	nur einmal aufgerufen. sorted() geht dann alle Elemente der Reihe nach
	durch und vergleicht jeweils zwei Nachbarn (insgesamt length - 1 Vergleiche).

	Da alles schon richtig sortiert ist, muss nichts vertauscht werden
	und random_sort() gibt am Ende 0 Vertauschungen zurück.
	*/


int main(void) {
	
	// (b) TODO: test compare function
	compare_test();
	
	
	//some output
	int number_of_random_cars = 10;
	Car* car_park = create_car_park(number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	
	printf("Sorting...\n");
	
	//TODO: sort the car_park array.
	int swaps = random_sort(car_park, number_of_random_cars);
	printf("swaps = %d\n", swaps);
	printf("compares = %d\n", compares);

	print_car_array(car_park, number_of_random_cars);
	
	delete_car_park(car_park);

    return 0;
}
/* 
gcc random_sort.c ../prog1lib/lib/base.c -o x
 
./x
 
*/