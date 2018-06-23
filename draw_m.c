
#ifndef  DRAW_MAIN_C
#define DRAW_MAIN_C
//.....................................................
// Ver. 1.00.00  Draw_main.c
//
// 2018-04-26
//  event driver all circle draw 
//  draw html  file to show test result !!
//  it also can use function call draw every elemet 
//  now just to test html Canvas 2D function 
//          is ok to show result of simulation!!
//  2D graph now, future can use html5 3D show graph !!
//
//  to do list:
//      * 3D html5 file !!
//      * lib function
//      * C++ class lib
//
//  by David Tang, chung Lung 2018
//   ver 1.00  2018-04-26
//.....................................................


#define DEBUG_PRINT    printf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIX_y      500

#define MAX_PIX_x      600 
#define PI             ( (double) 3.14159)

#define ARRAY_MAX   2048   // 1024
#define DRAW_PIXS_CIR     (10.00)
//................................................................
typedef struct dcurvestr 
{
double x[ARRAY_MAX],y[ARRAY_MAX];
int xx[1024],yy[ARRAY_MAX];
// double delta_t[ARRAY_MAX],now_t[ARRAY_MAX];  
// double total_t;

double max_x;
double min_x;

double max_y;
double min_y;
int    total;
double rate_x;
double rate_y;
int    Start_i;

} DRAW_CURVE_DATA_DEF;
//..........................
typedef struct drawballstr 
{
double x[ARRAY_MAX],y[ARRAY_MAX];
int xx[1024],yy[ARRAY_MAX];
double delta_t[ARRAY_MAX],now_t[ARRAY_MAX];  
double total_t;

// double max_x;
// double min_x;

// double max_y;
// double min_y;
int    total;
// double rate_x;
// double rate_y;
int    Start_i;

} DRAW_BALL_DATA_DEF;
//.............................
DRAW_CURVE_DATA_DEF   b_data; // curve info
DRAW_CURVE_DATA_DEF   c_data; // curve info

DRAW_BALL_DATA_DEF    d_data; // curve test 001 data
DRAW_BALL_DATA_DEF    e_data; // curve test 002 data
DRAW_BALL_DATA_DEF    f_data; // curve test 003 data

DRAW_BALL_DATA_DEF    g_data; // slop test data  
//................................................................
const char h1[]= { "<!DOCTYPE html> \r\n" };
const char h2[]= { "<html>\r\n<body> <div> \r\n" };

// after < can not used one space, <body> , can not < body> .......

const char svg_h1[] = { "<svg width=\"%i\" height=\"%i\"> \r\n"};
const char svg_end1[] = { "</svg> \r\n"};
const char circle_yellow[] = 
{"<circle cx =\"%i\" cy=\"%i\"  r=\"%i\" stroke=\"green\" stroke-width=\"%i\" fill=\"yellow\"/>  \r\n" };

const char end1[] = {"</div></body> \r\n</html> \r\n"};


//................................................................
//................................................................
//................................................................
//...draw circle, mean the ball for yellow.................
//......input : from math data
//......output: to file !! and canvas_ID, html
//......version: 2018-04  first ver 1.00 David Tang , clt  .
//................................................................
//................................................................

int draw_circle(FILE *fp, char canvas_ID[], double x, double y,double r, char c[])
{
  // xx[i] = (int) (x[i]*rate_x);
  // yy[i] = (int) (500 - y[i]*rate_y);

int int_x;
int int_y;
int int_r;
DEBUG_PRINT("----- draw_circle() ------\n");

int_x= (int) x*c_data.rate_x;
int_y= (int) (MAX_PIX_y- y*c_data.rate_y);

// svg ==> fprintf(fp,circle_yellow, x, y, r, 4);
// canvas ==> fprintf(fp,"ctx.arc("%s ,%s, %s, %s, %s");\r\n",x,y,r,0, 2*PI);
fprintf(fp,"<script>\r\n");
fprintf(fp,"var canvas = document.getElementById(\"%s\");\r\n ",canvas_ID) ;
fprintf(fp,"var ctx = canvas.getContext('2d'); \r\n" );
fprintf(fp,"ctx.beginPath();\r\n");
fprintf(fp,"ctx.arc(%i ,%i, %i, %i, %f);\r\n",int_x,int_y,int_r,0, 2*PI);
fprintf(fp,"ctx.fillStyle = '%s' ; \r\n",c);
fprintf(fp,"ctx.fill(); \r\n");

fprintf(fp,"ctx.stroke();\r\n");
fprintf(fp,"ctx.closePath();\r\n");
fprintf(fp,"</script>\r\n");
return 0;
}
//................................................................
//................................................................
//................................................................
int draw_pix(FILE *fp, int x, int y)
{

DEBUG_PRINT("----- draw_pix() ------\n");
fprintf(fp,circle_yellow, x, y, 3, 4);

return 0;
}

