#include "param.h"
#include "types.h"
#include "defs.h"

//This function will generate a random number within the min max
//values passed in. Arguments must be greater than zero.
//If not, it will return -1;

/*git config --global user.name "Your Name"
    git config --global user.email you@example.com
    git commit --amend --reset-author
*/
//implement lfsr

//idea : the most random thing on here is the address assigned to
//each variable. how about lfsr with memory location?

//gcc tash.c -Wall -Werror -O -std=c99 -o tash
/* IMPLEMENTATION

xv6 system so int is a 32 bit number.
I will take the difference between the min and max (call it diff)
online documentation shows that for a 32 bit, set taps to be
32,22,2,1 which will be : (),(>>10),(>>30),(>>31)
by doing this we are able to generate all possible values (0 
(only if diff zero) to 2^32  )
before repitition.
I will always take 
*/

uint* randomnum_gen_seed;

void
random_seed(uint* seed_val)
{
    randomnum_gen_seed = seed_val;
    //cprintf("passed in value successfully: %d \n",*randomnum_gen_seed);
}


uint 
random(uint min, uint max)
{
    
    uint return_val, tmp;

    if(max < min){
        tmp = min;
        min = max;
        max = tmp;
    }

    //diff is x

    uint x = max - min + 1; /*To include max as well(since % is used)*/
    uint result= *randomnum_gen_seed;
    result = result ^ (result << 13);
    result = result ^ (result >> 17);
    result = result ^ (result << 5);
    *randomnum_gen_seed = result;
    return_val = min + (result % x);
    return return_val;
}
