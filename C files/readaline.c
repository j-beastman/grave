/*
 * Will Eykyn and John Eastman
 * 1/20/23
 * Homework: Filesofpix
 * readaline.c
 * 
 * CS logins: weykyn01, jeastm01
 * 
 * Purpose: This function takes an open file pointer and a pointer to 
 *          a char. The function will allocate space on the heap and populate 
 *          the array with one full line of the file up to 1000 bytes. The 
 *          function will return the number of bytes in the populated array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>
#include "readaline.h"

/*
 * name:      readaline
 * purpose:   this function reads in chars one by one until it reads either a 
 *            '\n' character or reaches End of File (EOF). Eveyrtime a char is 
 *            read in, the function populates an array of chars in newly 
 *            allocated memory. If the line read is longer than 1000 bytes, 
 *            the function reallocates a larger amount of memory.
 * arguments: file pointer to the input file, and a pointer to a pointer of 
 *            type char
 * returns:   the number of bytes read and stored in the array of chars
 * effects:   allocates memory on the heap and populates it with chars
 */
size_t readaline(FILE *inputfd, char **datapp) {
        /* assert that neither parameter is passed as NULL */
        assert(datapp != NULL && inputfd != NULL);

        (*datapp) = malloc(1000);
        /* assert that malloc worked */
        assert(*datapp != NULL);

        size_t count = 0;
        size_t max = 1000;
        char c;
        c = getc(inputfd);
        if (c == EOF) {
                free(*datapp);
                *datapp = NULL;
                return 0;
        } 

        /* assert no error reading in the file */
        assert(ferror(inputfd) == 0);

        while (c != '\n' && c != EOF) {
                if (count >= max) {
                        *datapp = realloc(*datapp, (count + 1000));
                        max += 1000;
                }
                (*datapp)[count] = c;
                c = getc(inputfd);
                assert(ferror(inputfd) == 0);
                count++;
        }

        return count;
}