//................................................................
//................................................................
int draw_slop(FILE *fp, char canvas_ID[], int xf[], int yf[], int total)
{
int i;
DEBUG_PRINT("----- draw_slop() ------\n");
fprintf(fp,"<script>\r\n");
fprintf(fp,"var canvas = document.getElementById(\"%s\");\r\n ",canvas_ID) ;
fprintf(fp,"var ctx = canvas.getContext('2d'); \r\n" );
fprintf(fp,"ctx.beginPath();\r\n");


fprintf(fp,"ctx.moveTo(%i,%i);\r\n",xf[0],yf[0]);



fprintf(fp,"var ctx = canvas.getContext('2d'); \r\n" );
fprintf(fp,"ctx.beginPath();\r\n");
fprintf(fp,"ctx.moveTo(%i,%i);\r\n",xf[0],yf[0]);


for(i =1; i< total; i++)
{
fprintf(fp,"ctx.lineTo(%i,%i);\r\n", xf[i],yf[i] );
}




fprintf(fp,"ctx.stroke();\r\n");
fprintf(fp,"ctx.closePath();\r\n");
fprintf(fp,"</script>\r\n");

return 0;
}

//................................................................



int draw_poly(FILE *fp, char canvas_ID[], int xf[], int yf[], int total)
{
int i;
DEBUG_PRINT("----- draw_poly() ------\n");
fprintf(fp,"<script>\r\n");
fprintf(fp,"var canvas = document.getElementById(\"%s\");\r\n ",canvas_ID) ;
fprintf(fp,"var ctx = canvas.getContext('2d'); \r\n" );
fprintf(fp,"ctx.beginPath();\r\n");
fprintf(fp,"ctx.moveTo(%i,%i);\r\n",xf[0],yf[0]);
for(i =1; i< total; i++)
{
fprintf(fp,"ctx.lineTo(%i,%i);\r\n", xf[i],yf[i] );
}
fprintf(fp,"ctx.stroke();\r\n");
fprintf(fp,"ctx.closePath();\r\n");
fprintf(fp,"</script>\r\n");
return 0;
}




