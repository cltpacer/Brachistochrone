
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "lib.c"

#include  "l2.c"
#include  "l3.c"

/////////////////////////////////////////
int test_001();

/////////////////////////////////////////////////////////
int  main()
{

printf(" Slop curve ...Start !! \n" );

if( 0 != test_mem() )
{
   printf(" MEM test fail !! \n");
   return 1;

}

test_001();

return 0;

}

////////////////////////////////////////////////////////////////
int test_001()
{
char inputfilename[200];
char outputfilename[200];

strcpy(inputfilename, "curve_001.txt");
strcpy(outputfilename, "curve_001.txt");

draw_cal_slop_001("o1.txt");
draw_cal_slop_002("o2.txt");
draw_cal_slop_003("o3.txt");

go_test("o1.txt","result1.txt", 15);
go_test("o2.txt","result2.txt", 12);
go_test("o3.txt","result3.txt", 8);


return 0;

}
///////////////////////////////////////////////////////////















