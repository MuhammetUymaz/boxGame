#include <iostream>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include <conio.h>
#include <windef.h>
#include <wincon.h>

using namespace std;

//Screen Informations
int axisX = 80, axisY = 30;
int followingX = 0, followingY = 0; //They are about movement of the camera
int followingXVersion1 = 0, followingYVersion1 = 0;
bool isGameHasBeenPlayed = false; //When we play game again, we will not see the the UI two times

	//For input
//Controller
char key;
bool isPaused = false;

	//For Random System
int pressedTime = 0;

//int gSpeed = 0;
float mSideSpeed = 0;
float difficulityAcceleration = 1;
//Score
int score = 0;
int gettingScoreMusic = 1000;

//Declaring the functions to use them later
struct Image;
void randomLocation(Image* shape, int xResolution, int yResolution, int beginPointX, int beginPointY);
void Debug(char sentence[100]);
void Debug(int number);
void cursor(int x, int y, char character);
void GameOver();
void intro();
int main();

void drawFromTheFile()
{
	FILE *fileOperation;
	fileOperation = fopen("mainMenuUI.txt", "r");

	char allCharacters[30 * 80];

	while(fgets(allCharacters, 30 * 80, fileOperation) != NULL)
	{

	}

	fclose(fileOperation);

	/*
	for(int y = 0 ; y < 30; y++)
	{
		for(int x = 0 ; x < 80; x++)
		{
			character[x][y] = allCharacters[(y*80) + x];
		}
	}*/

	system("cls");

	//Draw

	for(int i = 0; i < 30*80; i++)
	{
		printf("%c", allCharacters[i]);
	}

	POINT p;
	HWND hWnd = GetConsoleWindow();

	while(1)
	{
		GetCursorPos(&p); //Get the cursor position
		//Set the position for "our console's position".
			//That's important to be able to make our application "portable" when we use mouse inputs
		ScreenToClient(hWnd, &p);

		//Press or hold left button (Actually when we hold press button, it means we press it also. But more frequently)
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			/* TO FIND WHERE THE MOUSE IS
				Beep(500, 250);
				COORD cor;
				cor.X = 0;
				cor.Y = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
				printf("PosX: %li PosY: %li", p.x, p.y);
				//printf("X: %li", p.x); //p.x is in long int kind
				//return;
			*/
			 //Note: Each character has 8 width, 12 height
			//PLAY BUTTON
			if(p.x >= 24 * 8 && p.x <= 53 * 8 && p.y >= 1 * 12 && p.y <= 12 * 12)
			{
				Beep(183*2.5, 250);
				Beep(208*2.5, 250);
				Beep(183*2.5, 250);
				Beep(208*2.5, 250);
				Beep(183*2.5, 500);
				return;
			}

			//QUIT BUTTON
			else if(p.x >= 24 * 8 && p.x <= 53* 8 && p.y >= 15 * 12 && p.y <= 26 * 12)
			{
				Beep(222*2.5, 150);
				Beep(222*2.5, 150);
				exit(0);
			}

		}
	}

	/*
	for(int j = 0; j < 30; j++)
	{
		for(int i = 0; i < 80; i++)
		{
			printf("%c", character[i][j]);
		}
	}
	*/

}

//Cursor System
void Cursor(int x, int y, char character)
{
	COORD cor;
	//Assign the coordinate
	cor.X = x;
	cor.Y = y;
	//Set the cursor
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
	printf("%c", character);
}

//UI For Main Menu
void mainMenuUI()
{
	//We set the screen as 80x25
	char UI[80][25];

	for(int x = 0; x < 25; x++)
	{
		//for(y)
	}

	for(int i = 0; i < 25; i++)
	{
		for(int j= 0; j < 80; j++)
		{
			printf("%c", UI[i][j]);
		}
	}
}

class Map{

	public:
	char level1[800][25];
	char backLevel[800][25];
		void Level1() //Printing level (for beginning)
		{
			for(int i = 0; i < 25; i++)
			{
				for(int j = 0; j < 800; j++)
				{
					level1[j][i] = ' ';
				}
			}
		}

		void BackLevel()
		{
			for(int i = 0; i < 25; i++)
			{
				for(int j = 0; j < 800; j++)
				{
					backLevel[j][i] = ' ';
				}
			}
		}


