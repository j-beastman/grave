/*
 * Will Eykyn and John Eastman
 * 1/20/23
 * Restoration.c
 * Homework: Filesofpix
 * CS logins: weykyn01, jeastm01
 * 
 * Program Purpose: This program uses Hanson's Abstract Data Types to read in 
 *                  corrupted "plain" PGM files and output a restored RAW PGM 
 *                  file of the image. More specifically, this program 
 *                  utilizes Hanson's Atoms for quick and easy comparisons of 
 *                  keys found when reading in the corrupted image file. These 
 *                  Atoms are hashed into a Hanson Table where the numerical 
 *                  values associated with that specific key are stored. When 
 *                  a matched key is found, the numerical sequence is added to 
 *                  a Hanson Sequence of integer arrays. This represents the 
 *                  restored raster.
 * BUGS: Our program cannot handle the case where the '\n' is injected in
 *      whitespace.
 */

#include "split.h"
#include "hanson_funcs.h"
#include <assert.h>
#include <stdbool.h>
#include "atom.h"
#include "readaline.h"

static FILE *open_or_abort(char *fname, char *mode);

int main(int argc, char *argv[]) 
{
        assert(argc <= 2);
        FILE *fp;
        /* Read from stdin or from file */
        if (argc == 2) {
                fp = open_or_abort(argv[1], "r");
        } else if (argc == 1) { /* taking data from stdin */
                fp = stdin;
        }
        /*      
         * datap is pointer to the bytes that readaline returns. Num_bytes is
         * the length of that sequence of bytes. We call readaline before the
         * loop to assert that we're not dealing with an empty file.
         */
        char *datap;
        size_t num_bytes = 0;
        num_bytes = readaline(fp, &datap);
        if (feof(fp)) {
                fclose(fp);
                fp = NULL;
                exit(EXIT_SUCCESS);
        }

        /* Make counters for the split arrays and raster dimensions */
        int gunkCounter, numsCounter, rasterHeight, rasterWidth = 0;

        /* 
         * -Create a sequence to hold original raster lines.
         * -Create a table to hold all raster lines until we find a match
         *      once the Table_put function returns a non-void pointer, then
         *      we know we've found a match.
         */
        Seq_T originalRaster = Seq_new(1000);
        Table_T rasterTable = Table_new(1000, NULL, NULL);
        void *resultPointer;

        /* 
         * Once we find a match between two raster lines, we've found the 
         * original sequence of gunk, as we call it. So, we'll store this
         * as an Atom to compare to future sequences of gunk as a new way of
         * finding original raster lines (instead of using the rasterTable)
         */ 
        const char *theGunk = NULL;
        bool match = false;

        /*********************************************************************
         * This loop will continue to run until we've read all of the lines
         * in the corrupt .pgm file.
         * There are 2 cases inside of loop: match is found or not found
         * If match not found yet...
         *    - We add each key, value pair to our table.
         * Once we've found a match...
         *    - We set match = true, 
         *    - Make the theGunk Atom for future gunk comparisons,
         *    - Set the rasterWidth (because we know that each original 
         *              line will have the same number of gray values), and 
         *    - We add first 2 lines to the sequence
         *    - Set the rasterHeight to 2 because we now have
         *              2 lines in the sequence
         *    - Deallocate table because it's no longer needed
         *              in the search for original lines
         *    - For each subsequent loop run, we check if the current 
         *              line's sequence is original by comparing its atom
         *              to the 'theGunk' atom. If it is original, we add it to 
         *              the sequence. If it's not original, we recycle the 
         *              array holding its gray values (a.k.a 'nums').
         *********************************************************************/
        while (!feof(fp)) {
                gunkCounter = 0;
                numsCounter = 0;
                /* gunk filled with sequence of injected non-digit chars */
                char *gunk = malloc(sizeof(*gunk) * num_bytes);
                assert(gunk != NULL);
                /* nums filled with digit chars (converted to ints) */
                int *nums = malloc(sizeof(*nums) * num_bytes);
                assert(nums != NULL);

                /* split() distributes digit and non-digit chars */
                split(nums, gunk, &datap, num_bytes, &numsCounter, 
                      &gunkCounter);
                      
                const char *key = Atom_new(gunk, gunkCounter);
            
                if (match == false) {
                        resultPointer = Table_put(rasterTable, key, nums);
                        if (resultPointer != NULL) {
                                match = true;
                                theGunk = Atom_new(gunk, gunkCounter);
                                rasterWidth = numsCounter;
                                /* Add original line that was in the table */
                                Seq_addhi(originalRaster, resultPointer);
                                /* Then add the line was just put into table */
                                Seq_addhi(originalRaster, 
                                        Table_remove(rasterTable, theGunk));
                                rasterHeight = 2;
                        }
                } else {
                        if (key == theGunk) {
                                Seq_addhi(originalRaster, nums);
                                rasterHeight++;
                        } else {
                                FREE(nums);
                        }
                }
                FREE(gunk);
                FREE(datap);   
                /* call to readaline() will determine when to leave loop */
                num_bytes = readaline(fp, &datap);
        }
        /* Output raw .pgm file to standard output */
        output(rasterWidth, rasterHeight, originalRaster);

        freeTable(rasterTable);
        fclose(fp);
        fp = NULL;
        Seq_free(&originalRaster);
        exit(EXIT_SUCCESS);
}

/*
 * name:      open_or_abort
 * purpose:   used to open the input file given by commandline
 * arguments: the file name to be opened, the mode for which the file will 
 *            be used
 * returns:   a pointer to the open file
 * effects:   leaves file open for action. MUST be closed at end of use
 */
static FILE *open_or_abort(char *fname, char *mode) {
        FILE *fp = fopen(fname, mode);
        if (fp == NULL) {
                fprintf(stderr, "Could not open file %s with mode %s\n", 
                fname, mode);
                exit(EXIT_FAILURE);
        }
        return fp;
}
