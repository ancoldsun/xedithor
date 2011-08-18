/********************************************
* Tetrisonyx
* A Tetris Clone
* August 08, 2011
* author: edi.ermawan@gmail.com
*********************************************/
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>

using namespace std;

/* define list */
//#ifdef _DEBUG
	#define _DBGLOG(info,val) std::cout<<info<<" : "<<val<<std::endl;
//#endif //

#define KEY_UP     72
#define KEY_DOWN   80
#define KEY_RIGHT  77
#define KEY_LEFT   75
#define ESCAPE     1
#define ENTER      28
#define SPACE_BAR  59

#define GAME_SCREEN_WIDTH 700
#define GAME_SCREEN_HEIGHT 620

#define MAX_TILE_HEIGHT 20
#define MAX_TILE_WIDTH 10
#define SIZE_BOARD 30
#define START_BOARD_X (GAME_SCREEN_WIDTH-(MAX_TILE_WIDTH*SIZE_BOARD))/2  // back net pos at the middle of game screen
#define START_BOARD_Y 10

/* game variable */
SDL_Surface* Tsx_display;
SDL_Surface* Tsx_backgnd;
SDL_Surface* Tsx_Imgtetriminon;
SDL_Surface* Tsx_Imgtetriminons[7];
SDL_Surface* Tsx_Imgtetri_ungu;
SDL_Surface* Tsx_Imgtetri_grey;

SDL_Surface* Tsx_ImgGameOver;

int Tsx_level_now=0;
int Tsx_speed[11]={ 1000,900,800,700,600,500,400,300,200,100,50};
int Tsx_max_score_in_level[11]= { 100, 400, 600, 2000,5000,7000,10000,15000,25000,30000,50000};

int Tsx_fallingDelay=0;
int Tsx_slideDelay=0;// left-right
int Tsx_NextTetri=0; // left-right

bool Tsx_isGameOver;

bool m_running=true;
SDL_Event m_event;
int m_keypressed;

struct Point
{
	int x,y;
};

struct Color
{
	Uint8 r,g,b;
};



/* graphics SDL util : create surface*/
SDL_Surface* Create_SDLSurface(const char* ImgFile)
{
	SDL_Surface* temp(0);
	SDL_Surface* result(0);
	if((temp= IMG_Load(ImgFile)))
	{
		if(temp->format->Amask)
		{
			result= SDL_DisplayFormatAlpha(temp);
		}
		else
		{
			result= SDL_DisplayFormat(temp);
		}
		SDL_FreeSurface(temp);
	}
	return result;
}
/* graphics SDL util : draw surface*/
bool DrawSurface(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
	SDL_Rect DestR;
    DestR.x = x;
    DestR.y = y;
    SDL_BlitSurface(src, NULL, dest, &DestR);

	return true;
}
/* graphics SDL util   : draw pixel. 
   DrawPixel came from : http://cone3d.gamedev.net/cgi-bin/index.pl?page=tutorials/gfxsdl/tut1 
*/
void DrawPixel(SDL_Surface *screen, int x, int y,Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
}
/* graphics util : draw line */
void DrawLine(const Point& point1,const Point& point2, const Color& color)
{
	float grad_value=1;
	if(0!=point2.x-point1.x)
	{
		grad_value=(point2.y-point1.y)/(point2.x-point1.x);
	}
	else
	{
		int bigy,lowy=0;
		if(point1.y>=point2.y)
		{
			bigy=point1.y;
			lowy=point2.y;
		}
		else
		{
			bigy=point2.y;
			lowy=point1.y;
		}
		for(int posy_=lowy;posy_<bigy;posy_++)
		{
			DrawPixel(Tsx_display, point1.x, posy_, color.r, color.g, color.b);
		}
		return;
	}
	int bigx,lowx=0;
	if(point1.x>=point2.x)
	{
		bigx=point1.x;
		lowx=point2.x;
	}
	else
	{
		bigx=point2.x;
		lowx=point1.x;
	}
	for(int posx_=lowx;posx_<bigx;posx_++)
	{
		int posy_=(grad_value)*(posx_-point1.x)+point1.y;
		DrawPixel(Tsx_display, posx_, posy_, color.r, color.g, color.b);
	}
}

