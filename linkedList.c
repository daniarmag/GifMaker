#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
Creates a new frame with the given details.
input: name of frame, its duration and path.
output: the new frame.
**/
Frame* createFrame(char* name, unsigned int duration, char* path)
{
	Frame* f = (Frame*)malloc(sizeof(Frame));
	if (f)
	{
		f->name = name;
		f->duration = duration;
		f->path = path;
	}

	return f;
}


/**
Get user details for a frame, and create it.
input: none.
output: a new frame.
**/
Frame* createNewFrame(void)
{
	char* path = (char*)malloc(MAX_PATH_SIZE);
	char* name = (char*)malloc(MAX_NAME_SIZE);
	unsigned int duration = 0;
	printf("*** Creating new frame ***\n");

	// Get file path:
	printf("Please insert frame path:\n");
	myFgets(path, MAX_PATH_SIZE);

	// Get frame duration:
	printf("Please insert frame duration(in miliseconds):\n");
	scanf("%d", &duration);
	getchar();// clear stdin

	// Get frame name:
	printf("Please choose a name for that frame:\n");
	myFgets(name, MAX_NAME_SIZE);

	return createFrame(name, duration, path);
}


/**
Delete a frame and free the memory of the frame, name and path.
input: frame to delete.
output: none
**/
void deleteFrame(Frame* f)
{
	if (f)
	{
		if (f->path)
		{
			free(f->path);
		}
		if (f->name)
		{
			free(f->name);
		}
		free(f);
	}
}


/**
Adds a new frame to the end of given list according to details given by user.
input: the list to add the frame to.
output: none
**/
void addNewFrame(FrameNode** list)
{
	FrameNode* newLink = (FrameNode*)malloc(sizeof(FrameNode));
	Frame* frame1 = createNewFrame();
	FrameNode* iterator = NULL;
	FILE* pic = fopen(frame1->path, "r");

	if (!pic)
	{
		printf("Can't find file! Frame will not be added\n");
		deleteFrame(frame1);
		free(newLink);
	}
	else
	{
		fclose(pic);
	}

	if (pic) // file is OK - add the frame to the movie
	{
		//check that the name is not taken
		while (findFrame(*list, frame1->name))
		{
			printf("The name is already taken, please enter another name\n");
			myFgets(frame1->name, MAX_NAME_SIZE);
		}
		newLink->frame = frame1;
		newLink->next = NULL;

		if (!(*list)) // empty list
		{
			*list = newLink;
		}
		else
		{
			iterator = *list;
			while (iterator->next)
			{
				iterator = iterator->next;
			}
			iterator->next = newLink;
		}
	}
}


/**
This function removes a frame from the list.
It asks the user for the name of the frame, and if exists it removes it.
input: the list
output: none
**/
void removeFrame(FrameNode** frameList)
{
	FrameNode* toErase = NULL;
	printf("Enter the name of the frame you wish to erase\n");
	char* name = (char*)malloc(MAX_NAME_SIZE);
	myFgets(name, MAX_NAME_SIZE);

	toErase = removeAndReturn(frameList, name);
	if (!toErase)
	{
		printf("The frame was not found\n");
	}
	else
	{
		deleteList(&toErase); // only the removed node will be deleted from the memory
	}
	free(name);
}

/**
Change the index of a frame in the list.
Ask the user to enter a frame name and an index and if both are legal,
move the frame to that index in the movie.
input: the list.
output: none
**/
void changeIndex(FrameNode** frameList)
{
	int i = 0;
	char* name = (char*)malloc(MAX_NAME_SIZE);
	int index = 0;
	FrameNode* iter = NULL;
	FrameNode* link = NULL;

	//boolean var to indicate that the index is in the list
	int badIndex = TRUE;
	printf("Enter the name of the frame\n");
	myFgets(name, MAX_NAME_SIZE);

	//get the requested link if exists
	link = removeAndReturn(frameList, name);
	if (!link)
	{
		printf("this frame does not exist\n");
	}
	else
	{
		iter = *frameList;
		do
		{
			printf("Enter the new index in the movie you wish to place the frame\n");
			scanf("%d", &index);
			getchar(); //remove \n from buffer

			//if this is the first frame- add it at the begining
			if (index == 1)
			{
				link->next = iter;
				*frameList = link;
				//the index is good
				badIndex = FALSE;
			}
			else
			{
				//go to the link previous to the new place 
				for (i = 0; i < index - 2 && iter; i++)
				{
					iter = iter->next;
				}
				if (iter)
				{
					link->next = iter->next;
					iter->next = link;
					//the index is good
					badIndex = FALSE;
				}
				else
				{
					printf("The movie contains only %d frames!\n", i + 1);
				}
			}//else
		}//doWhile
		while (badIndex);
	}//else
	free(name);
}//function



