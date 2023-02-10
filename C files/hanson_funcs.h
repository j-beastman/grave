/*
 * Will Eykyn and John Eastman
 * 1/31/23
 * Homework: Filesofpix
 * hanson_funcs.h
 * 
 * CS logins: weykyn01, jeastm01
 * 
 * File Purpose: This file is the interface for the helper functions that 
 *               interact with Hanson's data structures. 
 */

#include "mem.h"
#include "seq.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>

void output(int width, int height, Seq_T raster);
char int_to_char(int x);
void printHeader(int rasterWidth, int rasterHeight);
void freeTable(Table_T freeMe);
void vfree(const void *key, void **value, void *cl);