		void level1_UpdateScreen()
		{
			system("cls");

			for(int i = 0; i < 25; i++)
			{
				for(int j = 0; j < 800; j++)
				{
					cout << level1[j][i];
				}
			}
		}

};


//Current Level (This is the common level for object, obstacles, "Debug System" etc)
Map currentLevel;

struct Vector{
	int x;
	int y;

	//To define the what the vector is. We assign x and y of the "Vector" by this way WHEN we make a new "Vector" struct
	Vector(int posX, int posY)
	{
		x = posX;
		y = posY;
	}

};

struct xyPlane{

	int x;
	int y;
};

class Image{ //We write a special function so we use class instead of struct

public:
	char shape[100]; //100 the max pixels that image can get
	struct xyPlane shapeCor[100]; //Each pixel has got coordinate on XY plane. DONT FORGET THAT EVERY PIXEL HAS DIFFERENT COORDINATE
								 //So we wrote [100] on shapeCor
	int degree[100]; //Each pixel has their own degree
					 //Center of mass (image) has -1 degree. We don't turn that

	//Resolution to understand how many pixels the image is using
	int resolutionX = 0;
	int resolutionY = 0;

	//For animation
	int animationPiece = 0; //That's animation order
	char tempChar = shape[0];
	char temp2Char = 'L';
	int animationSpeed = 0;

	void animation()
	{
		if(animationSpeed >= 0)
		{


		//We write "-2" instead of "-1" because we don't turn center of mass
		for(int i = animationPiece; i < 8; i++)
		{
				if(degree[i] != -1) //If it isn't center of mass
				{
					int theDegree = ((i+1) * 45) % 360;
					//degree[i] = (degree[i] + 45) % 360;

					if(tempChar != 'L')
					{

						temp2Char = *findPieceWithDegree(theDegree);
						//printf("Shape is: %c", temp2Char);
						*findPieceWithDegree(theDegree) = tempChar;
						tempChar = 'L';
					}
					else if(temp2Char != 'L')
					{
						//printf("tempChar is: %c", tempChar);
						printf("Finding is: %c", *findPieceWithDegree(theDegree));


						tempChar = *findPieceWithDegree(theDegree);
						*findPieceWithDegree(theDegree) = temp2Char;
						temp2Char = 'L';
					}

				}
				//animationPiece++;
		}

				//Initail animation
				//animationPiece = 0;
				//animationSpeed = 0;

		}
		else
		{
			animationSpeed++;
			animation();
		}


	}


	char *findPieceWithDegree(int targetDegree)
	{
		for(int i = 0; i < (resolutionX * resolutionY) -1; i++)
		{
			if(degree[i] == targetDegree)
			{
				char *piece = &shape[i];


				return piece;

				break; //Maybe "break" is useless, because we've written "return"
			}
		}
	}



};

class Object{

	//Force components

	public:

	int f; //Force
	int m; //Mass
	int a; //Acceleration

	bool isConstant = true; //The object can be fallen or not
	int gSpeed = 0;
	int forcingSpeed = 0;

	//Path
	int vi; //Velocity initial
	int vf; //Velocity final
	int t; //Time
	int xi; //Path initial
	int xf; //Path final

	//Energy
	double ke;
	double pe;

	//Name
	string name;

	//Coordinate
	int cx = 0; //X-Axis
	int cy = 0; //Y-Axis
		//When the player exceeds the boundeds of the camera's resolution
	int cameraDirectionX;
	int cameraDirectionY;

	//For priting in the level
	Map *theLevel; //We dont make a new Map. We use the "map of the level". That's common map

	//For the shape
	Image theShape;

	//For the movement of npc, player etc
	bool isPlayer;

	//The player collides with the ground
	bool isFallen;

	/*Every object has a PRIVATE symbol for the background of the game (theLevel)
	We draw this shape on the level.
	When we check the collision, we check the "symbol"'s left or right has got ANOTHER PRIVATE SYMBOL (it means the collision)
	or it can be Space it means space of the Level
	*/

	char collisionSymbol;

	public:
		//Finding force
	 double force(int mass, int acceleration)
	{
		double force;
		force = mass * a;

		f = force;
		m = mass;
		a = acceleration;

		return force;
	}

