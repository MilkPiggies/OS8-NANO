====================================================================================

                        // FTxt \\

  *FTxt is a file system created by MilkPiggies (tm)*

====================================================================================

FTxt works on basic text files in its core. All registers and alu's are stored and processed in text (.txt) files.

====================================================================================




Registers a, b, c, ... x, y, z  are stored in /reg
(by default only 4 registers are loaded (a,b, c, d.) )

*if more registers are needed, continue with /a1 as a folder name
====================================================================================




ALU a, b, and c are stored in /alu

/alu folder also contains /alu_reg. alu_reg is used to store the current number in said alu (a, b or c). alu_reg can be opened and closed on command ( alu_reg read on | alu_reg read off )

contents of /alu/alu_reg is the same as /reg. 
====================================================================================




All opcode is stored under /opcode

See opcodes in /opcode/opcode.txt
====================================================================================




This file system is also an assembler, meaning you can write code for a FTxt cpu to boot off of. Adding registers and alu's are possible by simply adding a folder in said (/reg or /alu) folder.

This system works like c code. you can define "headers" in the c code for it to include
====================================================================================




                     // Loading disks //

disks are folders. for floppy disks for example, the structure is as follows;
/disk1                      // root disk folder
    /sectors                //
        /sector1            // first sector of disk
             track1.txt     // first track of first sector
             track2.txt     // second track of first sector
        /sector2            // second sector of disk 
             track1.txt     // first track of second sector    
             track2.txt     // second track of second sector
head.txt                    // 8 bit address of current location

the command to load disks is LOAD with argument DISK and location of disk.

Example:
        LOAD DISK /disk1

This will load disk1 to /media/disk1 and will be accesible.

head.txt must specify the starting address of the disk. it will also contain an 8
bit address for where it is currently reading from. For example; if you load a 
program off of disk1, and the program starts at address 0x501a on the disk 
(see how disks are written bellow) then the program must tell head.txt where to
start reading from, else data will be corrupted and unreadable.

Writing disks is simple. the text files that make up tracks are written in hex.
so for example; 
            a program that writes hello world to the screen would be;

              63 6c 72 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 31 30 30 30 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 30 31 30 31 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 31 31 30 30 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 31 31 31 31 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 30 31 30 30 30 30 30 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 31 30 31 31 31 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 31 31 31 31 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 31 30 30 31 30 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 31 31 30 30 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 31 31 30 30 31 30 30 20 7c 20 6d 6f 76 20 72 65 67 5f 61 20 6d 65 6d 31 20 7c 20 73 65 74 20 72 65 67 5f 61 20 30 30 31 30 30 30 30 31 20 7c 20 64 65 63 6f 20 6d 65 6d 20 62 69 6e 61 72 79 20 61 73 63 69 69 20 6d 65 6d 32 20 7c 20 70 72 6e 74 20 6d 65 6d 32 


                Hello world! in binary = 01101000 01100101 01101100 01101100 01101111 00100000 01110111 01101111 01110010 01101100 01100100 00100001

                Hello world! in hex = 48 65 6c 6f 20 57 6f 72 6c 64 21 

                Hello world in binary in hex = 30 31 31 30 31 30 30 30 20 30 31 31 30 30 31 30 31 20 30 31 31 30 31 31 30 30 20 30 31 31 30 31 31 30 30 20 30 31 31 30 31 31 31 31 20 30 30 31 30 30 30 30 30 20 30 31 31 31 30 31 31 31 20 30 31 31 30 31 31 31 31 20 30 31 31 31 30 30 31 30 20 30 31 31 30 31 31 30 30 20 30 31 31 30 30 31 30 30 20 30 30 31 30 30 30 30 31 


this code loads "Hello world!" into memory then prints the content of memory.

here "mem1" is used to store the hex code, and then mem1 is decoded from hex into ascii and the result of the decode is loaded into mem2. mem2 is then printed.


This program is stored in a track, on a sector, on a disk. for example, a 12 kilobyte disk with only this program stored on it.
    For example we will use exampledisk1.txt . this text file has 12 kilobytes of hexidecimal text. later on we will learn how the cpu decodes
    hexidecimal to binary. Once loaded ( with LOAD DISK exampledisk1.txt ) the cpu will load each line of binary to a memory bank ( eg: /mem/mem_1.txt )
    we can then run the binary code loaded into mem1 with ( RUN MEM_1 ). Running this will load "Hello world!" letter by letter into mem1, after this it will also
    load the command "deco mem binary ascii mem2" which will decode the binary text stored on mem1 onto mem2, then it will print the ascii text stored on mem2.


