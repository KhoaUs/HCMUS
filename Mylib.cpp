#include "Mylib.h"

//Ham chinh van hanh toan bo
void Operating_System()
{
    //Khai bao mang Arr luu cac gia tri cua tung o trong bang 2D, sub_arr mang lưu cac loai Pokemon va so luong cua no
    Board Pikachu;
    Pikachu.Arr = NULL;
    Pikachu.sub_arr = NULL;

    //Khoi tao de ramdo gia tri cua cac pokemon
    srand(time(NULL));

    cout << "Hay bat full man hinh de co trai nghiem tot nhat! " << endl;
    system("pause");
    system("cls");

    //Goi ham xu ly chinh
    play(Pikachu);

    //Thu hoi bo nho
    deleleDinamicArr (Pikachu);
    delete[] Pikachu.Arr;
    delete[] Pikachu.sub_arr;
}

void play(Board& Pikachu)
{
    int middle, rows, start_point;

    //khoi tao diem bat dau cua bang
    Coordinate pos_menu;

    //Tinh kich thuoc console
    calculateColumnsConsole(middle, rows);

    //Khai bao bien start_point cho bang, pos_menu cho toa do cua menu
    pos_menu.x = middle - 3;
    pos_menu.y = 21;

    drawMenu(middle);

    bool check = true;
    while (true)
    {
        if(_kbhit())
        {
            char c = _getch();
            check = true;

            gotoXY(pos_menu.x, pos_menu.y);
            cout << "__________";

            gotoXY(pos_menu.x, pos_menu.y - 2);
            cout << "__________";

            if (check)
            {
                if(c == 72)
                {
                    if(pos_menu.y == 21)
                    {
                        pos_menu.y = 21 + 8;
                    }
                    else
                    {
                        pos_menu.y -= 2;
                    }

                    selectOption(pos_menu);

                    //Kiểm tra điều kiện để tránh in dư tại vị trí đáy
                    if(pos_menu.y != 29)
                    {
                        gotoXY(pos_menu.x, pos_menu.y + 2);
                        cout << "__________";
                    }
                    check = false;
                }

                if(c == 80)
                {
                    if(pos_menu.y == 29)
                    {
                        pos_menu.y = 29 - 8;
                    }
                    else
                    {
                        pos_menu.y += 2;
                    }

                    selectOption(pos_menu);
                    gotoXY(pos_menu.x, pos_menu.y - 2);
                    cout << "__________";
                    check = false;
                }

                if (c == 13 || c == 32)
                {
                        break;
                }
            }
        }
    }
    switch (pos_menu.y)
    {
        case 21:
            //cho nguoi choi chon do kho
            system("cls");
            selectLevel (middle, Pikachu.size);

            start_point = middle - Pikachu.size * 4;
            setValueBoard (Pikachu);
            drawBoard(Pikachu, start_point);
            operateBoard(Pikachu, start_point);
            play(Pikachu);
            break;
        case 23:
            //dan toi trang dang nhap de nhap tai khoan
            //de quay lai menu bap esc hoac chon "tro ve"
            system("cls");
            start_point = middle - Pikachu.size * 4;
            drawBoard(Pikachu, start_point);
            operateBoard(Pikachu, start_point);
            play(Pikachu);
            break;
        case 25:
            //dan toi trang dang nhap de nhap tai khoan, va hien thi thanh tich nguoi choi
            //de quay lai menu bap esc hoac chon "tro ve"
            break;
        case 27:
            //hien thi BXH, de quay lai menu bap esc hoac chon "tro ve"
            break;
        case 29:
            //thoat
            system("cls");
            break;
        default:
            cout << "Loi he thong, vui long reset va bao voi doi ngu ho tro!" << endl;
            break;
    }
}

