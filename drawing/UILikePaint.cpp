#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int consoleW = 80, consoleH = 30; //The console sizes
const int sizeW = 8, sizeH = 12; //The each character's sizes

char character[consoleW][consoleH]; //The screen has characters as consoleW and consoleH

char paintingSymbol = 219;
char key; //To print the UI

void printUI();
//Cursor System
void theCursor(int x, int y, char command);
void zeroCharacter();
void drawFromTheFile();


int main()
{
	
	POINT p;
//	p = ::ScreenToClient(POINT->Handle, &p);
	HWND hWnd = GetConsoleWindow();
	
	//Zero the characters
	zeroCharacter();
	
while(1)
{
	
	
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	//printf("Position X is: %d", p.x);
	//printf("\tPosition Y is: %d\n", p.y);
	
	//mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
	
	//When the user press the mouse (or hold the button)
		//Draw
	if(GetAsyncKeyState(VK_LBUTTON))
	{
		
		//The user should press the mouse available interval
			//The boundeds are: for width => consoleWidth * characterSizeWidth, heigth => consoleHeight * characterSizeHeight
		if(p.x >= 0 && p.x <= (consoleW * sizeW) && p.y >= 0 && p.y <= ((consoleH-1) * sizeH))
		//if(p.x >= 0 && p.x <= 640 && p.y >= 0 && p.y <= 360)
		{
			//system("cls");
		
		//Get character position x and y
			//Round down
		float cx = ((p.x) / sizeW) - ((p.x % sizeW) / sizeW);
		float cy = ((p.y) / sizeH) - ((p.y % sizeH) / sizeH);
		int cx2 = (int) cx;
		int cy2 = (int) cy;
		//char c = character[cx2][cy2];
		
		//printf("The point is: X: %d Y: %d", cx2 ,cy2);
		theCursor(cx2, cy2, 'w');
		
   		//break;
		}
		
			
		//To save the project
		
		
		
 	}
 	//Erase
 	if(GetAsyncKeyState(VK_RBUTTON))
 	{
 				//The user should press the mouse available interval
			//The boundeds are: for width => consoleWidth * characterSizeWidth, heigth => consoleHeight * characterSizeHeight
		if(p.x >= 0 && p.x <= (consoleW * sizeW) && p.y >= 0 && p.y <= ((consoleH-1) * sizeH))
		//if(p.x >= 0 && p.x <= 640 && p.y >= 0 && p.y <= 360)
		{
			//system("cls");
		
		//Get character position x and y
			//Round down
		float cx = ((p.x) / sizeW) - ((p.x % sizeW) / sizeW);
		float cy = ((p.y) / sizeH) - ((p.y % sizeH) / sizeH);
		int cx2 = (int) cx;
		int cy2 = (int) cy;
		//char c = character[cx2][cy2];
		
		//printf("The point is: X: %d Y: %d", cx2 ,cy2);
		theCursor(cx2, cy2, 'e');
		
   		//break;
		}
		//To save the project
	}
	
	//Keyboard operations
	if(kbhit())
	{
		key = getch();
		
		//Clean
		if(key == 'c' || key == 'C')
		{
			system("cls");
		}
		
		//Print
		if(key == 'p' || key == 'P')
		{
			printUI();
		}
		
		//Draw file
		if(key == 'S' || key == 's')
		{
			drawFromTheFile();
		}
		
	}
	
	
 	
}
	
//	printf("Oldu");
//	break;
	
}
		//FUNCTIONS
		
void zeroCharacter()
{
	
	for(int i = 0; i < consoleW; i++)
	{
		for(int j= 0; j < consoleH; j++)
		{
			character[i][j] = ' ';
		}
	}
}


//Cursor System
void theCursor(int x, int y, char command)
{
	COORD cor;
	//Assign the coordinate
	cor.X = x;
	cor.Y = y;
	
	//Write or erase
	if(command == 'w')
	{
		//Set the cursor
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
		//Change the character
		character[x][y] = paintingSymbol;
		printf("%c", paintingSymbol);
		//printf("Coordinates are X: %d Y: %d", x, y);	
	}
	else if(command == 'e')
	{
		//Set the cursor
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
		//Change the character
		character[x][y] = ' ';
		printf("%c", ' ');
		//printf("Coordinates are X: %d Y: %d", x, y);	
	}

}

void drawFromTheFile()
{
	FILE *fileOperation;
	fileOperation = fopen("drawingUI.txt", "r");
	
	char allCharacters[consoleW * consoleH];
	
	while(fgets(allCharacters, consoleW * consoleH, fileOperation) != NULL)
	{
	
	}
	
	fclose(fileOperation);
	
	for(int y = 0 ; y < 30; y++)
	{
		for(int x = 0 ; x < 80; x++)
		{
			character[x][y] = allCharacters[(y*80) + x];
		}
	}
	
	system("cls");
	
	//Draw
	
	for(int j = 0; j < 30; j++)
	{
		for(int i = 0; i < 80; i++)
		{
			printf("%c", character[i][j]);
		}
	}
	
}


void cleanAndDraw()
{
	system("cls");
	
	for(int i = 0; i < consoleW; i++)
	{
		for(int j = 0; j < consoleH; j++)
		{
			printf("%c", character[i][j]);
		}
	}
}

void printUI()
{
	FILE *fileOperation;	
	fileOperation = fopen("mainMenuUI.txt", "w");
	
	/*Note: There is a very important point. The file is written from left to right. Not from up to bottom
	Hence, we start to write horizontal lines (x) then we get botton line (y)
	We can operate the character[x][y] without appliying this rule. But, if we would like the notepad to show
	the image correctly, we should apply that
	*/
	
	for(int j = 0; j < consoleH; j++)
	{
		for(int i = 0; i < consoleW; i++)
		{
			fprintf(fileOperation, "%c", character[i][j]);
		}
	}
	
	//fprintf(fileOperation, "%s", "Deneme!!!");
	
	fclose(fileOperation);
//	cleanAndDraw();
	
}





