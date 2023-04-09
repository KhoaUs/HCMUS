#include "Mylib.h"



void Operating_System()
{
    int **Arr = NULL, *sub_arr = NULL, size;

    cout << "Hay bat full man hinh de co trai nghiem tot nhat! " << endl;
    system("pause");
    system("cls");

    srand(time(NULL));

    play(Arr, sub_arr, size);
}

void play(int **&Arr, int *&sub_arr, int &size)
{
    //khoi tao diem bat dau cua bang
    int middle, rows, pos_menu_x, pos_menu_y, start_point;

    //Tinh kich thuoc console
    calculateColumnsConsole(middle, rows);

    //Khai bao bien start_point cho bang, pos_menu cho toa do cua menu
    start_point = middle - size * 4;
    pos_menu_x = middle - 3;
    pos_menu_y = 21;

    drawMenu(middle);

    bool check = true;
    while (true)
    {
        if(_kbhit())
        {
            char c = _getch();
            check = true;

            gotoXY(pos_menu_x, pos_menu_y);
            cout << "__________";

            gotoXY(pos_menu_x, pos_menu_y - 2);
            cout << "__________";

            if (check)
            {
                if(c == 72)
                {
                    if(pos_menu_y == 21)
                    {
                        pos_menu_y = 21 + 8;
                    }
                    else
                    {
                        pos_menu_y -= 2;
                    }

                    selectOption(pos_menu_x, pos_menu_y);

                    //Kiểm tra điều kiện để tránh in dư tại vị trí đáy
                    if(pos_menu_y != 29)
                    {
                        gotoXY(pos_menu_x, pos_menu_y + 2);
                        cout << "__________";
                    }
                    check = false;
                }

                if(c == 80)
                {
                    if(pos_menu_y == 29)
                    {
                        pos_menu_y = 29 - 8;
                    }
                    else
                    {
                        pos_menu_y += 2;
                    }

                    selectOption(pos_menu_x, pos_menu_y);
                    gotoXY(pos_menu_x, pos_menu_y - 2);
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
    switch (pos_menu_y)
    {
        case 21:
            //cho nguoi choi chon do kho
            system("cls");
            selectLevel (middle, size);
            setValueBoard (Arr, sub_arr, size);
            drawBoard(size, start_point, Arr);
            operateBoard(Arr, 1, 1, 1, 1, size, start_point, pos_menu_x, pos_menu_y);
            play(Arr, sub_arr, size);
            break;
        case 23:
            //dan toi trang dang nhap de nhap tai khoan
            //de quay lai menu bap esc hoac chon "tro ve"
            system("cls");
            drawBoard(size, start_point, Arr);
            operateBoard(Arr, 1, 1, 1, 1, size, start_point, pos_menu_x, pos_menu_y);
            play(Arr, sub_arr, size);
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
    deleleDinamicArr (Arr, size);
    delete[] Arr;
    delete[] sub_arr;
}


void operateBoard (int **&a, int cur_x, int cur_y, int old_x, int old_y, int size, int start_point, int x, int y)
{
    char c;
    int select_x = -1, select_y = -1, temp = 0;
    //Khoi tao vung chon dau tien
    highLightBlock(cur_x , cur_y, a, 143, start_point);

    while (true)
    {
        c = _getch();
        old_x = cur_x;
        old_y = cur_y;
         //Di chuyen len
        if(c == 72 || c == 'w' || c == 'W')
         {
             if(cur_y == 1)
             {
                 cur_y = size;
             }
             else
             {
                 cur_y--;
             }
         }
         //Di chuyen xuong
         if(c == 80 || c == 's' || c == 'S')
         {
             if(cur_y == size)
             {
                 cur_y = 1;
             }
             else
             {
                 cur_y++;
             }
         }
        //Di chuyen trai
         if(c == 75 || c == 'a' || c == 'A')
        {
            if(cur_x == 1)
            {
                cur_x = size;
            }
            else
            {
                cur_x--;
            }
        }
        //Di chuyen phai
        if(c == 77 || c == 'D' || c == 'd')
        {
            if(cur_x == size)
            {
                cur_x = 1;
            }
            else
            {
                cur_x++;
            }
        }
        //Tai lai neu man hinh hien thi loi
        if(c == 'r' || c == 'R')
        {
            system("cls");
            drawBoard(size, start_point, a);
        }
        //Enter hoac Space
        if(c == 13 || c == 32)
        {
            if(a[cur_x][cur_y] != -1)
            {
                highLightBlock(cur_x, cur_y, a, 177, start_point);
                if(select_x == -1 && select_y == -1)
                {
                    select_x = cur_x;
                    select_y = cur_y;
                }
                else
                {
                    if(a[select_x][select_y] == a[cur_x][cur_y])
                    {
                        matchWholeShape (cur_x, cur_y, select_x, select_y, a, start_point, temp, size);
                        //playSound (temp);
                        //Xoa khung
                        if(temp == 1)
                        {
                            drawRec((start_point + 9 * (select_x - 1)) , (5 + 5 * (select_y - 1)), (start_point + 9 * (select_x - 1) + 8), (9 + 5 * (select_y - 1)), ' ', ' ');
                            drawRec((start_point + 9 * (cur_x - 1)) , (5 + 5 * (cur_y - 1)), (start_point + 9 * (cur_x - 1) + 8), (9 + 5 * (cur_y - 1)), ' ', ' ');

                            //Danh dau vi tri da xoa va xoa mau
                            a[select_x][select_y] = -1;
                            a[cur_x][cur_y] = -1;
                            highLightBlock(select_x, select_y, a, 0, start_point);

                            //Reset toa do vung chon
                            select_x = -1;
                            select_y = -1;

                            temp = 0;
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
        if (cur_x != old_x || cur_y != old_y )
        {
            //Tranh to lai mau mac dinh cho o da chon
            if (select_x == cur_x && select_y == cur_y)
            {
                //To mau khac biet khi di lai vung da chon mot lan nua
                highLightBlock(cur_x, cur_y, a, 199, start_point);
                c = _getch();
                if(c == 13 || c == 32 || c == 'b')
                {
                    select_x = -1;
                    select_y = -1;
                    gotoXY(0, 0);
                    cout << "Da bo chon";
                    Sleep (200);
                    gotoXY(0, 0);
                    cout << "           ";
                }
            }
            else
            {
                //To mau vung con tro
                highLightBlock(cur_x, cur_y, a, 143, start_point);
            }

            if (old_x != select_x || old_y != select_y)
            {
                //To lai mau mac dinh sau khi di chuyen
                highLightBlock(old_x, old_y, a, 14, start_point);
            }
            else
            {
                //Xu ly sau khi di qua lai o da chon mot lan nua
                highLightBlock(old_x, old_y, a, 177, start_point);
            }
            gotoXY(1, 1);
            cout << cur_x << ", " << cur_y;
        }
    }
    Sleep(100);
}

void resetBoard (int **&Arr, int size)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (Arr[i][j] < 0 && Arr[i][j] != -1)
            {
                Arr[i][j] = -1;
            }
        }
    }
}

void selectLevel (int middle, int &size)
{
    int left, pos_menu_x, pos_menu_y;
    left = middle - 7;
    pos_menu_x = middle - 3;
    pos_menu_y = 21;
    drawFrame (left, 20, "    KHO");
    drawFrame (left, 22, " TRUNG BINH");
    drawFrame (left, 24, "     DE");
    selectOption(pos_menu_x, pos_menu_y);

    bool check = true;
    while (true)
    {
        if(_kbhit())
        {
            char c = _getch();
            check = true;

            gotoXY(pos_menu_x, pos_menu_y);
            cout << "__________";

            gotoXY(pos_menu_x, pos_menu_y - 2);
            cout << "__________";

            if (check)
            {
                //Di chuyen len
                if(c == 72)
                {
                    //neu da gap dinh, thi con tro nhay xuong duoi day
                    if(pos_menu_y == 21)
                    {
                        pos_menu_y = 25;
                    }
                    else
                    {
                        pos_menu_y -= 2;
                    }

                    selectOption(pos_menu_x, pos_menu_y);

                    //Kiểm tra điều kiện để tránh in dư tại vị trí đáy
                    if(pos_menu_y != 25)
                    {
                        gotoXY(pos_menu_x, pos_menu_y + 2);
                        cout << "__________";
                    }
                    check = false;
                }
                //Di chuyen xuong
                if(c == 80)
                {
                    //Neu cham day, con tro tu tro len dau
                    if(pos_menu_y == 25)
                    {
                        pos_menu_y = 21;
                    }
                    else
                    {
                        pos_menu_y += 2;
                    }

                    selectOption(pos_menu_x, pos_menu_y);
                    gotoXY(pos_menu_x, pos_menu_y - 2);
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

    switch(pos_menu_y)
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
void setValueBoard (int **&Arr, int *&sub_arr, int size)
{
    //Khai bao bien count de dem so luong pokemon da set, sub_size de luu so loai pokemon
    int count = 0;
    int sub_size = size * 2;

    //Cap phat dong cho mang
    Arr = new int *[size + 2];
    sub_arr = new int [sub_size];

    //Set so luong cua cac loai pokemon ban dau la 0, vi chua co pokemon nao
    for (int i = 0; i < sub_size; i++)
    {
        sub_arr[i] = 0;
    }

    //muc dich tao ra mot hinh chu nhat phu ben ngoai de ho tro matching
    for (int i = 0; i <= size + 1; i++)
    {
        Arr[i] = new int [size + 2];
    }

    for (int i = 0; i <= size + 1; i++)
    {
        for(int j = 0; j <= size + 1; j++)
        {
            if (i == 0 || j == 0 || i == size + 1 || j == size + 1)
            {
                Arr[j][i] = -1;
            }
            else
            {
                //De lai mot so luong sub_size phan tu de lam chan so luong cac pokemon
                if (count < (size * size - sub_size))
                {
                    //random cac loai pokemon va dem so luong da ramdon
                    Arr[j][i] = rand() % sub_size;
                    count++;

                    //Dem so luong cac loai pokemon, chi so index trong mang sub_arr ung voi gia tri cua pokemon, con gia tri tai index do se ung voi so luong loai do
                    sub_arr[Arr[j][i]]++;
                }
                //chi random den mot so luong size * size - sub_size sau do ktra xem pokemon nao dang le thi se tang them mot, neu khong con pokemon nao le, se tao so le sau do lam chan
                else
                {
                    int sub_count = count;
                    for (int p = 0; p < sub_size; p++)
                    {
                        if ((sub_arr[p] % 2) != 0 )
                        {
                            //neu so luong cua loai pokemon p la le, se tang len 1 de lam chan
                            Arr[j][i] = p;
                            sub_arr[p]++;

                            //tang bien sub_count de khang dinh rang con pokemon co so luong le
                            sub_count++;
                            break;
                        }
                    }

                    //Neu nhu khong con pokemon nao le, hay lam cho no le :D
                    if (sub_count == count)
                    {
                        //random va dem so luong cac loai pokemon
                        Arr[j][i] = rand() % sub_size;
                        sub_arr[Arr[j][i]]++;
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


void drawLine(int **&Arr, int size, int start_point)
{
    changeColor (FOREGROUND_GREEN);
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (Arr[i][j] == -2)
            {
                gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                cout << ">>>>>>>>";
                Sleep (150);
                gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                cout << "        ";
            }

            if (Arr[i][j] == -3)
            {
                for (int k = 0; k < 3; k++)
                {
                gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                cout << char(166);
                Sleep (150);
                gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                cout << " ";
                }
            }
        }
    }

    //Chay lai
    changeColor (FOREGROUND_BLUE);
    for (int i = size; i >= 1; i--)
    {
        for (int j = size; j >= 1; j--)
        {
            if (Arr[i][j] == -2)
            {
                gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                cout << ">>>>>>>>";
                Sleep (150);
                gotoXY((start_point + 9 * (i - 1)), (7 + 5 * (j - 1)));
                cout << "        ";
            }

            if (Arr[i][j] == -3)
            {
                for (int k = 3; k > 0; k--)
                {
                gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                cout << char(166);
                Sleep (150);
                gotoXY((start_point + 4 + 9 * (i - 1)), (5 + 5 * (j - 1) + k));
                cout << " ";
                }
            }
        }
    }
    resetBoard (Arr, size);
}

bool matchShapeI(int cur_x, int cur_y, int old_x, int old_y, int **&a, int start_point, int size)
{
    //Kiem tra xem hai toa do co trung nhau khong truoc do trong ham cha
    //Kiem tra co cung hang, hay cung cot hay khong
    //Truong hop cung truc Oy
    if (cur_y == old_y)
    {
        if(cur_x > old_x)
        {
            for (int i = old_x + 1; i < cur_x; i++)
            {
                if(a[i][cur_y] != -1)
                {
                    resetBoard (a, size);
                    return 0;
                }
                a[i][cur_y] = -2;
            }
            return 1;
        }
        else
        {
            for (int i = old_x - 1; i > cur_x; i--)
            {
                if(a[i][cur_y] != -1)
                {
                    resetBoard (a, size);
                    return 0;
                }
                a[i][cur_y] = -2;
            }
            return 1;
        }
    }
    //Truong hop trung truc Ox
    else if (cur_x == old_x)
    {
        if(cur_y > old_y)
        {
            for (int i = old_y + 1; i < cur_y; i++)
            {
                if(a[cur_x][i] != -1)
                {
                    resetBoard (a, size);
                    return 0;
                }
                a[cur_x][i] = -3;
            }
            return 1;
        }
        else
        {
            for (int i = old_y - 1; i > cur_y; i--)
            {
                if (a[cur_x][i] != -1)
                {
                    resetBoard (a, size);
                    return 0;
                }
                a[cur_x][i] = -3;
            }
            return 1;
        }
    }
    return 0;
}

bool matchShapeL(int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int size)
{
    if (cur_x == old_x || cur_y == old_y)
    {
        return 0;
    }
    //Chia lam 4 trương hop cho loai nay, khi old ben phai cua cur
    if(cur_x < old_x && cur_y > old_y)
    {
        //Truong hop 1: ngang - len
        for (int i = cur_x + 1; i <= old_x; i++)
        {
            //Truong hop 2: len - ngang
            if (a[i][cur_y] != -1)
            {
                for (int t = cur_y - 1; t >= old_y; t--)
                {
                    if (a[cur_x][t] != -1)
                    {
                        return 0;
                    }
                }
                for (int p = cur_x + 1; p < old_x; p++)
                {
                    if (a[p][old_y] != -1)
                    {
                        return 0;
                    }
                }
                return 1;
            }
        }
        for (int j = cur_y - 1; j > old_y; j--)
        {
            if (a[old_x][j] != -1)
            {
                return 0;
            }
        }
        return 1;
    }
    //Truong hop 3 + 4
    if (cur_x < old_x && cur_y < old_y)
    {
        {
        //Truong hop 3: ngang - xuong
        for (int i = cur_x + 1; i <= old_x; i++)
        {
            //Truong hop 4: xuong - ngang
            if (a[i][cur_y] != -1)
            {
                for (int t = cur_y + 1; t <= old_y; t++)
                {
                    if (a[cur_x][t] != -1)
                    {
                        return 0;
                    }
                }
                for (int p = cur_x + 1; p < old_x; p++)
                {
                    if (a[p][old_y] != -1)
                    {
                        return 0;
                    }
                }
                return 1;
            }
        }
        for (int j = cur_y + 1; j < old_y; j++)
        {
            if (a[old_x][j] != -1)
            {
                return 0;
            }
        }
        return 1;
        }
    }
    //Chia 4 truong hop 5 - 8 cho viec old ben trai cur
    //TH 5 + 6
    //Th 5: Ngang - len
    if (cur_x > old_x && cur_y > old_y)
    {
        for(int i = cur_x - 1; i >= old_x; i--)
        {
            //Th6: Len - ngang
            if(a[i][cur_y] != -1)
            {
                for (int t = cur_y - 1; t >= old_y; t--)
                {
                    if(a[cur_x][t] != -1)
                    {
                        return 0;
                    }
                }
                for (int k = cur_x -  1; k > old_x; k--)
                {
                    if(a[k][old_y] != -1)
                    {
                        return 0;
                    }
                }
                return 1;
            }
        }
        //Ngang dung --> len
        for (int j = cur_y - 1; j > old_y; j--)
        {
            if (a[old_x][j] != -1)
            {
                return 0;
            }
        }
        return 1;
    }
    //Th 7 - 8
    //Th 7: Ngang - xuong
    if (cur_x > old_x && cur_y < old_y)
    {
        for (int i = cur_x - 1; i >= old_x; i--)
        {
            //Th8: xuong - ngang
            if(a[i][cur_y] != -1)
            {
                for (int t = cur_y + 1; t <= old_y; t++)
                {
                    if (a[cur_x][t] != -1)
                    {
                        return 0;
                    }
                }
                //ngang
                for (int k = cur_x - 1; k > old_x; k--)
                {
                    if (a[k][old_y] != -1)
                    {
                        return 0;
                    }
                }
                return 1;
            }
        }
        for (int j = cur_y + 1; j < old_y; j++)
        {
            if(a[old_x][j] != -1)
            {
                return 0;
            }
        }
        return 1;
    }

    return 0;


}

bool matchShapeZ (int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int size)
{
    //Se co 8 truong hop, tuong tu L
    //De ap dung loai Z, hai diem khong duoc thang hang
    if (cur_x == old_x || cur_y == old_y)
    {
        return 0;
    }
    //Gop 8 truong hop thanh 4 truong hop bang cach ep vi tri co toa do x nho hon thanh vi tri cua cur, sau do xet tu trai sang phai
    if (cur_x > old_x)
    {
        //Khai bao 2 bien tam de luu thong tin cho buoc xu ly tiep theo
        int temp_x, temp_y;
        temp_x = cur_x;
        temp_y = cur_y;

        cur_x = old_x;
        cur_y = old_y;

        old_x = temp_x;
        old_y = temp_y;
    }
    //old ben tren
    if (cur_y > old_y)
    {
        //th1: ngang - len - ngang
        for (int i = cur_x + 1; i < old_x; i++)
        {
            if (a[i][cur_y] != -1)
            {
                break;
            }
            else
            {
                int j;
                for (j = cur_y - 1; j > old_y; j--)
                {
                    if(a[i][j] != -1)
                    {
                        break;
                    }
                }
                if(j == old_y)
                {
                    int k = i;
                    for (k; k < old_x; k++)
                    {
                        if (a[k][old_y] != -1)
                        {
                            break;
                        }
                    }
                    if (k == old_x)
                    {
                        return 1;
                    }
                }
            }
        }
        //th2: len - ngang - len
        for(int i = cur_y - 1; i > old_y; i--)
        {
            if(a[cur_x][i] != -1)
            {
                break;
            }
            else
            {
                int j = cur_x + 1;
                for(; j < old_x; j++)
                {
                    if(a[j][i] != -1)
                    {
                        break;
                    }
                }
                if (j == old_x)
                {
                    int k = i;
                    for(; k > old_y; k--)
                    {
                        if(a[old_x][k] != -1)
                        {
                            break;
                        }
                    }
                    if (k == old_y)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    //old ben duoi cur
    else if (cur_y < old_y)
    {
        //th3: ngang - xuong - ngang
        for (int i = cur_x + 1; i < old_x; i++)
        {
            if (a[i][cur_y] != -1)
            {
                break;
            }
            else
            {
                int j;
                for (j = cur_y + 1; j < old_y; j++)
                {
                    if(a[i][j] != -1)
                    {
                        break;
                    }
                }
                if(j == old_y)
                {
                    int k = i;
                    for (k; k < old_x; k++)
                    {
                        if (a[k][old_y] != -1)
                        {
                            break;
                        }
                    }
                    if (k == old_x)
                    {
                        return 1;
                    }
                }
            }
        }
        //th4: xuong - ngang - xuong
        for(int i = cur_y + 1; i < old_y; i++)
        {
            if(a[cur_x][i] != -1)
            {
                break;
            }
            else
            {
                int j = cur_x + 1;
                for(; j < old_x; j++)
                {
                    if(a[j][i] != -1)
                    {
                        break;
                    }
                }
                if (j == old_x)
                {
                    int k = i;
                    for(; k < old_y; k++)
                    {
                        if(a[old_x][k] != -1)
                        {
                            break;
                        }
                    }
                    if (k == old_y)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

bool matchShapeU (int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int size)
{
    //Hoan doi vi tri sao cho vi tri diem old luon ben phai cua cur
    if (cur_x > old_x)
    {
        //Khai bao 2 bien tam de luu thong tin cho buoc xu ly tiep theo
        int temp_x, temp_y;
        temp_x = cur_x;
        temp_y = cur_y;

        cur_x = old_x;
        cur_y = old_y;

        old_x = temp_x;
        old_y = temp_y;
    }
    //Th1 : len - ngang - xuong
    for (int i = cur_y - 1; i >= 0; i--)
    {
        if (a[cur_x][i] != -1)
        {
            break;
        }
        int j = cur_x + 1;
        for (; j < old_x; j++)
        {
            if (a[j][i] != -1)
            {
                break;
            }
        }
        if (j == old_x)
        {
            int k = i;
            for (; k < old_y; k++)
            {
                if (a[old_x][k] != -1)
                {
                    break;
                }
            }
            if (k == old_y)
            {
                return 1;
            }
        }
    }

    //Th2: Xuong - ngang - len
    for (int i = cur_y + 1; i <= size + 1; i++)
    {
        if (a[cur_x][i] != -1)
        {
            break;
        }
        //Ngang;
        int j = cur_x + 1;
        for (; j < old_x; j++)
        {
            if(a[j][i] != -1)
            {
                break;
            }
        }
        if (j == old_x)
        {
            //len
            int k = i;
            for (; k > old_y; k--)
            {
                if (a[j][k] != -1)
                {
                    break;
                }
            }
            if(k == old_y)
            {
                return 1;
            }
        }
    }

    //Th3: ngang qua phai
    for (int i = cur_x + 1; i <= size + 1; i++)
    {
        if (a[i][cur_y] != -1)
        {
            break;
        }
        //Duyet ngang qua phai den khi nao i vuot qua old_x
        if (i > old_x)
        {
            //truong hop old nam ben tren cua cur --> di len
            if (cur_y > old_y)
            {
                int j = cur_y - 1;
                for (; j > old_y; j--)
                {
                    if (a[i][j] != -1)
                    {
                        break;
                    }
                }
                if (j == old_y)
                {
                    int k = i;
                    for (; k > old_x; k--)
                    {
                        if (a[k][j] != -1)
                        {
                            break;
                        }
                    }
                    if (k == old_x)
                    {
                        return 1;
                    }
                }
            }
            //truong hop old nam ben duoi cua cur
            if (cur_y < old_y)
            {
                int j = cur_y + 1;
                for (; j < old_y; j++)
                {
                    if (a[i][j] != -1)
                    {
                        break;
                    }
                }
                if (j == old_y)
                {
                    int k = i;
                    for (; k > old_x; k--)
                    {
                        if (a[k][j] != -1)
                        {
                            break;
                        }
                    }
                    if (k == old_x)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    //Th4 ngang qua trai
    for (int i = cur_x - 1; i >= 0; i--)
    {
        if (a[i][cur_y] != -1)
        {
            break;
        }
        //truong hop old nam duoi cur
        if (cur_y < old_y)
        {
            int j = cur_y + 1;
            for (; j < old_y; j++)
            {
                if (a[i][j] != -1)
                {
                    break;
                }
            }
            //neu duyet duoc toi vi tri toa do bang old_y thi tiep tuc duyet ngang
            if (j == old_y)
            {
                int k = i;
                for (; k < old_x; k++)
                {
                    if (a[k][old_y] != -1)
                    {
                        break;
                    }
                }
                if (k == old_x)
                {
                    return 1;
                }
            }
        }
        //Truong hop old nam tren cur
        else if (cur_y > old_y)
        {
            int j = cur_y - 1;
            for (; j > old_y; j--)
            {
                if (a[i][j] != -1)
                {
                    break;
                }
            }
            //neu duyet duoc toi vi tri toa do bang old_y thi tiep tuc duyet ngang
            if (j == old_y)
            {
                int k = i;
                for (; k < old_x; k++)
                {
                    if (a[k][old_y] != -1)
                    {
                        break;
                    }
                }
                if (k == old_x)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

 void matchWholeShape(int cur_x, int cur_y, int old_x, int old_y, int**& a, int start_point, int &temp, int size)
 {
     //Trung vi tri thi in ra thong bao va ngung xu ly
     if (cur_x == old_x && cur_y == old_y)
     {
         gotoXY (0, 0);
         cout << "Khong duoc chon lai vi tri cu!";
         Sleep(300);
         gotoXY (0, 0);
         cout << "                                ";

     }
     else
     {
        if(matchShapeI(cur_x, cur_y, old_x, old_y, a, start_point, size))
        {
            gotoXY (0, 0);
            cout << "Match loai I";
            Sleep(300);
            gotoXY (0, 0);
            cout << "                       ";
            drawLine( a, size, start_point);

            temp = 1;
        }
        else if(matchShapeL(cur_x, cur_y, old_x, old_y, a, start_point, size))
        {
            gotoXY (0, 0);
            cout << "Match loai L";
            Sleep(300);
            gotoXY (0, 0);
            cout << "                       ";

            temp = 1;
        }
        else if(matchShapeZ(cur_x, cur_y, old_x, old_y, a, start_point, size))
        {
            gotoXY (0, 0);
            cout << "Match loai Z";
            Sleep(300);
            gotoXY (0, 0);
            cout << "                       ";

            temp = 1;
        }
        else if(matchShapeU(cur_x, cur_y, old_x, old_y, a, start_point, size))
        {
            gotoXY (0, 0);
            cout << "Match loai U";
            Sleep(300);
            gotoXY (0, 0);
            cout << "                       ";

            temp = 1;
        }
        else
        {
            gotoXY (0, 0);
            cout << "Khong thuoc loai matching nao!";
            Sleep(300);
            gotoXY (0, 0);
            cout << "                                  ";

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

void highLightBlock(int x, int y, int **arr, int color, int start_point)
{

    changeColor(color);
    int pos_x = start_point + 9 * (x - 1);
    int pos_y = 5 + 5 * (y - 1);
    for (int i = pos_x + 1; i < pos_x + 8 ; i++)
    {
        for(int j = pos_y + 1; j < pos_y + 4; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }
    }
    gotoXY(pos_x + 4, pos_y + 2);
    if(arr[x][y] == -1)
    {
        cout << " ";
    }
    else
    {
        cout << char('A' + arr[x][y]);
    }
    changeColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
}

//Ve man hinh bat dau
void drawMenu(int middle)
{


    int x, y, left;
    left = middle - 7;
    x = middle - 3;
    y = 21;
    //Ve tieu de
    changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoXY(0, 0);
    cout <<  "  ,'\ ";
    cout <<  R"(
                                                          ,'\
                            _.----.        ____         ,'  _\   ___    ___     ____
                        _,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
                        \      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
                         \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
                           \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
                            \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
                             \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
                              \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
                               \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
                                \_.-'       |__|    `-._ |              '-.|     '-.| |   |
                                                        `'                            '-._|
                    )";


    drawFrame (left, 16, "PIKACHU GAME");
    gotoXY(left + 7, 17);
    cout << "MENU";

    changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_YELLOW);
    drawFrame (left, 20, "   BAT DAU");
    drawFrame (left, 22, "  TIEP TUC");
    drawFrame (left, 24, " THANH TICH");
    drawFrame (left, 26, "     BXH");
    drawFrame (left, 28, "    THOAT");
    changeColor (BACKGROUND_BLACK || FOREGROUND_WHITE);
    selectOption(x, y);
}


//Ham ve bang
void drawBoard (int Size, int start_point, int **a)
{

    for (int j = 0; j < Size; j++)
    {
        for (int i = 0; i < Size; i++)
        {
            //Chon mau khung
            if(a[i + 1][j + 1] != -1)
            {
                //Chon mau khung
                changeColor (FOREGROUND_INTENSITY);
                drawRec((start_point + 9 * i ), (5 + 5 * j), (start_point + 9 * i + 8), (9 + 5 * j), '-', '|');

                //Chon mau chu
                changeColor (FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                gotoXY (start_point + 9 * i  + 4, 5 + 5 * j + 2);
                cout << char('A' + a[i + 1][j + 1]);
            }
        }
    }
}



//lam noi bat khung chon menu
void selectOption (int _x, int _y)
{
    changeColor(FOREGROUND_RED | FOREGROUND_INTENSITY );

    gotoXY(_x, _y);
    for (int i = _x; i < _x + 10; i++)
    {
    cout << "-";
    }

    gotoXY(_x, _y - 2);
    for (int i = _x; i < _x + 10; i++)
    {
        cout << "-";
    }

    _getch();
    changeColor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
}


//thu hoi bo nho
void deleleDinamicArr(int **Arr, int size)
{
    for (int i = 0; i <= size + 1; i++)
    {
        delete[] Arr[i];
    }
}