/* font class to write number  */
/* seven segment style font :D */
/*
class Segment
{
	Segment
	virtual void Draw(int px,int py){}=0;
}
class Segment0
{
	Draw()
};
*/
class SevSegment
{
private:
	//static SevSegment* m_sevseg;
	SDL_Surface* m_disp;
	SDL_Surface* m_imgHdark;
	SDL_Surface* m_imgVdark;
	SDL_Surface* m_imgHlight;
	SDL_Surface* m_imgVlight;
	void (SevSegment::*Drawer[10])();
	int m_maxDigit;
	int m_posX,m_posY;
public:
	SevSegment(SDL_Surface* disp,SDL_Surface* imgHdark,SDL_Surface* imgVdark,
		       SDL_Surface* imgHlight,SDL_Surface* imgVlight,int maxDigit)
	{
		m_disp      = disp;
		m_imgHdark  = imgHdark;
		m_imgVdark  = imgVdark;
		m_imgHlight = imgHlight;
		m_imgVlight = imgVlight;
		m_posX=100;
		m_posY=100;

		m_maxDigit=maxDigit;

		Drawer[0]=&SevSegment::Draw_00;
		Drawer[1]=&SevSegment::Draw_01;
		Drawer[2]=&SevSegment::Draw_02;
		Drawer[3]=&SevSegment::Draw_03;
		Drawer[4]=&SevSegment::Draw_04;
		Drawer[5]=&SevSegment::Draw_05;
		Drawer[6]=&SevSegment::Draw_06;
		Drawer[7]=&SevSegment::Draw_07;
		Drawer[8]=&SevSegment::Draw_08;
		Drawer[9]=&SevSegment::Draw_09;
		
	};
	void setPos(const int posx_,const int posy_)
	{
		m_posX=posx_;
		m_posY=posy_;
	};

	void DrawLastDigit(int n,int iter)
	{
		if(iter==0)
			return;
		m_posX=m_posX-(25);
		(this->*Drawer[n%10])();
		DrawLastDigit(n/10,--iter);
	}

	void DrawNumber(int number)
	{
		int temp=m_posX;
		m_posX=m_posX+(25*(m_maxDigit));
		DrawLastDigit(number,m_maxDigit);
		m_posX=temp;

	};

	void Draw_00()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_01()
	{
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY-20);
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY);
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY+20);

		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY+1);
		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_02()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY+1);
		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY-19);

		//DrawSurface(m_disp,m_imgVdark,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_03()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY+1);
		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_04()
	{
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		///DrawSurface(m_disp,m_imgHdark,m_posX,m_posY+20);

		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_05()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		//DrawSurface(m_disp,m_imgVdark,m_posX+18,m_posY-19);
	};
	void Draw_06()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		//DrawSurface(m_disp,m_imgVdark,m_posX+18,m_posY-19);
	};
	void Draw_07()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY);
		//DrawSurface(m_disp,m_imgHdark,m_posX,m_posY+20);

		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY+1);
		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_08()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
	void Draw_09()
	{
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY-20);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY);
		DrawSurface(m_disp,m_imgHlight,m_posX,m_posY+20);

		//DrawSurface(m_disp,m_imgVdark,m_posX,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX,m_posY-19);

		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY+1);
		DrawSurface(m_disp,m_imgVlight,m_posX+18,m_posY-19);
	};
};


SevSegment* Tsx_your_score;
SevSegment* Tsx_hight_score;
SevSegment* Tsx_level;

SevSegment* Tsx_time_play_H;
SevSegment* Tsx_time_play_M;
SevSegment* Tsx_time_play_S;

int  Tsx_time_play_H_val;
int  Tsx_time_play_M_val;
int  Tsx_time_play_S_val;

int Tsx_your_score_value;
int Tsx_hight_score_value;
int Tsx_level_value;