		//Finding mass
	 double Mass(int force, int acceleration)
	{
		double mass;
		mass = force / a;


		f = force;
		m = mass;
		a = acceleration;

		return mass;

	}

		//Finding acceleration
	double Acceleration(int force, int mass)
	{
		double ac;

		ac = force / mass;

		f = force;
		m = mass;
		a = ac;

		return ac;
	}

		//Finding xf
		//xf = xi + Vi * t + ((1/ 2) * a * t^2)
	double xfinal(int xinitial, int vinitial, int time, int ac)
	{
		double result;
		result = xinitial + (vinitial * time) + (0.5 * ac * time* time);

		xf = result;
		xi = xinitial;
		vi = vinitial;
		t = time;
		ac = a;

		return result;
	}

		//Work

		//Finding KE
		//KE = (1/2) * m * v^2
	double KE(int vinitial)
	{
		double result;
		result = 0.5 * m * vinitial * vinitial;

		ke = result;

		vi = vinitial;

		return result;
	}

		//Finding PE
		//PE = m * g * h
	double PE(double h)
	{
		double result;
		result = m * 9.8 * h;

		pe = result;

		return result;
	}

		//Gravity Force
	void gravity()
	{
		gSpeed += m; //Mass is right proportion with gravitational acceleration
		if(gSpeed > 10000 && !isFallen) //When the player hasn't fallen
		{

			move(Vector(1,1));

			gSpeed = 0; //Zero it
		}

	}


			//Add Forcing
	void addForce(Vector *v)
	{
		forcingSpeed += m; //Mass is right proportion with gravitational acceleration
		if(forcingSpeed > 7000 && !isFallen) //When the player hasn't fallen
		{

			move(*v);


				v->y += 1;



			forcingSpeed = 0; //Zero it
		}

	}



		//Movement
	void move(struct Vector v)
	{
		//Previous Controls

				//***Obstacles
		//Control that if the object is obstacles etc and has exceeded the boundeds
		if(!isPlayer && theShape.shapeCor[0].x + v.x <= 0)
		{
			//Removing the shape
				for(int i = 0; i < theShape.resolutionY * theShape.resolutionX; i++)
				{
				//We use "->" instead of dot "." for the pointer in class
			theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y] = ' ';
	     	Cursor(theShape.shapeCor[i].x, theShape.shapeCor[i].y, ' ');


				}

		    //We've gotten score
			score++;
			Beep(gettingScoreMusic, 25);
			Debug(score);
			//cout << "\a";
			gettingScoreMusic += 100;

			difficulityAcceleration += 0.1f;

			//Get the random location
			randomLocation(&theShape, theShape.resolutionX, theShape.resolutionY, 40, 14);
			return;
		}


		//Deleting Signs
		for(int i = 0; i < theShape.resolutionY * theShape.resolutionX; i++)
		{


				//We use "->" instead of dot "." for the pointer in class
				//theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y] = ' ';
				theLevel->level1[theShape.shapeCor[i].x % axisX][theShape.shapeCor[i].y % axisY] = ' ';


				theLevel->backLevel[theShape.shapeCor[i].x][theShape.shapeCor[i].y] = ' ';

				/*Actually the resolutions of the screen is determined. So we need to use
				this resolutions for our screen. For example 80x30. We need to use this resolution
				where the player is going even player is in 300,500 point
					So we use "Modular" operation
				*/
				Cursor(theShape.shapeCor[i].x % axisX, theShape.shapeCor[i].y % axisY, ' ');

			//	Cursor(theShape.shapeCor[i].x /*- followingXVersion1*/, theShape.shapeCor[i].y /*- followingYVersion1*/, ' ');
		}




	/*WE HAVE ALREADY CONSIDER PIXELS' COORDINATES. SO ENTERING TOTAL PIXEL IS ENOUGH FOR US

	resoX * resoY = Total Pixels
	*/

	//For Moving Fluently
	/*
	int horizontal = v.x, vertical = v.y, tour;
	if(horizontal > vertical)
	{
		tour = horizontal;
	}
	else
	{
		tour = vertical;
	}
	*/

//	for(tour; tour > 0; tour--)
	//{

