#include <iostream>

#include "target.h"

uint8_t UBSanFinding(const uint8_t * const message, size_t len) {
    if (len > 4)
    {
        if (message[0] == 'F')
        {
            if (message[1] == 'U')
            {
                if (message[2] == 'Z')
                {
                    if (message[3] == 'Z')
                    {
                        int x[3];
                        int y = 4;
                        int z = x[y];
                        int i = z;
                    }
                }
            }
        }
    }
    return 0;
}