/* tetriminon's type, there is 7 standart type */
enum TetriType
{
	Type_I,
	Type_J,
	Type_L,
	Type_O,
	Type_S,
	Type_T,
	Type_Z
};
int TetrisBoard[10][21];
int TetrisNextBoard[4][4];
int TetriPoint[7][4][4]= 
	{ 	{    {0,0,0,0},
			 {1,1,1,1},
			 {0,0,0,0},
			 {0,0,0,0},}, // I
		{    {0,1,1,0},
			 {0,1,0,0},
			 {0,1,0,0},
			 {0,0,0,0},}, // J
		{    {0,1,0,0},
			 {0,1,0,0},
			 {0,1,1,0},
			 {0,0,0,0},}, // L
		{    {0,1,1,0},
			 {0,1,1,0},
			 {0,0,0,0},
			 {0,0,0,0},}, // O
		{    {0,1,0,0},
			 {0,1,1,0},
			 {0,0,1,0},
			 {0,0,0,0},}, // S
		{    {0,1,0,0},
			 {0,1,1,0},
			 {0,1,0,0},
			 {0,0,0,0},}, // T
		{    {0,0,1,0},
			 {0,1,1,0},
			 {0,1,0,0},
			 {0,0,0,0},}  // Z
	};

class Tetriminon
{
public:
	Tetriminon(SDL_Surface* display, SDL_Surface* image):m_display(display),m_image(image)
	{
	};
	void setType(int type)
	{
		m_type=type;
	};
	int getType()
	{
		return m_type;
	};
	void setTypeArray(int* type)
	{
		m_typeArray=type;
	};
	void setPos(int x,int y)
	{
		m_pos_x=x;
		m_pos_y=y;
	};
	int getPosY() const
	{
		return m_pos_y;
	}
	bool falling()
	{
		if(m_pos_y<0)
		{
			
			m_pos_y++;
			return false;
		}
		bool isCollide_=false;
		for(int i=3;i>-1;i--)
		{
			for(int j=0;j<4;j++)
			{
				if(((m_typeArray+(i*sizeof(int)))[j]==1) &&(TetrisBoard[m_pos_x+j][m_pos_y+i+1]==1))// m_pos_y+i+1 -->next y
				{
					isCollide_=true;
					// transfer filled point
					for(int m=0;m<4;m++)
					{
						for(int n=0;n<4;n++)
						{
							if(m_pos_x+m<10 && m_pos_y+n<21)
							{
								int val=(m_typeArray+(n*sizeof(int)))[m];
								TetrisBoard[m_pos_x+m][m_pos_y+n]=TetrisBoard[m_pos_x+m][m_pos_y+n]|val;
							}
						}
					}
					break;
				}
			}
		}
		if(!isCollide_ && m_pos_y<19)
			m_pos_y++;
		return isCollide_;
	};
	bool ToRight()
	{
		bool isCollide_=false;
		for(int i=3;i>-1;i--)
		{
			for(int j=3;j>-1;j--)
			{
				if((m_typeArray+(i*sizeof(int)))[j]==1)
				{
					std::cout<<"j: "<<j<<std::endl;
					if( ((TetrisBoard[m_pos_x+j+1][m_pos_y+i]==1)) || ((m_pos_x+j+1)>9) )
						isCollide_=true;
					break;
				}
			}
			if(isCollide_)
				break;
		}
		if(!isCollide_)	
			m_pos_x++;
		return isCollide_;

	}
	bool ToLeft()
	{
		bool isCollide_=false;
		for(int i=3;i>-1;i--)
		{
			for(int j=0;j<4;j++)
			{
				if((m_typeArray+(i*sizeof(int)))[j]==1)
				{
					std::cout<<"j: "<<j<<std::endl;
					if( ((TetrisBoard[m_pos_x+j-1][m_pos_y+i]==1)) || ((m_pos_x+j-1)<0) )
						isCollide_=true;
					break;
				}
			}
			if(isCollide_)
				break;
		}
		if(!isCollide_)	
			m_pos_x--;
		return isCollide_;
	}
	void Rotate()
	{
		if(m_type==Type_O)
			return;
		//back up array
		int m_typeArray_temp[4][4];
		
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				m_typeArray_temp[i][j]=(m_typeArray+(i*sizeof(int)))[j];
			}
		}
		int temp1=(m_typeArray+(0*sizeof(int)))[0];
		int temp2=(m_typeArray+(0*sizeof(int)))[2];
		int temp3=(m_typeArray+(2*sizeof(int)))[2];
		int temp4=(m_typeArray+(2*sizeof(int)))[0];

		(m_typeArray+(0*sizeof(int)))[0]=temp4;
		(m_typeArray+(0*sizeof(int)))[2]=temp1;
		(m_typeArray+(2*sizeof(int)))[2]=temp2;
		(m_typeArray+(2*sizeof(int)))[0]=temp3;
        ///------------------------------------
		temp1=(m_typeArray+(0*sizeof(int)))[1];
		temp2=(m_typeArray+(1*sizeof(int)))[2];
		temp3=(m_typeArray+(2*sizeof(int)))[1];
		temp4=(m_typeArray+(1*sizeof(int)))[0];

		(m_typeArray+(0*sizeof(int)))[1]=temp4;
		(m_typeArray+(1*sizeof(int)))[2]=temp1;
		(m_typeArray+(2*sizeof(int)))[1]=temp2;
		(m_typeArray+(1*sizeof(int)))[0]=temp3;

		if(m_type==Type_I)
		{
			temp1=(m_typeArray+(3*sizeof(int)))[1];
			(m_typeArray+(3*sizeof(int)))[1]=(m_typeArray+(1*sizeof(int)))[3];
			(m_typeArray+(1*sizeof(int)))[3]=temp1;
		}
		//check cllide 

		// check left--------------
		bool isCollide_=false;
		for(int i=3;i>-1;i--)
		{
			for(int j=0;j<4;j++)
			{
				if((m_typeArray+(i*sizeof(int)))[j]==1)
				{
					std::cout<<"j: "<<j<<std::endl;
					if( ((TetrisBoard[m_pos_x+j-1][m_pos_y+i]==1)) || ((m_pos_x+j)<0) )
						isCollide_=true;
					break;
				}
			}
			if(isCollide_)
				break;
		}
		// check right--------------
		for(int i=3;i>-1;i--)
		{
			for(int j=3;j>-1;j--)
			{
				if((m_typeArray+(i*sizeof(int)))[j]==1)
				{
					std::cout<<"j: "<<j<<std::endl;
					if( ((TetrisBoard[m_pos_x+j+1][m_pos_y+i]==1)) || ((m_pos_x+j)>9) )
						isCollide_=true;
					break;
				}
			}
			if(isCollide_)
				break;
		}
		//below

		//if collide , no rotation
		if(isCollide_)
		{
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
				{
					(m_typeArray+(i*sizeof(int)))[j]=m_typeArray_temp[i][j];
				}
			}
		}

	}
	void Draw()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if((m_typeArray+(i*sizeof(int)))[j]==1)
				{
					int pix_x=START_BOARD_X+(j*SIZE_BOARD+(m_pos_x)*SIZE_BOARD);
					int pix_y=START_BOARD_Y+(i*SIZE_BOARD+(m_pos_y)*SIZE_BOARD);
					
					DrawSurface(m_display,m_image,pix_x,pix_y);			
				}
			}
		}
	};
