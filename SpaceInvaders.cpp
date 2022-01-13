#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <mmsystem.h>

using namespace std;

void main_menu();
void game(char map[20][80], int l);
void scrollup(char levelmenu[15][112], int y);
void scrolldown(char levelmenu[15][112], int y);
void levels(char title[31][112]);
void levelselector(int y);
void closegame();
int score = 0;
int refreshrate = 150;

int main()
{
main_menu();
}

void levels(char title[31][112])
{
    Sleep(refreshrate);
    char levelmenu [15][112] =
    {
    "                                                  MAIN MENU                                                    ",
    "                                                                                                               ",
    "                                          >        LEVEL 1        <                                            ",
    "                                                                                                               ",
    "                                                   LEVEL 2                                                     ",
    "                                                                                                               ",
    "                                                   LEVEL 3                                                     ",
    "                                                                                                               ",
    "                                                   LEVEL 4                                                     ",
    "                                                                                                               ",
    "                                                   LEVEL 5                                                     ",
    "                                                                                                               ",
    "                                                 BOSS  LEVEL                                                   ",
    "                                                                                                               ",
    "                                                   RETURN                                                      "
    };

    while(1)
    {
        system("cls");
        system("color 0a");
        for (int y = 21; y < 31;y++)
            cout << title[y]<<endl;

        cout << endl;
        cout << endl;

		for (int y = 0; y < 15; y++)
		{
		cout << levelmenu[y] << endl;

        if(GetAsyncKeyState(VK_ESCAPE) != 0)
            main_menu();
        if(GetAsyncKeyState(VK_UP) != 0 && y != 2 && levelmenu[y][42] == '>')
            scrollup(levelmenu, y);
        if(GetAsyncKeyState(VK_DOWN) != 0 && y != 14 && levelmenu[y][42] == '>')
            scrolldown(levelmenu, y);
        if(GetAsyncKeyState(VK_RETURN) != 0)
        {
        switch (levelmenu[y][42])
            case '>' :
            {
                if (y != 14)
                {
                levelselector(y);
                }
                else
                main_menu();
            }
        }
		}
    Sleep(refreshrate);
    }


}

