/* 
 * File:   main.c
 * Authors: Adam Ziel, Matt Bennett
 *
 * Created on June 26, 2016, 12:24 PM
 * 
 * ELEC3725 Assignment #6 - ARMv8 Decoder
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Determine control bits for an ARMv8 binary opcode stored as ASCII characters 
 * of 1's and 0's with index 0 being the largest place value.
 * 
 * Return 9 element character array with i[0] being a letter to represent the
 * format of the opcode and i[1:8] representing the needed control bit value.
 */
char* decode( char * inputBinary ){
    char *control = malloc(12);
    if ( inputBinary[ 5 ] == '1' ) {
       if ( inputBinary[ 1 ] == '0' && inputBinary[ 2 ] == '0' ){
            // BR is decoded as branch type and not register type. 
            // Branch Type
            control = "B11100X00";
       } else {
           // Conditional Branch Type
           control = "C10100X00";
       }
    } else if ( inputBinary[ 4 ] == '0' ){
        if ( inputBinary[ 8 ] == '0' ){
            // LSL & LSR are decoded as immediate types and not data types.
            // Immediate Type
            control = "IX00X0011";
        } else{
            // IM Type
            control = "MX0001010";
        }
    } else if ( inputBinary[ 3 ] == '0' ){
        // STXR & LDXR are decoded as register types and not data types. 
        // Register Type
        control = "R00000001";
    } else{
        // STXR & LDXR are decoded as register types and not data types.
        // BR, LSL, & LSR are decoded as branch, immediate, & immediate types
        // and not data types.
        if ( inputBinary[ 8 ] == '0' && inputBinary[ 9 ] == '0' ){
            // Data Type - Store
            control = "S10001X10";
        } else{
            // Data Type - Load
            control = "LX0010111";
        }
    } 
    return control;
}


/*
 * Receive console input from user corresponding to ARMv8 binary opcode.
 * Determine the resulting control bits needed for the provided opcode.
 * Provide basic results to console.
 */
int main(int argc, char** argv) {
    while ( 1 ) {
        char inputBinary[ 11 ];
        printf( "Please enter opcode in binary: " );
        scanf( "%s", &inputBinary );
        getchar();
        
        char *control = decode( inputBinary );
        
        char *type = malloc( 10 );
        switch ( control[ 0 ] ){
            case 'B': type = "Branch"; break;
            case 'C': type = "CondBranch"; break;
            case 'I': type = "Immediate"; break;
            case 'M': type = "IM"; break;
            case 'R': type = "Register"; break;
            case 'S': type = "Data Store"; break;
            case 'L': type = "Data Load"; break;
        }
        printf( "%s Type\n", type );
        
        const char *nameList[ 8 ] = { "Reg2Loc", "UncondBranch", "Branch", 
                "MemRead", "MemWrite", "MemToReg", "ALUSrc", "RegWrite" };
        for ( char i = 0; i < 8; i++ ){
            printf( "%-15s", nameList[ i ]);
            printf( " = %c\n", control[ i+1 ] );
        }
        
        char continueChar[ 1 ];
        printf( "\nContinue? (Y/N) " );
        scanf( "%s", &continueChar );
        getchar();
        if ( *continueChar != 'Y' && *continueChar != 'y' ){
            break;
        }
    }
    return (EXIT_SUCCESS);
}