private:
	int* m_typeArray;
	int m_type;
	int m_pos_x,m_pos_y;
	SDL_Surface* m_image;
	SDL_Surface* m_display;	 
};



Tetriminon* Tsx_TetriNow=NULL;

void NewTetriminon()
{
	if(Tsx_TetriNow!=NULL)
		delete Tsx_TetriNow;
	
	Tsx_TetriNow= new Tetriminon(Tsx_display,Tsx_Imgtetriminons[Tsx_NextTetri]);

	Tsx_TetriNow->setType(Tsx_NextTetri);
	Tsx_TetriNow->setTypeArray(*(TetriPoint[Tsx_NextTetri]));
	Tsx_TetriNow->setPos(3,-2);
	
	srand(time(NULL)*rand());
	int tetriminon_type=(rand()%6);
	Tsx_NextTetri=tetriminon_type;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			TetrisNextBoard[j][i]=TetriPoint[Tsx_NextTetri][i][j];
		}
	}
}

int Tsx_delta_time1; // for left right 
int Tsx_delta_time2; // for falling
int Tsx_delta_time3; // for measure time elapsed playing

void shift_array(int startindex)
{
	for(int i=startindex;i>1;i--)
	{
		for(int j=0;j<10;j++)
		{
			TetrisBoard[j][i]=TetrisBoard[j][i-1];
		}
	}
}
void eliminate()
{
	bool willEliminate=true;
	for(int i=19;i>0;i--)
	{
		willEliminate=true;
		int j;
		for(j=0;j<10;j++)
		{
			if(TetrisBoard[j][i]==0)
			{
				willEliminate=false;
			}
		}
		if(willEliminate)
		{
			Tsx_your_score_value+= 40 * (Tsx_level_now + 1);
			if(Tsx_your_score_value>Tsx_max_score_in_level[Tsx_level_now])
			{
				Tsx_level_now++;
			}
			for(j=0;j<10;j++)
			{
				TetrisBoard[j][i]=2;
			}
			shift_array(i);
			eliminate();
			break;
		}
	}
}

