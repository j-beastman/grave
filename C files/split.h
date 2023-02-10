/*
 * Will Eykyn and John Eastman
 * 1/20/23
 * Split.h
 * Homework: Filesofpix
 * CS logins: weykyn01, jeastm01
 * 
 * File Purpose: This file contains the interface for split.c. It shows the
 *              libraries that we utilize for our functions as well as the
 *              declarations for our functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

void split(int nums[], char gunk[], char **datapp, size_t length, 
           int *numsCounter, int *gunkCounter);
int number_finder(char **datapp, size_t count, size_t lineLength);
int char_to_int(char c);
void splitTester(int nums[], char gunk[], int *numsCounter, int *gunkCounter);