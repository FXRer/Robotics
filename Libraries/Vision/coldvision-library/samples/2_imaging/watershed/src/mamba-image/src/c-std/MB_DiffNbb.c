/*
 * Copyright (c) <2012>, <Nicolas BEUCHER and ARMINES for the Centre de 
 * Morphologie Mathématique(CMM), common research center to ARMINES and MINES 
 * Paristech>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to permit 
 * persons to whom the Software is furnished to do so, subject to the following 
 * conditions: The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * Except as contained in this notice, the names of the above copyright 
 * holders shall not be used in advertising or otherwise to promote the sale, 
 * use or other dealings in this Software without their prior written 
 * authorization.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "mambaApi_loc.h"
#include "mambaApi_vector.h"

/****************************************
 * Neighbor functions                   *
 ****************************************/

#define VEC_TYPE MB_Vector1
#define VEC_LOAD(pointer) MB_vec1_load(pointer)
#define VEC_STORE(pointer, value) MB_vec1_store(pointer, value)

#define COMP_NO_SHIFT(cond,inout,in)                                        \
{                                                                           \
    if (neighbors&(cond)) {                                                 \
        inout = inout & ~(in);                                              \
    }                                                                       \
}                                                                           \

#define COMP_SHIFT_LEFT(cond,inout,inl,inr)                                 \
{                                                                           \
    if (neighbors&(cond)) {                                                 \
        MB_Vector1 temp1, temp2;                                            \
        temp1 = (inr<<(MB_vec1_size-1));                                    \
        temp2 = (inl>>1);                                                   \
        temp1 = temp1 | temp2;                                              \
        inout = inout & ~(temp1);                                           \
    }                                                                       \
}                                                                           \

#define COMP_SHIFT_RIGHT(cond,inout,inl,inr)                                \
{                                                                           \
    if (neighbors&(cond)) {                                                 \
        MB_Vector1 temp1, temp2;                                            \
        temp1 = (inl>>(MB_vec1_size-1));                                    \
        temp2 = (inr<<1);                                                   \
        temp1 = temp1 | temp2;                                              \
        inout = inout & ~(temp1);                                           \
    }                                                                       \
}                                                                           \

#include "MB_Neighbors_vector.h"

#undef VEC_TYPE
#undef VEC_LOAD
#undef VEC_STORE
#undef COMP_NO_SHIFT
#undef COMP_SHIFT_LEFT
#undef COMP_SHIFT_RIGHT

/****************************************/
/* Main function                        */
/****************************************/

/*
 * Computes the set difference between two binary image pixels
 * (a central pixel and its neighbors in the other image).
 * The neighbor depends on the grid used (see mambaCommon.h). Neighbors are
 * described using a pattern (see enum MB_Neighbors_code_t). If no neighbor
 * is defined, the function will leave silently doing nothing.
 *
 * \param src source image in which the neighbor are taken
 * \param srcdest source of the central pixel and destination image
 * \param neighbors the neighbors to take into account
 * \param grid the grid used (either square or hexagonal)
 * \param edge the kind of edge to use (behavior for pixel near edge depends on it)
 *
 * \return An error code (MB_NO_ERR if successful)
 */
MB_errcode MB_DiffNbb(MB_Image *src, MB_Image *srcdest, Uint32 neighbors, enum MB_grid_t grid, enum MB_edgemode_t edge)
{
    Uint32 bytes_in;
    MB_Image *temp;
    PLINE *plines_in, *plines_inout;
    MB_errcode err;
    MB_Vector1 edge_val = BIN_FILL_VALUE(edge);

    /* Error management */
    /* Verification over image size compatibility */
    if (!MB_CHECK_SIZE_2(src, srcdest)) {
        return MB_ERR_BAD_SIZE;
    }
    /* Only greyscale images can be processed */
    switch (MB_PROBE_PAIR(src, srcdest)) {
    case MB_PAIR_1_1:
        break;
    default:
        return MB_ERR_BAD_DEPTH;
    }

    /* If src and srcdest are the same image, we create a temporary */
    /* images where we copy the pixels value */
    if (src==srcdest) {
        temp = MB_malloc(sizeof(MB_Image));
        if (temp==NULL) {
            return MB_ERR_CANT_ALLOCATE_MEMORY;
        }
        err = MB_Create(temp, src->width, src->height, src->depth);
        if (err!=MB_NO_ERR) {
            return err;
        }
        err = MB_Copy(src, temp);
        if (err!=MB_NO_ERR) {
            return err;
        }
    } else {
        temp = src;
    }

    /* Setting up pointers */
    plines_in = temp->plines;
    plines_inout = srcdest->plines;
    bytes_in = MB_LINE_COUNT(src);

    /* Calling the corresponding function */
    if (grid==MB_SQUARE_GRID) {
        if ((neighbors&MB_NEIGHBOR_ALL_SQUARE)==0) {
            /* No neighbors to take into account */
            return MB_NO_ERR;
        }
        MB_comp_neighbors_square(plines_inout, plines_in, bytes_in, temp->height,
                                 neighbors, edge_val);
    } else {
        if ((neighbors&MB_NEIGHBOR_ALL_HEXAGONAL)==0) {
            /* No neighbors to take into account */
            return MB_NO_ERR;
        }
        MB_comp_neighbors_hexagonal(plines_inout, plines_in, bytes_in, temp->height,
                                    neighbors, edge_val);
    }

    /* Destroying the temporary image if one was created */
    if (src==srcdest) {
        MB_Destroy(temp);
    }
    
    return MB_NO_ERR;
}