void game(char map[20][80], int l)
{
bool endgame = false;
int gamespeed = 10;
int enemyfire;
int maxhealth = 5;
int phealth = maxhealth;
double bosshealth = 75;
int mapy;
int enemyfound = 0;
	    if (l==0)
        {
            mapy = 30;
            system("color 0c");
        }
        else
        {
            system("color 0a");
            mapy = 20;
        }


	while (endgame == false)
	{
        srand(time(0));
	    system("cls");
        enemyfound = 0;
		for (int y = 0; y < mapy; y++)
			cout << map[y] << endl;

			cout << "Your Health: " << phealth;
			cout << "                      Your Score: " << score*10 <<endl;
            cout << endl;
            if (l==0)
            {
                cout << " BOSS HEALTH :" << (bosshealth/75)*100;
                cout << endl;
            }
			cout << "USE ARROW KEYS TO MOVE, SPACE TO SHOOT" << endl;

        for (int y = 0; y < mapy; y++)
        {
            for (int x = 0; x < 80; x++)
            {
                switch (map[y][x])
                {
                case 'W':
                {
                    if (GetAsyncKeyState(VK_LEFT) != 0 && GetAsyncKeyState(VK_SPACE) == 0)
                    {
                        int newX = x - 1;
                        switch (map[y][newX])
                        {
                        case ' ':
                            map[y][x] = ' ';
                            x--;
                            map[y][newX] = 'W';

                            break;
                        }
                    }

                    if (GetAsyncKeyState(VK_RIGHT) != 0 && GetAsyncKeyState(VK_SPACE) == 0)
                    {
                        int newX = x + 1;
                        switch (map[y][newX])
                        {
                        case ' ':
                            map[y][x] = ' ';
                            x++;
                            map[y][newX] = 'W';

                            break;
                        }
                    }

                    if (GetAsyncKeyState(VK_UP) != 0)
                    {
                        int newY = y - 1;
                        switch (map[newY][x])
                        {
                        case ' ':
                            map[y][x] = ' ';
                            y--;
                            map[newY][x] = 'W';

                            break;
                        }
                    }

                    if (GetAsyncKeyState(VK_DOWN) != 0)
                    {
                        int newY = y + 1;
                        switch (map[newY][x])
                        {
                        case ' ':
                            map[y][x] = ' ';
                            y++;
                            map[newY][x] = 'W';

                            break;
                            bool echeck = false;
                            while (echeck == false)
                            {
                            if (map[y][x] == '@')
                                y++;
                            else
                            {
                                echeck = true;
                                map[y][x] = '*';
                            }
                            }
                        }
                    }


                    if (GetAsyncKeyState(VK_SPACE) != 0)
                    {
                      y--;
                      if (map[y][x] != '-')
                        map[y][x] = '^';

                            break;
                    }

                    if (GetAsyncKeyState(VK_ESCAPE) != 0)
                        system("PAUSE");

                    break;
                }
                    case '^':
                    {
                            map[y][x] = ' ';
                            y--;
                            if (map[y][x] != '-' && map[y][x] != '@' && map[y][x] != '*')
                            {
                                map[y][x] = '^';
                            }
                            else if (map[y][x] == '@')
                            {
                                score++;
                                if (l==0)
                                    bosshealth--;
                                map[y][x] = ' ';
                            }
                            else if (map[y][x] == '*')
                            {
                                map[y][x] = '^';
                                y++;
                                map[y][x] = '*';
                            }

                    break;
                    }

                    case '@':
                    {
                        if (l==0)
                        enemyfire = rand() % 300;

                        else
                        enemyfire = rand() % 100;

                        if (enemyfire == 1)
                        {
                            y++;
                            bool echeck = false;
                            while (echeck == false)
                            {
                            if (map[y][x] == '@')
                                y++;
                            else
                            {
                                echeck = true;
                                map[y][x] = '*';
                            }
                            }
                        }

                    break;

                    }

                    case '*':
                    {

                        map[y][x] = ' ';
                        y++;

                        if (map[y][x] != '-' && map[y][x] != 'W' && map[y][x] != '@')
                        {
                        map[y][x] = '*';
                        }
                        else if (map[y][x] == 'W')
                        {
                            phealth--;
                        }
                        else if (map[y][x] == '@')
                        {
                            bool echeck = false;
                            while (echeck == false)
                            {
                            if (map[y][x] == '@')
                                y++;
                            else
                            {
                                echeck = true;
                                map[y][x] = '*';
                            }
                            }
                        }
                        else if (map[y][x] == '^')
                        {
                            map[y][x] = '*';
                            y--;
                            map[y][x] = '^';
                        }



                    break;
                    }


                break;
            }
        }
    }
        if (phealth <= 0)
        {
            endgame = true;
            system("cls");
            cout << "GAME OVER!" << endl;
        }
        if (bosshealth <= 0)
        {
             endgame = true;
             system("cls");
             Sleep(refreshrate);
             cout << "YOU KILLED THE BOSS. GAME SUCCESSFULLY COMPLETED!" << endl;
             cout << "YOUR SCORE IS: " << score*10 << endl;
             cout << "Press Escape to continue... " << endl;
             while (1)
             {
             if (GetAsyncKeyState(VK_ESCAPE) != 0)
             {
                 main_menu();
             }
             }
        }
        else
        {
            for (int y=0; y < mapy; y++)
            {
                for (int x = 0; x < 80; x++)
                {
                    switch (map[y][x])
                    {
                    case '@':
                        {
                            enemyfound = 1;
                        }
                    }
                }
            }
        }

        if (enemyfound == 0 && l!= 0)
        {
             endgame = true;
             system("cls");
             cout << "LEVEL SUCCESSFULLY COMPLETED!" << endl;
             system("PAUSE");;

             levelselector(((l+1)*2));
        }
        Sleep(gamespeed);
	}

}