/**
Change the duration of a frame.
Ask the user for a frame name and if exists change the duration.
input: the list
output: none
**/
void changeDurFrame(FrameNode* frameList)
{
	char* name = (char*)malloc(MAX_PATH_SIZE);
	int duration = 0;
	printf("enter the name of the frame\n");
	myFgets(name, MAX_NAME_SIZE);

	Frame* frame = findFrame(frameList, name);
	if (!frame)
	{
		printf("The frame does not exist\n");
	}
	else
	{
		printf("Enter the new duration\n");
		scanf("%d", &duration);
		getchar(); //remove \n from buffer

		frame->duration = duration;
	}
	free(name);
}


/**
Change the duration of all frames to a new value entered by the user
input: the list
output: none
**/
void changeAlldur(FrameNode* frameList)
{
	FrameNode* iter = frameList;
	int dur = 0;
	printf("Enter the duration for all frames: \n");
	scanf("%d", &dur);
	getchar(); //remove \n from buffer

	while (iter)
	{
		iter->frame->duration = dur;
		iter = iter->next;
	}
}

/**
A recursive function that prints the informatin of all the frames in the list.
input: the list.
output: none
**/
void printRecursive(FrameNode* frameList)
{
	if (frameList)
	{
		Frame* fp = frameList->frame;
		printf("\t\t%s\t\t%u ms\t\t%s\n", fp->name, fp->duration, fp->path);
		printRecursive(frameList->next);
	}
}

/**
prints the information of all the frames in the list
uses the recursive function printRecursive
input: the list to print.
output: none
**/
void listFrames(FrameNode* frameList)
{
	printf("\t\tName\t\tDuration\tPath\n");
	printRecursive(frameList);
	printf("\n\n");
}

/**
Find if a frame is in the list and return it.
input: the list and frame name to search
output: the frame or NULL if it doesn't exist
**/
Frame* findFrame(FrameNode* frameList, char* name)
{
	int found = FALSE;
	Frame* frame = NULL;
	while (!found && frameList)
	{
		if (strcmp(frameList->frame->name, name) == 0)
		{
			found = TRUE;
			frame = frameList->frame;
		}
		frameList = frameList->next;
	}
	return frame;
}


/**
Delete the list and free all the memory.
input: the list to delete
output: none
**/
void deleteList(FrameNode** list)
{
	FrameNode* iter = *list;
	FrameNode* toDelete = NULL;
	while (iter)
	{
		toDelete = iter;
		iter = iter->next;
		deleteFrame(toDelete->frame);
		free(toDelete);
	}
	*list = NULL;
}

/**
Remove the link with a frame name "name" frome the movie and return it.
input: frame list and name to remove
output: the removed frame or null if it doesn't exist.
**/
FrameNode* removeAndReturn(FrameNode** list, char* name)
{
	int found = 0;
	FrameNode* iter = *list;
	FrameNode* ans = NULL;
	if (!iter)
	{
		// empty list
		// we will return NULL
	}
	//in case its the first link
	else if (strcmp(iter->frame->name, name) == 0)
	{
		ans = iter;
		*list = iter->next;
		ans->next = NULL;
	}
	else
	{
		while (!found && iter->next)
		{
			if (strcmp(name, iter->next->frame->name) == 0)
			{
				ans = iter->next;
				iter->next = iter->next->next;
				ans->next = NULL;
				found = 1;
			}
			else
			{
				iter = iter->next;
			}
		}
	}
	return ans;
}