void operateBoard (Board& Pikachu, int start_point)
{
    char c;
    int temp = 0, NumberofPokemon = Pikachu.size * Pikachu.size;

    //Khoi tao gia tri ban dau cua cac diem de khoi chay bang
    Pikachu.select = {-1, -1};
    Pikachu.cur = {1, 1};
    Pikachu.old = {1, 1};

    //To mau vung chon dau tien
    highLightBlock(Pikachu.cur, Pikachu.Arr, 143, start_point);

    while (true)
    {
        c = _getch();
        Pikachu.old.x = Pikachu.cur.x;
        Pikachu.old.y = Pikachu.cur.y;
        //Di chuyen len
        if(c == 72 || c == 'w' || c == 'W')
         {
             if(Pikachu.cur.y == 1)
             {
                 Pikachu.cur.y = Pikachu.size;
             }
             else
             {
                 Pikachu.cur.y--;
             }
         }
         //Di chuyen xuong
         if(c == 80 || c == 's' || c == 'S')
         {
             if(Pikachu.cur.y == Pikachu.size)
             {
                 Pikachu.cur.y = 1;
             }
             else
             {
                 Pikachu.cur.y++;
             }
         }
        //Di chuyen trai
         if(c == 75 || c == 'a' || c == 'A')
        {
            if(Pikachu.cur.x == 1)
            {
                Pikachu.cur.x = Pikachu.size;
            }
            else
            {
                Pikachu.cur.x--;
            }
        }
        //Di chuyen phai
        if(c == 77 || c == 'D' || c == 'd')
        {
            if(Pikachu.cur.x == Pikachu.size)
            {
                Pikachu.cur.x = 1;
            }
            else
            {
                Pikachu.cur.x++;
            }
        }
        //Tai lai neu man hinh hien thi loi
        if(c == 'r' || c == 'R')
        {
            system("cls");
            drawBoard(Pikachu, start_point);
        }
        //Enter hoac Space
        if(c == 13 || c == 32)
        {
            if(Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y] != -1)   //Neu o co Pikachu
            {
                highLightBlock(Pikachu.cur, Pikachu.Arr, 177, start_point);
                if(Pikachu.select.x == -1 && Pikachu.select.y == -1)   //Neu chua luu Pokemon nao
                {
                    Pikachu.select.x = Pikachu.cur.x;   //Luu vi tri Pokemon
                    Pikachu.select.y = Pikachu.cur.y;
                }
                else if(Pikachu.select.x != -1 && Pikachu.select.y != -1)   //Neu trong select da co Pokemon
                {
                    //So sanh 2 Pokemon co giong nhau khong
                    if(Pikachu.Arr[Pikachu.select.x][Pikachu.select.y] == Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y])
                    {
                        matchWholeShape (Pikachu, start_point, temp);
                        //Da match
                        if(temp == 1)
                        {
                            //Xoa khung
                            drawRec((start_point + 9 * (Pikachu.select.x - 1)) , (5 + 5 * (Pikachu.select.y - 1)), (start_point + 9 * (Pikachu.select.x - 1) + 8), (9 + 5 * (Pikachu.select.y - 1)), ' ', ' ');
                            drawRec((start_point + 9 * (Pikachu.cur.x - 1)) , (5 + 5 * (Pikachu.cur.y - 1)), (start_point + 9 * (Pikachu.cur.x - 1) + 8), (9 + 5 * (Pikachu.cur.y - 1)), ' ', ' ');

                            //Danh dau vi tri da xoa va xoa mau
                            Pikachu.Arr[Pikachu.select.x][Pikachu.select.y] = -1;
                            Pikachu.Arr[Pikachu.cur.x][Pikachu.cur.y] = -1;

                            //Xoa mau vung da match
                            highLightBlock(Pikachu.select, Pikachu.Arr, 0, start_point);
                            highLightBlock(Pikachu.cur, Pikachu.Arr, 177, start_point);
                            //Reset toa do vung chon
                            Pikachu.select = {-1, -1};
                            //Tru so luong Pokemon con lai trong bang
                            NumberofPokemon -= 2;
                            //reset gia tri temp
                            temp = 0;

                            if (NumberofPokemon == 0)
                            {
                                gotoXY (start_point + Pikachu.size * 4, 30);
                                cout << "WIN WIN CHICKEN LEGGGG!!!";
                                _getch();
                                system("cls");
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                gotoXY(0, 0);
                cout << "Khong co Pikachu de chon!";
                Sleep(300);
                gotoXY(0, 0);
                cout << "                         ";
            }

        }
        //Esc de thoat
        if(c == 27)
        {
            system("cls");
            break;
        }
        //Ktra xem co di chuyen chua
        if (Pikachu.cur.x != Pikachu.old.x || Pikachu.cur.y != Pikachu.old.y )
        {
            //Tranh to lai mau mac dinh cho o da chon
            if (Pikachu.select.x == Pikachu.cur.x && Pikachu.select.y == Pikachu.cur.y)
            {
                //To mau khac biet khi di lai vung da chon mot lan nua
                highLightBlock(Pikachu.cur, Pikachu.Arr, 199, start_point);
                c = _getch();
                if(c == 13 || c == 32 || c == 'b')
                {
                    Pikachu.select = {-1, -1};
                    gotoXY(0, 0);
                    cout << "Da bo chon            ";
                    Sleep (200);
                    gotoXY(0, 0);
                    cout << "                      ";
                }
            }
            else
            {
                //To mau vung con tro
                highLightBlock(Pikachu.cur, Pikachu.Arr, 143, start_point);
            }

            if (Pikachu.old.x != Pikachu.select.x || Pikachu.old.y != Pikachu.select.y)
            {
                //To lai mau mac dinh sau khi di chuyen
                highLightBlock(Pikachu.old, Pikachu.Arr, 14, start_point);
            }
            else
            {
                //Xu ly sau khi di qua lai o da chon mot lan nua
                highLightBlock(Pikachu.old, Pikachu.Arr, 177, start_point);
            }
            gotoXY(1, 1);
            cout << Pikachu.cur.x << ", " << Pikachu.cur.y;
        }
    }
    Sleep(100);
}

void resetBoard (Board& Pikachu)
{
    for (int i = 1; i <= Pikachu.size; i++)
    {
        for (int j = 1; j <= Pikachu.size; j++)
        {
            if (Pikachu.Arr[i][j] < 0 && Pikachu.Arr[i][j] != -1)
            {
                Pikachu.Arr[i][j] = -1;
            }
        }
    }
}

void selectLevel (int middle, int &size)
{
    int left;
    Coordinate pos_menu;

    left = middle - 7;
    pos_menu.x = middle - 3;
    pos_menu.y = 21;

    drawFrame (left, 20, "    KHO");
    drawFrame (left, 22, " TRUNG BINH");
    drawFrame (left, 24, "     DE");
    selectOption(pos_menu);

    bool check = true;
    while (true)
    {
        if(_kbhit())
        {
            char c = _getch();
            check = true;

            gotoXY(pos_menu.x, pos_menu.y);
            cout << "__________";

            gotoXY(pos_menu.x, pos_menu.y - 2);
            cout << "__________";

            if (check)
            {
                //Di chuyen len
                if(c == 72)
                {
                    //neu da gap dinh, thi con tro nhay xuong duoi day
                    if(pos_menu.y == 21)
                    {
                        pos_menu.y = 25;
                    }
                    else
                    {
                        pos_menu.y -= 2;
                    }

                    selectOption(pos_menu);

                    //Kiểm tra điều kiện để tránh in dư tại vị trí đáy
                    if(pos_menu.y != 25)
                    {
                        gotoXY(pos_menu.x, pos_menu.y + 2);
                        cout << "__________";
                    }
                    check = false;
                }
                //Di chuyen xuong
                if(c == 80)
                {
                    //Neu cham day, con tro tu tro len dau
                    if(pos_menu.y == 25)
                    {
                        pos_menu.y = 21;
                    }
                    else
                    {
                        pos_menu.y += 2;
                    }

                    selectOption(pos_menu);
                    gotoXY(pos_menu.x, pos_menu.y - 2);
                    cout << "__________";
                    check = false;
                }
                //Neu chon bang enter hoac space
                if (c == 13 || c == 32)
                {
                        break;
                }
            }
        }
    }

    switch(pos_menu.y)
    {
    case 21:
        size = 8;
        break;
    case 23:
        size = 6;
        break;
    case 25:
        size = 4;
        break;
    default:
        cout << "Loi he thong!" << endl;
    }
    system("cls");
}

//Ham ve bang
void drawBoard (Board Pikachu, int start_point)
{
    for (int j = 0; j < Pikachu.size; j++)
    {
        for (int i = 0; i < Pikachu.size; i++)
        {
            //Chon mau khung
            if(Pikachu.Arr[i + 1][j + 1] != -1)
            {
                //Chon mau khung
                changeColor (FOREGROUND_INTENSITY);
                drawRec((start_point + 9 * i ), (5 + 5 * j), (start_point + 9 * i + 8), (9 + 5 * j), '-', '|');

                //Chon mau chu
                changeColor (Pikachu.Arr[i + 1][j + 1] | FOREGROUND_INTENSITY);
                gotoXY (start_point + 9 * i  + 4, 5 + 5 * j + 2);
                cout << char('A' + Pikachu.Arr[i + 1][j + 1]);
            }
        }
    }
}


void changeColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//Ham tinh kich thuoc man hinh console
void calculateColumnsConsole(int &middle, int &rows)
{
    //CONSOLE_SCREEN_BUFFER_INFO la mot kieu du lieu chua thong tin ve bo dem man hinh
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //Ham GetConsoleScreenBufferInfo se lay thong tin bo dem man hinh console, bien csbi se luu thong tin kich thuoc va vi tri cua man hinh console
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    middle = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

//Khoi tao gia tri bang
void setValueBoard (Board& Pikachu)
{
    //Khai bao bien count de dem so luong pokemon da set, Pikachu.sub_size de luu so loai pokemon
    int count = 0;
    Pikachu.sub_size = Pikachu.size * 2;

    //Cap phat dong cho mang
    Pikachu.Arr = new int *[Pikachu.size + 2];
    Pikachu.sub_arr = new int [Pikachu.sub_size];

    //Set so luong cua cac loai pokemon ban dau la 0, vi chua co pokemon nao
    for (int i = 0; i < Pikachu.sub_size; i++)
    {
        Pikachu.sub_arr[i] = 0;
    }

    //muc dich tao ra mot hinh chu nhat phu ben ngoai de ho tro matching
    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        Pikachu.Arr[i] = new int [Pikachu.size + 2];
    }

    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        for(int j = 0; j <= Pikachu.size + 1; j++)
        {
            if (i == 0 || j == 0 || i == Pikachu.size + 1 || j == Pikachu.size + 1)
            {
                Pikachu.Arr[j][i] = -1;
            }
            else
            {
                //De lai mot so luong Pikachu.sub_size phan tu de lam chan so luong cac pokemon
                if (count < (Pikachu.size * Pikachu.size - Pikachu.sub_size))
                {
                    //random cac loai pokemon va dem so luong da ramdon
                    Pikachu.Arr[j][i] = rand() % Pikachu.sub_size;
                    count++;

                    //Dem so luong cac loai pokemon, chi so index trong mang sub_arr ung voi gia tri cua pokemon, con gia tri tai index do se ung voi so luong loai do
                    Pikachu.sub_arr[Pikachu.Arr[j][i]]++;
                }
                //chi random den mot so luong Pikachu.size * Pikachu.size - Pikachu.sub_size sau do ktra xem pokemon nao dang le thi se tang them mot, neu khong con pokemon nao le, se tao so le sau do lam chan
                else
                {
                    int sub_count = count;
                    for (int p = 0; p < Pikachu.sub_size; p++)
                    {
                        if ((Pikachu.sub_arr[p] % 2) != 0 )
                        {
                            //neu so luong cua loai pokemon p la le, se tang len 1 de lam chan
                            Pikachu.Arr[j][i] = p;
                            Pikachu.sub_arr[p]++;

                            //tang bien sub_count de khang dinh rang con pokemon co so luong le
                            sub_count++;
                            break;
                        }
                    }

                    //Neu nhu khong con pokemon nao le, hay lam cho no le :D
                    if (sub_count == count)
                    {
                        //random va dem so luong cac loai pokemon
                        Pikachu.Arr[j][i] = rand() % Pikachu.sub_size;
                        Pikachu.sub_arr[Pikachu.Arr[j][i]]++;
                    }
                    count++;
                }
            }
        }
    }
}

//Ham tro con tro van ban den vi tri co toa do x, y
void gotoXY(int x, int y){
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{x,y});
}