				for(int i = 0; i < theShape.resolutionY * theShape.resolutionX; i++)
			{
				//We dont use Center of Mass To Move the character. But we can do that, as well

					//Assign their new coodinates
					theShape.shapeCor[i].x += v.x;
					theShape.shapeCor[i].y += v.y;

				//For Moving Fluently
			/*	if(horizontal > 0)
				{
					theShape.shapeCor[i].x += 1;

				}
				if(vertical > 0)
				{
					theShape.shapeCor[i].y += 1;

				}*/


					//Write - For Collision
				//theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y] = collisionSymbol;
		    	theLevel->level1[theShape.shapeCor[i].x % axisX][theShape.shapeCor[i].y % axisY] = collisionSymbol;

					//Write - Background
				theLevel->backLevel[theShape.shapeCor[i].x][theShape.shapeCor[i].y] = theShape.shape[i];

					//Write - Render
					Cursor(theShape.shapeCor[i].x % axisX, theShape.shapeCor[i].y % axisY, theShape.shape[i]);

				//	Cursor(theShape.shapeCor[i].x /*- followingXVersion1*/, theShape.shapeCor[i].y /*- followingYVersion1*/, theShape.shape[i]);
			}

			//For Moving Fluently
			/*
			if(horizontal > 0)
			{
				horizontal--;
			}
			if(vertical > 0)
			{
			vertical--;
			}
			*/

	//}




	//	level1.level1[cx][cy] = 'X';

		//Update screen (that's temporary)
	//	theLevel->level1_UpdateScreen();

		/*
		followingXVersion1 = followingX;
		followingYVersion1 = followingY;*/

		//**Player
		//Collisions with screen boundeds
		if(isPlayer && (theShape.shapeCor[theShape.resolutionY-1].y >= axisY-7 || theShape.shapeCor[theShape.resolutionY-1].y <= 0 || theShape.shapeCor[theShape.resolutionX-1].x >= axisX-1 || theShape.shapeCor[theShape.resolutionX-1].x <= 2))
		{
			isFallen = true; //Stop the player
			Beep(210 * 2.5, 200);
		    Beep(196 * 2.5, 200);
		    Beep(183 * 2.5, 200);
			Beep(176 * 2.5, 200);
			GameOver();
			isPaused = true;

		}

		//**Collision Detection (For Player)

		collisionDetection();


		//WHEN THE PLAYER EXCEEDS THE SIDE BOUNDED (+X ALONG), THE CAMERA WILL MOVE
		if(isPlayer && theShape.shapeCor[theShape.resolutionX].x + v.x >= 30 &&
	   	   isPlayer && theShape.shapeCor[theShape.resolutionX].x + v.x <= 32)
		{

		//	cameraMove(cameraDirectionX, 0);
		}


	}

		//Movement (constantly)
	void moveConstantly(struct Vector v, int time)
	{
		while(time)
		{
			cx += v.x;
			cy += v.y;

			cout << "\nThe character is at: " << cx << ',' << cy;

			time--;
		}
	}


	//**Detection For Collision
	void collisionDetection()
	{
		//We check right, left, up and bottom of each pixel of shape of the object
		//From Right, Left, Up and Bottom. But WE MUST CONSIDER AFTER 1 PIXEL. SO WE ADD/SUBSTRACT 1
		for(int i = 0; i < theShape.resolutionY * theShape.resolutionX; i++)
		{


			if(
					//Right
					(theShape.shapeCor[i].x+1 != axisX && theLevel->level1[theShape.shapeCor[i].x+1][theShape.shapeCor[i].y] != collisionSymbol && theLevel->level1[theShape.shapeCor[i].x+1][theShape.shapeCor[i].y] != ' ')
					||
					//Left
					(theShape.shapeCor[i].x-1 > 0 && theLevel->level1[theShape.shapeCor[i].x-1][theShape.shapeCor[i].y] != collisionSymbol && theLevel->level1[theShape.shapeCor[i].x-1][theShape.shapeCor[i].y] != ' ')
					||
					//Up
					(theShape.shapeCor[i].y-1 != axisY && theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y-1] != collisionSymbol && theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y-1] != ' ')
					||
					//Bottom
					(theShape.shapeCor[i].y+1  > 0 && theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y+1] != collisionSymbol && theLevel->level1[theShape.shapeCor[i].x][theShape.shapeCor[i].y+1] != ' ')
			  )
			{
					 isPaused = true;
					 //Beep(210 * 2.5, 500);

					 //Sound Effect -  Game Over
					 Beep(210 * 2.5, 200);
					 Beep(196 * 2.5, 200);
					 Beep(183 * 2.5, 200);
					 Beep(176 * 2.5, 200);
					 //Beep(176 * 2.5, 500);
					 GameOver();
					 break;
			}

		}

	}

	void cameraMove(int increaseX, int increaseY)
	{
		if(cameraDirectionX > 0)
		{
			Debug("Move to Right");
		}
		else
		{
			Debug("Move to Left");
		}

	/*	for(int j = 0; j < axisY; j++)
		{

			for(int i = 0; i < axisX-1; i++)
			{
				theLevel->backLevel[i][j] = theLevel->backLevel[i+1][j];
				Cursor(i, j, theLevel->backLevel[i][j]);
			}
		}*/

		followingX += increaseX;
		followingY += increaseY;

	}


};

