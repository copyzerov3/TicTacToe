
#include <stdio.h>
#include "SceneGraph.h"
#include "Cube.h"
#include "Sphere.h"
#include "Client.h"
#include "Button.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SceneGraph Graph;
Client NetworkClient;
Cube* board[9];
Button* ResetButton;

bool PlayerTurn = true;

std::string WinnerMessage = "";
void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	Graph.Traverse();
	std::string instructions = "You are Red and the computer is blue to start over press the reset button";

	glColor3f(1, 0, 0);
	glRasterPos2i(100, 100);
	for (int i = 0; i < instructions.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, instructions[i]);
	}
	glRasterPos2i(500, 500);
	for (int i = 0; i < WinnerMessage.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, WinnerMessage[i]);
	}
	glutSwapBuffers();
}
void ClientNetworkUpdate()
{
	NetworkClient.Update();
	if (NetworkClient.Events.size() != 0)
	{
		bool GameWon = false;
		for (int i = 0; i < NetworkClient.Events.size();i++)
		{
			if (NetworkClient.Events[i] == GAME_OVER_COMPUTER)
			{

				WinnerMessage = "You Lose the computer wins, Play again?";
				PlayerTurn = false;
				GameWon = true;

			}
			else if (NetworkClient.Events[i] == GAME_OVER_PLAYER)
			{

				WinnerMessage = "You WIN!, Play again?";
				PlayerTurn = false;
				GameWon = true;
			}
			else if (NetworkClient.Events[i] == GAME_OVER_TIE)
			{

				WinnerMessage = "A TIE! , Play again?";
				PlayerTurn = false;
				GameWon = true;
			}
			else
			{
				board[NetworkClient.Events[i]]->SetCellValue(1);
				if (!GameWon)
					PlayerTurn = true;
			}
		}
		
		
		NetworkClient.Events.clear();
	}
}
void idle()
{	
	Graph.Update();
	ClientNetworkUpdate();
	glutPostRedisplay();
}
void init(void)
{
	/* select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -100.0, 100.0);
}
void OnMouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
		printf("Mouse X : %d\nMouse Y : %d\n", x, y);
		for (int i = 0; i < 9; i++)
		{
			if (board[i]->IsPointWithin(x, SCREEN_HEIGHT - y) && board[i]->IsAvailable() && PlayerTurn)
			{
				board[i]->SetCellValue(-1);
				NetworkClient.SendPackets(i);
				printf("CELL %d selected\n", i);
				PlayerTurn = false;
			}
		}
		if (ResetButton->IsPointWithin(x, SCREEN_HEIGHT - y))
		{
			for (int i = 0; i < 9; i++)
			{
				board[i]->SetCellValue(0);
				NetworkClient.SendPackets(RESTART_GAME);
				WinnerMessage = "";
				PlayerTurn = true;
			}
		}
	}
}
int main(int argc, char** argv)
{
	int xPos = 100, yPos= 500;
	for (int i = 0; i < 9; i++)
	{
		board[i] = new Cube(100);
		board[i]->SetPosition(xPos, yPos, 0);
		Graph.AddSceneNode(board[i]);
		xPos += 110;
		if ((i + 1) % 3 == 0)
		{
			xPos = 100;
			yPos -= 110;
		}
	}
	ResetButton = new Button(100, "Reset");
	ResetButton->SetPosition(SCREEN_WIDTH - 100, 100,0);
	Graph.AddSceneNode(ResetButton);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GL");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(OnMouse);
	glutMainLoop();


	return 0;   /* ISO C requires main to return int. */
}
