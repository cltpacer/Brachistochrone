
#include <math.h>	
#define  PI  (3.1415926542654)
#define MAX_TEST   ((double)100 )
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
//............................................

int cal_slop()
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

fp = fopen("o.txt","w");

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


  double delta_yy, delta_xx;

  if(flag_first ==1 )
   {
    // delta_y = y[i]-temp_x;  // y[i-1]; 
    // delta_x = x[i]-temp_y;  // x[i-1]; 
    // m[i] =  delta_y/delta_x; 
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

     // .............................................
     // ..  forward 
     // .............................................
     // v[i] = v[i-1]+ (acc[i] * delta_t);    .......... eq 1
     // delta_s[i] = ( (v[i]-v[i-1])/2) * delta_t; ..... eq 2

     
      
     double ans1, ans2;



      if( TEST_HIGH >= y[i] )
      { 
      ans1 = pow( v[i-1],2) + 2*a_curv[i]*delta_s[i];
      ans2 = sqrt(ans1);
      v[i] = ans2;
      delta_curv_t[i] = (2*delta_s[i]) / (v[i]+v[i-1])  ;
               // 2018-04 
       total_t = delta_curv_t[i] + total_t;

      printf(" v[i]=[%f] v[i-1]=[%f] \n" , v[i], v[i-1] );
      printf(" delta_s[i]=[%f]  \n", delta_s[i] );
      printf(" d_curv_t=[%f] \n" , delta_curv_t[i] );
      }else
        {
           v[i] =0;
           delta_curv_t[i] = 0;

        }

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

  fprintf(fp, " [%i] %f %f %f %f %f %f \n", 
           i, t, x[i] , y[i] , m[i] , angle_deg[i] , a_curv[i] );
  printf("------------------------------------------------------\n"); 

      flag_first = 1; 
         temp_x = x[i];
         temp_y = y[i];

}  //  end of for i .. loop ..

fprintf(fp,"total_t = %f \n", total_t);
fprintf(fp,"from high = %f  \n", TEST_HIGH);
printf("total_t = %f \n", total_t);
printf("from high = %f  \n", TEST_HIGH);

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