//Debug System
void Debug(char sentence[100])
{
	int order = 0;
	while(sentence[order] != 0)
	{

     //(A) 	currentLevel.level1[order][yAxis] = sentence[order];

	  Cursor(order, axisY-3, sentence[order]);

	order++;
	}

	//Clean the remain words
	for(order; order <80; order++)
	{
		Cursor(order, axisY-3, ' ');
	}

}

void Debug(int number)
{
		int tempNumber = 0, modTimer = 10, digitNumber = 1;

		while(tempNumber != number)
		{
			tempNumber = number % modTimer;

			modTimer *= 10;
			digitNumber++;
		}

		digitNumber--; //Finding digit
		modTimer /= 10; //Finding mod timer

		char digits[digitNumber]; //To save the digits
		int digitOrder = 0;

		while(modTimer >= 10)
		{
			//Eg: modTimer: 1000=> Number: 123 => 123 - 23 => 100
			int theDigitValue = (number % modTimer) - (number % (modTimer / 10));

			//So: 100 ==> 100 / (1000/10) => 100 / 100 => 1
			theDigitValue = theDigitValue / (modTimer / 10);

			//Save the value
				//48: To find get char value of the digit
			digits[digitOrder] = theDigitValue + 48;
			digitOrder++;


			modTimer /= 10;
		}

		//Debug(digits);
		 //To write
		 	int order = 0;
			while(digits[order] != 0)
			{

		     //(A) 	currentLevel.level1[order][yAxis] = sentence[order];

			  Cursor(order+70, axisY-3, digits[order]);

			order++;
			}

			//Clean the remain words
			for(; order+70 <80; order++)
			{
				Cursor(order+70, axisY-3, ' ');
			}

}

void GameOver()
{
    Debug("Game Over - Press Enter To Play Again");

    isGameHasBeenPlayed = true;

    char key = getch();
    if(key == 13)
    {
        Debug("Interesting!");
        //Zeroing
        followingX = 0;
        followingY = 0; //They are about movement of the camera
        followingXVersion1 = 0;
        followingYVersion1 = 0;
        key;
        isPaused = false;
        pressedTime = 0;
        mSideSpeed = 0;
        difficulityAcceleration = 1;
        score = 100;
        gettingScoreMusic = 1000;

        //Play again
        main();
    }
}

/*For the obstacle. We assign random location for obstacles. Also if the obstacles exceed the boundeds, they will
taken the screen
*/
void randomLocation(Image* shape, int xResolution, int yResolution, int beginPointX, int beginPointY)
{


	int pixelOrder = 0; //We must give an initial value IF we use it

	int random[5];
	//For random
	//int x = random[(random[random[6]] * random[random[13]] ) % random[random[14]]];

	int x;

	if(pressedTime == 0)
	{
	x = random[(random[random[8]] * random[13] ) % random[14]] % 80;
	beginPointX = x % 10;
	}
	else
	{
		beginPointX = (pressedTime * pressedTime*pressedTime + 845123) % 80;
	}

	if((pressedTime + (shape->shapeCor[0].x * shape->shapeCor[0].y)) % 2 == 0)
	{
		beginPointY = 14;
	}
	else{
		beginPointY = 0;
	}



	//0: From Up, 1: From Bottom


		for(int j = 0; j < yResolution; j++)
			{
				for(int i = 0; i < xResolution; i++)
				{

					//shape = new Image; //We can assign the a struct which we make a "new"

					//shape->shapeCor[pixelOrder].x = beginPointX + i;
					shape->shapeCor[pixelOrder].x = 80 + i;
					shape->shapeCor[pixelOrder].y = beginPointY + j;
					pixelOrder++;
				}
			}
}




