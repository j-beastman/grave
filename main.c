/*
 * Will Eykyn and John Eastman
 * 1/20/23
 * Lab01 Rawness
 * 
 * CS logins: weykyn01, jeastm01
 * 
 */

/* TODO:
 * 1. It is an unchecked run-time error to call Pnmrdr_new twice on the same 
 *      file handle
 * 2. Change P2 to P5
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "readaline.h"


int main(int argc, char *argv[]) {
        FILE *fp;
        fp = open_or_abort(argv[1], "w");
        
        fprintf(fp, )
}