#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
//function list
void mainmenu();
void box1();
void box2();
void box3();
void box4();
void login();
void calculate();
void dbill();
void addorders();
void disporders();
int info();
void fireexit();
void welcome();
int checkid(int t);
//variables
char uname[10];
char upass[10];
char user[10]={"happy"};
char pass[10]={"cafe"};
int h;
//File list
FILE *fp;

COORD coord={0,0};
void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Structure
struct foods{
    int id;
    char name[20];
    int qnty;
    double price;
};
struct foods a;
//main function
int main()
{
    welcome();
    getch();
    return 0;
}
//starting function
void mainmenu()
{
    system("cls");
    gotoxy(15,3);
    printf("\xb1\xb1\xb1\xb1\xdb\xdb\xdb\xb1\xb1\xb1\xb1\xdb\xdb\xdb\xb1\xb1\xb1\xb1 MAIN MENU \xb1\xb1\xb1\xb1\xdb\xdb\xdb\xb1\xb1\xb1\xb1\xdb\xdb\xdb\xb1\xb1\xb1\xb1\n");
    box1();
    box2();
    box3();
    box4();
    gotoxy(12,7);
    printf("   1.Order Foods");
    gotoxy(42,7);
    printf("   2.Add Food Items");
    gotoxy(12,15);
    printf("   3.Display Food Items");
    gotoxy(42,15);
    printf("   4.Exit");
    gotoxy(15,20);
    printf("Enter Your Choice: ");
    switch(getch())
    {
        case '1':
        calculate();
        break;
        case '2':
        addorders();
        break;
        case '3':
        disporders();
        break;
        case '4':
        fireexit();
    default:
    {
      gotoxy(10,23);
      printf("\aWrong Entry!!Please re-entered correct option");
      if(getch())
      mainmenu();
}
    }
}
void calculate()
{
    int x;
    int j=13,q=0,size=0,i=1;
    float total=0,gtotal=0;
    fp=fopen("cafe.txt","r+");
    rewind(fp);
    system("cls");
    dbill();
    gotoxy(26,2);
    printf("Enter  '0' to finish input");
    while(1)
    {
        gotoxy(25,4);
        printf("                    ");
        gotoxy(25,5);
        printf("                    ");
        gotoxy(25,4);
        printf("Enter Item Code:");
        scanf("%d",&x);
        if(x==0)
            break;
        gotoxy(25,5);
        printf("Enter Quantity:");
        scanf("%d",&q);
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp))
        {
            if(a.id==x)
            {
                if(a.qnty==0){
                        gotoxy(25,7);
                    printf("'Sorry.The Food is Finished'");
                    break;
                }
                total=a.price*q;
                gotoxy(11,j);
                printf("%4d",i);
                printf("%9s",a.name);
                printf("%13d",q);
                printf("%15.2f",a.price);
                printf("%13.2f",total);
                gtotal=gtotal+total;
                size=sizeof(a);
                a.qnty=a.qnty-q;
                j+=2;
                i++;
                fseek(fp,-size,SEEK_CUR);
                fwrite(&a,sizeof(a),1,fp);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        gotoxy(30,j+5);
        printf("TOTAL AMOUNT = TK. %6.2f",gtotal);
    }
    fclose(fp);
    getch();
    mainmenu();
}
/*function to display bill window*/
void dbill()
{
    int i;

    gotoxy(32,10);
    printf("CUSTOMER'S BILL") ;
//textcolor(8);
    gotoxy(13,11);
    printf("SN.   Item Name     Quantity     Rate          Total");

}
void addorders()
{
    system("cls");
    fp=fopen("cafe.txt","a+");
    if(info()==1){
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        gotoxy(21,17);
        printf("The record is sucessfully saved");
        gotoxy(21,18);
        printf("Save any more?(Y / N):");
        if(getch()=='y') addorders();
        else mainmenu();
    }

}
int info()
{
    int d;
    gotoxy(23,3);
    printf("Enter The Information");
    gotoxy(17,4);printf("****************************************");
    gotoxy(17,5);
    printf("\xB2");gotoxy(56,5);printf("\xB2");
    gotoxy(17,6);
    printf("\xB2");gotoxy(56,6);printf("\xB2");
    gotoxy(17,7);
    printf("\xB2");gotoxy(56,7);printf("\xB2");
    gotoxy(17,8);
    printf("\xB2");gotoxy(56,8);printf("\xB2");
    gotoxy(17,9);
    printf("\xB2");gotoxy(56,9);printf("\xB2");
    gotoxy(17,10);
    printf("\xB2");gotoxy(56,10);printf("\xB2");
    gotoxy(17,11);
    printf("\xB2");gotoxy(56,11);printf("\xB2");
    gotoxy(17,12);
    printf("\xB2");gotoxy(56,12);printf("\xB2");
    gotoxy(17,13);
    printf("\xB2");gotoxy(56,13);printf("\xB2");
    gotoxy(17,14);
    printf("\xB2");gotoxy(56,14);printf("\xB2");
    gotoxy(17,15);
    printf("****************************************");
    gotoxy(19,5);
    printf("[Food ID]: ");
    gotoxy(19,8);
    printf("[Food name]: ");
    gotoxy(19,10);
    printf("[Quantity]: ");
    gotoxy(19,13);
    printf("[Price]: ");
    gotoxy(30,5);
    scanf("%d",&d);
    if(checkid(d)==0){
        gotoxy(19,16);
        printf("This Food is already exists");
        getch();
        mainmenu();
    }
    a.id=d;
    gotoxy(32,8);
    scanf("%s",a.name);
    gotoxy(31,10);
    scanf("%d",&a.qnty);
    gotoxy(28,13);
    scanf("%lf",&a.price);
    return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    if(a.id==t)
    return 0;  //returns 0 if book exits
    return 1; //return 1 if it not
}
void disporders()
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("*********************************Food Items*****************************");
    gotoxy(1,2);
    printf("-------------------------------------------------------------------------");
    gotoxy(1,3);
    printf(" Food Name          Food ID               Quantity                PRICE ");
    gotoxy(1,4);
    printf("-------------------------------------------------------------------------");
    j=5;
    fp=fopen("cafe.txt","r");
    while(fread(&a,sizeof(a),1,fp))
    {
        gotoxy(3,j);
        printf("%s",a.name);
        gotoxy(23,j);
        printf("%d",a.id);
        gotoxy(46,j);
        printf("%d",a.qnty);
        gotoxy(67,j);
        printf("%.2lf",a.price);
        j++;
        }
        fclose(fp);
        gotoxy(40,21);
        printf("Enter any key to go Mainmenu:");
        if(getch()) mainmenu();
}
void login()
{
    int i=0;
    char ch;
    system("cls");
    gotoxy(20,3);
    printf("\xdb\xdb\xdb\xdb ADMIN PANEL \xdb\xdb\xdb\xdb\n");
    gotoxy(20,6);
    printf("USERNAME: ");
    gotoxy(20,8);
    printf("PASSWORD: ");
    gotoxy(30,6);
    scanf("%s",uname);
    gotoxy(30,8);
    while(ch!=13){
        ch=getch();
        if(ch!=13 && ch!=8){
        putch('*');
        upass[i] = ch;
        i++;
        }
    }
    pass[i] = '\0';
    if(strcmp(upass,pass)==0&&strcmp(uname,user)==0){
        gotoxy(20,12);
        printf("Successfully Logged in\n");
        gotoxy(20,13);
        printf("Please enter any key to continue....");
        getch();
        mainmenu();
    }
    else{
        gotoxy(20,12);
        printf("You'r Password or Username is incorrect\n");
        gotoxy(20,13);
        printf("Please Try Again...");
        getch();
        login();
    }

}
void welcome()
{
    gotoxy(1,1);
    printf("*********************** This is a Canteen Management System *****************");
    gotoxy(25,3);
    printf("\xdb\xdb\xdb\xdb Welcome To 'Happy Cafe' \xdb\xdb\xdb\xdb ");
    gotoxy(30,5);
    printf("  [STUDENT PROJECT]");
    gotoxy(1,6);
    printf("Submitted To:");
    gotoxy(1,8);
    printf("REZWANA SULTANA");
    gotoxy(1,9);
    printf("Department of CSE");
    gotoxy(1,10);
    printf("Daffodil International University");
    gotoxy(50,11);
    printf("Project Made By:");
    gotoxy(45,13);
    printf("1. Sakib Ahmad   : 181-15-10776");
    gotoxy(45,14);
    printf("2. Antara Biswas : 181-15-10644");
    gotoxy(45,15);
    printf("3. MD.AL-AMIN    : 181-15-10510");
    gotoxy(45,17);
    printf("Student of CSE Department");
    gotoxy(45,18);
    printf("Daffodil international University");
    gotoxy(25,23);
    printf("Enter any key to continue.....");
    getch();
    login();
}
void fireexit()
{
    system("cls");
    gotoxy(25,8);
    printf("Are you sure?[Y/N]");
    if(getch()=='y') exit(0);
    else mainmenu();
}
void box1()
{
    gotoxy(10,5);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10,6);
    printf("\xB2");gotoxy(36,6);printf("\xB2");
    gotoxy(10,7);
    printf("\xB2");gotoxy(36,7);printf("\xB2");
    gotoxy(10,8);
    printf("\xB2");gotoxy(36,8);printf("\xB2");
    gotoxy(10,9);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
}
void box2()
{
    gotoxy(40,5);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(40,6);
    printf("\xB2");gotoxy(66,6);printf("\xB2");
    gotoxy(40,7);
    printf("\xB2");gotoxy(66,7);printf("\xB2");
    gotoxy(40,8);
    printf("\xB2");gotoxy(66,8);printf("\xB2");
    gotoxy(40,9);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
}
void box3()
{
    gotoxy(10,13);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10,14);
    printf("\xB2");gotoxy(36,14);printf("\xB2");
    gotoxy(10,15);
    printf("\xB2");gotoxy(36,15);printf("\xB2");
    gotoxy(10,16);
    printf("\xB2");gotoxy(36,16);printf("\xB2");
    gotoxy(10,17);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
}
void box4()
{
    gotoxy(40,13);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(40,14);
    printf("\xB2");gotoxy(66,14);printf("\xB2");
    gotoxy(40,15);
    printf("\xB2");gotoxy(66,15);printf("\xB2");
    gotoxy(40,16);
    printf("\xB2");gotoxy(66,16);printf("\xB2");
    gotoxy(40,17);printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
}

