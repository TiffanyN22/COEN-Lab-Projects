/*
 * File Name: generate.c
 * Author: Tiffany Nguyen
 * Date: November 11, 2022
 * Description: This files generates a random list of number and name pairs in 2 columns
 * and adds it to the file data.txt. 
 */

#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *data;
	data = fopen("data1000000.txt", "w+");
	
	int numOfElements = 1000000;

	time_t t;
	srand((unsigned) time(&t));
	
	const int numOfNames = 35;
	const int maxNameLength = 20;
	char names[35][20] = {"Tiffany", "Crystal", "Tisha", "Rita", "Juniper", "Lorraine", "Connie", "Ushoshi", "Melia", "Jade", "Sophie", "Nancy", "Adele", "Beth", "Carter", "Tracey", "Pamela", "Melinda", "Alex", "Lance", "Nora", "Inex", "Valerie", "Dening", "Allison", "Anishka", "Parnika", "Irwin", "Angela", "Carter", "Dorian", "Nicole", "Katelyn", "Alan", "Lorenzo"};
	
	int i;
	for (i = 0; i < numOfElements; i++){
		//random num before word from 1-1000
		int randomInt = 1 + rand()%1000;
		
		//get random name from list
		int nameIndex = rand()%numOfNames;

		fprintf(data, "%d %s\n", randomInt, names[nameIndex]);
	}

	fclose(data);
	exit(EXIT_SUCCESS);
}
