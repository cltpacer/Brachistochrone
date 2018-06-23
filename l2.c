
#ifndef GLABAL_INC
#define GLABAL_INC
#include <math.h>	
#define  PI  (3.1415926542654)

#define MAX_TEST   ((double)1000 )

#define GRAV_g    (9.8)
#define MAX_ARRAY   2000
#define TEST_R                 5
#define TEST_DRAW_V            1
#define TEST_DRAW_FROM_THEATA  (PI/2)
#define TEST_DRAW_TO_THEATA    (PI/2)

#define TEST_HIGH              (10.0)  
//.......................................................................
double total_v;
double total_t;

double x[MAX_ARRAY]; 
double y[MAX_ARRAY];
double delta_t;   // for curve drawing ... 
                  // not for speed of rolling down ball speed ..

double m[MAX_ARRAY];
double slop[MAX_ARRAY];
double angle[MAX_ARRAY];
double angle_deg[MAX_ARRAY];    // in degree 
double delta_x[MAX_ARRAY];   // when draw pic, diff t get diff delta_x
double delta_y[MAX_ARRAY];
double delta_curv_t[MAX_ARRAY];   //

double a_curv[MAX_ARRAY];   // diff x position get diff g*cos(theata)
double delta_v[MAX_ARRAY];   // diff acc get diff v
double v[MAX_ARRAY];
double delta_s[MAX_ARRAY];   // diff d_x get diff d_s 
double s[MAX_ARRAY];

#endif

//............................................
#ifndef   DRAW_002
#define   DRAW_002
/////////////////////////////////////////////////////////
int draw_cal_slop_002(const char *filename)
{
double V = TEST_DRAW_V;
double R = TEST_R;
int i,j,k;

//      if( start_test_high >= real_y_now )
double start_test_high, real_y_now;

FILE *fp;
double temp_x, temp_y;
double delta_temp_x, temp2;

total_v =0;
total_t =0;
delta_t = (5*PI) / (double) MAX_TEST ;

fp = fopen(filename, "w");

printf("[i]     t     x[]     y[]  m  angle acc \n");
fprintf( fp, " [i]    t     x[]     y[]    m     m2angle   acc \n");
temp_x = 0;

int flag_first;

v[0] = 0;

delta_curv_t[0] = 0.001;

total_t =0;
flag_first =0;
for(i = 0; i< MAX_TEST; i++)
{
double t; 
  t =(i+1)*delta_t;
  if(t > 5*PI) break;
  x[i] = V*t + R*cos( (PI/2) + (t/5) );
  y[i] = R + R*sin( (PI/2) + (t/5) );
  if(flag_first ==  1 )
  {
  delta_temp_x = temp_x - x[i];

  if(delta_temp_x < 0)  delta_temp_x *= (-1);   // *temp1;

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


  double delta_yy, delta_xx;

  if(flag_first ==1 )
   {
     delta_yy = y[i]-y[i-1];  // y[i-1]; 
     delta_xx = x[i]-x[i-1];  // x[i-1]; 

     m[i] =  delta_yy/delta_xx;    // slop of this point around !!
     delta_x[i] = delta_xx;
     delta_y[i] = delta_yy;
     slop[i] = pow(delta_yy, 2.0) + pow(delta_xx, 2.0);
     slop[i] = sqrt( slop[i] );

     angle[i] = atan(m[i]);
     angle_deg[i] = ( angle[i] * (double) 180)/PI;

     a_curv[i]  = sin(angle[i])*GRAV_g;
     if(a_curv[i] < 0 ) a_curv[i] *= (-1);
     delta_s[i] = delta_xx * ( 1.00 / cos(angle[i]) );  

     printf("i=[%i] x[i]=%f x[i-1]=%f d-s=%f \n",i , x[i], x[i-1], delta_s[i]); 

   }else {   
     // first 
     angle_deg[0] = -89.9;
     // angle_deg[0] = -89.9;
     angle[0] = angle_deg[0] * (PI/180.00) ;

     m[i] = tan(angle[0]); 
     // v[i] = 0.00000001 ;
     a_curv[0]  = sin(angle[0])*GRAV_g;

     if(a_curv[0] < 0 ) a_curv[0] *= (-1);
     // delta_s[0] = delta_xx * ( 1.00 / cos(angle[i]) );  
     // t[i] =0 ;
    
   }


  printf("[%i] %f %f %f %f %f %f \n",
           i ,t, x[i] , y[i] , m[i] , angle_deg[i], a_curv[i] );

  fprintf(fp, " %i %f %f %f %f %f %f \n", 
           i, t, x[i] , y[i] , m[i] , angle_deg[i] , a_curv[i] );
  printf("------------------------------------------------------\n"); 

      flag_first = 1; 
         temp_x = x[i];
         temp_y = y[i];

}  //  end of for i .. loop ..


fclose(fp);
return 0;
}
//........................................................................
#endif

#ifndef  TEST_MEM
#define  TEST_MEM
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
#endif
//...................................................................