void drawLine (Board& Pikachu, int start_point)
{
    for (int i = 0; i < 4; i++)
    {
        int color;
        if (i % 2 == 0)
        {
            changeColor (FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            color = 174;
        }
        else
        {
            changeColor (FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            color = 177;
        }

        for (int i = 1; i <= Pikachu.size; i++)
        {
            for (int j = 1; j <= Pikachu.size; j++)
            {
                if (Pikachu.Arr[i][j] == -2)
                {
                    gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                    cout << ">>>>>>>>>";
                }

                if (Pikachu.Arr[i][j] == -3)
                {
                    for (int k = 0; k < 5; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                    cout << char(166);
                    }
                }

                if (Pikachu.Arr[i][j] == -4)
                {
                    for (int k = 3; k < 5; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                    cout << ">>>>>";
                }

                if (Pikachu.Arr[i][j] == -5)
                {
                    for (int k = 0; k < 2; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                    cout << ">>>>>";
                }

                if (Pikachu.Arr[i][j] == -6)
                {
                    for (int k = 0; k < 2; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                    cout << "    >>>>>";
                }

                if (Pikachu.Arr[i][j] == -7)
                {
                    for (int k = 3; k < 5; k++)
                    {
                    gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                    cout << char(166);
                    }
                    gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                    cout << "    >>>>>";
                }
            }
        }
        highLightBlock(Pikachu.select, Pikachu.Arr, color, start_point);
        highLightBlock(Pikachu.cur, Pikachu.Arr, color, start_point);
        Sleep(100);
    }
    resetBoard (Pikachu);
    for (int i = 1; i <= Pikachu.size; i++)
    {
        for (int j = 1; j <= Pikachu.size; j++)
        {
            if (Pikachu.Arr[i][j] == -1)
            {
                for (int k = 0; k < 5; k++)
                {
                    gotoXY((start_point + 9 * (i - 1)), (5 + 5 * (j - 1)+ k));
                    cout << "         ";
                }
            }
        }
    }
}

bool matchShapeI(Board& Pikachu)
{
    //Kiem tra xem hai toa do co trung nhau khong truoc do trong ham cha
    //Kiem tra co cung hang, hay cung cot hay khong
    //Truong hop cung truc Oy
    if (Pikachu.cur.y == Pikachu.select.y)
    {
        if(Pikachu.cur.x > Pikachu.select.x)
        {
            for (int i = Pikachu.select.x + 1; i < Pikachu.cur.x; i++)
            {
                if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[i][Pikachu.cur.y] = -2;
            }
            return 1;
        }
        else
        {
            for (int i = Pikachu.select.x - 1; i > Pikachu.cur.x; i--)
            {
                if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[i][Pikachu.cur.y] = -2;
            }
            return 1;
        }
    }

    //Truong hop trung truc Ox
    else if (Pikachu.cur.x == Pikachu.select.x)
    {
        if(Pikachu.cur.y > Pikachu.select.y)
        {
            for (int i = Pikachu.select.y + 1; i < Pikachu.cur.y; i++)
            {
                if(Pikachu.Arr[Pikachu.cur.x][i] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[Pikachu.cur.x][i] = -3;
            }
            return 1;
        }
        else
        {
            for (int i = Pikachu.select.y - 1; i > Pikachu.cur.y; i--)
            {
                if (Pikachu.Arr[Pikachu.cur.x][i] != -1)
                {
                    resetBoard (Pikachu);
                    return 0;
                }
                Pikachu.Arr[Pikachu.cur.x][i] = -3;
            }
            return 1;
        }
    }
    return 0;
}

bool matchShapeL(Board& Pikachu)
{
    if (Pikachu.cur.x == Pikachu.select.x || Pikachu.cur.y == Pikachu.select.y)
    {
        return 0;
    }

    //Chia lam 4 trương hop cho loai nay, khi select ben phai cua Pikachu.cur
    if(Pikachu.cur.x < Pikachu.select.x && Pikachu.cur.y > Pikachu.select.y)
    {

        //Truong hop 1: ngang - len: NGANG
        for (int i = Pikachu.cur.x + 1; i <= Pikachu.select.x; i++)
        {

            //Truong hop 2: len - ngang, neu gap o khong trong se vao TH2 de xet tiep
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau truoc do cho viec Matching
                for (int t = Pikachu.cur.y - 1; t >= Pikachu.select.y; t--)
                {
                    if (Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau truoc do cho viec Matching
                        return 0;
                    }

                    Pikachu.Arr[Pikachu.cur.x][t] = -3;  //Danh dau duong thang len
                }
                for (int p = Pikachu.cur.x + 1; p < Pikachu.select.x; p++)
                {
                    if (Pikachu.Arr[p][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }

                    Pikachu.Arr[p][Pikachu.select.y] = -2;   //Danh dau de ve duong thang ngang qua
                }

                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -7;   //Danh dau giao diem
                return 1;
            }

            Pikachu.Arr[i][Pikachu.cur.y] = -2;  //Danh dau hang ngang de ve matching
        }

        //LEN
        for (int j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
        {
            if (Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
        }

        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -5; //Danh dau giao diem
        return 1;
    }

    //Truong hop 3 + 4
    if (Pikachu.cur.x < Pikachu.select.x && Pikachu.cur.y < Pikachu.select.y)
    {
        //Truong hop 3: ngang - xuong: NGANG
        for (int i = Pikachu.cur.x + 1; i <= Pikachu.select.x; i++)
        {

            //Truong hop 4: xuong - ngang, neu gap o khong trong, se xet vao TH4
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau truoc do cho viec Matching
                for (int t = Pikachu.cur.y + 1; t <= Pikachu.select.y; t++)
                {
                    if (Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[Pikachu.cur.x][t] = -3;   //Danh dau hang doc
                }
                for (int p = Pikachu.cur.x + 1; p < Pikachu.select.x; p++)
                {
                    if (Pikachu.Arr[p][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[p][Pikachu.select.y] = -2;      //Danh dau hang ngang
                }

                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -6;      //Danh dau giao diem
                return 1;
            }

            Pikachu.Arr[i][Pikachu.cur.y] = -2;  //Danh dau hang ngang
        }

        //XUONG
        for (int j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
        {
            if (Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
            Pikachu.Arr[Pikachu.select.x][j] = -3; //Danh dau hang doc
        }
        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -4;  //Danh dau giao diem
        return 1;
    }

    //Chia 4 truong hop 5 - 8 cho viec select ben trai cur
    //TH 5 + 6
    //Th 5: Ngang - len
    if (Pikachu.cur.x > Pikachu.select.x && Pikachu.cur.y > Pikachu.select.y)
    {
        //NGANG
        for(int i = Pikachu.cur.x - 1; i >= Pikachu.select.x; i--)
        {
            //Th6: Len - ngang: Neu di ngang gap o khong trong se vao TH6
            if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                //LEN
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                for (int t = Pikachu.cur.y - 1; t >= Pikachu.select.y; t--)
                {
                    if(Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[Pikachu.cur.x][t] = -3;
                }
                //NGANG
                for (int k = Pikachu.cur.x -  1; k > Pikachu.select.x; k--)
                {
                    if(Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[k][Pikachu.select.y] = -2;      //Danh dau hang ngang
                }
                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -4;   //Danh dau giao diem
                return 1;
            }
            Pikachu.Arr[i][Pikachu.cur.y] = -2;     //Danh dau hang ngang
        }

        //LEN
        for (int j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
        {
            if (Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
            Pikachu.Arr[Pikachu.select.x][j] = -3;      //Danh dau hang doc
        }
        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -6;     //Danh dau giao diem
        return 1;
    }

    //Th 7 - 8
    //Th 7: Ngang - xuong
    if (Pikachu.cur.x > Pikachu.select.x && Pikachu.cur.y < Pikachu.select.y)
    {
        //NGANG
        for (int i = Pikachu.cur.x - 1; i >= Pikachu.select.x; i--)
        {

            //Th8: xuong - ngang; gap o khong trong se vao TH8
            if(Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                //XUONG
                resetBoard (Pikachu);   //Reset lai cac vung du lieu da danh dau
                for (int t = Pikachu.cur.y + 1; t <= Pikachu.select.y; t++)
                {
                    if (Pikachu.Arr[Pikachu.cur.x][t] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[Pikachu.cur.x][t] = -3;     //Danh dau hang doc
                }

                //ngang
                for (int k = Pikachu.cur.x - 1; k > Pikachu.select.x; k--)
                {
                    if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                        return 0;
                    }
                    Pikachu.Arr[k][Pikachu.select.y] = -2;      //Danh dau hang ngang
                }
                Pikachu.Arr[Pikachu.cur.x][Pikachu.select.y] = -5;      //Danh dau giao diem
                return 1;
            }
            Pikachu.Arr[i][Pikachu.cur.y] = -2;     //Danh dau hang ngang
        }
        //XUONG
        for (int j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
        {
            if(Pikachu.Arr[Pikachu.select.x][j] != -1)
            {
                resetBoard (Pikachu); //Reset lai cac vung du lieu da danh dau
                return 0;
            }
            Pikachu.Arr[Pikachu.select.x][j] = -3;      //Danh dau hang doc
        }
        Pikachu.Arr[Pikachu.select.x][Pikachu.cur.y] = -7;    //Danh dau giao diem
        return 1;
    }
    resetBoard (Pikachu); //Double check!
    return 0;
}

bool matchShapeZ (Board& Pikachu)
{

    //Se co 8 truong hop, tuong tu L
    //De ap dung loai Z, hai diem khong duoc thang hang
    if (Pikachu.cur.x == Pikachu.select.x || Pikachu.cur.y == Pikachu.select.y)
    {
        return 0;
    }

    //Gop 8 truong hop thanh 4 truong hop bang cach ep vi tri co toa do x nho hon thanh vi tri cua Pikachu.cur, sau do xet tu trai sang phai
    if (Pikachu.cur.x > Pikachu.select.x)
    {

        //Khai bao 2 bien tam de luu thong tin cho buoc xu ly tiep theo
        Coordinate temp;
        temp.x = Pikachu.cur.x;
        temp.y = Pikachu.cur.y;

        Pikachu.cur.x = Pikachu.select.x;
        Pikachu.cur.y = Pikachu.select.y;

        Pikachu.select.x = temp.x;
        Pikachu.select.y = temp.y;
    }

    //select ben tren
    if (Pikachu.cur.y > Pikachu.select.y)
    {

        //th1: ngang - len - ngang
        for (int i = Pikachu.cur.x + 1; i < Pikachu.select.x; i++)
        {
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                break;
            }
            else
            {
                int j;
                for (j = Pikachu.cur.y - 1; j > Pikachu.select.y; j--)
                {
                    if(Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if(j == Pikachu.select.y)
                {
                    int k = i;
                    for (k; k < Pikachu.select.x; k++)
                    {
                        if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        return 1;
                    }
                }
            }
        }

        //th2: len - ngang - len
        for(int i = Pikachu.cur.y - 1; i > Pikachu.select.y; i--)
        {
            if(Pikachu.Arr[Pikachu.cur.x][i] != -1)
            {
                break;
            }
            else
            {
                int j = Pikachu.cur.x + 1;
                for(; j < Pikachu.select.x; j++)
                {
                    if(Pikachu.Arr[j][i] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.x)
                {
                    int k = i;
                    for(; k > Pikachu.select.y; k--)
                    {
                        if(Pikachu.Arr[Pikachu.select.x][k] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.y)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    //Pikachu.select ben duoi Pikachu.cur
    else if (Pikachu.cur.y < Pikachu.select.y)
    {

        //th3: ngang - xuong - ngang
        for (int i = Pikachu.cur.x + 1; i < Pikachu.select.x; i++)
        {
            if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
            {
                break;
            }
            else
            {
                int j;
                for (j = Pikachu.cur.y + 1; j < Pikachu.select.y; j++)
                {
                    if(Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if(j == Pikachu.select.y)
                {
                    int k = i;
                    for (k; k < Pikachu.select.x; k++)
                    {
                        if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        return 1;
                    }
                }
            }
        }

        //th4: xuong - ngang - xuong
        for(int i = Pikachu.cur.y + 1; i < Pikachu.select.y; i++)
        {
            if(Pikachu.Arr[Pikachu.cur.x][i] != -1)
            {
                break;
            }
            else
            {
                int j = Pikachu.cur.x + 1;
                for(; j < Pikachu.select.x; j++)
                {
                    if(Pikachu.Arr[j][i] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.x)
                {
                    int k = i;
                    for(; k < Pikachu.select.y; k++)
                    {
                        if(Pikachu.Arr[Pikachu.select.x][k] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.y)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

bool matchShapeU (Board& Pikachu)
{

    //Hoan doi vi tri sao cho vi tri diem Pikachu.select luon ben phai cua Pikachu.cur
    if (Pikachu.cur.x > Pikachu.select.x)
    {
        //Khai bao 2 bien tam de luu thong tin cho buoc xu ly tiep theo
        Coordinate temp;

        temp.x = Pikachu.cur.x;
        temp.y = Pikachu.cur.y;

        Pikachu.cur.x = Pikachu.select.x;
        Pikachu.cur.y = Pikachu.select.y;

        Pikachu.select.x = temp.x;
        Pikachu.select.y = temp.y;
    }

    //Th1 : len - ngang - xuong
    for (int i = Pikachu.cur.y - 1; i >= 0; i--)
    {
        if (Pikachu.Arr[Pikachu.cur.x][i] != -1)
        {
            break;
        }
        int j = Pikachu.cur.x + 1;
        for (; j < Pikachu.select.x; j++)
        {
            if (Pikachu.Arr[j][i] != -1)
            {
                break;
            }
        }
        if (j == Pikachu.select.x)
        {
            int k = i;
            for (; k < Pikachu.select.y; k++)
            {
                if (Pikachu.Arr[Pikachu.select.x][k] != -1)
                {
                    break;
                }
            }
            if (k == Pikachu.select.y)
            {
                return 1;
            }
        }
    }

    //Th2: Xuong - ngang - len
    for (int i = Pikachu.cur.y + 1; i <= Pikachu.size + 1; i++)
    {
        if (Pikachu.Arr[Pikachu.cur.x][i] != -1)
        {
            break;
        }

        //Ngang;
        int j = Pikachu.cur.x + 1;
        for (; j < Pikachu.select.x; j++)
        {
            if(Pikachu.Arr[j][i] != -1)
            {
                break;
            }
        }
        if (j == Pikachu.select.x)
        {

            //len
            int k = i;
            for (; k > Pikachu.select.y; k--)
            {
                if (Pikachu.Arr[j][k] != -1)
                {
                    break;
                }
            }
            if(k == Pikachu.select.y)
            {
                return 1;
            }
        }
    }

    //Th3: ngang qua phai
    for (int i = Pikachu.cur.x + 1; i <= Pikachu.size + 1; i++)
    {
        if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
        {
            break;
        }

        //Duyet ngang qua phai den khi nao i vuot qua Pikachu.select.x
        if (i > Pikachu.select.x)
        {

            //truong hop Pikachu.select nam ben tren cua Pikachu.cur --> di len
            if (Pikachu.cur.y > Pikachu.select.y)
            {
                int j = Pikachu.cur.y - 1;
                for (; j > Pikachu.select.y; j--)
                {
                    if (Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.y)
                {
                    int k = i;
                    for (; k > Pikachu.select.x; k--)
                    {
                        if (Pikachu.Arr[k][j] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        return 1;
                    }
                }
            }

            //truong hop Pikachu.select nam ben duoi cua Pikachu.cur
            if (Pikachu.cur.y < Pikachu.select.y)
            {
                int j = Pikachu.cur.y + 1;
                for (; j < Pikachu.select.y; j++)
                {
                    if (Pikachu.Arr[i][j] != -1)
                    {
                        break;
                    }
                }
                if (j == Pikachu.select.y)
                {
                    int k = i;
                    for (; k > Pikachu.select.x; k--)
                    {
                        if (Pikachu.Arr[k][j] != -1)
                        {
                            break;
                        }
                    }
                    if (k == Pikachu.select.x)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    //Th4 ngang qua trai
    for (int i = Pikachu.cur.x - 1; i >= 0; i--)
    {
        if (Pikachu.Arr[i][Pikachu.cur.y] != -1)
        {
            break;
        }

        //truong hop Pikachu.select nam duoi Pikachu.cur
        if (Pikachu.cur.y < Pikachu.select.y)
        {
            int j = Pikachu.cur.y + 1;
            for (; j < Pikachu.select.y; j++)
            {
                if (Pikachu.Arr[i][j] != -1)
                {
                    break;
                }
            }

            //neu duyet duoc toi vi tri toa do bang Pikachu.select.y thi tiep tuc duyet ngang
            if (j == Pikachu.select.y)
            {
                int k = i;
                for (; k < Pikachu.select.x; k++)
                {
                    if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        break;
                    }
                }
                if (k == Pikachu.select.x)
                {
                    return 1;
                }
            }
        }

        //Truong hop Pikachu.select nam tren Pikachu.cur
        else if (Pikachu.cur.y > Pikachu.select.y)
        {
            int j = Pikachu.cur.y - 1;
            for (; j > Pikachu.select.y; j--)
            {
                if (Pikachu.Arr[i][j] != -1)
                {
                    break;
                }
            }

            //neu duyet duoc toi vi tri toa do bang Pikachu.select.y thi tiep tuc duyet ngang
            if (j == Pikachu.select.y)
            {
                int k = i;
                for (; k < Pikachu.select.x; k++)
                {
                    if (Pikachu.Arr[k][Pikachu.select.y] != -1)
                    {
                        break;
                    }
                }
                if (k == Pikachu.select.x)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void matchWholeShape (Board& Pikachu, int start_point, int& temp)
 {

     //Trung vi tri thi in ra thong bao va ngung xu ly
     if (Pikachu.cur.x == Pikachu.select.x && Pikachu.cur.y == Pikachu.select.y)
     {
         gotoXY (0, 0);
         cout << "Khong duoc chon lai vi tri cu!   ";

     }
     else
     {
        if(matchShapeI(Pikachu))
        {
            gotoXY (0, 0);
            cout << "Match loai I                   ";
            drawLine(Pikachu, start_point);

            temp = 1;
        }
        else if(matchShapeL(Pikachu))
        {
            gotoXY (0, 0);
            cout << "Match loai L                  ";
            drawLine(Pikachu, start_point);

            temp = 1;
        }
        else if(matchShapeZ(Pikachu))
        {
            gotoXY (0, 0);
            cout << "Match loai Z                 ";
            drawLine(Pikachu, start_point);
            temp = 1;
        }
        else if(matchShapeU(Pikachu))
        {
            gotoXY (0, 0);
            cout << "Match loai U                   ";
            drawLine(Pikachu, start_point);

            temp = 1;
        }
        else
        {
            gotoXY (0, 0);
            cout << "Khong thuoc loai matching nao!  ";
            temp = 0;
        }
     }
 }

void drawFrame (int pos_x, int pos_y, string str)
{
    for (int i = pos_x + 1; i < pos_x + 17; i++)
    {
        gotoXY(i, pos_y - 1);
        cout << '_';
        gotoXY(i, pos_y + 1);
        cout << '_';
    }
    for (int j = pos_y; j < pos_y + 2; j++)
    {
        gotoXY(pos_x, j);
        cout << '|';
        gotoXY(pos_x + 17, j);
        cout << '|';
    }
    gotoXY(pos_x + 3, pos_y);
    cout << str;
}


//Ham ve hinh chu nhat
void drawRec(int begin_x, int begin_y, int end_x, int end_y, char ch_1, char ch_2)
{
    //Ve cac duong thang ngang
    for (int i = begin_x + 1; i < end_x; i++)
    {
        gotoXY(i , begin_y);
        cout << ch_1;
        gotoXY(i, end_y);
        cout << ch_1;
    }

    //Ve cac doan thang xuong
    for (int j = begin_y + 1 ; j < end_y ; j++)
    {
        gotoXY(begin_x, j);
        cout << ch_2;
        gotoXY(end_x, j);
        cout << ch_2;
    }
}

void highLightBlock(Coordinate select, int **arr, int color, int start_point)
{
    Coordinate pos;
    pos.x = start_point + 9 * (select.x - 1);
    pos.y = 5 + 5 * (select.y - 1);

    changeColor(color);
    for (int i = pos.x + 1; i < pos.x + 8 ; i++)
    {
        for(int j = pos.y + 1; j < pos.y + 4; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }
    }
    gotoXY(pos.x + 4, pos.y + 2);
    if(arr[select.x][select.y] == -1)
    {
        cout << " ";
    }
    else
    {
        cout << char('A' + arr[select.x][select.y]);
    }
    changeColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
}

//Ve man hinh bat dau
void drawMenu(int middle)
{
    int left;
    Coordinate first;
    left = middle - 7;
    first.x = middle - 3;
    first.y = 21;

    for (int i = 20; i >= 0; i--)
    {
    //Ve tieu de
        if (i % 2 == 0)
        {
            changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
        else changeColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);

        gotoXY(left - 40 - 2 * i, 0);
        cout << "|||||||||     ||||||   |||     ||| |||||||||| ||||       ||||    ||||||    ||| ||     || ||";
        gotoXY(left - 40 - 2 * i, 1);
        cout << " ||      || ||      ||   ||   ||    ||          ||||    ||||   ||      ||    || ||     ||";
        gotoXY(left - 40 - 2 * i, 2);
        cout << " ||      || ||      ||   ||  ||     ||          || ||  || ||   ||      ||    ||  ||    ||";
        gotoXY(left - 40 - 2 * i, 3);
        cout << " ||      || ||      ||   || ||      ||   |      ||  ||||  ||   ||      ||    ||   ||   ||";
        gotoXY(left - 40 - 2 * i, 4);
        cout << " ||||||||   ||  ||  ||   ||||       |||||||     ||   ||   ||   ||  ||  ||    ||    ||  ||";
        gotoXY(left - 40 - 2 * i, 5);
        cout << " ||         ||      ||   || ||      ||   |      ||        ||   ||      ||    ||     || ||";
        gotoXY(left - 40 - 2 * i, 6);
        cout << " ||         ||      ||   ||  ||     ||          ||        ||   ||      ||    ||      ||||";
        gotoXY(left - 40 - 2 * i, 7);
        cout << " ||         ||      ||   ||   ||    ||          ||        ||   ||      ||    ||       |||";
        gotoXY(left - 40 - 2 * i, 8);
        cout << "||||          ||||||    ||||  |||| |||||||||| |||||      |||||   ||||||    || ||    ||  ||";

        Sleep (150);

        if (i != 0)
        {
            system("cls");
        }
    }

    for (int i = 0; i < 5; i++)
    {
        changeColor(2 + i | FOREGROUND_INTENSITY);

        drawFrame (left, 16, "PIKACHU GAME");
        gotoXY(left + 7, 17);
        cout << "MENU";
        Sleep (100);
        drawFrame (left, 20, "   BAT DAU");
        Sleep (100);
        drawFrame (left, 22, "  TIEP TUC");
        Sleep (100);
        drawFrame (left, 24, " THANH TICH");
        Sleep (100);
        drawFrame (left, 26, "     BXH");
        Sleep (100);
        drawFrame (left, 28, "    THOAT");
    }

    changeColor (BACKGROUND_BLACK || FOREGROUND_WHITE);
    selectOption(first);
}

//lam noi bat khung chon menu
void selectOption (Coordinate select)
{
    changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY );

    gotoXY(select.x, select.y);
    for (int i = select.x; i < select.x + 10; i++)
    {
    cout << "-";
    }

    gotoXY(select.x, select.y - 2);
    for (int i = select.x; i < select.x + 10; i++)
    {
        cout << "-";
    }

    _getch();
    changeColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
}

//thu hoi bo nho
void deleleDinamicArr(Board Pikachu)
{
    for (int i = 0; i <= Pikachu.size + 1; i++)
    {
        delete[] Pikachu.Arr[i];
    }
}