//................................................................
int draw_all_circle_var(FILE *fp, const char canvas[])
{
int i,j,k;
double draw_delta_t; // = d_data.total_t/DRAW_PIXS;

const char h_circle01[] = {"<script> var t_yellow_ball =["} ;
const char h_circle02[] = {"<script> var t_blue_ball =["} ;
const char h_circle03[] = {"<script> var t_green_ball =["} ;
const char t_circle01[] = {"]; </script> \r\n"} ;
const char t_circle02[] = {"]; </script> \r\n"} ;
const char t_circle03[] = {"]; </script> \r\n"} ;

DEBUG_PRINT("----- draw_all_circle() ------\n");

//..............................................
DEBUG_PRINT("----- yellow ------\n");
draw_delta_t = d_data.total_t/DRAW_PIXS_CIR;
DEBUG_PRINT("time = %f %f\n",d_data.total_t,draw_delta_t);

fprintf(fp,h_circle01);
j =1;
for(i=0; i < d_data.total; i++)
{
 if(i==0) 
     fprintf(fp,"%i , %i ,",d_data.xx[i], d_data.yy[i]);
 else if( i == (d_data.total-1))
     fprintf(fp,"%i , %i ",d_data.xx[i], d_data.yy[i]);
 else
 {
   if(d_data.now_t[i] > (j*draw_delta_t) )
    {
     fprintf(fp," %i , %i ,",d_data.xx[i], d_data.yy[i]);
     j++;
    }
 }
}

fprintf(fp,t_circle01);
//........................

//..............................................
DEBUG_PRINT("----- blue ------\n");
draw_delta_t = e_data.total_t/DRAW_PIXS_CIR;
DEBUG_PRINT("time = %f %f\n",e_data.total_t,draw_delta_t);

fprintf(fp,h_circle02);
j =1;
for(i=0; i < e_data.total; i++)
{
 if(i==0) 
     fprintf(fp,"%i , %i ,",e_data.xx[i], e_data.yy[i]);
 else if( i == (e_data.total-1))
     fprintf(fp,"%i , %i ",e_data.xx[i], e_data.yy[i]);
 else
 {
   if(e_data.now_t[i] > (j*draw_delta_t) )
    {
     fprintf(fp," %i , %i ,",e_data.xx[i], e_data.yy[i]);
     j++;
    }
 }
}

fprintf(fp,t_circle02);
//........................

//..............................................
DEBUG_PRINT("----- green ------\n");
draw_delta_t = f_data.total_t/DRAW_PIXS_CIR;
DEBUG_PRINT("time = %f %f\n",f_data.total_t,draw_delta_t);

fprintf(fp,h_circle03);
j =1;
for(i=0; i < f_data.total; i++)
{
 if(i==0) 
     fprintf(fp,"%i , %i ,",f_data.xx[i], f_data.yy[i]);
 else if( i == (f_data.total-1))
     fprintf(fp,"%i , %i ",f_data.xx[i], f_data.yy[i]);
 else
 {
   if(f_data.now_t[i] > (j*draw_delta_t) )
    {
     fprintf(fp," %i , %i ,",f_data.xx[i], f_data.yy[i]);
     j++;
    }
 }
}

fprintf(fp,t_circle03);
//........................



//........................
return 0;
}
//................................................................
//................................................................
int draw_main()
{

FILE *fp;
double x_001;
double y_001;
double x_002;
double y_002;
double x_003;
double y_003;
const char Button001[] = 
{"</br>        <button onclick=\"mybtfunction()\" > Go Test </button> " };

char canvas[100];
strcpy(canvas,"myCanvas");
fp = fopen("d1.html","w");

DEBUG_PRINT("----- draw_main() ------\n");

fprintf(fp,"%s%s", h1, h2 );
// fprintf(fp,svg_h1,100,100);
// fprintf(fp,"not support svg !!\r\n </svg>\r\n");


fprintf(fp,"<canvas id=\"%s\" width=\"%i\" height=\"%i\" style=\"border:1px solid #d3d3d3;\" > \r\n "
, canvas, 600+50,500+50);

fprintf(fp,"not support HTML5 \r\n </canvas>\r\n");

//...........Begin.........
fprintf(fp, "<script src=\"file://d:/tmp/myjs.js\"> </script>\r\n" );
fprintf(fp,Button001);
draw_all_circle_var(fp,canvas);
//int draw_all_circle_var(FILE *fp, const char canvas[])

draw_slop(fp,canvas, b_data.xx , b_data.yy , b_data.total);

draw_poly(fp,canvas, c_data.xx , c_data.yy , c_data.total);

//#<script src="file://d:/tmp/myjs.js"> </script>
// draw_circle(FILE *fp, int x, int y,int r) ;
// int draw_yellow_circle(FILE *fp, int x, int y,int r) ;
// draw_circle(fp,canvas, 5 , 5 ,4, "yellow") ;
// draw_circle(fp,canvas, 5 , 5 ,4, "yellow") ;

//............end..........
fprintf(fp,"%s\r\n", end1);
fclose(fp);


system(" cp d1.html /tmp/d1.html ");
system(" cp myjs.js /tmp/myjs.js ");

return 0;
}