void main_menu()
{

    char title [31][112] =
{
    "                                                                                                               ",
    "                                 _                      _______                      _                         ",
    "                              _dMMMb._              .adOOOOOOOOOba.              _,dMMMb_                      ",
    "                             dP'  ~YMMb            dOOOOOOOOOOOOOOOb            aMMP~  `Yb                     ",
    "                             V      ~'Mb          dOOOOOOOOOOOOOOOOOb          dM'~      V                     ",
    "                                      `Mb.       dOOOOOOOOOOOOOOOOOOOb       ,dM'                              ",
    "                                       `YMb._   |OOOOOOOOOOOOOOOOOOOOO|   _,dMP'                               ",
    "                                  __     `YMMM| OP'~'YOOOOOOOOOOOP'~`YO |MMMP'     __                          ",
    "                                ,dMMMb.     ~~' OO     `YOOOOOP'     OO `~~     ,dMMMb.                        ",
    "                             _,dP~  `YMba_      OOb      `OOO'      dOO      _aMMP'  ~Yb._                     ",
    "                            <MMP'     `~YMMa_   YOOo   @  OOO  @   oOOP   _adMP~'      `YMM>                   ",
    "                                         `YMMMMM`OOOo     OOO     oOOO'MMMMMP'                                 ",
    "                                 ,aa.     `~YMMb `OOOb._,dOOOb._,dOOO'dMMP~'       ,aa.                        ",
    "                               ,dMYYMba._         `OOOOOOOOOOOOOOOOO'          _,adMYYMb.                      ",
    "                              ,MP'   `YMMba._      OOOOOOOOOOOOOOOOO       _,adMMP'   `YM.                     ",
    "                              MP'        ~YMMMba._ YOOOOPVVVVVYOOOOP  _,adMMMMP~       `YM                     ",
    "                              YMb           ~YMMMMM`OOOOI`````IOOOOO'MMMMMP~           dMP                     ",
    "                               `Mb.           `YMMMb`OOOI,,,,,IOOOO'dMMMP'           ,dM'                      ",
    "                                 `'                  `OObNNNNNdOO'                   `'                        ",
    "                                                      `~OOOOO~'                                                ",
    "                                                                                                               ",
    " ssss    ppppp    aaaaa    ccccc   eeeee     iiiii   n     n   v   v   aaaaa   ddddd   eeeee   rrrrr    ssss   ",
    "s    s   p    p   a   a   c        e           i     nn    n   v   v   a   a   d   d   e       r   r   s    s  ",
    " s       p    p   a   a   c        e           i     n n   n   v   v   a   a   d   d   e       r   r    s      ",
    "  ssss   pppp     aaaaa   c        eee   ---   i     n  n  n   v   v   aaaaa   d   d   eee     rrr       ssss  ",
    "     s   p        a   a   c        e           i     n   n n   v   v   a   a   d   d   e       r r          s  ",
    "s    s   p        a   a   c        e           i     n    nn    v v    a   a   d   d   e       r  r    s    s  ",
    " ssss    p        a   a    ccccc   eeeee     iiiii   n     n     v     a   a   ddd     eeeee   r   r    ssss   ",
    "                                                                                                               ",
    "                                                                                                               "
};

    char menu [5][112] =
    {
    "                                                    MAIN MENU                                                  ",
    "                                                                                                               ",
    "                                                >   PLAY GAME   <                                              ",
    "                                                                                                               ",
    "                                                    EXIT GAME                                                  "
    };

    while(1)
    {
        system("cls");
        system("color 0a");
        for (int y = 0; y < 31; y++)
            cout << title[y]<<endl;
        cout << endl;
        cout << endl;
		for (int y = 0; y < 5; y++)
			cout << menu[y] << endl;

        if(GetAsyncKeyState(VK_UP) != 0 && menu[4][48] == '>')
        {
            menu[4][48] = ' ';
            menu[4][64] = ' ';
            menu[2][48] = '>';
            menu[2][64] = '<';
        }

        if(GetAsyncKeyState(VK_DOWN) != 0 && menu[2][48] == '>')
        {
            menu[2][48] = ' ';
            menu[2][64] = ' ';
            menu[4][48] = '>';
            menu[4][64] = '<';
        }

        if(GetAsyncKeyState(VK_RETURN) != 0)
        {
            if (menu[2][48] == '>')
                levels(title);
            if (menu[4][48] == '>')
                closegame();
        }
    Sleep(refreshrate);
    }
}

void closegame()
{
    system("cls");
    cout << "THANKYOU FOR PLAYING!!!" << endl;
    Sleep(1000);
    exit(0);
}

void scrollup(char levelmenu[15][112], int y)
{
    levelmenu[y][42] = ' ';
    levelmenu[y-2][42] = '>';
    levelmenu[y][66] = ' ';
    levelmenu[y-2][66] = '<';
    Sleep(100);
}

void scrolldown(char levelmenu[15][112], int y)
{
    levelmenu[y][42] = ' ';
    levelmenu[y+2][42] = '>';
    levelmenu[y][66] = ' ';
    levelmenu[y+2][66] = '<';
    Sleep(100);
}

