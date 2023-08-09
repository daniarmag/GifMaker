#ifndef LINKEDLISTH
#define LINKEDLISTH
#define _CRT_SECURE_NO_WARNINGS

#define MAX_PATH_SIZE 256
#define MAX_NAME_SIZE 50
#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int	duration;
	char* path;
} Frame;


// Frame functions
Frame* createFrame(char* name, unsigned int duration, char* path);
Frame* createNewFrame(void);
void deleteFrame(Frame* f);

// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;


// Link functions
FrameNode* removeAndReturn(FrameNode** list, char* name);
Frame* findFrame(FrameNode* list, char* name);
void addNewFrame(FrameNode** list);
void listFrames(FrameNode* frameList);
void removeFrame(FrameNode** frameList);
void changeIndex(FrameNode** frameList);
void changeDurFrame(FrameNode* frameList);
void changeAlldur(FrameNode* frameList);
void deleteList(FrameNode** list);

#endif
