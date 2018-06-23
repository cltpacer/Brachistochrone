
#include <math.h>	
double PI = 3.1415926542654;
double V = 1;
double t = 1;
double R = 5;
#define MAX_TEST   ((double)1000 )
//............................................
//............................................

int cal_slop()
{
int i,j,k;

double temp_x, temp_y;
double delta_temp_x, temp2;

double x[2000]; 
double y[2000];
double delta_t;   // for curve drawing ... 
                  // not for speed of rolling down ball speed ..

double m[2000];
double angle[2000];
double angle_deg[2000];    // in degree 

double delta_x[2000];   // when draw pic, diff t get diff delta_x
double delta_y[2000];

double acc[2000];       // diff x position get diff g*cos(theata)
double delta_v[2000];   // diff acc get diff v
double v[2000];
double delta_s[2000];   // diff d_x get diff d_s 
double s[2000];





delta_t = (5*PI) / (double) MAX_TEST ;
FILE *fp;


fp = fopen("o.txt","w");


printf(" i     t     x[]     y[]  m  \n");
fprintf( fp, " [i]    t     x[]     y[]    m     m2angle \n");
temp_x = 0;
int flag_first;
flag_first =0;
for(i = 1; i< MAX_TEST; i++)
{
 
  t =i*delta_t;
  if(t > 5*PI) break;
  x[i] = V*t + R*cos( (PI/2) + (t/5) );
  y[i] = R + R*sin( (PI/2) + (t/5) );
  if(flag_first ==  1 )
  {
  delta_temp_x = temp_x - x[i];

  if(delta_temp_x < 0)  delta_temp_x *= (-1);   // *temp1;

//  temp1 =  abs(temp1);
      if( delta_temp_x < 0.00000001 ) 
       {
         // temp unchange ...............
         printf("  ERR  unchange delta_x= [%f] temp_x=[%f] x[i]=[%f] \n"
           , delta_temp_x , temp_x , x[i]);
         continue;
       }else
       {

       }
   } else
   {

    }


  double delta_y, delta_x;

  if(flag_first ==1 )
   {
    // delta_y = y[i]-temp_x;  // y[i-1]; 
    // delta_x = x[i]-temp_y;  // x[i-1]; 
    // m[i] =  delta_y/delta_x; 
     delta_y = y[i]-y[i-1];  // y[i-1]; 
     delta_x = x[i]-x[i-1];  // x[i-1]; 

     m[i] =  delta_y/delta_x;    // slop of this point around !!

     angle[i] = atan(m[i]);
     angle_deg[i] *= ( (double) 180)/PI;

     acc[i]  = cos(angle[i])*9.8;
     if(acc[i] <0 ) acc[i] *= (-1);
     delta_s[i] = delta_x * ( 1.00 / cos(angle[i]) );  

   }else {
      m[i] = 0.123456; 
   }


  printf("[%i] %f %f %f %f %f  \n", i ,t, x[i] , y[i] , m[i] , angle_deg[i] );
  fprintf(fp, " [%i] %f %f %f %f %f  \n",
       i, t, x[i] , y[i] , m[i] , angle_deg[i]);
      flag_first =1; 
         temp_x = x[i];
         temp_y = y[i];

}  // end for loop 
fclose(fp);

return 0;
}
//........................................................................
int math_integral(double *ptr_fx,double from_x, double to_x, double *ret_ans)
{
double MAX_POINT;
int i,j,k;
double delta_x;

double temp_ans;
MAX_POINT = MAX_TEST;


}

//.........................................................................
int test_mem()
{
int i,j,k;
long *ptr;
#define MAX_MEM_TEST (1024*1024)
printf(" ................ START test_mem() !! ............. \n");

ptr = (long *) malloc( sizeof(long)*MAX_MEM_TEST);

if(ptr == NULL)
{
  printf("ERROR malloc !! memory array size too large !! \n"); 
   
   return 1;  // error !!
}
else
{
   
}

for( i=0; i < MAX_MEM_TEST; i++)
{
   ptr[i] = 0x55aa55aa;
   

}

for( i=0; i < MAX_MEM_TEST; i++)
{
   if( ptr[i] != 0x55aa55aa )
    {
         printf(" mem test ERR pass001 !! [i=%x] \n", i);
    } 

}


for( i=0; i < MAX_MEM_TEST; i++)
{
   ptr[i] = 0xaa55aa55;
   

}

for( i=0; i < MAX_MEM_TEST; i++)
{
   if( ptr[i] != 0xaa55aa55 )
    {
         printf(" mem test ERR pass002 !! [i=%x] \n", i);
    } 

}

free(ptr);

printf(" MEM test ALL PASS !! \n ");

return 0;

}

//...................................................................










