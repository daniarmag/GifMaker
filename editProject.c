#include "editProject.h"

/**
This function displays the menu of the movie maker.
input: none.
output: the selected option by the user
**/
int menu(void)
{
	int valid = FALSE;
	int ans = 0;
	while (!valid)
	{
		printf("\nWhat would you like to do? \n");
		printf(" [%d] Exit\n", EXIT);
		printf(" [%d] Add new Frame\n", ADD);
		printf(" [%d] Remove a Frame\n", REMOVE);
		printf(" [%d] Change frame index\n", CHNG_IND);
		printf(" [%d] Change frame duration\n", CHNG_DUR);
		printf(" [%d] Change duration of all frames\n", CHNG_DUR_ALL);
		printf(" [%d] List frames\n", PRINT);
		printf(" [%d] Play movie!\n", PLAY);
		printf(" [%d] Save project\n", SAVE);
		scanf("%d", &ans);
		getchar(); //remove \n from buffer
		// check validity of user's answer
		valid = (ans >= EXIT && ans <= SAVE);
		if (!valid)
			printf("You should type one of the options - %d-%d!\n", EXIT, SAVE);
	}
	return ans;
}

/**
The main function
**/
int main(void)
{
	FrameNode* movie = NULL;
	int choice = 0;
	int index = 0;
	movie = openingMenu();
	do
	{
		choice = menu();
		switch (choice)
		{
		case ADD:
			addNewFrame(&movie);
			break;
		case REMOVE:
			removeFrame(&movie);
			break;
		case CHNG_IND:
			changeIndex(&movie);
			break;
		case CHNG_DUR:
			changeDurFrame(movie);
			break;
		case CHNG_DUR_ALL:
			changeAlldur(movie);
			break;
		case PRINT:
			listFrames(movie);
			break;
		case PLAY:
			play(movie);
			break;
		case SAVE:
			saveProject(movie);
			break;
		}
	} while (choice != EXIT);
	printf("\nBye!");
	deleteList(&movie);
	getchar();
	return 0;
}

/**
Save project to a file.
input: the movie to save.
output: none.
**/
void saveProject(FrameNode* list)
{
	char* path = (char*)malloc(MAX_PATH_SIZE);
	printf("Where to save the project? enter a full path and file name\n");
	myFgets(path, MAX_PATH_SIZE);
	FILE* fptr;
	if ((fptr = fopen(path, "wt")) == NULL)
		printf("Error! canot create file");
	else
	{
		while (list)
		{
			fprintf(fptr, "%s,%d,%s\n", list->frame->path, list->frame->duration, list->frame->name);
			list = list->next;
		}
		free(path);
		fclose(fptr);
	}
}

/**
Display the opening menu with 2 options: create a new project or load an existing one
input: none
output: the movie to edit
**/
FrameNode* openingMenu(void)
{
	int ans = 0;
	int validChoice = FALSE;
	FrameNode* movie = NULL;
	FILE* fptr = NULL;
	printf("Welcome to GIF Maker! what would you like to do? \n");
	while (!validChoice)
	{
		printf(" [%d] Create a new project\n", NEW_PROJECT);
		printf(" [%d] Load existing project\n", LOAD_PROJECT);
		scanf("%d", &ans);
		getchar(); //remove \n from buffer
		if (!(validChoice = (ans == NEW_PROJECT || ans == LOAD_PROJECT)))
			printf("Invalid choice, try again:\n");
	}
	if (ans == LOAD_PROJECT)
	{
		char* path = (char*)malloc(MAX_PATH_SIZE);
		printf("Enter the path of the project (including project name): \n");
		myFgets(path, MAX_PATH_SIZE);
		if ((fptr = fopen(path, "r")) == NULL)
			printf("Error!- cant open file, creating a new project");
		else
		{
			movie = readFromFile(fptr);
			free(path);
			fclose(fptr);
			printf("Project loaded successfully\n", path);
		}
	}
	else
		printf("Working on a new project.\n");
	return movie;
}


/**
Load and create all frames listed in the given file.
input: file to load project from.
output: a movie containing all the frames saved in the file.
**/
FrameNode* readFromFile(FILE* project)
{
	const size_t line_size = MAX_NAME_SIZE + MAX_PATH_SIZE + 5;
	char* line = (char*)malloc(line_size);
	FrameNode* movie = NULL;
	if (project == NULL)
		printf("Error: file pointer is null.");
	else
	{
		while (fgets(line, line_size, project) != NULL) /* read a line */
			lineToFrame(line, &movie);
		free(line);
	}
	return movie;
}

/**
This function parse the string into the frame details, creats a frame and add it to the movie
Input: a string with frame info and a movie pointer
output: none
**/
void lineToFrame(const char* line, FrameNode** list) 
{
	FrameNode* newLink;
	if (!(newLink = (FrameNode*)malloc(sizeof(FrameNode))))
		return;

	char path[MAX_PATH_SIZE];
	char name[MAX_NAME_SIZE];
	int duration = 0;

	// Parse the input line
	int tokensRead = sscanf(line, "%s %d %s", path, &duration, name);
	if (tokensRead != 3) 
	{
		free(newLink);
		return;
	}

	// Trim newline characters
	path[strcspn(path, "\n")] = '\0';
	name[strcspn(name, "\n")] = '\0';

	// Create the frame
	newLink->frame = createFrame(name, duration, path);
	newLink->next = NULL;

	// Add the frame to the end of the list
	if (*list == NULL) 
		*list = newLink;
	else {
		FrameNode* iterator = *list;
		while (iterator->next) 
			iterator = iterator->next;
		iterator->next = newLink;
	}
}

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
input: the buffer to read into, the number of chars to read
*/
void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}
