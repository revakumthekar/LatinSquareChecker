/******************************************************************************
 * @file: latin_square_functions.c
 *
 * WISC NETID: rkumthekar
 * CANVAS USERNAME: Reva Kumthekar
 * WISC ID NUMBER: 9082067217
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Reva Kumthekar (rkumthekar@wisc.edu)
 * @modified: 11/16/2021
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/* 
 * This helper method verifies that each element only appears in a row once
 *
 * @param *row is the pointer to that specific row
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @return 0 if there is a duplicate value in the row, 1 otherwise
 */
int verify_row(int n, char *row)
{

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                if(*(row + i) == *(row + j))
                {

                    return 0;
                }
            }
            
        }
    }

    return 1;
}

/* 
 * This helper method goes through all of the rows and verifies that each row does not contain duplicate
 * characters, using verify_row on each row.
 *
 * @param **latin_square is a pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @return 1 if there is even one occurence of an error, 0 otherwise.
 */
int verify_rows(int n, char **latin_square)
{
    int flag = 0;
    for(int i = 0; i < n; i++)
    {
        if(verify_row(n, *(latin_square+i)))
        {
            continue;
        }else{
            printf("Error in row %d\n", i);
            flag = 1;
        }
    }
    return flag;
}

/* 
 * This helper method verifies that each element only appears in a column once
 *
 * @param *column is the pointer to that specific column
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @return 0 if there is a duplicate value in the column, 1 otherwise
 */
int verify_column(int n, char *column)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                if(*(column + i) == *(column + j))
                {
                    return 0;
                }
            }
            
        }
    }
    return 1;
}

/* 
 * This helper method goes through all of the columns and verifies that each column does not contain duplicate
 * characters, using verify_colum on each row.
 *
 * @param **latin_square is a pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @return 1 if there is even one occurence of an error, 0 otherwise.
 */
int verify_columns(int n, char **latin_square)
{
    char *column_array = malloc(n*sizeof(char));
    int flag = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            *(column_array+j) = *((*(latin_square+j)+i));
        }
        if(verify_column(n, column_array))
        {
            continue;
        }else{
            printf("Error in column %d\n", i);
            flag = 1;
        }
    }
    free(column_array);
    return flag;
}

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
    /* BEGIN MODIFYING CODE HERE */

    FILE *fp;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        return;
    }

    char *buff = malloc(1002 * sizeof(char));
    int rowLength = 0;

    //getting the length of each row
    while(fgetc(fp) != '\n')
    {
        rowLength++;
    }

    *n = rowLength;

    //reserving memory for the pointers to the rows
    *latin_square_in = calloc(*n, sizeof(char *));

    if(*latin_square_in == NULL)
    {
        free(buff);
        *latin_square_in = NULL;
    }

    //reserving memory for each row
    for(int i = 0; i < *n; i++)
    {
        *((*latin_square_in) + i) = calloc(*n, sizeof(char));

    }

    fclose(fp);
    fp = fopen(filename, "r");

    char *row_info;

    //fill in the latin_square data structure 
    for(int i = 0; i < *n; i++)
    {
        row_info = fgets(buff, 1002, fp);
        memcpy(*((*latin_square_in)+i), row_info, *n);

    }
    fclose(fp);
    free(buff);

    /* END MODIFYING CODE HERE */
}\

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    
    //the current char you're looking at
    char current = **latin_square;

    int count = 0;
    //The outer two loops will be getting each element in the square and setting it to current
    //The inner two loops will be checking the current against every element in the square and 
    //  counting occurences.
    for(int i = 0; i < n; i++)
    {
        for(int j =0; j<n; j++)
        {
            current = *(*(latin_square + i)+j);
            count = 0;
            for(int k = 0; k<n; k++)
            {
                for(int l = 0; l<n; l++)
                {
                    if(*(*(latin_square + k)+l) == current)
                    {
                        count++;
                    }
                }
            }
            //if the occurence of that character isn't equal to n, it's not valid
            if(count != n)
            {
                return 0;
            }
        }
    }

    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
  
    // printf("Error in row %d\n", i);
    // printf("Error in column %d\n", i);

    int flag_row = 0;
    int flag_col = 0;

    if(verify_rows(n, latin_square))
    {
        flag_row = 1;
    }
    if( verify_columns(n, latin_square))
    {
        flag_col = 1;
    }

    if(flag_row || flag_col)
    {
        return 0;
    }

    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */

    //freeing each row of pointers
    for(int i = 0; i< n; i++)
    {
        free(*(latin_square+i));
    }
    //freeing the pointer to the 2D array itself
    free(latin_square);

    /* END MODIFYING CODE HERE */
}