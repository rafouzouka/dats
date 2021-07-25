#include <stdint.h>
#include <stdlib.h>

#include "dense_array.h"
#include "dynamic_array.h"

typedef enum
{
    DATS_DENSE_ARRAY_CELL_EMPTY,
    DATS_DENSE_ARRAY_CELL_DATA,
} dats_dense_array_state;

typedef struct
{
    dats_dense_array_state state;
    uint64_t index;
} dats_dense_array_cell;