//THE INTRODUCTION
void intro()
{
	char sampleString[2001];
	FILE *ftext;
	ftext = fopen("sampleUIMenu.txt", "r");

	//The UI
	Map UI;


	fgets(sampleString, 20001, ftext); //To save char
	/*while(i < 4)
	{
		//cout << sampleString[i];
		cout << sampleString[i];
		i++;
	}*/

	int letter = 0;
	for(int j = 0; j < 25; j++)
	{
		for(int i = 0; i < 80; i++)
		{
			UI.level1[i][j] = sampleString[letter];
			letter++;
		}
	}

	UI.level1_UpdateScreen();



	key = getch();
	if(key == 13)
	{
		return;
	}
	fclose(ftext);
	/*
	else{
		intro();
	}*/
}



int main()
{
    //For UI
    if(!isGameHasBeenPlayed)	drawFromTheFile();

	//For debuggins' linesd
	for(int a = 0; a < 15; a++)
	{
		Cursor(a, axisY-4, '-');
	}

	//Clean the screen
	system("cls");

	//Starting Game
	Debug("Game Started");

	//Debug(123);

	//Screen Color
	system("COLOR 76"); //3f

	/*Initial components
	Map, Object, Vector for movement of the Object

	*/



	Map myLevel1; myLevel1.Level1(); myLevel1.BackLevel(); //Assign the initial values of "Level 1"

	currentLevel = myLevel1;

	Object go; go.m = 7; go.f = 20; go.a = 4; go.theLevel = &currentLevel; //Assign the initial values of the "go"
	go.name = "Player";
	go.isPlayer = true;

	go.isConstant = false;

	go.collisionSymbol = 'A';

	//Moving vector of the player
	Vector projectile = Vector(4,0);


	Image myShape;
	{

	//Resolution
	myShape.resolutionX = 3;
	myShape.resolutionY = 3;

	//The shape's pieces
	/*myShape.shape[0] = '0';
	myShape.shape[1] = '1';
	myShape.shape[2] = '2';
	myShape.shape[3] = '3';
	myShape.shape[4] = '4';
	myShape.shape[5] = '5';
	myShape.shape[6] = '6';
	myShape.shape[7] = '7';
	myShape.shape[8] = '8';*/
	myShape.shape[0] = 254;
	myShape.shape[1] = 254;
	myShape.shape[2] = 254;
	myShape.shape[3] = 254;
	myShape.shape[4] = 254;
	myShape.shape[5] = 254;
	myShape.shape[6] = 254;
	myShape.shape[7] = 254;
	myShape.shape[8] = 254;

	//Their degrees
	myShape.degree[0] = 0;
	myShape.degree[1] = 45;
	myShape.degree[2] = 90;
	myShape.degree[3] = 315;
	myShape.degree[4] = -1; //That's center
	myShape.degree[5] = 135;
	myShape.degree[6] = 270;
	myShape.degree[7] = 225;
	myShape.degree[8] = 180;

	//Coordinates
	myShape.shapeCor[0].x = 3; myShape.shapeCor[0].y = 3;
	myShape.shapeCor[1].x = 4; myShape.shapeCor[1].y = 3;
	myShape.shapeCor[2].x = 5; myShape.shapeCor[2].y = 3;
	myShape.shapeCor[3].x = 3; myShape.shapeCor[3].y = 4;
	myShape.shapeCor[4].x = 4; myShape.shapeCor[4].y = 4;
	myShape.shapeCor[5].x = 5; myShape.shapeCor[5].y = 4;
	myShape.shapeCor[6].x = 3; myShape.shapeCor[6].y = 5;
	myShape.shapeCor[7].x = 4; myShape.shapeCor[7].y = 5;
	myShape.shapeCor[8].x = 5; myShape.shapeCor[8].y = 5;
	}


	//Assign
	go.theShape = myShape;

	//For obstacles
	Object obs[3]; obs[0].m = 20; obs[0].a = 0; obs[0].f = 0; obs[0].theLevel = &currentLevel;
	obs[0].isPlayer = false;
	obs[0].name = "Obstacle";
	obs[0].collisionSymbol = 'B';
	Image obShape[3];

	{
		obShape[0].resolutionX = 2;
		obShape[0].resolutionY = 12;

		//Shape
		obShape[0].shape[0] = 'O'; obShape[0].shape[1] = 'O'; obShape[0].shape[2] = 'O'; obShape[0].shape[3] = 'O';
		obShape[0].shape[4] = 'O'; obShape[0].shape[5] = 'O';
		obShape[0].shape[6] = 'O'; obShape[0].shape[7] = 'O'; obShape[0].shape[8] = 'O'; obShape[0].shape[9] = 'O';
		obShape[0].shape[10] = 'O'; obShape[0].shape[11] = 'O'; obShape[0].shape[12] = 'O'; obShape[0].shape[13] = 'O';
		obShape[0].shape[14] = 'O'; obShape[0].shape[15] = 'O'; obShape[0].shape[16] = 'O'; obShape[0].shape[17] = 'O';
		obShape[0].shape[18] = 'O'; obShape[0].shape[19] = 'O'; obShape[0].shape[20] = 'O'; obShape[0].shape[21] = 'O';
		obShape[0].shape[22] = 'O'; obShape[0].shape[23] = 'O';

		randomLocation(&obShape[0], 2, 12, 78, 14);
		randomLocation(&obShape[1], 2, 12, 78, 0);
	//	randomLocation(&obShape[2], 2, 12, 78, 14);
	}

	//Assign
	obs[0].theShape = obShape[0];

	obs[1] = obs[0];
	obs[2] = obs[0];

	/*
	Object cloud; cloud.m = 0; cloud.f = 0; cloud.a = 0; cloud.theLevel = &currentLevel; //Assign the initial values of the "cloud"
	cloud.name = "cloud";
	cloud.isPlayer = false;

	cloud.isConstant = true;

	cloud.collisionSymbol = 'A';

		Image cloudShape;
	{

	//Resolution
	cloudShape.resolutionX = 5;
	cloudShape.resolutionY = 5;

	//The shape's pieces
	cloudShape.shape[0] = ' ';      cloudShape.shape[16] = 254;
	cloudShape.shape[1] = ' ';		cloudShape.shape[17] = 254;
	cloudShape.shape[2] =  254;		cloudShape.shape[18] = 254;
	cloudShape.shape[3] = 254;		cloudShape.shape[19] = 254;
	cloudShape.shape[4] = ' ';		cloudShape.shape[20] =  ' ';
	cloudShape.shape[5] = 254;		cloudShape.shape[21] = 254;
	cloudShape.shape[6] = 254;		cloudShape.shape[22] = 254;
	cloudShape.shape[7] = 254;		cloudShape.shape[23] = 254;
	cloudShape.shape[8] = 254;		cloudShape.shape[24] = ' ';
	cloudShape.shape[9] = 254;
	cloudShape.shape[10] = 254;
	cloudShape.shape[11] = 254;
	cloudShape.shape[12] = 254;
	cloudShape.shape[13] = 254;
	cloudShape.shape[14] = 254;
	cloudShape.shape[15] = 254;
	//Coordinates
	cloudShape.shapeCor[0].x = 10; cloudShape.shapeCor[0].y = 1;
	cloudShape.shapeCor[1].x = 10; cloudShape.shapeCor[1].y = 1;
	cloudShape.shapeCor[2].x = 10; cloudShape.shapeCor[2].y = 1;
	cloudShape.shapeCor[3].x = 10; cloudShape.shapeCor[3].y = 1;
	cloudShape.shapeCor[4].x = 10; cloudShape.shapeCor[4].y = 1;
	cloudShape.shapeCor[5].x = 11; cloudShape.shapeCor[5].y = 2;
	cloudShape.shapeCor[6].x = 11; cloudShape.shapeCor[6].y = 2;
	cloudShape.shapeCor[7].x = 11; cloudShape.shapeCor[7].y = 2;
	cloudShape.shapeCor[8].x = 11; cloudShape.shapeCor[8].y = 2;

	cloudShape.shapeCor[9].x = 11; cloudShape.shapeCor[9].y = 2;
	cloudShape.shapeCor[10].x = 12; cloudShape.shapeCor[10].y = 3;
	cloudShape.shapeCor[11].x = 12; cloudShape.shapeCor[11].y = 3;
	cloudShape.shapeCor[12].x = 12; cloudShape.shapeCor[12].y = 3;
	cloudShape.shapeCor[13].x = 12; cloudShape.shapeCor[13].y = 3;
	cloudShape.shapeCor[14].x = 12; cloudShape.shapeCor[14].y = 3;
	cloudShape.shapeCor[15].x = 13; cloudShape.shapeCor[15].y = 4;
	cloudShape.shapeCor[16].x = 13; cloudShape.shapeCor[16].y = 4;
	cloudShape.shapeCor[17].x = 13; cloudShape.shapeCor[17].y = 4;

    cloudShape.shapeCor[18].x = 13; cloudShape.shapeCor[18].y = 4;
	cloudShape.shapeCor[19].x = 13; cloudShape.shapeCor[19].y = 4;
	cloudShape.shapeCor[20].x = 14; cloudShape.shapeCor[20].y = 5;
	cloudShape.shapeCor[21].x = 14; cloudShape.shapeCor[21].y = 5;
	cloudShape.shapeCor[22].x = 14; cloudShape.shapeCor[22].y = 5;
	cloudShape.shapeCor[23].x = 14; cloudShape.shapeCor[23].y = 5;
	cloudShape.shapeCor[24].x = 14; cloudShape.shapeCor[24].y = 5;
	}

	//Assign
	cloud.theShape = cloudShape;
	*/


   //	myForce.moveConstantly(movVector, 5); //Move the object








	//Game Loop
	/* Look at:

	1) Input
	2) Rendering

	*/


//The game is run even we pause the game
while(1)
{


	//Controllers are out of the normal inputs
/*	if(kbhit())
	{
		key = getch();

		//Pressing "P" (Pausing/Continuing)
			//We can press "P" both of time when we play game or pause the game
		if(key == 80 || key == 112)
		{

			isPaused = !isPaused;
		}
	}*/


	//When the game isn't paused
	if(!isPaused)
	{

//1) INPUT
if(kbhit())
{
			key = getch();

		//Pressing "A"
		if(key == 65 || key == 97)
		{
			//NOTE: WE CAN USE THE CLASS BY THIS TECHNIQUE DIRECTLY. Class() The paranthesis are definition
			//printf("Run");
			//go.move(Vector(-1,0));

			projectile = Vector(-2, -2);

			pressedTime++; //Increase

			go.cameraDirectionX = -1; //Moving left
		}


		//Pressing "D"
		if(key == 68 || key == 100)
		{

			//go.move(Vector(6,-3));

			projectile = Vector(2, -2);
		//go.theShape.animation();
		//go.move(Vector(0,0));
			pressedTime++; //Increase

		//	go.cameraDirectionX = +1; //Moving right
		}


		//Pressing "W"
		if(key == 87 || key == 119)
		{

			//go.move(Vector(6,-3));
		//go.move(Vector(0,0));
			projectile = Vector(0, -2);

			/*int number[5]; number[0] = 65;
			char myChar[5];
			free(myChar);

			myChar[0] = number[0];

			Debug(myChar);*/

			pressedTime++; //Increase


		}



		//Pressing "P" (Pausing/Continuing)
		if(key == 80 || key == 112)
		{

			isPaused = !isPaused;

			pressedTime++; //Increase
		}



}


			//Gravity
		if(!go.isConstant)
		{
		//	go.gravity();
		go.addForce(&projectile);



		}





		//Moving side


		mSideSpeed += difficulityAcceleration;
		if(mSideSpeed > 5000 / 2)
		{
			obs[0].move(Vector(-1,0));
			obs[1].move(Vector(-2,0));
			obs[2].move(Vector(-3,0));

			//cloud.move(Vector(0,0));
			mSideSpeed = 0; //Zero it
		}





	}
	else if(kbhit() && isPaused)
	{
		key = getch();
	//REPLAY
		if(key == 82 || key == 114)
		{
			main();
		}
	}


}




	return 0;
}
