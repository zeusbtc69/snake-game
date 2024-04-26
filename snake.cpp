#include <iostream>
#include <windows.h>
#include <conio.h>

// global declaration
int score = 0;                  // score
int g = 1;						// variable to increase the snakes body
bool gameover = false;          // game end condition

// linked list
struct snake
{
	// x and y coordinates of the snake
	int x;
	int y;

	// to print the character to represent the snakes head and body
	char ch;

	// next node for the snakes body
	snake* next;


	// to make our snake move
	void move(int X, int Y)
	{
		x += X;
		y += Y;
	}
}*head, a;


// fruit
class fruit
{
public:

	// fruits x and y coordinates
	int fruit_x;
	int fruit_y;
}star;



// snake direction
enum snake_direction
{
	stop = 0, up, left, right, down
}sdir;


// printiong the 
void playzone()
{
	// to update the console
	system("cls");

	// to print the score
	std::cout << "Score : " << score << "\n\n";

	// printing part
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			snake* temp = head;

			// boundaries
			if (i == 0 || i == 29 || j == 0 || j == 59)
				std::cout << "#";

			// printing the fruit
			else if (star.fruit_y == i && star.fruit_x == j && gameover != true)
				std::cout << "*";

			// printing the snakes body  ----> I guess important troubled me the most as I was new to linked list
			else if (temp != NULL)
			{
				int b = 0;
				while (temp != NULL)
				{
					if (temp->y == i && temp->x == j)
					{
						std::cout << temp->ch;
						b = 1;		// avoiding spaces between body
					}
					temp = temp->next;
				}

				// space printing
				if (b == 0)
					std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	// game over print
	if (gameover)
	{
		std::cout << "\t\t\tGame Over!\n\n\n\n\n";
	}

}


// function to create the snakes body on collision with the fruit
void create_new_node(int xa, int ya) {
	snake* node = new snake();
	node->x = xa;
	node->y = ya;
	node->ch = 'o';
	node->next = nullptr;

	if (head == nullptr) {
		head = node;
	}
	else {
		snake* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = node;
	}
}


// keyboard input 
void game_input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			sdir = up;
			break;
		case 'a':
			sdir = left;
			break;
		case 'd':
			sdir = right;
			break;
		case 's':
			sdir = down;
			break;
		case 'x':
			exit(0);
		}
	}
}

// game update
void game_update() {

	// Store the current position of the head
	int prevX = head->x;
	int prevY = head->y;

	// Move the head according to the direction
	switch (sdir) {
	case up:
		head->move(0, -1);
		break;
	case down:
		head->move(0, 1);
		break;
	case right:
		head->move(1, 0);
		break;
	case left:
		head->move(-1, 0);
		break;
	default:
		break;
	}


	// to detect collision with walls
	if (head->x == 0 || head->x == 59 || head->y == 0 || head->y == 29)
	{
		snake* temp = head;
		while (temp != NULL)
		{
			temp->ch = 'x';
			temp = temp->next;
		}
		gameover = true;
	}


	// to detect collision with the body 
	int xh = head->x, yh = head->y;
	snake* temp = head->next;
	while (temp != NULL)
	{
		if (temp->x == xh && temp->y == yh)
		{
			snake* change = head;
			while (change != NULL)
			{
				change->ch = 'x';
				change = change->next;
				gameover = true;
			}
		}
		temp = temp->next;
	}


	// adding body and fruit collision
	if (head->x == star.fruit_x && head->y == star.fruit_y)
	{
		score += 10;
		create_new_node(a.x + g, a.y);
		g++; // global variable for some reason
		star.fruit_y = rand() % 28; // fruit randomizer
		star.fruit_x = rand() % 58;
	}

	// Move the body segments to the position of the segment in front of them
	snake* current = head->next;
	while (current != nullptr) {

		// Store the current position of the segment
		int tempX = current->x;
		int tempY = current->y;

		// Update the position of the segment to the previous position
		current->x = prevX;
		current->y = prevY;

		// Update the previous position for the next segment
		prevX = tempX;
		prevY = tempY;
		current = current->next;
	}

}



int main()
{
	// random seed
	srand(time(NULL));

	// fruit first print
	star.fruit_y = rand() % 28;
	star.fruit_x = rand() % 58;

	// linked list head ->  snake head
	a.x = 15;
	a.y = 15;
	a.ch = 'O';
	a.next = NULL;
	head = &a;

	// game loop
	while (!gameover)
	{
		game_update();
		playzone();
		game_input();
		Sleep(100);
	}
}