//...................................................................
//...................................................................
int read_time_file(const char fname[])
{
FILE* fp;
int i,j,k;
int flag_exit =0;
char temp_s[20][200];
char buf_noused[100];
DRAW_BALL_DATA_DEF *d_ptr ;


DEBUG_PRINT("----- read_time_file() ------\n");

DEBUG_PRINT(" name=%s \n", fname);

if(0 == strcmp(fname,"res1.txt")  )
   d_ptr = &d_data;   
else if( 0 == strcmp(fname, "res2.txt") )
   d_ptr = &e_data;
else if( 0 == strcmp(fname, "res3.txt") )
   d_ptr = &f_data;
else if( 0 == strcmp(fname, "res100.txt") )
   d_ptr = &g_data;
else
   DEBUG_PRINT("ERR ff2938477 !!\n");

fp = fopen(fname,"r");
if(fp == NULL)
{
 DEBUG_PRINT("ERR f3947939!! \n");
 exit(1);
}
fgets( temp_s[0],98,fp);
fgets( temp_s[1],98,fp);
fgets( temp_s[2],98,fp);
fgets( temp_s[3],98,fp);
fgets( temp_s[4],98,fp);
fgets( temp_s[5],98,fp);
DEBUG_PRINT("%s \n %s \n %s \n %s \n %s \n %s\n" 
           , temp_s[0], temp_s[1], temp_s[2],temp_s[3],temp_s[4]
           , temp_s[5] );

int ret;
i=0;
do
{
    fgets( buf_noused, 98, fp);
    //fgets( temp_s[5],98,fp);
    ret = fscanf(fp,"%s %s %s %s %s \n"
           , temp_s[0], temp_s[1], temp_s[2],temp_s[3],temp_s[4]
           )  ; 

   if(ret == EOF)
    {
       break; 
    }else {
       DEBUG_PRINT("%s  %s  %s  %s  %s  \n" 
           , temp_s[0], temp_s[1], temp_s[2],temp_s[3],temp_s[4]
            );

    } 
   d_ptr->now_t[i]   = atof(temp_s[1]);
   d_ptr->delta_t[i] = atof(temp_s[2]);
   d_ptr->x[i]       = atof(temp_s[3]);
   d_ptr->y[i]       = atof(temp_s[4]);
   d_ptr->total = i+1;
   d_ptr->total_t = d_ptr->now_t[i];
   DEBUG_PRINT("=>[%i] %f  %f  %f  %f \n",d_ptr->total, d_ptr->now_t[i], 
     d_ptr->delta_t[i], d_ptr->x[i],d_ptr->y[i]);
i++;
}while(1);

fclose(fp);
return 0;
}
//...................................................................
//...................................................................
//...................................................................
int old_test_main()
{
int x[] =
{
0, 10,20, 30,40,50,60 , 70, 80, 90,100,110,120
};
int y[] =
{
0, 10,30, 40, 50, 60,70,100,200,300,400
};
int total =9;


draw_main( x, y, total );


}