void ResetBoard()
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<21;j++)
		{
			if(j==20)
				TetrisBoard[i][j]=1;
			else
				TetrisBoard[i][j]=0;
		}
	}
}

void GameLoop()
{
	int tick_now1=0,tick_now2=0,tick_now3=0;
	if(Tsx_delta_time1==0)
		Tsx_delta_time1=SDL_GetTicks();
	else
		tick_now1=SDL_GetTicks();

	if(Tsx_delta_time2==0)
		Tsx_delta_time2=SDL_GetTicks();
	else
		tick_now2=SDL_GetTicks();

	if(Tsx_delta_time3==0)
		Tsx_delta_time3=SDL_GetTicks();
	else
		tick_now3=SDL_GetTicks();

	//std::cout<<"tick_now2: "<<tick_now2<<std::endl;
	//std::cout<<"Tsx_delta_time2: "<<Tsx_delta_time2<<std::endl;
	int delta_time =tick_now1-Tsx_delta_time1;
	int delta_time2=tick_now2-Tsx_delta_time2;
	int delta_time3=tick_now3-Tsx_delta_time3;

	
	if(delta_time3>1000 && !Tsx_isGameOver)
	{
		if(++Tsx_time_play_S_val>59)
		{
			Tsx_time_play_S_val=0;
			if(++Tsx_time_play_M_val>59)
			{
				Tsx_time_play_M_val=0;
				Tsx_time_play_H_val++;
			}
		}
		Tsx_delta_time3=0;
	}
	

	bool iscollide=false;
	switch(m_keypressed)
		{
			case KEY_UP   : 
							if(delta_time>20 && Tsx_TetriNow!=NULL)
							{
								Tsx_TetriNow->Rotate();
								//_DBGLOG("rotation-------------------",0);
							}
							m_keypressed=0;
							break;
			case KEY_DOWN : if(delta_time>Tsx_fallingDelay && Tsx_TetriNow!=NULL)
							{
								iscollide=Tsx_TetriNow->falling();
								if(Tsx_fallingDelay-100>0)
									Tsx_fallingDelay=Tsx_fallingDelay-100;
								else
									Tsx_fallingDelay=20;
								Tsx_delta_time1=0;
							}
							
							//m_keypressed=0;
							break;
			case KEY_RIGHT: if(delta_time>Tsx_slideDelay && Tsx_TetriNow!=NULL)
							{
								//iscollide=
								Tsx_TetriNow->ToRight();
								if(Tsx_slideDelay-30>0)
									Tsx_slideDelay=Tsx_slideDelay-30;
								else
									Tsx_slideDelay=20;
								Tsx_delta_time1=0;
							}
							break;
			case KEY_LEFT : if(delta_time>Tsx_slideDelay && Tsx_TetriNow!=NULL)
							{
								//iscollide=
								Tsx_TetriNow->ToLeft();
								if(Tsx_slideDelay-30>0)
									Tsx_slideDelay=Tsx_slideDelay-30;
								else
									Tsx_slideDelay=20;
								Tsx_delta_time1=0;
							}
							break;
			case ESCAPE   : m_running=false;
							break;
			case ENTER    :
							break;
			case SPACE_BAR: if(delta_time>20 && Tsx_TetriNow!=NULL)
								Tsx_TetriNow->Rotate();
							m_keypressed=0;
							break;
		}
	//std::cout<<"delta_time2: "<<delta_time2<<std::endl;
	if(delta_time2>Tsx_speed[Tsx_level_now] && Tsx_TetriNow!=NULL)
	{
		iscollide=Tsx_TetriNow->falling();
		Tsx_delta_time2=0;
	}
	if(iscollide)
	{
		if(Tsx_TetriNow->getPosY()==0)
		{
			Tsx_isGameOver=true;
			//_DBGLOG(" ----- GAME OVER ------- ",0);
		}
		else
		{
			//*** check eliminate
			eliminate();
			NewTetriminon();
			Tsx_fallingDelay=200;
		}
		return;
	}
}

