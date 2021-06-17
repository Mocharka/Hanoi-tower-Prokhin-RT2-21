#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void gotoxy (int x, int y){
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
    }

void console_hide_cursor() {                                        //to hide cursor
	HANDLE handle;
	CONSOLE_CURSOR_INFO structCursorInfo;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

int CheckClick(){                                                                       //to get coords of click
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD c;

    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
    while (true)
    {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);

       if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            c.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            c.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
        }
        if ((c.X == 13 && c.Y == 16) || (c.X == 13 && c.Y == 17) || (c.X == 37 && c.Y == 16) || (c.X == 37 && c.Y == 17) || (c.X == 61 && c.Y == 16) || (c.X == 61 && c.Y == 17)) break;
    }
return c.X;
 }

void DrawBars (){                                                                               //to draw bars
gotoxy(0,0);
cout << "Press arrow buttons to move discs." <<endl;
cout << "You need to move the pyramid from the first bar to the third." <<endl;
for (int i = 0; i < 10; i++){
gotoxy(13, 5 + i);
    cout << "|";
gotoxy(37, 5 + i);
    cout << "|";
gotoxy(61, 5 + i);
    cout << "|";
}
gotoxy(13,16);
cout << "^";
gotoxy(13,17);
cout << "|";
gotoxy(37,16);
cout << "^";
gotoxy(37,17);
cout << "|";
gotoxy(61,16);
cout << "^";
gotoxy(61,17);
cout << "|";

};

class Disk{
public:
    int size;
    int position;
    void DrawDisk(int x, int y){
        gotoxy(x-size, y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD) ((15<<4) | 0));
        for (int t = 0; t < 2*size + 1; t++)
            cout << "_";
    };

    void CleanDisk(int x, int y, bool z){
        gotoxy(x-size, y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD) ((0<<4) | 7));
        for (int t = 0; t < 2*size + 1; t++)
        cout <<" ";
        if (z == 0){
        gotoxy(x, y);
        cout <<"|";
        };
    };
};





int main(){
    int number;
    int win;
    int c = 0;
    int nonenull = 0;
    int check;
    int memory;
DrawBars();
gotoxy(0,20);
cout << "Enter quantity of disks (from 1 to  10):";
cin  >> number;
console_hide_cursor();
gotoxy(0, 20);
for (int i = 0; i < 50; i++) {cout << " ";};                                  // to set start position
Disk disk[number];

for (int i = 0; i < number; i++){
    disk[i].size = i+1;
    disk[i].position = 1;
}

for (int i = 0; i < number; i++){
    disk[i].DrawDisk(13, 15 - number + i);
}





while (win < number){                                                           //we need to understand which bar we are working with
switch(CheckClick()){
case 13:

    for (int i = 0; i < number; i++){                                          // if there is a raised disk , it must be put on a bar
        if (disk[i].position == 0){
            check++;
            int min1 = disk[i].size;
            for (int j = 0; j < number; j++){
               if (disk[j].size < min1 && disk[j].position == 1)
                    min1 = disk[j].size;
            };
            if (disk[i].size == min1){
                disk[i].position = 1;

                 for (int k = 0; k < number; k++){
                    if (disk[k].position == 1) c++;

                 };

                disk[i].CleanDisk(memory, 3, 1);
                disk[i].DrawDisk(13, 15 - c);

            };
        };
    };
c = 0;

     for (int i = 0; i < number; i++){                                     // if there is no disk raised, it must be raised
        if (disk[i].position == 0 ) nonenull++;
     };

     if (nonenull == 0 && check == 0) {
        int min2 = 10;

        for (int i = 0; i < number; i++){
            if (disk[i].size < min2 && disk[i].position == 1) min2 = disk[i].size;
        };
        for (int i = 0; i < number; i++){
            if (disk[i].size == min2){
                disk[i].position = 0;

                 for (int k = 0; k < number; k++){
                    if (disk[k].position == 1) c++;
                 };
                disk[i].CleanDisk(13, 14 - c, 0 );
                disk[i].DrawDisk(13, 3);
            };
        };

        memory = 13;

     };
nonenull = 0;
c = 0;
check = 0;
    break;
case 37:

    for (int i = 0; i < number; i++){
        if (disk[i].position == 0){
            check++;
            int min3 = disk[i].size;
            for (int j = 0; j < number; j++){
               if (disk[j].size < min3 && disk[j].position == 2)
                    min3 = disk[j].size;
            };
            if (disk[i].size == min3){
                disk[i].position = 2;

                 for (int k = 0; k < number; k++){
                    if (disk[k].position == 2) c++;

                 };

                disk[i].CleanDisk(memory, 3, 1);
                disk[i].DrawDisk(37, 15 - c);

            };
        };
    };
c = 0;
     for (int i = 0; i < number; i++){
        if (disk[i].position == 0 ) nonenull++;
     };

     if (nonenull == 0 && check == 0) {
        int min4 = 10;

        for (int i = 0; i < number; i++){
            if (disk[i].size < min4 && disk[i].position == 2) min4 = disk[i].size;
        };
        for (int i = 0; i < number; i++){
            if (disk[i].size == min4){
                disk[i].position = 0;

                 for (int k = 0; k < number; k++){
                    if (disk[k].position == 2) c++;
                 };
                disk[i].CleanDisk(37, 14 - c, 0 );
                disk[i].DrawDisk(37, 3);
            };
        };

        memory = 37;

     };
nonenull = 0;
c = 0;
check = 0;
    break;
case 61:

    for (int i = 0; i < number; i++){
        if (disk[i].position == 0){
            check++;
            int min5 = disk[i].size;
            for (int j = 0; j < number; j++){
               if (disk[j].size < min5 && disk[j].position == 3)
                    min5 = disk[j].size;
            };
            if (disk[i].size == min5){
                disk[i].position = 3;

                 for (int k = 0; k < number; k++){
                    if (disk[k].position == 3) c++;

                 };

                disk[i].CleanDisk(memory, 3, 1);
                disk[i].DrawDisk(61, 15 - c);
                win++;
            };
        };
    };
c = 0;
     for (int i = 0; i < number; i++){
        if (disk[i].position == 0 ) nonenull++;
     };

     if (nonenull == 0 && check == 0) {
        int min6 = 10;

        for (int i = 0; i < number; i++){
            if (disk[i].size < min6 && disk[i].position == 3) min6 = disk[i].size;
        };
        for (int i = 0; i < number; i++){
            if (disk[i].size == min6){
                disk[i].position = 0;

                 for (int k = 0; k < number; k++){
                    if (disk[k].position == 3 ) c++;
                 };
                disk[i].CleanDisk(61, 14 - c, 0 );
                disk[i].DrawDisk(61, 3);
                win --;
            };
        };

        memory = 61;

     };
nonenull = 0;
c = 0;
check = 0;
    break;

}
}
                                                                                            //the game continues until there are three disks on the 3rd bar


gotoxy(0, 20);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD) ((0<<4) | 7));
cout << "YOU WIN!!!" << endl;
return  0;
}
