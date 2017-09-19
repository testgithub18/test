
#include<conio.h>
#include<string.h>
#include <stdio.h>
#define MAX 100
#include<stdlib.h>
#include <ctype.h>
#include <windows.h>
#include<stdlib.h>



typedef struct hocsinh { //cung cấp một tên cho người sử dụng kiểu dữ liệu
  char hoten[50];
  char lop[50];
  char masinhvien[50];
  char quequan[50];
  char namsinh[50];
  char diemtb[50];
} HOCSINH;
HOCSINH danhsach[MAX];

typedef struct sapxep
{
  char chuoi1[50];
  char chuoi2[50];
} SAPXEP;
SAPXEP list[MAX];
int choise;
int stt;

int numrecords = 0;
char filename[] = "D:/hoangkimcuong.txt";

void data()
{
  char c;
  int start, nrec;
  FILE *fp;
  long curpos, length;
  start = 0;

  if ((fp = fopen(filename, "a+")) == NULL)
    printf("\nKhong co du lieu ve tap tin.\nChuong trinh tien hanh tao file moi tai duong dan D:/hoangcuong.txt ", filename);
  else
  {
    curpos = ftell(fp); //
    fseek(fp, 0L, SEEK_END); //
    length = ftell(fp); //
    fseek(fp, curpos, SEEK_SET); //
    nrec = length / sizeof(HOCSINH);//tinh so hang trong du lieu
    fread(&danhsach[start], sizeof(HOCSINH), nrec, fp);
    // sizeof() là hàm trả ra dung lượng bộ nhớ
    //được cấp phát cho phần tử ở trong sizeof()
    fclose(fp);
    printf("\n                ... ... ... LOADING DATA ... ... ...");
    printf("\n       Cap nhat %d thong tin hoc sinh tu co so du lieu.\n", nrec);
    numrecords = numrecords + nrec;
  }
}

void nhapmoi()
{
    int done = 0;
    char hoten[50];
    char a[50];// chuan hoa nam sinh
    char ngay[50],thang[50],nam[50];
    int i,l,test,j;
    do
    {
    printf("\nNhap Ho ten (de trong neu muon thoat) : ");
    gets(hoten);
    chuanhoachuoi(hoten);
    if (strlen(hoten) == 0)
      done = 1;
    else
    {
    strcpy(danhsach[numrecords].hoten, hoten);
    //Ma so sinh vien bao gom 4 chu so.
    //So dau tien la mot so lon hon 1.
    printf("Nhap Ma sinh vien : ");
    gets(a);
    l=strlen(a);
    test=0;
        while (test==0)
            {
            l=strlen(a);
           // printf(" \n TEST do dai chuoi:%d",l);
                if (l!=8)
                    { printf("\nNhap sai chuan thong tin ma sinh vien.");
                    test++;
                    }
                if (test>0)
                    {
                    printf("\nNhap Ma sinh vien (8 chu so): ");
                    gets(a);
                    test=0;
                    }
                else test=1;
            }
     strcpy(danhsach[numrecords].masinhvien,a);
    //gets(danhsach[numrecords].masinhvien);
    printf("Nhap Lop : ");
    gets(danhsach[numrecords].lop);
    printf("Nhap Nam sinh : ");
    gets(a);
    test=0;
        while (test==0)
            {
            l=strlen(a);
           // printf(" \n TEST do dai chuoi:%d",l);
                if (l!=10)
                    { printf("\nNhap sai chuan thong tin nam sinh.");
                    test++;
                    }
                else
                {
                    for (i=0;i<2;i++)
                    {
                        ngay[i]=a[i];
                    }
                    ngay[i+1]= '\0';
                    l=atoi(ngay);
                    //printf(" \n TEST ngay:%d",l);
                    if (l>31)
                        { printf("\nNhap sai chuan thong tin ngay sinh.");
                        //printf("\n i= %d",i);
                        test++;
                        }

                    for (i=3;i<5;i++)
                    {
                        thang[i-3]=a[i];
                    }
                    thang[i+1-3]= '\0';
                    l=atoi(thang);
                    //printf(" \n TEST thang:%d",l);
                    if (l>12)
                        { printf("\nNhap sai chuan thong tin thang sinh.");
                        test++;
                        }

                    for (i=6;i<10;i++)
                    {
                        nam[i-6]=a[i];
                    }
                    nam[i+1-6]= '\0';
                    l=atoi(nam);
                   //printf(" \n TEST nam:%d",l);
                    if (l>2017)
                        { printf("\nNhap sai chuan thong tin nam sinh.");
                        test++;
                       }

                }
                if (test>0)
                    {
                    printf("\nNhap Nam sinh : ");
                    gets(a);
                    test=0;
                    }
                else test=1;
            }
    strcpy(danhsach[numrecords].namsinh,a);
    //gets(danhsach[numrecords].namsinh);
    printf("Nhap Que quan : ");
    gets(danhsach[numrecords].quequan);
    chuanhoachuoi(danhsach[numrecords].quequan);
    printf("Nhap diem trung binh: ");
    gets(danhsach[numrecords].diemtb);
    numrecords++;
   }
  } while (!done);
}

void lietke()
{
  int i;

  if (numrecords != 0)
  {
    printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
    printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
    printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
    for (i=0; i<numrecords; i++)
    {
      printf("\n| %3d | ", i+1);
      printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
             danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
    }
    printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
  }
  getch();
}

void luudata()
{
  FILE *fp;

  if ((fp = fopen(filename, "w+")) == NULL)
    printf("\nKhong thay ghi tap tin %s", filename);
  else
  {
    fwrite(&danhsach[0], sizeof(HOCSINH), numrecords, fp);
    fclose(fp);
    printf("\nLUU CO SO DU LIEU... ...\nHien tai luu tru  %d thong tin sinh vien.", numrecords);
    getch();
  }
}