When coding in hexidecimal, it must be formatted as such before its converted to hex;

    Example:

clr mem | set reg_a 10101010 | mov reg_a mem1 | set reg_b 11110000 |
prnt alu_a | ...etc... 



if we run exampledisk.txt by itself it would be inefficient since the program starts at 10785 bytes out of ~12,000 ( 12,371 bytes ).
To run it properly, we would have to specify the start of the program.

    Example:

            Rx01    Rx02   Rx03     Rx04     Rx05     Rx06
     Cx01   00      00     00       00       00       00

     Cx02   00      00     00       00       00       00 

     Cx03   00      00     00       00       00       00 

     Cx04   00      00     00       00       32       e0 

     Cx05   30      31     30       30       30       30 

     Cx06   20      7c     20       00       00       00 


MOV DISK /exampledisk1/sector1/track1.txt MEM_2
LOAD MEM_2 -START Cx04 Rx05 -END Cx06 Rx03
RUN MEM_2

    -START requires <C> <R>
                <C> = Cx##
                <R> = Rx##

    -END requires <C> <R>
                <C> = Cx##
                <R> = Rx##

Since our program starts with 32, and before that is just 0's, we need to tell LOAD to start loading from address Cx04 Rx05 on exampledisk1 sector1 track1 and end when the rest is just 0's, or at adress Cx06 Rx03 on exampledisk1 sector1 track1. Since track1 in sector1 on exampledisk1 is loaded into mem_2, we can load the program with said arguments.

When we use RUN, the cpu will take the arguments ( RUN MEM_2 ) for example the contents of mem_2 ( currently has contents of /exampledisk1/sector1/track1.txt ) and run the content of
mem_2, in this case our hello world, since we loaded /exampledisk1/sector1/track1.txt at address Cx04 Rx05 with an end of Cx06 Rx03, it will run the program located there. This is:
    32 e0 30 31 30 30 30 30 20 7c 20 ( this isint an actual hello world code, just an example, /exampledisk1/sector1/track1.txt does infact contain a hello world program )
The run command can and will decode hex to ascii if needed. it can detect the language being loaded and convert it into the needed ascii text.

Another example:
        [track1 contains] = 43 4c 52 20 4d 45 4d 5f 31 20 7c 20 53 45 54 20 52 45 47 5f 41 20 30 30 30 30 31 31 31 31 20 7c 20 53 45 54 20 52 45 47 5f 42 20 31 31 31 31 30 30 30 30 20 7c 20 4d 4f 56 20 41 4c 55 5f 41 20 4d 45 4d 5f 31 

        43 4c 52 20 4d 45 4d 5f 31 20 7c 20 53 45 54 20 52 45 47 5f 41 20 30 30 30 30 31 31 31 31 20 7c 20 53 45 54 20 52 45 47 5f 42 20 31 31 31 31 30 30 30 30 20 7c 20 4d 4f 56 20 41 4c 55 5f 41 20 4d 45 4d 5f 31 
        [in ascii] = CLR MEM_1 | SET REG_A 00001111 | SET REG_B 11110000 | MOV ALU_A MEM_1

        if track1 is loaded and run command is sent, [CLR MEM_1 | SET REG_A 00001111 | SET REG_B 11110000 | MOV ALU_A MEM_1] will be ran
        * | in commands will declare a new command *
====================================================================================




                                       // Commands //

- CLR    = sets desired reg/alu/mem to 0000 0000 ---------------------------------- ( 0 )
- SET    = sets a register to desired number ----------------------------------------------------------------- ex: SET REG_A 00001111
- MOV    = moves one reg/alu/mem to another reg/alu/mem --------------------------- ( arguments: <device> <from> <to> ) ex: MOV REG_A REG_B    ( both arguments must be filled exept   for <device>, it is to be used if moving from a disk )

- PRNT   = prints the content of desired reg/alu/mem to bus or desired location --- ( arguments: <from> <to> ) ex: PRNT REG_A BUS     ( if <to> is empty, will default to display )
- RUN    = runs the code in selected memory bank ---------------------------------- ( arguments: <from>      ) ex: RUN MEM_1          
- DECO   = decodes file/address to desired language ------------------------------- ( arguments: <file/addr> <bin/hex/dec> )          
- RECO   = recodes file/address from desired language to desired language --------- ( arguments: <file/addr> <bin/hex/dec> )