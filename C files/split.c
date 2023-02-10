/*
 * Will Eykyn and John Eastman
 * 1/20/23
 * Split.c
 * Homework: Filesofpix
 * CS logins: weykyn01, jeastm01
 * 
 * File Purpose: This file contains functions necessary to split an array
 *              of chars into an array of digit bytes and an array of non-digit
 *              bytes. No memory is allocated in this file.
 */

#include "split.h"

/*
 * name:      split
 * purpose:   to take an array of non-digit and digit chars and organize them 
 *            into 2 different arrays. Digits go into a nums array and 
 *            non-digit chars go into the gunk array
 * arguments: nums[] array of ints, gunk[] array of chars, the original array 
 *            populated from readaline(), int length of original array, 
 *            counters for the amount of elements in nums[] array and in 
 *            gunk[] array.
 * returns:   nothing
 * effects:   populates the nums[] array and gunk[] array with their 
 *            respective digit or non-digit chars
 */
void split(int nums[], char gunk[], char **datapp, size_t length, 
                int *numsCounter, int *gunkCounter) 
{
        size_t count = 0;
        char c;
        while (count < length) {
                c = (*datapp)[count];
                /* Case in which char is a digit byte */
                if (c >= '0' && c <= '9') {
                        /* Call number_finder() to find integer */
                        int value = number_finder(datapp, count, length);
                        if (value >= 10 && value < 100) {
                                count = count + 1;
                        } else if (value >= 100) {
                                count = count + 2;
                        }
                        nums[*numsCounter] = value;
                        *numsCounter += 1;
                } else {
                        gunk[*gunkCounter] = c;
                        *gunkCounter += 1;
                }
                count = count + 1;
        }
}

/*
 * name:      number_finder
 * purpose:   when splitting arrays, if an int has more than 1 digit, this 
 *            function will check if int has either 1 or 2 or 3 digits and 
 *            return the entire number as one int. ie if '8' is read, then 
 *            number_finder will check the next char and if it is an int, then 
 *            multiply 8*10 and add the new char read and return 80
 * arguments: pointer to the original array datapp, and int count as an index 
 *            for where the reader is in the array
 * returns:   integer
 * effects:   changes the char read to an int
 */
int number_finder(char **datapp, size_t count, size_t lineLength) {
        char c = (*datapp)[count];
        int x = char_to_int(c);
        int y;
        if (count < (lineLength - 1)) {
                if ((*datapp)[count + 1] >= '0' &&
                    (*datapp)[count + 1] <= '9') {
                        x = x * 10;
                        c = (*datapp)[count + 1];
                        y = char_to_int(c);
                        x = x + y;
                } else {
                        return x;
                }
        }
        if (count < (lineLength - 2)) {
                if ((*datapp)[count + 2] >= '0' && 
                    (*datapp)[count + 2] <= '9') {
                        x = x * 10;
                        c = (*datapp)[count + 2];
                        y = char_to_int(c);
                        x = x + y;
                }
        }
        return x;
}

/*
 * name:      char_to_int
 * purpose:   cast a char into its ASCII integer value
 * arguments: a char
 * returns:   integer
 * effects:   changes the type of a char into an integer
 */
int char_to_int(char c) {
        return (int)(c) - '0';
}

/*
 * name:      splitTester
 * purpose:   print out the organized arrays AFTER calling split
 * arguments: int nums[] array, char gunk[] array, int counter for nums, int 
 *            counter for gunk
 * returns:   nothing
 * effects:   prints to stdout
 * NEEDSWORK: 
 *      Can we change this to just print out an array, without given type, i.e.
 *      just pass in one array instead of both arrays with their respective 
 *      counters. Could be good exercise with void pointers.
 *      Only issue is that  we don't know where indicator to use: %i or %c
 *     
 */
void splitTester(int nums[], char gunk[], int *numsCounter, int *gunkCounter) {
        printf("Nums array: ");
        for (int i = 0; i < *numsCounter; i++) {
                printf("%i ", nums[i]);
        }
        printf("// Gunk array:");
        for (int i = 0; i < *gunkCounter; i++) {
                printf("%c ", gunk[i]);
        }
        printf("\n");
}