void GameRender()
{
	/* draw background image */
	DrawSurface(Tsx_display,Tsx_backgnd,0,0);
	
    /* draw back net */
	Point p1;
	Point p2;
	Color col;
	col.r=0; col.g=255; col.b=0;

	p1.x=START_BOARD_X;
	p1.y=START_BOARD_Y;
	p2.x=START_BOARD_X+(SIZE_BOARD*MAX_TILE_WIDTH);
	p2.y=START_BOARD_Y;
	for(int i=0;i<MAX_TILE_HEIGHT;i++)
	{
		DrawLine(p1,p2,col);
		p1.y=p2.y=p1.y+(SIZE_BOARD);
	}
	DrawLine(p1,p2,col);
	p1.x=START_BOARD_X;
	p1.y=START_BOARD_Y;
	p2.x=START_BOARD_X;
	p2.y=START_BOARD_Y+(SIZE_BOARD*MAX_TILE_HEIGHT);
	for(int i=0;i<MAX_TILE_WIDTH;i++)
	{
		DrawLine(p1,p2,col);
		p1.x=p2.x=p1.x+(SIZE_BOARD);
	}
	DrawLine(p1,p2,col);

	if(Tsx_TetriNow!=NULL)
		Tsx_TetriNow->Draw();
	/* draw board */
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(TetrisBoard[i][j]==1)
			{
				int pix_x=START_BOARD_X+((i)*SIZE_BOARD);
				int pix_y=START_BOARD_Y+((j)*SIZE_BOARD);
				DrawSurface(Tsx_display,Tsx_Imgtetriminons[5],pix_x,pix_y);
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(TetrisNextBoard[i][j]==1)
			{
				int pix_x=START_BOARD_X+350+((i)*SIZE_BOARD);
				int pix_y=START_BOARD_Y+35+((j)*SIZE_BOARD);
				DrawSurface(Tsx_display,Tsx_Imgtetriminons[5],pix_x,pix_y);
			}
		}
	}
	if(Tsx_isGameOver)
	{
		DrawSurface(Tsx_display,Tsx_ImgGameOver,START_BOARD_X+25,START_BOARD_Y+100);
	}
	Tsx_your_score->DrawNumber(Tsx_your_score_value);
	Tsx_hight_score->DrawNumber(Tsx_hight_score_value);
	Tsx_level->DrawNumber(Tsx_level_now);

	Tsx_time_play_H->DrawNumber(Tsx_time_play_H_val);
	Tsx_time_play_M->DrawNumber(Tsx_time_play_M_val);
	Tsx_time_play_S->DrawNumber(Tsx_time_play_S_val);
}

void GameEvent(SDL_Event* sdl_event_)
{
	if(SDL_KEYDOWN==sdl_event_->key.type)
	{
		//_DBGLOG("SDL_KEYDOWN key: ",sdl_event_->key.keysym.scancode);
		m_keypressed=sdl_event_->key.keysym.scancode;
		if(m_keypressed==KEY_DOWN)
			Tsx_fallingDelay=200;
		else if(m_keypressed==KEY_LEFT || m_keypressed==KEY_RIGHT)
			Tsx_slideDelay=100;

		if(Tsx_isGameOver)
		{
			Tsx_isGameOver=false;
			Tsx_time_play_H_val=Tsx_time_play_M_val=Tsx_time_play_S_val=0;
			ResetBoard();
		}
	}
	if(SDL_KEYUP==sdl_event_->key.type)
	{
		//_DBGLOG("SDL_KEYUP key: ",sdl_event_->key.keysym.scancode);
		m_keypressed=0;
	}
	//if(SDL_PRESSED==sdl_event_->key.state)
	//{
		//_DBGLOG("SDL_PRESSED: key",sdl_event_->key.keysym.scancode);
	//}
}


