#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define MAXSIZE 100
#define MAXFRAME_X 119
#define MAXFRAME_Y 29

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Cursorposition;
void gotoxy(int x, int y)
{
    Cursorposition.X = x;
    Cursorposition.Y = y;
    SetConsoleCursorPosition(console,Cursorposition);
}
void menu();
class Possition{
    private:
        int x;
        int y;
    public:
        Possition():x(0),y(0){}
        Possition(int x,int y):x(x),y(y){}

        void moveUp(){y--; if(y < 0) y = MAXFRAME_Y;}
        void moveDown(){y++;if(y > MAXFRAME_Y) y = 0;}
        void moveRight(){x++;if(x > MAXFRAME_X) x = 0;}
        void moveLeft(){x--;if(x < 0) x = MAXFRAME_X;}

        Possition cpyPos();

        int getX(){return x;}
        int getY(){return y;}

        void draw(char);

};

class Snake{
    private:
        Possition snake[MAXSIZE];
        char dir;
        int size;
        Possition fruit;
    public:
        Snake();
        ~Snake();
        void gamelogic();
        void turnUp(){if(dir!='s')dir = 'w';}
        void turnDown(){if(dir!='w')dir = 's';}
        void turnRight(){if(dir!='a')dir = 'd';}
        void turnLeft(){if(dir!='d')dir = 'a';}
        void eaten();
        void grow();
        void collide();
};

bool gameover = false;
int main()
{
    menu();
    getch();
    srand(time(NULL));
    Snake snake;
    char ch;
    while(!gameover){
        if(kbhit())
            ch = getch();
        switch(ch){
            case 'w':snake.turnUp(); break;
            case 's':snake.turnDown(); break;
            case 'd':snake.turnRight(); break;
            case 'a':snake.turnLeft(); break;
        }
        snake.gamelogic();
    }
    Sleep(950);

    return 0;
}
Snake::Snake(){
    size = 1;
    snake[0] = Possition(0,0);
    fruit = Possition(rand()%50,rand()%25);
}
void Possition::draw(char ch = '*'){
    gotoxy(x,y);
    cout << ch;
}

Possition Possition::cpyPos(){
    Possition p;
    p.x = x;
    p.y = y;
    return Possition(p);
}
void Snake::grow(){
    snake[size++] = Possition();
}
void Snake::eaten(){
    if(snake[0].getX() == fruit.getX() && snake[0].getY() == fruit.getY() ){
        grow();
        fruit = Possition(rand()%50,rand()%25);
    }
}
void Snake::collide(){
    for(int i=1;i<size;i++)
        if(snake[0].getX()==snake[i].getX() && snake[0].getY()==snake[i].getY())
            gameover = true;
}
Snake::~Snake(){
    gotoxy(50,25);
    cout << "game over ";
}
void Snake::gamelogic(){
    system("cls");
    for(int i=size-1; i>0 ;i--){
        snake[i] = snake[i-1].cpyPos();
    }
    switch(dir){
        case 'w': snake[0].moveUp(); break;
        case 's': snake[0].moveDown(); break;
        case 'd': snake[0].moveRight(); break;
        case 'a': snake[0].moveLeft(); break;
    }
    eaten();
    for(int i=0;i<size;i++)
        snake[i].draw();
   fruit.draw('#');
   collide();
}

void menu()
{
    cout<<" --------------------------------------------------------------------------------------------------  "<<endl;
    cout<<"|                                                                                                 |"<<endl;
    cout<<"|    |||||||  ||     ||      ||     ||  ||  ||||||    |||||||||     ||     ||        || ||||||    |"<<endl;
    cout<<"|   |         || ||  ||    ||  ||   || ||   ||        ||          ||  ||   || ||   |||| ||        |"<<endl;
    cout<<"|    ||||||   ||  || ||   ||    ||  |||     ||||      ||  |||||  ||    ||  ||  || || || ||||      |"<<endl;
    cout<<"|          |  ||   ||||   ||||||||  || ||   ||        ||     ||  ||||||||  ||   ||   || ||        |"<<endl;
    cout<<"|    ||||||   ||     ||   ||    ||  ||  ||  ||||||    |||||||||  ||    ||  ||        || ||||||    |"<<endl;
    cout<<"|                                                                                                 |"<<endl;
    cout<<" --------------------------------------------------------------------------------------------------  "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                                             PRESS ANY BUTTON    "<<endl<<endl;
}