// Sap xep
void SapXepMSV()
{
int i,test,luachon;
int n=numrecords;
int a[n];
// gan gia tri

for(i=0; i<numrecords ;i++)
    {
     a[i] = atoi(danhsach[i].masinhvien);
    }
 int imin,j,temp,t;
printf("\n Module sap xep theo ma sinh vien:");
printf("\n Nhap 1: De lua chon thuat toan sap xep chon.");
printf("\n Nhap 2: De lua chon thuat toan sap xep noi bot.");
printf("\n Nhap 3: De lua chon thuat toan sap xep chen.");
printf("\n Nhap: ");
scanf("%d",&luachon);
 switch (luachon)
    {
        case 1:printf("\nDang su dung thuat toan sap xep chon de sap xep lai du lieu....\n");
           // sap xep chon

            for (i=0; i<=n-2; i++)
            {
            imin = a[i]; //Tìm imin
            for (j=i+1; j<=n-1; j++)
            if (a[j] < imin)
            {
                imin = a[j];
                 //Hoán đổi a[i] và a[j]
                 temp = a[i];
                 a[i] = a[j];
                 a[j] = temp;
            }
            }
            break;
        case 2:printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");

            for (i=0; i<n; i++)
            {
            for (j=n-1; j>i; j--)
                if(a[j - 1] > a[j])
            {
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
            }

            break;
        case 3: printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");
            // sap xep chen

            for( i=1;i<n;i++)
            {
            j=i-1;
            t=a[i];
            while(t<a[j]&&j>=0)
            {
            a[j+1]=a[j];
            j--;
            }
            a[j+1]=t;
            }

            break;
        default: printf("\nNhap sai so thu tu thuat toan.\n Yeu cau nhap lai ");
    }



//printf("\n SAU SAP XEP ");
// doi choi cac gia tri
    char trunggianhoten[50];
  char trunggianlop[50];
  char trunggianmasinhvien[50];
  char trunggianquequan[50];
  char trunggiannamsinh[50];
  char trunggiandiemtb[50];
//printf("\n tien hanh doi cho trong vong for");

for (i=0;i<numrecords;i++)
{
    for (j=0;j<numrecords;j++)
    {
    test = atoi(danhsach[j].masinhvien);
    //printf("\n%d",test);
    if (test==a[i])
        {
        //if (i!=j)
       // printf("\n Hoan doi vi tri cua %d cho %d",i,j);
        //printf("\nDoi CHO cho %d va %d",i,j);
        strcpy(trunggianmasinhvien,danhsach[i].masinhvien);
        strcpy(danhsach[i].masinhvien,danhsach[j].masinhvien);
        strcpy(danhsach[j].masinhvien,trunggianmasinhvien);

        strcpy(trunggianhoten,danhsach[i].hoten);
        strcpy(danhsach[i].hoten,danhsach[j].hoten);
        strcpy(danhsach[j].hoten,trunggianhoten);

        strcpy(trunggianlop,danhsach[i].lop);
        strcpy(danhsach[i].lop,danhsach[j].lop);
        strcpy(danhsach[j].lop,trunggianlop);

        strcpy(trunggiannamsinh,danhsach[i].namsinh);
        strcpy(danhsach[i].namsinh,danhsach[j].namsinh);
        strcpy(danhsach[j].namsinh,trunggiannamsinh);

        strcpy(trunggianquequan,danhsach[i].quequan);
        strcpy(danhsach[i].quequan,danhsach[j].quequan);
        strcpy(danhsach[j].quequan,trunggianquequan);

        strcpy(trunggiandiemtb,danhsach[i].diemtb);
        strcpy(danhsach[i].diemtb,danhsach[j].diemtb);
        strcpy(danhsach[j].diemtb,trunggiandiemtb);
        }
    }

}

}

void SapXepten()
{
     int length;
    int i,j,k,dodai;
    int ret; // so sanh hai chuoi
    int n=numrecords;
    char tendaydu[50],ten[50];
    // sao chep chuoi
    // tach ten
    for (j=0;j<n;j++)
    {
        strcpy(tendaydu,danhsach[j].hoten);
        dodai=strlen(tendaydu);

            for((i=dodai-1);i>=0;i--)
        {
            if (tendaydu[i]==' ')
            {

            strcpy(ten,tendaydu+1+i); // copy tu ky tu thu i +1
            break;
        }
        }
        strcpy(list[j].chuoi1,ten);

     }

/*
    printf("\n Test Tach ten:");
    for (i=0;i<n;i++)
    {
        printf("\n Ho ten: %s",danhsach[i].hoten);
        printf("\n Ten: %s",list[i].chuoi1);
    }
*/
    // copy sang chuoi trung gian
    for (i=0;i<n;i++)
    {
        strcpy(list[i].chuoi2,list[i].chuoi1);
    }


    int luachon;
    char imin[50],temp[50],t[50];
    printf("\n Module sap xep theo ho ten sinh vien:");
    printf("\n Nhap 1: De lua chon thuat toan sap xep chon.");
    printf("\n Nhap 2: De lua chon thuat toan sap xep noi bot.");
    printf("\n Nhap 3: De lua chon thuat toan sap xep chen.");
    printf("\n Nhap: ");
    scanf("%d",&luachon);
     switch (luachon)
        {
                    case 1:printf("\nDang su dung thuat toan sap xep chon de sap xep lai du lieu....\n");
                   // sap xep chon

                    for (i=0; i<=n-2; i++)
                    {
                    strcpy(imin,list[i].chuoi2);
                //    imin = a[i]; //Tìm imin
                    for (j=i+1; j<=n-1; j++)
                        {
                            ret=strcmp(list[j].chuoi2,imin);
                            if (ret < 0)
                                {
                                    strcpy(imin,list[j].chuoi2);
                                    //imin = a[j];
                                     //Hoán đổi a[i] và a[j]
                                     strcpy(temp,list[i].chuoi2);
                                     //temp = a[i];
                                     strcpy(list[i].chuoi2,list[j].chuoi2);
                                     //a[i] = a[j];
                                     strcpy(list[j].chuoi2,temp);
                                     //a[j] = temp;
                                }
                        }
                    }
                    break;


                   case 2:printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");

                    for (i=0; i<n; i++)
                        {
                        for (j=n-1; j>i; j--)
                            {
                                ret=strcmp(list[j-1].chuoi2,list[j].chuoi2);
                                if(ret>0)
                                    {
                                    //temp = a[j-1];
                                    strcpy(temp,list[j-1].chuoi2);
                                    //a[j-1] = a[j];
                                    strcpy(list[j-1].chuoi2,list[j].chuoi2);
                                    //a[j] = temp;
                                    strcpy(list[j].chuoi2,temp);
                                    }
                            }
                        }

                    break;

                    case 3: printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");


                        for( i=1;i<n;i++)
                        {
                            j=i-1;
                            strcpy(t,list[i].chuoi2);
                            //t=a[i];
                            ret =strcmp(t,list[j].chuoi2);
                            // while(t<a[j]&&j>=0)
                            while(ret<0&&j>=0)
                            {
                            strcpy(list[j+1].chuoi2,list[j].chuoi2);
                            //a[j+1]=a[j];
                            j--;
                            }
                            strcpy(list[j+1].chuoi2,t);
                            //a[j+1]=t;
                        }


                        break;
                        default: printf("\nNhap sai so thu tu thuat toan.\n Yeu cau nhap lai ");

        }



/*
   printf("\nTEST SAU SAP XEP TEN:");
    for (i=0;i<n;i++)
    {

        printf("\n Ten: %d %s      %d %s ",i,list[i].chuoi1,i,list[i].chuoi2);
    }
*/
    char trunggianhoten[50];
    char trunggianlop[50];
    char trunggianmasinhvien[50];
    char trunggianquequan[50];
    char trunggiannamsinh[50];
    char trunggiandiemtb[50];

//printf("\n tien hanh doi cho trong vong for");

    int x;
    for (i=0;i<numrecords;i++)
    {

        for (j=0;j<numrecords;j++)
        {
            strcpy(tendaydu,danhsach[j].hoten);
            dodai=strlen(tendaydu);
            //printf("\n1 TEST TEN %s",tendaydu);
           // printf("\n2 test do dai %d",dodai);

                for((x=dodai-1);x>=0;x--)
                {
                if (tendaydu[x]==' ')
                    {
                    strcpy(ten,tendaydu+1+x); // copy tu ky tu thu i +1
                    break;
                    }
                }
               // printf("\n3 VOng lap i:%d   j: %d",i,j);
                //printf(" \n4 TEST TEN %s\n",ten);

            ret=strcmp(ten,list[i].chuoi2);
            if (ret==0)
            {
           // if (i!=j)
           // printf("\n Hoan doi vi tri cua %d cho %d",i,j);
            //printf("\nDoi CHO cho %d va %d",i,j);
            strcpy(trunggianmasinhvien,danhsach[i].masinhvien);
            strcpy(danhsach[i].masinhvien,danhsach[j].masinhvien);
            strcpy(danhsach[j].masinhvien,trunggianmasinhvien);

            strcpy(trunggianhoten,danhsach[i].hoten);
            strcpy(danhsach[i].hoten,danhsach[j].hoten);
            strcpy(danhsach[j].hoten,trunggianhoten);

            strcpy(trunggianlop,danhsach[i].lop);
            strcpy(danhsach[i].lop,danhsach[j].lop);
            strcpy(danhsach[j].lop,trunggianlop);

            strcpy(trunggiannamsinh,danhsach[i].namsinh);
            strcpy(danhsach[i].namsinh,danhsach[j].namsinh);
            strcpy(danhsach[j].namsinh,trunggiannamsinh);

            strcpy(trunggianquequan,danhsach[i].quequan);
            strcpy(danhsach[i].quequan,danhsach[j].quequan);
            strcpy(danhsach[j].quequan,trunggianquequan);

            strcpy(trunggiandiemtb,danhsach[i].diemtb);
            strcpy(danhsach[i].diemtb,danhsach[j].diemtb);
            strcpy(danhsach[j].diemtb,trunggiandiemtb);


            }

        }

    }

}

void SapXepLop()
{
    int i,j,k,dodai;
    int ret; // so sanh hai chuoi
    int n=numrecords;
    char tendaydu[50],ten[50];
    // sao chep chuoi

    for (j=0;j<n;j++)
    {

        strcpy(list[j].chuoi1,danhsach[j].lop);

     }

    // copy sang chuoi trung gian
    for (i=0;i<n;i++)
    {
        strcpy(list[i].chuoi2,list[i].chuoi1);
    }

    int luachon;
    char imin[50],temp[50],t[50];
    printf("\n Module sap xep theo Lop cua sinh vien:");
    printf("\n Nhap 1: De lua chon thuat toan sap xep chon.");
    printf("\n Nhap 2: De lua chon thuat toan sap xep noi bot.");
    printf("\n Nhap 3: De lua chon thuat toan sap xep chen.");
    printf("\n Nhap: ");
    scanf("%d",&luachon);
     switch (luachon)
        {
                    case 1:printf("\nDang su dung thuat toan sap xep chon de sap xep lai du lieu....\n");
                   // sap xep chon

                    for (i=0; i<=n-2; i++)
                    {
                    strcpy(imin,list[i].chuoi2);
                //    imin = a[i]; //Tìm imin
                    for (j=i+1; j<=n-1; j++)
                        {
                            ret=strcmp(list[j].chuoi2,imin);
                            if (ret < 0)
                                {
                                    strcpy(imin,list[j].chuoi2);
                                    //imin = a[j];
                                     //Hoán đổi a[i] và a[j]
                                     strcpy(temp,list[i].chuoi2);
                                     //temp = a[i];
                                     strcpy(list[i].chuoi2,list[j].chuoi2);
                                     //a[i] = a[j];
                                     strcpy(list[j].chuoi2,temp);
                                     //a[j] = temp;
                                }
                        }
                    }
                    break;


                   case 2:printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");

                    for (i=0; i<n; i++)
                        {
                        for (j=n-1; j>i; j--)
                            {
                                ret=strcmp(list[j-1].chuoi2,list[j].chuoi2);
                                if(ret>0)
                                    {
                                    //temp = a[j-1];
                                    strcpy(temp,list[j-1].chuoi2);
                                    //a[j-1] = a[j];
                                    strcpy(list[j-1].chuoi2,list[j].chuoi2);
                                    //a[j] = temp;
                                    strcpy(list[j].chuoi2,temp);
                                    }
                            }
                        }

                    break;

                    case 3: printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");


                        for( i=1;i<n;i++)
                        {
                            j=i-1;
                            strcpy(t,list[i].chuoi2);
                            //t=a[i];
                            ret =strcmp(t,list[j].chuoi2);
                            // while(t<a[j]&&j>=0)
                            while(t<0&&j>=0)
                            {
                            strcpy(list[j+1].chuoi2,list[j].chuoi2);
                            //a[j+1]=a[j];
                            j--;
                            }
                            strcpy(list[j+1].chuoi2,t);
                            //a[j+1]=t;
                        }


                        break;
                        default: printf("\nNhap sai so thu tu thuat toan.\n Yeu cau nhap lai ");

        }

/*

   printf("\nTEST SAU SAP XEP TEN:");
    for (i=0;i<n;i++)
    {
        printf("\n Ho ten: %s",danhsach[i].hoten);
        printf("\n Ten: %s      %s ",list[i].chuoi1,list[i].chuoi2);
    }
*/


    char trunggianhoten[50];
    char trunggianlop[50];
    char trunggianmasinhvien[50];
    char trunggianquequan[50];
    char trunggiannamsinh[50];
    char rong1[50]="cuongepzai";
    char rong2[50]="cuongepzaiqw";
    char trunggiandiemtb[50];
//printf("\n tien hanh doi cho trong vong for");

    for (i=0;i<numrecords;i++)
    {
        for (j=0;j<numrecords;j++)
        {
            ret=strcmp(list[i].chuoi2,danhsach[j].lop);
            if (ret==0)
            {
            //if (i!=j)
            //printf("\n Hoan doi vi tri cua %d cho %d",i,j);
            //printf("\nDoi CHO cho %d va %d",i,j);
            strcpy(trunggianmasinhvien,danhsach[i].masinhvien);
            strcpy(danhsach[i].masinhvien,danhsach[j].masinhvien);
            strcpy(danhsach[j].masinhvien,trunggianmasinhvien);

            strcpy(trunggianhoten,danhsach[i].hoten);
            strcpy(danhsach[i].hoten,danhsach[j].hoten);
            strcpy(danhsach[j].hoten,trunggianhoten);

            strcpy(trunggianlop,danhsach[i].lop);
            strcpy(danhsach[i].lop,danhsach[j].lop);
            strcpy(danhsach[j].lop,trunggianlop);

            strcpy(trunggiannamsinh,danhsach[i].namsinh);
            strcpy(danhsach[i].namsinh,danhsach[j].namsinh);
            strcpy(danhsach[j].namsinh,trunggiannamsinh);

            strcpy(trunggianquequan,danhsach[i].quequan);
            strcpy(danhsach[i].quequan,danhsach[j].quequan);
            strcpy(danhsach[j].quequan,trunggianquequan);


            strcpy(trunggiandiemtb,danhsach[i].diemtb);
            strcpy(danhsach[i].diemtb,danhsach[j].diemtb);
            strcpy(danhsach[j].diemtb,trunggiandiemtb);

            strcpy(list[i].chuoi1,rong1);
            strcpy(list[j].chuoi1,rong2);
            }
        }

    }
}

void SapXepQueQuan()
{
    int i,j,k,dodai;
    int ret; // so sanh hai chuoi
    int n=numrecords;
    char tendaydu[50],ten[50];
    char rong[50]="1";
    // sao chep chuoi
    memset(ten, '\0', sizeof(ten));
    for (j=0;j<n;j++)
    {
        strcpy(tendaydu,danhsach[j].quequan);
        dodai=strlen(tendaydu);

            for(i=0;i<dodai;i++)
        {
            if (tendaydu[i]==' ')
            {
            strcpy(ten,rong);
            //printf("\n TEN: %s",ten);
            strncpy(ten,tendaydu,1); // copy
            break;
            }
        }
        //printf("\n TEN: %s",ten);
        strcpy(list[j].chuoi1,ten);

     }

    // copy sang chuoi trung gian
    for (i=0;i<n;i++)
    {
        strcpy(list[i].chuoi2,list[i].chuoi1);
    }


    int luachon;
    char imin[50],temp[50],t[50];
    printf("\n Module sap xep theo Que quan cua sinh vien:");
    printf("\n Nhap 1: De lua chon thuat toan sap xep chon.");
    printf("\n Nhap 2: De lua chon thuat toan sap xep noi bot.");
    printf("\n Nhap 3: De lua chon thuat toan sap xep chen.");
    printf("\n Nhap: ");
    scanf("%d",&luachon);
     switch (luachon)
        {
                    case 1:printf("\nDang su dung thuat toan sap xep chon de sap xep lai du lieu....\n");
                   // sap xep chon

                    for (i=0; i<=n-2; i++)
                    {
                    strcpy(imin,list[i].chuoi2);
                //    imin = a[i]; //Tìm imin
                    for (j=i+1; j<=n-1; j++)
                        {
                            ret=strcmp(list[j].chuoi2,imin);
                            if (ret < 0)
                                {
                                    strcpy(imin,list[j].chuoi2);
                                    //imin = a[j];
                                     //Hoán đổi a[i] và a[j]
                                     strcpy(temp,list[i].chuoi2);
                                     //temp = a[i];
                                     strcpy(list[i].chuoi2,list[j].chuoi2);
                                     //a[i] = a[j];
                                     strcpy(list[j].chuoi2,temp);
                                     //a[j] = temp;
                                }
                        }
                    }
                    break;


                   case 2:printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");

                    for (i=0; i<n; i++)
                        {
                        for (j=n-1; j>i; j--)
                            {
                                ret=strcmp(list[j-1].chuoi2,list[j].chuoi2);
                                if(ret>0)
                                    {
                                    //temp = a[j-1];
                                    strcpy(temp,list[j-1].chuoi2);
                                    //a[j-1] = a[j];
                                    strcpy(list[j-1].chuoi2,list[j].chuoi2);
                                    //a[j] = temp;
                                    strcpy(list[j].chuoi2,temp);
                                    }
                            }
                        }

                    break;

                    case 3: printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");


                        for( i=1;i<n;i++)
                        {
                            j=i-1;
                            strcpy(t,list[i].chuoi2);
                            //t=a[i];
                            ret =strcmp(t,list[j].chuoi2);
                            // while(t<a[j]&&j>=0)
                            while(t<0&&j>=0)
                            {
                            strcpy(list[j+1].chuoi2,list[j].chuoi2);
                            //a[j+1]=a[j];
                            j--;
                            }
                            strcpy(list[j+1].chuoi2,t);
                            //a[j+1]=t;
                        }


                        break;
                        default: printf("\nNhap sai so thu tu thuat toan.\n Yeu cau nhap lai ");

        }

/*

   printf("\nTEST SAU SAP XEP TEN:");
    for (i=0;i<n;i++)
    {
        printf("\n Ho ten: %s",danhsach[i].hoten);
        printf("\n Ten: %s      %s ",list[i].chuoi1,list[i].chuoi2);
    }
*/
    char trunggianhoten[50];
    char trunggianlop[50];
    char trunggianmasinhvien[50];
    char trunggianquequan[50];
    char trunggiannamsinh[50];
    char trunggiandiemtb[50];
//printf("\n tien hanh doi cho trong vong for");
    int x;
    for (i=0;i<numrecords;i++)
    {
        for (j=0;j<numrecords;j++)
        {
            strcpy(tendaydu,danhsach[j].quequan);
            dodai=strlen(tendaydu);
            //printf("\n1 TEST TEN %s",tendaydu);
           //printf("\n2 test do dai %d",dodai);

                for(x=0;x<dodai;x++)
            {
                if (tendaydu[x]==' ')
                {
                strcpy(ten,rong);
                //printf("\n TEN: %s",ten);
                strncpy(ten,tendaydu,1); // copy
                break;
                }
            }
            // printf("\n3 VOng lap i:%d   j: %d",i,j);
            //printf(" \n4 TEST TEN %s\n",ten);
            ret=strcmp(ten,list[i].chuoi2);
            if (ret==0)
            {
          //  if (i!=j)
          //  printf("\n Hoan doi vi tri cua %d cho %d",i,j);
            //printf("\nDoi CHO cho %d va %d",i,j);
            strcpy(trunggianmasinhvien,danhsach[i].masinhvien);
            strcpy(danhsach[i].masinhvien,danhsach[j].masinhvien);
            strcpy(danhsach[j].masinhvien,trunggianmasinhvien);

            strcpy(trunggianhoten,danhsach[i].hoten);
            strcpy(danhsach[i].hoten,danhsach[j].hoten);
            strcpy(danhsach[j].hoten,trunggianhoten);

            strcpy(trunggianlop,danhsach[i].lop);
            strcpy(danhsach[i].lop,danhsach[j].lop);
            strcpy(danhsach[j].lop,trunggianlop);

            strcpy(trunggiannamsinh,danhsach[i].namsinh);
            strcpy(danhsach[i].namsinh,danhsach[j].namsinh);
            strcpy(danhsach[j].namsinh,trunggiannamsinh);

            strcpy(trunggianquequan,danhsach[i].quequan);
            strcpy(danhsach[i].quequan,danhsach[j].quequan);
            strcpy(danhsach[j].quequan,trunggianquequan);


            strcpy(trunggiandiemtb,danhsach[i].diemtb);
            strcpy(danhsach[i].diemtb,danhsach[j].diemtb);
            strcpy(danhsach[j].diemtb,trunggiandiemtb);

            }
        }

    }
}

void SapXepNamsinh()
{
    int i,j,test,luachon,dodai;
    int n=numrecords;
    int a[n],b[n];
    char tg[50],tg1[50];
    // gan gia tri

    for(i=0; i<numrecords ;i++)
        {
            strcpy(tg,danhsach[i].namsinh);
            dodai=strlen(tg);
            for((j=dodai-1);j>=0;j--)
            {
                if (tg[j]=='/')
                {
                strcpy(tg1,tg+1+j); // copy tu ky tu thu i +1
                break;
            }
            }

            a[i] = atoi(tg1);
            b[i]=a[i];
        }

     int imin,temp,t;
    printf("\n Module sap xep theo Nam sinh cua sinh vien:");
    printf("\n Nhap 1: De lua chon thuat toan sap xep chon.");
    printf("\n Nhap 2: De lua chon thuat toan sap xep noi bot.");
    printf("\n Nhap 3: De lua chon thuat toan sap xep chen.");
    printf("\n Nhap: ");
    scanf("%d",&luachon);
     switch (luachon)
        {
        case 1:printf("\nDang su dung thuat toan sap xep chon de sap xep lai du lieu....\n");
           // sap xep chon

            for (i=0; i<=n-2; i++)
            {
            imin = a[i]; //Tìm imin
            for (j=i+1; j<=n-1; j++)
            if (a[j] < imin)
            {
                imin = a[j];
                 //Hoán đổi a[i] và a[j]
                 temp = a[i];
                 a[i] = a[j];
                 a[j] = temp;
            }
            }
            break;
        case 2:printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");

            for (i=0; i<n; i++)
            {
            for (j=n-1; j>i; j--)
                if(a[j - 1] > a[j])
            {
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
            }

            break;
        case 3: printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");
            // sap xep chen

            for( i=1;i<n;i++)
            {
            j=i-1;
            t=a[i];
            while(t<a[j]&&j>=0)
            {
            a[j+1]=a[j];
            j--;
            }
            a[j+1]=t;
            }

            break;
        default: printf("\nNhap sai so thu tu thuat toan.\n Yeu cau nhap lai ");
    }


    //printf("\n SAU SAP XEP ");
    // doi choi cac gia tri
        char trunggianhoten[50];
      char trunggianlop[50];
      char trunggianmasinhvien[50];
      char trunggianquequan[50];
      char trunggiannamsinh[50];
      char trunggiandiemtb[50];
    //printf("\n tien hanh doi cho trong vong for");
        int x,c;
    for (i=0;i<numrecords;i++)
    {
        for (j=0;j<numrecords;j++)
        {
        strcpy(tg,danhsach[j].namsinh);
            dodai=strlen(tg);
            for((x=dodai-1);x>=0;x--)
            {
                if (tg[x]=='/')
                {
                strcpy(tg1,tg+1+x); // copy tu ky tu thu i +1
                break;
            }
            }

            c = atoi(tg1);
        if (a[i]==c)
        {
       // if (i!=j)
     //   printf("\n Hoan doi vi tri cua %d cho %d",i,j);
        //printf("\nDoi CHO cho %d va %d",i,j);
        strcpy(trunggianmasinhvien,danhsach[i].masinhvien);
        strcpy(danhsach[i].masinhvien,danhsach[j].masinhvien);
        strcpy(danhsach[j].masinhvien,trunggianmasinhvien);

        strcpy(trunggianhoten,danhsach[i].hoten);
        strcpy(danhsach[i].hoten,danhsach[j].hoten);
        strcpy(danhsach[j].hoten,trunggianhoten);

        strcpy(trunggianlop,danhsach[i].lop);
        strcpy(danhsach[i].lop,danhsach[j].lop);
        strcpy(danhsach[j].lop,trunggianlop);

        strcpy(trunggiannamsinh,danhsach[i].namsinh);
        strcpy(danhsach[i].namsinh,danhsach[j].namsinh);
        strcpy(danhsach[j].namsinh,trunggiannamsinh);

        strcpy(trunggianquequan,danhsach[i].quequan);
        strcpy(danhsach[i].quequan,danhsach[j].quequan);
        strcpy(danhsach[j].quequan,trunggianquequan);

        strcpy(trunggiandiemtb,danhsach[i].diemtb);
        strcpy(danhsach[i].diemtb,danhsach[j].diemtb);
        strcpy(danhsach[j].diemtb,trunggiandiemtb);

        a[i]=9999;
        }
    }

}

}

void SapXepDiemTb()
{
    int i,j,test,luachon;
    char truocchuoi[50],sauchuoi[50];
    int n=numrecords;
    float b[n],a[n];// cai nay de sap xep
    float truoc,sau;
    float chuasx[n];
    float dasx[n];
    memset(truocchuoi, '\0', sizeof(truocchuoi));
    char tg[50];
    // gan gia tri

    for(i=0; i<numrecords ;i++)
        {
        strcpy(tg,danhsach[i].diemtb); // copy sau
        strncpy(truocchuoi,tg,1); // copy truoc
        strcpy(sauchuoi,tg+2); // copy sau
        // chuyen chuoi ve so
        truoc = atoi(truocchuoi);
        sau= atoi(sauchuoi);
        truoc = atoi(truocchuoi);
        sau= atoi(sauchuoi);
        a[i]=truoc+(sau/10);
        b[i]=a[i];
        }
   //for(i=0;i<n;i++)
   //printf("\nTEST %d: %f",i,a[i]);

    float imin,temp,t;
    printf("\n Module sap xep theo Diem trung binh cua sinh vien:");
    printf("\n Nhap 1: De lua chon thuat toan sap xep chon.");
    printf("\n Nhap 2: De lua chon thuat toan sap xep noi bot.");
    printf("\n Nhap 3: De lua chon thuat toan sap xep chen.");
    printf("\n Nhap: ");
    scanf("%d",&luachon);
     switch (luachon)
    {
        case 1:printf("\nDang su dung thuat toan sap xep chon de sap xep lai du lieu....\n");
           // sap xep chon

            for (i=0; i<=n-2; i++)
            {
            imin = a[i]; //Tìm imin
            for (j=i+1; j<=n-1; j++)
            if (a[j] > imin)
            {
                imin = a[j];
                 //Hoán đổi a[i] và a[j]
                 temp = a[i];
                 a[i] = a[j];
                 a[j] = temp;
            }
            }
            // sau doan nay mang a da bi thay doi, da duoc sap xep
            // anh oi, temp la kieu int, a[i] la kieu float ah
            break;
        case 2:printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....\n");

            for (i=0; i<n; i++)
            {
            for (j=n-1; j>i; j--)
                if(a[j - 1] > a[j])
            {
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
            }

            break;
        case 3: printf("\nDang su dung thuat toan noi bot de sap xep lai du lieu....(CO LOI)\n");
            // sap xep chen


            for( i=1;i<n;i++)
            {
            j=i-1;
            t=a[i];
            while(t<a[j]&&j>=0)
            {
            a[j+1]=a[j];
            j--;
            }
            a[j+1]=t;
            }

            break;
        default: printf("\nNhap sai so thu tu thuat toan.\n Yeu cau nhap lai ");
    }

  // for(i=0;i<n;i++)
   // printf("\nTEST %d: %f",i,a[i]);

// doi choi cac gia tri
  char trunggianhoten[50];
  char trunggianlop[50];
  char trunggianmasinhvien[50];
  char trunggianquequan[50];
  char trunggiannamsinh[50];
  char trunggiandiemtb[50];
  float c;
//printf("\n tien hanh doi cho trong vong for");

    for (i=0;i<numrecords;i++)
    {
        for (j=0;j<numrecords;j++)
        {
        strcpy(tg,danhsach[j].diemtb); // copy sau
        strncpy(truocchuoi,tg,1); // copy truoc
        strcpy(sauchuoi,tg+2); // copy sau
        // chuyen chuoi ve so
        truoc = atoi(truocchuoi);
        sau= atoi(sauchuoi);
        truoc = atoi(truocchuoi);
        sau= atoi(sauchuoi);
        c=truoc+(sau/10);
        //printf("\n TEST i:%d  j %d  :%f",i,j,c);
        if (c==a[i])
        {
        //if (i!=j)
      //  printf("\n Hoan doi vi tri cua %d cho %d",i,j);
        //printf("\nDoi CHO cho %d va %d",i,j);
        strcpy(trunggianmasinhvien,danhsach[i].masinhvien);
        strcpy(danhsach[i].masinhvien,danhsach[j].masinhvien);
        strcpy(danhsach[j].masinhvien,trunggianmasinhvien);

        strcpy(trunggianhoten,danhsach[i].hoten);
        strcpy(danhsach[i].hoten,danhsach[j].hoten);
        strcpy(danhsach[j].hoten,trunggianhoten);

        strcpy(trunggianlop,danhsach[i].lop);
        strcpy(danhsach[i].lop,danhsach[j].lop);
        strcpy(danhsach[j].lop,trunggianlop);

        strcpy(trunggiannamsinh,danhsach[i].namsinh);
        strcpy(danhsach[i].namsinh,danhsach[j].namsinh);
        strcpy(danhsach[j].namsinh,trunggiannamsinh);

        strcpy(trunggianquequan,danhsach[i].quequan);
        strcpy(danhsach[i].quequan,danhsach[j].quequan);
        strcpy(danhsach[j].quequan,trunggianquequan);

        strcpy(trunggiandiemtb,danhsach[i].diemtb);
        strcpy(danhsach[i].diemtb,danhsach[j].diemtb);
        strcpy(danhsach[j].diemtb,trunggiandiemtb);

        }
    }

}


}

// chuan hoa chuoi
void chuanhoachuoi(char[]);//khai bao nguyen mau ham
void strdelete(char *s,int vt,int sl);
void strdelete(char *s,int vt,int sl)
{
    int n=strlen(s),i;
    for (i=vt;i<=n-sl;++i)
        s[i]=s[i+sl];
}
void chuanhoachuoi(char a[])
{
    int i;
    while(a[strlen(a)-1]==' ')// xoa het cac ki tu trong o cuoi chuoi
        a[strlen(a)-1]=0;
    while(a[0]==' ')          //xoa het cac ki tu trong o dau chuoi
        strdelete(a,0,1);
    for(i=0;i<strlen(a);++i)
        if((a[i]>=65)&&(a[i]<=90))  //kiem tra co phai la ky tu hoa
            a[i]+=32;        //chuyen tat ca ve ky tu thuong

    i=0;
    while(i<strlen(a))                //xoa hai ki tu trong lien tiep
     if((a[i]==' ')&&(a[i+1]==' '))
         strdelete(a,i,1);
     else ++i;

   for(i=0;i<strlen(a);i++)
    if(a[i]==' ')
        a[i+1]-=32;  //chuyen chu cai sau khoang trang thanh chu hoa

   a[0]=toupper(a[0]);//chuyen chu cai dau tien thanh chu hoa


    i=0;
    while(i<strlen(a))    //xoa cac ki tu khong phai la chu cai
    if((a[i]!=' ')&&(!isalpha(a[i])))
        strdelete(a,i,1);
     else ++i;
}

// tIm kiem
    void timmsv()
    {
        int i,ret, n= numrecords;
        char tim[50];
        printf("\n MODULE Tim sinh vien theo Ma sinh vien");
        printf("\n Nhap ma sinh vien can tim: ");
        gets(tim);
        for (i=0;i<n;i++)
            {
                ret=strcmp(tim,danhsach[i].masinhvien);
                if (ret==0)
                {
                printf("\n KET QUA TIM KIEM: ");
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                break;
                }

            }

        if (i==n) printf("\n Khong ton tai sinh vien co ma %s", tim);

    }

    void timHoTen()
    {
        int i,ret, n= numrecords;
        char tim[50];
        printf("\n MODULE Tim sinh vien theo Ho Ten ");
        printf("\n Nhap ho ten sinh vien can tim: ");
        gets(tim);
        chuanhoachuoi(tim);
        for (i=0;i<n;i++)
            {
                ret=strcmp(tim,danhsach[i].hoten);
                if (ret==0)
                {
                printf("\n KET QUA TIM KIEM: ");
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                 break;
                }

            }

        if (i==n) printf("\n Khong ton tai sinh vien co ten %s", tim);

    }

    void timLop()
    {
        int i,ret, n= numrecords,dem;
        char tim[50];
        printf("\n MODULE Tim sinh vien theo Lop ");
        printf("\n Nhap lop can tim: ");
        gets(tim);
        for (i=0;i<n;i++)
            {
                ret=strcmp(tim,danhsach[i].lop);
                if (ret==0)
                {
                dem=1;
                printf("\n KET QUA TIM KIEM: ");
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                 break;
                }

            }

        i=i+1;
        for (i;i<n;i++)
            {   ret=strcmp(tim,danhsach[i].lop);
                if (ret==0)
                {
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                }

            }

        if (dem!=1) printf("\n Khong ton tai lop %s trong CSDL", tim);

    }

void timQueQuan()
    {
        int i,ret, n= numrecords;
        char tim[50];
        printf("\n MODULE Tim sinh vien theo Que Quan  ");
        printf("\n Nhap Que sinh vien can tim: ");
        gets(tim);
        chuanhoachuoi(tim);
        for (i=0;i<n;i++)
            {
                ret=strcmp(tim,danhsach[i].quequan);
                if (ret==0)
                {
                printf("\n KET QUA TIM KIEM: ");
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                 break;
                }

            }

        if (i==n) printf("\n Khong ton tai sinh vien co que tai %s", tim);

    }

void xoaThongTin()
{
    int n=numrecords,i,j,ret,a;
    char tim[50];
    printf("\n Nhap ma so sinh vien can xoa: ");
    gets(tim);
    for (i=0;i<n;i++)
            {   //printf("\n Chay lan %d  voi tim la: %s",i,tim);
                ret=strcmp(tim,danhsach[i].masinhvien);
                if (ret==0)
                {

                printf("\n Thong tin sinh vien co ma so: %s ",tim);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");

                printf("\n TIEN HANH XOA THONG TIN SINH VIEN MA SO %s ... ... ... ",tim);

               strcpy(danhsach[i].masinhvien,danhsach[n-1].masinhvien);
               strcpy(danhsach[i].hoten,danhsach[n-1].hoten);
               strcpy(danhsach[i].lop,danhsach[n-1].lop);
               strcpy(danhsach[i].namsinh,danhsach[n-1].namsinh);
               strcpy(danhsach[i].quequan,danhsach[n-1].quequan);
               strcpy(danhsach[i].diemtb,danhsach[n-1].diemtb);
               numrecords--;
                break;

                }





                }


        if (i==n) printf("\n Khong ton tai sinh vien co ma %s", tim);

}

void suaThongTin()
{
    int n=numrecords,i,ret,a;
    char tim[50];
    printf("\n Nhap ma so sinh vien can chinh xua: ");
    gets(tim);
    for (i=0;i<n;i++)
            {
                ret=strcmp(tim,danhsach[i].masinhvien);
                if (ret==0)
                {
                a=i;
                printf("\n Thong tin sinh vien co ma so: %s ",tim);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| STT |         H O   V A   T E N         |   Ma Sv    |   Lop      |  date        |  Que quan    |   Diem TB    |") ;
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n| %3d | ", i+1);
                printf("%-34s| %-11s| %-10s | %-12s | %-12s |%-13s |", danhsach[i].hoten,danhsach[i].masinhvien,
                danhsach[i].lop, danhsach[i].namsinh, danhsach[i].quequan,danhsach[i].diemtb);
                printf("\n+-----+-----------------------------------+------------+------------+--------------+--------------+--------------+");
                printf("\n Tien hanh chinh xua thong tin sinh vien:");
                printf("\n + Chinh xua ho ten:");
                gets(danhsach[i].hoten);
                chuanhoachuoi(danhsach[i].hoten);
                printf("\n +Chinh xua Lop:");
                gets(danhsach[i].lop);
                printf("\n + Chinh xua ngay sinh:");
                gets(danhsach[i].namsinh);
                printf("\n + Chinh xua que quan:");
                gets(danhsach[i].quequan);
                chuanhoachuoi(danhsach[i].quequan);
                printf("\n + Chinh xua Diem trung binh:");
                gets(danhsach[i].diemtb);
                printf("\n TIEN HANH CHINH XUA XONG THONG TIN SINH VIEN MA SO %s",tim);

                break;
                }
            }

        if (i==n) printf("\n Khong ton tai sinh vien co ma %s", tim);

}

// MUNU
enum
{
   KEY_ESC = 27,
   ARROW_UP = 256 + 72,
   ARROW_DOWN = 256 + 80,
   ARROW_LEFT = 256 + 75,
   ARROW_RIGHT = 256 + 77
};
int get_code(void)
{
   int ch = getch();

   if (ch == 0 || ch == 224)
       ch = 256 + getch();

   return ch;
}

// MENU 1
static const char *menu_options1[] =
{
   "       1. Chon chuc nang them moi ho so.",
   "       2. Chon chuc nang xuat du lieu.",
   "       3. Chon chuc nang Sap xep du lieu.",
   "       4. Chon chuc nang tim kiem thonng tin Sinh vien.",
   "       5. Chon chuc nang sua thong tin sinh vien.",
   "       6. Chon chuc nang xoa du lieu sinh vien",
   "       0.Thoat Chuong trinh"

};
static const int menu_size1 = 7;
void menu1(int arrow)
{
   int i;
   for (i = 0; i < menu_size1; i++) {
       if (i == arrow)
           printf(" --> ");
       else
           printf(" ");
       printf("%s\n", menu_options1[i]);
   }
}
int chon1;
int listchon1(void)
{
    printf("\n                THUC TAP KY THUAT LAP TRINH");
    printf("\n         CHUONG TRINH QUAN LY THONG TIN SINH VIEN");
    printf("\n       =======================MENU====================\n\n");
    printf("\n       Tien hanh lua chon chuc nang:\n");
    int a;
   int action;
   int arrow = 0;

   menu1(arrow);
   while ((action = get_code()) != KEY_ESC)
   {
       switch (action)
       {
       case ARROW_UP:
           if (--arrow < 0)
              arrow = menu_size1 - 1;
           break;
       case ARROW_DOWN:
           if (++arrow == menu_size1)
               arrow = 0;
           break;
       case '\r':

           chon1=arrow+1;
           a=1;
           break;
       default:
           break;
       }
       system("cls");
       if (a==1) break;
    printf("\n                THUC TAP KY THUAT LAP TRINH");
    printf("\n         CHUONG TRINH QUAN LY THONG TIN SINH VIEN");
    printf("\n       =======================MENU====================\n\n");
    printf("\n       Tien hanh lua chon chuc nang:\n");

       menu1(arrow);
   }

   return 0;
}

// MENU 2
static const char *menu_options2[] =
{
   "       1. Chon chuc nang: Sap xep theo Ma sinh vien.",
   "       2. Chon chuc nang: Sap xep theo Ho Ten sinh vien.",
   "       3. Chon chuc nang : Sap xep theo Noi sinh",
   "       4. Chon chuc nang: Sap xep theo Lop",
   "       5. Chon chuc nang: Sap xep theo Nam sinh",
   "       6. Chon chuc nang: Sap xep theo Diem trung binh",
   "       0. Thoat chuc nang"


};
static const int menu_size2 = 7;
void menu2(int arrow)
{
   int i;
   for (i = 0; i < menu_size2; i++) {
       if (i == arrow)
           printf(" --> ");
       else
           printf(" ");
       printf("%s\n", menu_options2[i]);
   }
}
int chon2;
int listchon2(void)
{
    printf("\n                THUC TAP KY THUAT LAP TRINH");
    printf("\n         CHUONG TRINH QUAN LY THONG TIN SINH VIEN");
    printf("\n       =======================MENU====================\n\n");
    printf("\n       Tien hanh lua chon chuc nang:\n");
    int a;
   int action;
   int arrow = 0;

   menu1(arrow);
   while ((action = get_code()) != KEY_ESC)
   {
       switch (action)
       {
       case ARROW_UP:
           if (--arrow < 0)
              arrow = menu_size2 - 1;
           break;
       case ARROW_DOWN:
           if (++arrow == menu_size2)
               arrow = 0;
           break;
       case '\r':

           chon2=arrow+1;
           a=1;
           break;
       default:
           break;
       }
       system("cls");
       if (a==1) break;
    printf("\n                THUC TAP KY THUAT LAP TRINH");
    printf("\n         CHUONG TRINH QUAN LY THONG TIN SINH VIEN");
    printf("\n       =======================MENU====================\n\n");
    printf("\n       Tien hanh lua chon chuc nang:\n");

       menu2(arrow);
   }

   return 0;
}

// MENU 3
static const char *menu_options3[] =
{
   "       1. Chon chuc nang: Tim kiem theo Ma sinh vien.",
   "       2. Chon chuc nang: Tim kiem theo Ho Ten sinh vien.",
   "       3. Chon chuc nang : Tim kiem theo Noi sinh",
   "       4. Chon chuc nang: Tim kiem theo Lop",
   "       0. Thoat chuc nang"


};
static const int menu_size3 = 5;
void menu3(int arrow)
{
   int i;
   for (i = 0; i < menu_size3; i++) {
       if (i == arrow)
           printf(" --> ");
       else
           printf(" ");
       printf("%s\n", menu_options3[i]);
   }
}
int chon3;
int listchon3(void)
{
    printf("\n                THUC TAP KY THUAT LAP TRINH");
    printf("\n         CHUONG TRINH QUAN LY THONG TIN SINH VIEN");
    printf("\n       =======================MENU====================\n\n");
    printf("\n       Tien hanh lua chon chuc nang:\n");
    int a;
   int action;
   int arrow = 0;

   menu1(arrow);
   while ((action = get_code()) != KEY_ESC)
   {
       switch (action)
       {
       case ARROW_UP:
           if (--arrow < 0)
              arrow = menu_size3 - 1;
           break;
       case ARROW_DOWN:
           if (++arrow == menu_size3)
               arrow = 0;
           break;
       case '\r':

           chon3=arrow+1;
           a=1;
           break;
       default:
           break;
       }
       system("cls");
       if (a==1) break;
    printf("\n                THUC TAP KY THUAT LAP TRINH");
    printf("\n         CHUONG TRINH QUAN LY THONG TIN SINH VIEN");
    printf("\n       =======================MENU====================\n\n");
    printf("\n       Tien hanh lua chon chuc nang:\n");

       menu3(arrow);
   }

   return 0;
}


int main()
{
    //data();
   //lietke();
    //SapXepMSV();
    //SapXepten();
    //SapXepLop();
    //SapXepQueQuan();
    //SapXepNamsinh();
    //SapXepDiemTb();
    //timmsv();
    //timHoTen();
    //timLop();
    //timQueQuan();
    //xoaThongTin();
    //suaThongTin();
   //lietke();
  /*  HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, 5 );
    */

    int stt1,a;
    stt1=1;
    data();
    system("cls"); // Xoa man hinh
    while (stt1!=0)
    {   listchon1();
        switch (chon1)
        {
            case 1:
                printf("\n  I.CHUC NANG NHAP THONG TIN SINH VIEN TU BAN PHIM:\n");
                nhapmoi();
                luudata();
                break;
            case 2:
                printf("\n  II.CHUC NANG LIET KE THONG TIN SINH VIEN DANG BANG:\n");
                lietke();
                break;
            case 3:
                printf("\n  III.CHUC NANG SAP XEP CO SO DU LIEU:\n");
                luachonsapxep();
                break;
            case 4:

                printf("\n  VI.CHUC NANG TIM KIEM THONG TIN SINH VIEN:\n");
                luachontimkiem();
                break;
            case 5:
                //printf("\n  V.CHUC NANG CHINH SUA THONG TIN SINH VIEN:\n");
                lietke();
                suaThongTin();
                printf("       DU LIEU SAU KHI CAP NHAT:");
                lietke();
                break;
            case 6:
                printf("\n  VI.CHUC NANG XOA THONG TIN SINH VIEN:\n");
                lietke();
                xoaThongTin();
                printf("\n       DU LIEU SAU KHI CAP NHAT:\n");
                lietke();
                break;

            case 7:
                stt1=0;
            break;
        }

        system("cls"); // Xoa man hinh

    }
    getch();
}

int luachonsapxep()
{   int stt2,a;
    stt2=1;
    system("cls"); // Xoa man hinh
    while (stt2!=0)
    {   listchon2();

        switch (chon2)
        {
            case 1:
                printf("\n  I.CHUC NANG SAP XEP THEO MA SINH VIEN:\n");
                SapXepMSV();
                lietke();
                break;
            case 2:
                printf("\n  II.CHUC NANG SAP XEP THEO HO TEN SINH VIEN:\n");
                SapXepten();
                lietke();
                break;
            case 3:
                printf("\n  III.CHUC NANG SAP XEP THEO NOI SINH:\n");
                SapXepQueQuan();
                lietke();
                break;
            case 4:
                printf("\n  VI.CHUC NANG SAP XEP THEO LOP:\n");
                SapXepLop();
                lietke();
                break;
            case 5:
                printf("\n  V.CHUC NANG SAP XEP THEO NAM SINH:\n");
                SapXepNamsinh();
                lietke();
                break;
            case 6:
                printf("\n  VI.CHUC NANG SAP XEP THEO DIEM TRUNG BINH:\n");
                SapXepDiemTb();
                lietke();
                break;
            case 7:
                stt2=0;
                a=0;
            break;
        }
            system("cls"); // Xoa man hinh
            if (a==0) break;
        listchon2();

    }
}


int luachontimkiem()
{   int dung;
    int stt3,a;
    stt3=1;
    system("cls"); // Xoa man hinh
    while (stt3!=0)
    {
        listchon3();
        switch (chon3)

        {
            case 1:
                printf("\n  I.CHUC NANG TIM KIEM THEO MA SINH VIEN:\n");
                timmsv();
                getch();
                break;
            case 2:
                printf("\n  II.CHUC NANG RIM KIEM THEO HO TEN SINH VIEN:\n");
                timHoTen();
                getch();
                break;
            case 3:
                printf("\n  III.CHUC NANG TIM KIEM THEO NOI SINH:\n");
                timQueQuan();
                getch();
                break;
            case 4:
                printf("\n  VI.CHUC NANG TIM KIEM THEO LOP:\n");
                timLop();
                getch();
                break;

            case 5:
             stt3=0;
                a=0;
            break;
        }
        system("cls"); // Xoa man hinh
        if (a==0) break;
        listchon3();

    }
}

void chuanhoanamsinh()
{
    char a[50]="12/12/1991";
    char thu[50],thang[50],nam[50];
    int i,l;
    l=strlen(a);
        if (l!=10)
            { printf(" nhap sai chuan thong tin nam sinh.");
            }
        else
        {
            for (i=0;i<2;i++)
            {
                thu[i]=a[i];
            }
            thu[i+1]= '\0';
            l=atoi(thu);
            if (l>31)
                { printf(" nhap sai chuan thong tin ngay sinh.");
                }

            for (i=3;i<5;i++)
            {
                thang[i]=a[i];
            }
            thang[i+1]= '\0';
            l=atoi(thang);
            if (l>12)
                { printf(" nhap sai chuan thong tin thang sinh.");

                }

            for (i=6;i<10;i++)
            {
                nam[i]=a[i];
            }
            thang[i+1]= '\0';
            l=atoi(thang);
            if (l>12)
                { printf(" nhap sai chuan thong tin nam sinh.");
               }

        }
}

