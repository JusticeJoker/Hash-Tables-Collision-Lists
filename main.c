#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// define
#define HASH_TABLE_SIZE 20
#define BASE 64


// enums
typedef enum Boolean
{ false, true } bool;

// profile struct 
typedef struct profile
{
	int id;
	int nickname[50 + 1];
	int age;
	int gender;
	char email[100 + 1];
	char debugInfo[100 + 1];
	struct profile *next;
	
} Profile;

// hash for the nickname
int h(char *nickname)
{
	// variables
	int i = 0, z = 0, x;
	
	// runs throug all the letters in the nickname
	while (x = *nickname++)
	{
		i = (x * BASE + z) / 7;
		z += z;
	}
	
	// returns the value calculated 
	return i % HASH_TABLE_SIZE;
}

// initialize hashtable array
void initialize(Profile *profiles[], int n)
{
	// variables
	int i;
	
	// initialize
	for(i = 0; i < n; i++)
		profiles[i] = NULL;
}

// function to add a new profile to the hash table
void newProfile(Profile *profiles[], int n, int profileId, char *profileNickname, int profileAge, char *profileEmail, int profileGender)
{
	// variables
	Profile *newProfile;
	int hash, index;
	Profile *list;
	Profile *actual;
	
	
	// compute hash
	hash = h(profileNickname);
	actual = profiles[hash];
	
	//navigate through the list till the end
	while (actual != NULL)
	{
		// compares if nickname is the same
		if (strcmp(actual->nickname, profileNickname) == 0)
		{
			printf("\nThis user nickname already exists. Try another!\n");
			return;
		}
		
		// next element
		actual = actual->next;
	}
	
	//build a new player profile
	newProfile = (Profile*) malloc(sizeof(Profile));
	newProfile->id = profileId;
	newProfile->gender = profileGender;
	strcpy(newProfile->nickname, profileNickname);
	strcpy(newProfile->email, profileEmail);
	newProfile->age = profileAge;
	sprintf(newProfile->debugInfo, "h(nickname) = h(\"%d\") = %d", profileNickname, hash);
	
	// get the reference to the linked list hanging on hash array element
	list = profiles[hash];
	
	// insert in the head
	newProfile->next = list;
	
	// save the user profile to the head in the array
	profiles[hash] = newProfile;	
}

// Function to remove a user profile
void removeProfile(Profile *profiles[], int n, char *profileNickname)
{
	//variables
	int hash;
	Profile *helper;
	Profile *actual; 
	Profile *previous;
	
	// compute hash of x
	hash = h(profileNickname);
	
	// save the begining of the list
	actual = profiles[hash];
	
	// special in case list is empty
	if (profiles[hash] == NULL)
	{
		printf("\nTrying to remove a profile that doesn't exist\n");
		return;
	}
	
	// compares if nickname is the same
	if (strcmp(actual->nickname, profileNickname) == 0)
	{
		profiles[hash] = actual->next;
		helper = actual;
		free(helper);
		return;		
	}
	
	// find the profile to be removed
	while (actual != NULL)
	{
		// move to the next element
		previous = actual;
		actual = actual->next;
	}
	
	// profile may not exist
	if (actual == NULL)
	{
		printf("\n profile does not exist\n", profileNickname);
		return;
	}
	
	// remove the profile
	previous->next = actual->next;
	free(actual);	
}

// search user Profile
Profile *getProfile(Profile *profiles[], int n, int profileId, char *profileNickname)
{
	// variables
	int hash;
	Profile *actual, *index;
	
	// compute hash of x
	hash = h(profileNickname);
	
	// get the reference to the list
	actual = profiles[hash];
		
	// find the user profile 
	while ((actual != NULL) && (actual->id != profileId))
		actual = actual->next;
		
	//return the actual profile 
	return actual;	
}

// show hash table with all the profiles
void showHashtableMap(Profile *profiles[], int n)
{
	// variables
	int i;
	Profile *actual;
	
	// show all profiles
	for(i = 0; i < n; i++)
	{
		// identy the current array slot
		printf("===========================================================================\n");
		printf(" slot: %02d\n", i);
		
		// get the reference to the list
		actual = profiles[i];
		
		// navigate through the list till the end
		while (actual != NULL)
		{
			// when the input is 1 the profile gender is set to male
			if(actual->gender == 1)
			{	
				printf("===========================================================================\n");
				// show the full user profile info
				printf("\t Profile ID: %d | Nickname: %s | Age: %d | Email: %s | Gender: Male\n", actual->id, actual->nickname, actual->age, actual->email);
				printf("\t> %s\n\n", actual->debugInfo);
			}
			// when the input is 1 the profile gender is set to female
			else if(actual->gender == 0)
			{
				printf("===========================================================================\n");
				// show the full user profile info
				printf("\t Profile ID: %d | Nickname: %s | Age: %d | Email: %s | Gender: Female\n", actual->id, actual->nickname, actual->age, actual->email);
				printf("\t> %s\n\n", actual->debugInfo);
			}
			// incase neither are valid for the gender
			else
				printf(" INVAID GENDER! PLEASE SET A VALID GENDER USING (1) - Male OR (2) - Female \n");
			
			
			// next element
			actual = actual->next;
		}
		
	}
}

