#ifndef EDIT_PROJECT_H
#define EDIT_PROJECT_H
#define _CRT_SECURE_NO_WARNINGS

#include "LinkedList.h"
#include "view.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DELIMETER ","

enum menuChoices
{
	NEW_PROJECT = 0,
	LOAD_PROJECT
};

enum movieChoices
{
	EXIT = 0,
	ADD,
	REMOVE,
	CHNG_IND,
	CHNG_DUR,
	CHNG_DUR_ALL,
	PRINT,
	PLAY,
	SAVE
};

void playIndex(FrameNode* list);
int menu(void);
int main(void);
void saveProject(FrameNode* list);
FrameNode* openingMenu(void);
FrameNode* readFromFile(FILE* project);
void lineToFrame(char* line, FrameNode** list);
void myFgets(char str[], int n);



#endif  //EDIT_PROJECT_H