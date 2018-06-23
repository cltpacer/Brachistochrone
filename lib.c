
#ifndef GLABAL_INC
#define GLABAL_INC
#include <math.h>	

#define  DEBUG_PRINT    printf

typedef  unsigned int UINT;

#define  PI  (3.1415926542654)

#define MAX_TEST   ((double)100 )
   // max_point .....
#define GRAV_g    (9.8)
#define MAX_ARRAY   2000
#define TEST_R                 5
#define TEST_DRAW_V            1
#define TEST_DRAW_FROM_THEATA  (PI/2)
#define TEST_DRAW_TO_THEATA    (PI/2)

#define TEST_HIGH              (10.0)  

#define SLOP_MAX_Y             (10)
#define SLOP_MAX_X             (5*PI)
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
#ifndef   DRRW_001
#define   DRAW_001

int draw_cal_slop_001(const char *filename)
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
fprintf(fp,"8\n");
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
  if(t >= 5*PI) break;
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
     // first  .................................................
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


  printf("[%i] %f %f %f %f %f %f %f \n",
           i ,t, x[i] , y[i] , m[i] , angle_deg[i], a_curv[i], delta_s[i] );

  fprintf(fp, " %i %f %f %f %f %f %f %f \n", 
           i, t, x[i] , y[i] , m[i] , angle_deg[i] , a_curv[i], delta_s[i] );
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

#define STATE_INIT   0x0001   
#define STATE_NO     0x0002  
#define STATE_YES    0x0004   
#define STATE_NO12   0x0008   
#define STATE_NO11   0x0010   
#define STATE_EXIT   0x1000   



