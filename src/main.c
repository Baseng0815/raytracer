#include <stdio.h>

#include "math.h"

int main(int argc, char *argv[])
{
        struct fvec3 vec = {
                .x = 2.0,
                .y = 3.0,
                .z = 4.0
        };

        fvec3_normalize(&vec);
        fvec3_print(&vec);

        printf("Test\n");
        return 0;
}
