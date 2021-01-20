#include<gl\freeglut.h>
#include "Ball.h"
#include<math.h>
#include"vars.h"
#include"Brick.h"


float r_x=50.0, r_y=290.0, r_w=80, r_h=8.0;


Ball ball(5); // radius
Brick brick[10][15]; // cate sunt ele array-iul

bool isCollision(Ball &b, Brick &br)
{
    float x=b.x, y=b.y, r=b.r, c=br.col, w=br.w, row=br.row, h=br.h;
/*daca mingea si brick se afla  in apropiere adica daca rama lor interactioneaza
mingea are rama patrata la fel ca si brick-urile*/
if(br.active)
      {
        if(abs(x-c*w-w/2-2)<=r+w/2 && abs(y-row*h-h/2-2)<=r+h/2)
       {
//concretizam , if = special pt lovitura de colturi si masuram distanta ,,pitagora si w/2-1*sqrt pentru patrate
//daca ele intersecteaza atunci return 1 daca nu return 0
           if(sqrt((c*w+w/2-x)*(c*w+w/2-x) + (row*h+h/2-y)*(row*h+h/2-y))
				- (w/2-1)*sqrt(2.0) - r > r*(sqrt(2.0)-1))
				return 0;
			else
				return 1;
           }
      }
       return 0 ;
       }


void Draw()
{
   //aici desenam mingea si restul
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.2,0.8,0.1);//culoarea verde
   glRectf(r_x, r_y, r_x+r_w, r_y+r_h); // bara de jos
   //desenam Mingea
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_POLYGON);
   for(float i =0 ; i<2*3.14; i=i+3.14/4)
   {
       glVertex2f(ball.x+ball.r*sin(i),ball.y+ball.r*cos(i));
   }
   glEnd();
   glColor3f(0.1,0.2,0.8);
   glBegin(GL_QUADS);
   for(int i=0; i<10; i++)
		{
		    glColor3ub(i*25,i*20,160);
			for(int j=0; j<15; j++)
			{
				Brick &b=brick[i][j];
				if(b.active)
				{
					glVertex2f(b.col*b.w+1, b.row*b.h+1);
					glVertex2f(b.col*b.w+b.w-1, b.row*b.h+1);
					glVertex2f(b.col*b.w+b.w-1, b.row*b.h+b.h-1);
					glVertex2f(b.col*b.w+1, b.row*b.h+b.h-1);
				}
			}
		}
   glEnd();
   glutSwapBuffers();
}


void MousePress(int button, int state , int x, int y){
if(button==GLUT_LEFT_BUTTON && !ball.active)
{
    ball.active=true;
    ball.dx=4;//viteza
    ball.dy=-4;//ridicarea  in sus y
}
}


void Timer(int)
{
   if(ball.active)
    {
       ball.move();
       for(int i=0; i<10; i++)
		{
			for(int j=0; j<15; j++)
			{
            Brick &b = brick[i][j];
            //saritura
            if(isCollision(ball,b))
            {
                //verificare daca mingea se afla sus sau jos
                if(abs(ball.x-b.col*b.w-b.w/2) < abs(ball.y-b.row*b.h-b.h/2))

                    //schimbam viteza verticala
                    {ball.dy*=-1;}

                //verificare daca se afla in dreapta sau in stanga
                else if(abs(ball.x-b.col*b.w-b.w/2) > abs(ball.y-b.row*b.h-b.h/2))

                    //schimbam viteza orizontala
                    {ball.dx*=-1;}

                //sau
                else
                {
                    //mingea se afla  in colt,in partea diagonala a partii blocului
                   if(ball.dx>0)
                      {if(ball.x < b.col*b.w+1) ball.dx*=-1;}
                    else if(ball.x > (b.col+1)*b.w-1) ball.dx*=-1;
                    if(ball.dy>0)
						{if(ball.y < b.row*b.h+1) ball.dy*=-1;}
						else if(ball.y > (b.row+1)*b.h-1) ball.dy*=-1;
					}
                if(--b.hit==0)
                    {b.active=false;}
                    goto o;
            }
         }
       }
   }
  o:    Draw(); //go to
   glutTimerFunc(33,Timer,0);
}


void Mouse(int ax ,int ay)
{

   r_x=ax-r_w/2;// mous-ul sa fie la mijloc

   if(!ball.active){
        ball.x=r_x+r_w/2;// mingea la fel
        ball.y=r_y-ball.r; //aflarea mingei pe bara
        }
   }


void Init()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 300, 300, 0, 1, 0);
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Acranoid");
	glutDisplayFunc(Draw);
	glutTimerFunc(33, Timer, 0);
	glutPassiveMotionFunc(Mouse);
	glutMouseFunc(MousePress);
	Init();
	for(int i=0; i<10; i++)
		for(int j=0; j<15; j++)
		{
			brick[i][j].active=true;
			brick[i][j].col=j;
			brick[i][j].row=i;
		}
	glutMainLoop();
	return 0;
}