void levelselector(int y)
{
    Sleep(100);
    char map1[20][80]=
{
    "|-----------------------------------------------------------------------------|",
    "|                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|",
    "|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                     |",
    "|                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|",
    "|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                     |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                     W                                       |",
	"|-----------------------------------------------------------------------------|"
};
char map2[20][80]={
    "|-----------------------------------------------------------------------------|",
    "|@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @|",
    "| @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ |",
    "|                                                                             |",
    "|                                                                             |",
    "|@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @|",
    "| @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                     W                                       |",
	"|-----------------------------------------------------------------------------|"
	};
char map3[20][80]={
    "|-----------------------------------------------------------------------------|",
    "|@@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@   |",
    "|@@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@   |",
    "|   @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@|",
    "|   @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@|",
    "|@@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@   |",
    "|@@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@   |",
    "|   @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@|",
    "|   @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@    @@|",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                     W                                       |",
	"|-----------------------------------------------------------------------------|"
	};
char map4[20][80]={
	"------------------------------------------------------------------------------|",
	"|                                                                             |",
	"|                                @ @ @ @ @ @ @ @                              |",
	"|                              @ @ @ @ @ @ @ @ @ @                            |",
	"|                     @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @                     |",
	"|             @ @    @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @  @                   |",
	"|           @ @ @ @    @ @ @ @ @ @ @ @ @ @  @  @ @ @ @ @ @                    |",
	"|         @ @ @ @ @ @         @ @ @          @ @ @               @ @          |",
	"|   @   @ @ @ @ @ @ @ @  @    @ @ @          @ @ @             @ @ @@         |",
	"|  @ @ @ @ @ @ @ @ @ @ @ @ @    @              @      @  @ @ @ @ @ @   @ @    |",
	"|    @  @  @  @  @  @ @ @ @                          @ @ @ @ @ @ @ @ @ @  @   |",
	"|                                                     @ @ @ @ @ @ @ @ @ @     |",
	"|                                                                             |",
	"|                                                                             |",
	"|                                                                             |",
	"|                                                                             |",
	"|                                                                             |",
	"|                                                                             |",
	"|                                      W                                      |",
	"------------------------------------------------------------------------------|"
	};
char map5[20][80]={
"|-----------------------------------------------------------------------------|",
"|                                  @@@@@@@@@                                  |",
"|                                 @@@     @@@                                 |",
"|                                @ @       @ @                                |",
"|                               @   @     @   @                               |",
"|                              @     @@@@@     @                              |",
"|                             @     @ @ @ @     @                             |",
"|                            @       @ @ @       @                            |",
"|                           @         @@@         @                           |",
"|                          @   @   @@@@@@@@@   @   @                          |",
"|                         @    @  @  @   @  @  @    @                         |",
"|                     @@@@    @@@@@@       @@@@@@    @@@@                     |",
"|                    @    @@@@@@@@@@@@@@@@@@@@@@@@@@@    @                    |",
"|                     @                                 @                     |",
"|                      @@@@      @ @ @ @ @ @ @      @@@@                      |",
"|                          @@@@@@@@@@@@@@@@@@@@@@@@@                          |",
"|                             @@@@@@@@@@@@@@@@@@@                             |",
"|                                                                             |",
"|                                     W                                       |",
"|-----------------------------------------------------------------------------|"
};
char BOSS[30][80]={
    "|-----------------------------------------------------------------------------|",
    "|            @                      @@@@@@@@                     @            |",
    "|         @@@@@@@@              @@@@@@@@@@@@@@@              @@@@@@@@         |",
    "|        @@@  @@@@@            @@@@@@@@@@@@@@@@@            @@@@@  @@@        |",
    "|        @      @@@@          @@@@@@@@@@@@@@@@@@@          @@@@      @        |",
    "|                 @@@@       @@@@@@@@@@@@@@@@@@@@@       @@@@                 |",
    "|                  @@@@@@   @@@@@@@@@@@@@@@@@@@@@@@   @@@@@@                  |",
    "|             @@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     @@             |",
    "|           @@@@@@@     @@@ @@     @@@@@@@@@     @@ @@@     @@@@@@@           |",
    "|        @@@@@  @@@@@@      @@@      @@@@@      @@@      @@@@@@  @@@@@        |",
    "|       @@@@@     @@@@@@@   @@@@   @  @@@  @   @@@@   @@@@@@@      @@@@@      |",
    "|                    @@@@@@@@@@@@     @@@     @@@@@@@@@@@@                    |",
    "|            @@@@     @@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@       @@@@           |",
    "|          @@@@@@@@@@         @@@@@@@@@@@@@@@@@@@          @@@@@@@@@@         |",
    "|         @@@@   @@@@@@@@      @@@@@@@@@@@@@@@@@       @@@@@@@@   @@@@        |",
    "|         @@@        @@@@@@@@@ @@@@@@@@@@@@@@@@@  @@@@@@@@@@       @@@        |",
    "|         @@@           @@@@@@@@@@@@@     @@@@@@@@@@@@@@           @@@        |",
    "|          @@@@           @@@@@@@@@@@     @@@@@@@@@@@@           @@@@         |",
    "|            @@                  @@@@@@@@@@@@@                   @@           |",
    "|                                 @@@@@@@@@@@                                 |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                                                             |",
    "|                                      W                                      |",
    "|-----------------------------------------------------------------------------|"
	};
	switch (y)
	{
    case 2:
        game(map1, 1);
    case 4:
        game(map2, 2);
    case 6:
        game(map3, 3);
    case 8:
        game(map4, 4);
    case 10:
        game(map5, 5);
    case 12:
        game(BOSS, 0);
	}
}


