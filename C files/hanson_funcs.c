/*
 * Will Eykyn and John Eastman
 * 1/31/23
 * Homework: Filesofpix
 * hanson_funcs.c
 * 
 * CS logins: weykyn01, jeastm01
 * 
 * File Purpose: This file serves as the implementation for the helper 
 *               functions that interact with Hanson's data structures. This 
 *               allows our restoration program to appear more modular and 
 *               provides a layer of abstraction.
 */

#include "hanson_funcs.h"

/*
 * name:      output
 * purpose:   This function outputs the header and original raster in RAW 
 *            format
 * arguments: int rasterWidth, int rasterHeight, and originalRaster sequence
 * returns:   nothing
 * effects:   prints to standard output and frees data array at each spot in 
 *            sequence
 */
void output(int width, int height, Seq_T raster) {

        printHeader(width, height);

        /* Nested four loop prints out arrays within the sequence */
        void *arrayPointer;
        for (int i = 0; i < height; i++) {
                arrayPointer = (Seq_get(raster, i));
                for (int j = 0; j < width; j++) {
                        printf("%c", int_to_char(((int*)arrayPointer)[j]));
                }
                /* Free sequence as we print */
                free(arrayPointer);
        }
}

/*
 * name:      int_to_char
 * purpose:   cast an integer into its equivalent ASCII char value
 * arguments: an integer
 * returns:   char
 * effects:   changes the type of int into a char
 */
char int_to_char(int x) {
        return x;
}

/*
 * name:      printHeader
 * purpose:   print the accurate file type, dimensions, and maxval for the 
 *            RAW .pgm image file
 * arguments: int width of restored raster, int height of restored raster
 * returns:   nothing
 * effects:   prints to stdout
 */
void printHeader(int rasterWidth, int rasterHeight) {
        char *magicNumber = "P5";
        char *maxVal = "255";
        printf("%s\n%i %i\n%s\n", magicNumber, rasterWidth, rasterHeight, 
                maxVal);
}

/*
 * name:      freeTable
 * purpose:   maps over Hanson table and frees all allocated memory within the 
 *            table, and then frees the table itself
 * arguments: Hanson table
 * returns:   nothing
 * effects:   frees up any allocated memory in the Hanson table, and frees the 
 *            Hanson table 
 */
void freeTable(Table_T freeMe) {
        Table_map(freeMe, vfree, NULL);
        Table_free(&freeMe);
}

/*
 * name:      vfree
 * purpose:   The apply function that frees the value of a key value pair. 
 *            Used in freeTable when mapping over table
 * arguments: a void pointer to a key, a void pointer to a value, and a void 
 *            pointer for closure
 * returns:   void
 * effects:   frees any memory passed in as a value.
 */
void vfree(const void *key, void **value, void *cl) {
        (void) cl;
        (void) key;
        FREE(*value);
}