// show list of all profiles
void showProfiles(Profile *profiles[], int n)
{
	
	int i;
	Profile *actual;
	
	// show all profiles
	for(i = 0; i < n; i++)
	{		
		// get the reference to the list
		actual = profiles[i];
	
		// navigate through the list till the end
		while (actual != NULL)
		{
			if(actual->gender == 1){
				
				//show the full user profile info
				printf("| %d %s (age: %d email: %s) gender: Male\n", actual->id, actual->nickname, actual->age, actual->email);
			}
			else if(actual->gender == 0)
			{
				printf("| %d %s (age: %d email: %s) gender: Female\n", actual->id, actual->nickname, actual->age, actual->email);
			}
			
			// next element
			actual = actual->next;
		}
	}
}

// update the club member
void updateProfile(Profile *profiles[], int n, int profileId, char *profileNickname, int profileAge, char *profileEmail, int profileGender)
{
	// variables	
	int hash;
	Profile *actual, *index;
	
	// compute hash of x
	hash = h(profileNickname);
	
	// get the reference to the list
	actual = profiles[hash];
		
	// find the user profile 
	while ((actual != NULL) && (actual->id != profileId))
		actual = actual->next;
	
	//update player
	actual->id = profileId;
	strcpy(actual->nickname, profileNickname);
	strcpy(actual->email, profileEmail);
	actual->age = profileAge;
	actual->gender = profileGender;

}

void avgAgeProfile(Profile *profiles[], int n)
{
	// variables
	int i, totalMale = 0, totalFemale = 0;
	float avgMale = 0, avgFemale = 0, avgAll;
	int counterMale = 0, counterFemale = 0;
	Profile *actual;
	
	// runs through all the profiles in the list
	for( i = 0; i < n; i++)
	{
		// get the reference to the list
		actual = profiles[i];
		
		// navigate through the list till the end
		while( actual != NULL)
		{
			
			if(actual->gender == 1)
			{
				// add a total of all male ages 
				totalMale += actual->age;
				counterMale++;	
			}
			else
			{
				// add a total of all female ages 
				totalFemale += actual->age;
				counterFemale++;
			}
			
			// next element
			actual = actual->next;
			
		}
	}
	
	// calculate the average age for male
	avgMale = totalMale/(float)counterMale;
	
	// calculate the average age for female
	avgFemale = totalFemale/(float)counterFemale;
	
	// calculate the average age of all the profiles
	avgAll = (totalMale + totalFemale)/(float)(counterMale + counterFemale);
	
	// print all the averages for the male and female and the total average
	printf("\n ============================== \n\n");
	printf("The average Male age is: %.2f\n\n", avgMale);
	printf("The average Female age is: %.2f\n\n", avgFemale);
	printf("The average age of all profiles is: %.2f\n\n", avgAll);
	
	
}

int main(int argc, char *argv[]) {

	// variables
	Profile *profiles[HASH_TABLE_SIZE];    //array of pointers
	Profile *profile;
	
	// initialize array
	initialize(profiles, HASH_TABLE_SIZE);
	
	// add user profiles
	newProfile(profiles, HASH_TABLE_SIZE, 87, "Metro22", 19, "matro22@gmail.com", 0);
	newProfile(profiles, HASH_TABLE_SIZE, 32, "BigLion2", 25, "BIGLION@gmail.com", 1);
	newProfile(profiles, HASH_TABLE_SIZE, 64, "Travis99", 29, "catdog3@hotmail.com", 1);
	newProfile(profiles, HASH_TABLE_SIZE, 92, "BloodMountain", 35, "BMountain@gmail.com", 1);
	newProfile(profiles, HASH_TABLE_SIZE, 12, "VikingSun1993", 22, "Viking97@yahoo.com", 0);
	newProfile(profiles, HASH_TABLE_SIZE, 73, "Furion", 41, "Furion@hotmail.com", 0);
	newProfile(profiles, HASH_TABLE_SIZE, 49, "SandelFox", 32, "Fox1984@yahoo.com", 0);
	newProfile(profiles, HASH_TABLE_SIZE, 52, "SandelFox", 25, "SandelFox33@gmail.com", 1);
	
	printf("===========================================================================\n");
	// show all active user profiles
	printf("\n\n\t\t LIST OF PROFILES \n\n");
	showProfiles(profiles, HASH_TABLE_SIZE);
	printf("\n===========================================================================\n");
	
	//get specific user profile
	profile = getProfile(profiles, HASH_TABLE_SIZE, 92, "BloodMountain");
	printf("\n    The user profile nickname is: %s\n", profile->nickname);
	
	printf("\n===========================================================================\n");
	// remove an user profile
	printf("\n After Removing Profile with the BigLion2 nickname\n");
	removeProfile(profiles, HASH_TABLE_SIZE, "BigLion2");
	
	printf("\n===========================================================================\n");
	// show hash table map
	printf("\n\t HASH TABLE MAP \n");
	showHashtableMap(profiles, HASH_TABLE_SIZE);	
	
	// update the profile
	printf("\n===========================================================================\n");
	printf("\n Updating the profile with the VikingSun1993 \n\n");
	updateProfile(profiles, HASH_TABLE_SIZE, 12, "VikingSun1993", 27, "Viking97@gmail.com", 0);
	
	// show the profiles list
	printf("\n\n\t\t LIST OF PROFILES \n\n");
	showProfiles(profiles, HASH_TABLE_SIZE);
	
	// show the average age of all profile aswell the average age of Male and Female profiles
	printf("\n===========================================================================\n");
	printf("\n\n\tLIST OF AVERAGE AGES \n\n");
	avgAgeProfile(profiles, HASH_TABLE_SIZE);
	

	return 0;
}