#define BREAK_YES   ((int)0x0001 )
#define NO_BREAK    ((int)0x0010 ) 

   int check_condition(int i)
   {
     if( x[i] >= 5*PI )
        return BREAK_YES;
     else
        return NO_BREAK;
   }
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
int  go_test(const char input[],const  char  output[], double high)
{

double temp_t;
FILE *fp, *fp2;
int i,j,k;
int temp_i;
char tmp_s[200];
double total_v;
double total_t = 0;
double delta_t; 

UINT state_machine;
printf("-----------go test go-------------------------------------\n");
if(high > SLOP_MAX_Y )
{
   DEBUG_PRINT("warning ERROR 865959 !!\n");
   high = 9.5;  // fix ERR
   // return 0;
}
DEBUG_PRINT("infname=%s outfname=%s\n", input, output);
 fp = fopen(input,"r");
 fp2 = fopen(output, "w");
if( fp ==NULL ){DEBUG_PRINT("ERROR 888444!!\n"); return -1;  }
if( fp2 ==NULL ){DEBUG_PRINT("ERROR 999888444!!\n"); return -1;  }

fprintf(fp2,"go test infname=\n%s\n from high=\n%f \n",input, high);
fprintf(fp2,"outname=\n%s\n",output);

int parameter;

fscanf(fp,"%i\n", &parameter);
DEBUG_PRINT("par=%i\n", parameter);
fgets(tmp_s, 200, fp);
DEBUG_PRINT("%s\n",tmp_s);

v[0] = 0.00000000001;

//////////////////////////////////////////////////////////
int flag_exit =0;
int ret;
ret =0;
       state_machine = STATE_INIT;
i=0;
     ret = fscanf(fp,
          " %i %f %f %f %f %f %f %f \n", 
           &temp_i, &temp_t, &x[i] , &y[i] , &m[i] , 
           &angle_deg[i] , &a_curv[i], &delta_s[i] ) ;
i =1;
j =1;
k =1;
do       
{
   double delta_t;
   double delta_xx, delta_yy;

  if(i > 200) break;

   switch(parameter)
   {
    case 8:
     ret = fscanf(fp,
          " %i %f %f %f %f %f %f %f \n", 
           &temp_i, &temp_t, &x[i] , &y[i] , &m[i] , 
           &angle_deg[i] , &a_curv[i], &delta_s[i] ) ;

        DEBUG_PRINT("par=%i\n",parameter);
        break;

    case 7:
        DEBUG_PRINT("par=%i\n",parameter);
        exit(1);
        break;
    default:
        DEBUG_PRINT(" ERROR 222987765 !!\n");
        exit(1);
        break;
    }

   if(ret == EOF)
   {
       DEBUG_PRINT(" ======== go test !! end of file !! ======\n");
       state_machine = STATE_EXIT;
   }
   else
   {

       state_machine = state_machine;
        DEBUG_PRINT("[read_i=%i] i=%i  x=%f y=%f d_s=%f\n"
            ,temp_i, i, x[i] , y[i], delta_s[i]);

   }
switch(state_machine)
{
case STATE_INIT:
      DEBUG_PRINT("STATE=INIT\n");
      if(y[i] <= high)
      {
      k = i;  // remember start from i array !!
      state_machine = STATE_YES;

      v[i] = 0.00000000001;
      DEBUG_PRINT("GOTO STATE=YES\n");
      }

      break;
case STATE_YES:
      DEBUG_PRINT("STATE=YES\n");
      printf("Release Ball !!\n");
      fprintf(fp2,"Release Ball !!\n");
   v[i] = pow(v[i-1],2) + 2*a_curv[i]*delta_s[i];
   v[i] = sqrt(v[i]);
   delta_t  = delta_s[i]/ ((v[i]+v[i-1]) /2 ) ; 
   DEBUG_PRINT("delta_t=%f \n", delta_t);

   total_t += delta_t;
   fprintf(fp2,"%i %f %f    %f %f \n",i,total_t,delta_t   ,x[i],y[i]);

   //state_machine = STATE_INIT;

   if( BREAK_YES == check_condition(i)) 
    {
      state_machine = STATE_EXIT;
      DEBUG_PRINT("GOTO STATE=EXIT\n");
    }
   break;
case STATE_EXIT:
      DEBUG_PRINT("STATE=EXIT\n");
      flag_exit = 1;    // one way exit !! here !! 
   break;
default:
   DEBUG_PRINT("ERROR 1173834!! \n");
   state_machine = STATE_INIT;
   break;
}

        i++;
        j++;
DEBUG_PRINT("while check\n");
}while(flag_exit == 0);

printf("total time = %f  \n", total_t); 

// fprintf(fp2, "total time = %f  \n", total_t); 

//////////////////////////////////////////////////////////

fclose(fp);
fclose(fp2);

return 0;

}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
int  xgo_testvvvv(char input[],  char  output[])
{
double temp_t;
FILE *fp, *fp2;
int i,j,k;
int temp_i;
char tmp_s[200];
double total_v;
double total_t = 0;
double delta_t; 
 fp = fopen(input,"r");
 fp2 = fopen(output, "w");
if( fp ==NULL ) return -1;
if( fp2 == NULL ) return -1;
fgets(tmp_s, 200, fp);

v[0] = 0.00000000001;
i =0;
//////////////////////////////////////////////////////////
printf("----------------------------------------------------------");
do       
{
   double t;
   double delta_xx, delta_yy;
i++;
   if(EOF == fscanf(fp,
   " %i %f %f %f %f %f %f %f \n", 
      &temp_i, &temp_t, &x[i] , &y[i] , &m[i] , 
      &angle_deg[i] , &a_curv[i], &delta_s[i] ))
   {
       break;
   }

   v[i] = pow(v[i-1],2) + 2*a_curv[i]*delta_s[i];

   v[i] = sqrt(v[i]);

   t  = delta_s[i]/ ((v[i]+v[i-1]) /2 ) ; 

   total_t += t;



}while(1);

printf("total time = %f  \n", total_t); 

fprintf(fp2, "total time = %f  \n", total_t); 

//////////////////////////////////////////////////////////

fclose(fp);
fclose(fp2);

return 0;

}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
int  xgo_testxxbb2(char input[],  char  output[])
{
double temp_t;
FILE *fp, *fp2;
int i,j,k;
int temp_i;
char tmp_s[200];
double total_v;
double total_t = 0;
double delta_t; 
 fp = fopen(input,"r");
 fp2 = fopen(output, "w");
if( fp ==NULL ) return -1;
if( fp2 == NULL ) return -1;
fgets(tmp_s, 200, fp);

v[0] = 0.00000000001;
i =0;
//////////////////////////////////////////////////////////
printf("----------------------------------------------------------");
do       
{
   double t;
   double delta_xx, delta_yy;
i++;
   if(EOF == fscanf(fp,
   " %i %f %f %f %f %f %f %f \n", 
      &temp_i, &temp_t, &x[i] , &y[i] , &m[i] , 
      &angle_deg[i] , &a_curv[i], &delta_s[i] ))
   {
       break;
   }

   v[i] = pow(v[i-1],2) + 2*a_curv[i]*delta_s[i];

   v[i] = sqrt(v[i]);

   t  = delta_s[i]/ ((v[i]+v[i-1]) /2 ) ; 

   total_t += t;



}while(1);

printf("total time = %f  \n", total_t); 

fprintf(fp2, "total time = %f  \n", total_t); 

//////////////////////////////////////////////////////////

fclose(fp);
fclose(fp2);

return 0;

}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
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