int main(int argc, char *argv[])
{

	/* initialize SDL */
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
        return false;
    }
    if((Tsx_display = SDL_SetVideoMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) 
	{
        return false;
    }
	SDL_WM_SetCaption("Tetrisonyx - ( edi.ermawan@gmail.com ) ", "edi.ermawan@gmail.com");
	/* game loop */
	Tsx_backgnd=Create_SDLSurface("dat\\backgnd.png");
	Tsx_Imgtetriminons[Type_I]=Create_SDLSurface("dat\\tetriminon.png");
	Tsx_Imgtetriminons[Type_J]=Create_SDLSurface("dat\\Tetri_ungu.png");
	Tsx_Imgtetriminons[Type_L]=Create_SDLSurface("dat\\Tetri_grey.png");
	Tsx_Imgtetriminons[Type_O]=Create_SDLSurface("dat\\Tetri_red.png");
	Tsx_Imgtetriminons[Type_S]=Create_SDLSurface("dat\\Tetri_green.png");
	Tsx_Imgtetriminons[Type_T]=Create_SDLSurface("dat\\Tetri_blue.png");
	Tsx_Imgtetriminons[Type_Z]=Create_SDLSurface("dat\\Tetri_brown.png");

	Tsx_Imgtetri_ungu=Create_SDLSurface("dat\\Tetri_ungu.png");
	Tsx_Imgtetri_grey=Create_SDLSurface("dat\\Tetri_grey.png");

	SDL_Surface* imgHdark  = Create_SDLSurface("dat\\hdark.png");
	SDL_Surface* imgVdark  = Create_SDLSurface("dat\\vdark.png");
	SDL_Surface* imgHlight = Create_SDLSurface("dat\\hlight.png");
	SDL_Surface* imgVlight = Create_SDLSurface("dat\\vlight.png");

	Tsx_your_score=new SevSegment(Tsx_display,imgHdark,imgVdark,imgHlight,imgVlight,7);
	Tsx_your_score->setPos(515,240);

	Tsx_hight_score=new SevSegment(Tsx_display,imgHdark,imgVdark,imgHlight,imgVlight,7);
	Tsx_hight_score->setPos(515,315);
	Tsx_hight_score_value=9999999;

	Tsx_level=new SevSegment(Tsx_display,imgHdark,imgVdark,imgHlight,imgVlight,2);
	Tsx_level->setPos(575,407);
	Tsx_level_value=1;

	Tsx_time_play_H=new SevSegment(Tsx_display,imgHdark,imgVdark,imgHlight,imgVlight,2);
	Tsx_time_play_M=new SevSegment(Tsx_display,imgHdark,imgVdark,imgHlight,imgVlight,2);
	Tsx_time_play_S=new SevSegment(Tsx_display,imgHdark,imgVdark,imgHlight,imgVlight,2);

	Tsx_time_play_H->setPos(515,485);
	Tsx_time_play_M->setPos(575,485);
	Tsx_time_play_S->setPos(635,485);

	Tsx_time_play_H_val=0;
	Tsx_time_play_M_val=0;
	Tsx_time_play_S_val=0;

	Tsx_isGameOver=false;
	Tsx_ImgGameOver=Create_SDLSurface("dat\\gameover.png");

	

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<21;j++)
		{
			if(j==20)
				TetrisBoard[i][j]=1;
			else
				TetrisBoard[i][j]=0;
		}
	}

	/* init new game */
	Tsx_delta_time1=Tsx_delta_time2=0;
	Tsx_your_score_value=0;

	srand(time(NULL)*rand());
	int tetriminon_type=(rand()%6);
	Tsx_NextTetri=tetriminon_type;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			TetrisNextBoard[i][j]=TetriPoint[Tsx_NextTetri][i][j];
		}
	}

	NewTetriminon();
	while(m_running) {
        while(SDL_PollEvent(&m_event)) 
		{
			GameEvent(&m_event);
        }
		GameRender();
        GameLoop();
       
		SDL_Flip(Tsx_display);
    }

	return 0;
}