//................................................................
//................................................................
//................................................................
int read_file(const char fname[])
{
FILE *fp;
char temp_s[10][200];
DEBUG_PRINT("----- read_file() ------\n");
DEBUG_PRINT("file=%s\n",fname);

fp = fopen(fname,"r");
int parameter;
fscanf(fp,"%i\n",&parameter);
printf("par=%i\n", parameter);

fgets(temp_s[0],98, fp);
printf("first line = %s \n", temp_s[0]);

int i;

c_data.max_x =0;
c_data.min_x =0;

c_data.max_y =0;
c_data.min_y =0;
c_data.total =0;
i = 0;
int ret;
while(1)
{
   switch(parameter)
   {
    case 7:
    ret = fscanf(fp,"%s %s %s %s %s %s %s\n"
           , temp_s[0], temp_s[1], temp_s[2],temp_s[3],temp_s[4],
           temp_s[5],temp_s[6])  ; 
      
      break; 
    case 8:
    ret = fscanf(fp,"%s %s %s %s %s %s %s %s \n"
        , temp_s[0], temp_s[1], temp_s[2],temp_s[3],temp_s[4],
        temp_s[5],temp_s[6], temp_s[7] )  ; 
      break;
    default:
       ret = EOF;
         printf("ERROR 784769!!\n");
      break;
   }

 if( EOF == ret) break; 

printf(" ==> %s %s %s %s \n", temp_s[0], temp_s[1] ,temp_s[2], temp_s[3] );

c_data.x[i] = atof(temp_s[2]);
c_data.y[i] = atof(temp_s[3]);
if(c_data.x[i] > c_data.max_x) c_data.max_x = c_data.x[i];
if(c_data.x[i] < c_data.min_x) c_data.min_x = c_data.x[i];

if(c_data.y[i] > c_data.max_y) c_data.max_y = c_data.y[i];
if(c_data.y[i] < c_data.min_y) c_data.min_y = c_data.y[i];

i++;
c_data.total =i;
printf("readfile=%s x=%f y=%f \n", temp_s[0] ,c_data.x[i-1], c_data.y[i-1]);

} // end of while !!


printf("total= %i \n", c_data.total);

fclose(fp);
return 0;
}
//................................................................
//................................................................
//................................................................
//................................................................
int re_size_all_data()
{
// x ==> 600
// y ==> 500

// org ==> 0, 500

DEBUG_PRINT("----- re_size_d_data() ------\n");


int i;
for(i=0; i < d_data.total; i++)
{
  d_data.xx[i] = (int) (d_data.x[i]*c_data.rate_x);
  d_data.yy[i] = (int) (MAX_PIX_y - d_data.y[i]*c_data.rate_y);
  // DEBUG_PRINT("resize cir  = %i %i  \n",d_data.xx[i], d_data.yy[i]);
}

for(i=0; i < e_data.total; i++)
{
  e_data.xx[i] = (int) (e_data.x[i]*c_data.rate_x);
  e_data.yy[i] = (int) (MAX_PIX_y - e_data.y[i]*c_data.rate_y);
  // DEBUG_PRINT("resize cir  = %i %i  \n",e_data.xx[i],e_data.yy[i]);
}

for(i=0; i < f_data.total; i++)
{
  f_data.xx[i] = (int) (f_data.x[i]*c_data.rate_x);
  f_data.yy[i] = (int) (MAX_PIX_y - f_data.y[i]*c_data.rate_y);
  // DEBUG_PRINT("resize cir  = %i %i  \n",f_data.xx[i], f_data.yy[i]);
}


for(i=0; i < g_data.total; i++)
{
  g_data.xx[i] = (int) (g_data.x[i]*c_data.rate_x);
  g_data.yy[i] = (int) (MAX_PIX_y - g_data.y[i]*c_data.rate_y);
  // DEBUG_PRINT("resize cir  = %i %i  \n",f_data.xx[i], f_data.yy[i]);
}

return 0;

}



//................................................................
//................................................................
int re_size_c_data()
{
// x ==> 600
// y ==> 500

// org ==> 0, 500

DEBUG_PRINT("----- re_size_data() ------\n");

c_data.rate_x = (MAX_PIX_x / ( (double) (c_data.max_x))  ); 
c_data.rate_y = (MAX_PIX_y / ( (double) (c_data.max_y))  ); 

int i;
for(i=0; i < c_data.total; i++)
{
  c_data.xx[i] = (int) (c_data.x[i]*c_data.rate_x);
  c_data.yy[i] = (int) (MAX_PIX_y - c_data.y[i]*c_data.rate_y);
   // org change 

}

return 0;
}
//................................................................
//................................................................
int re_size_b_data()
{
// x ==> 600
// y ==> 500

// org ==> 0, 500

DEBUG_PRINT("----- re_size_b_data() ------\n");

b_data.rate_x = (MAX_PIX_x / ( (double) (c_data.max_x))  ); 
b_data.rate_y = (MAX_PIX_y / ( (double) (c_data.max_y))  ); 

int i;
for(i=0; i < b_data.total; i++)
{
  b_data.xx[i] = (int) (b_data.x[i]*b_data.rate_x);
  b_data.yy[i] = (int) (MAX_PIX_y - b_data.y[i]*b_data.rate_y);
   // org change 

}

return 0;
}
//................................................................
//................................................................
//................................................................
int read_b_data()
{
b_data.total = 2;

  b_data.x[0] = 0 ;
  b_data.y[0] = 10 ;

  b_data.x[1] = 5*(3.14159);
  b_data.y[1] = 0;

//for(i=0; i < b_data.total; i++)


return 0;
}
//................................................................

//................................................................
//................................................................
int init_data()
{
read_file("o1.txt");
re_size_c_data();

read_b_data();
re_size_b_data(); 



// int read_time_file(const char fname[])


read_time_file("res1.txt");
read_time_file("res2.txt");
read_time_file("res3.txt");
read_time_file( "res100.txt"  );
re_size_all_data();

}


//................................................................
int main()
{

init_data();

draw_main(  );

return 0;
}

//...................................................................

#endif

