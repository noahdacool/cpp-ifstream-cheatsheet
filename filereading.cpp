/*
Program name:   File Reading Tests
Created by:     Noah Coolbeth
Created date:   February 18, 2025
Description:
This script analyzes the responses of ifstream.eof() and ifstream.fail()
on files with various end-of-line byte sequences.
*/

#include <fstream>      // for reading files
#include <iostream>     // for printing output
#include <iomanip>      // for printing hex streams
                        
using namespace std;
int main() {



    /* The files in the following array were written in hex, and each
     * file's name represents its contents. The file naming scheme is
     * as follows: a capital letter represents an ASCII byte for that
     * letter, and a two-digit number is the base10 representation of
     * an ASCII control byte. For example, if the file name begins 
     * with 'A' then the first byte in the file is 0x41, ASCII for
     * 'A'. If the next number is 13 then the next byte in the file
     * is 0x0D, ASCII for carriage return (CR). If the next number is
     * 10 then the next byte in the file is 0x0A, ASCII for line feed
     * (LF). */

    const string files[] = {
        "A1310B1310C1310",
        "A1310B1310C13",
        "A1310B1310C10",
        "A13B13C13",
        "A10B10C10",
        "A1310B1310C",
        "ABC"
    };



    /* This variable stores the number of times that ifstream.eof()
     * and .fail() will be recorded for each file in the list below.
     * Because ifstream.eof() and .fail() will be called before and
     * after each extraction, the number of extractions will be this
     * variable minus one. If this variable equals 5, ifstream.eof()
     * and .fail() will each be called 5 times, and the extraction
     * operator will be used 4 times. */

    const int ntests{ 5 };
    


    /* These arrays hold the values returned by ifstream.eof() and
     * .fail() for each time they are called on one file. The first
     * value in the array is the value of .eof/.fail before the
     * first extraction and the last value in the array is the value
     * of .eof/.fail after the last extraction. */

    int eof[ntests]{ 0 };
    int fail[ntests]{ 0 };



    /* This array stores the bytes of a file as a list. The size of
     * this array serves as the maximum length of the files that
     * can be used for this test. Adjust as necessary. */

    char bytes[20]{ 'E' };



    /* These variables store the file stream objects as each file is
     * opened. The first is stored as text - this is the ifstream
     * on which .eof/.fail will be tested. The second is stored as
     * bytes - this is for displaying the contents of the files. */

    ifstream textfile;
    ifstream bytefile;



    /* This variable serves as the destination for the >> operator. */

    string line;



    /* This variable serves as the destination for byte extraction. */

    char byte;



    /* This variable is incremented before each file is processed. */

    int counter{ 0 };



    /* This variable is incremented after each byte is read. */

    int filesize{ 0 };



    /* This line configues cout to output integers in hexadecimal. */

    cout << hex << uppercase << setfill('0');



    /* The following loop opens each file, displaying the status of
     * ifstream.eof() and .fail() before and after each extraction
     * operation. The output summary for a file appears as follows:
     *
     *      ┌───┬───┬───┬───┬───┐
     * >>'s │ 0 │ 1 │ 2 │ 3 │ 4 │ number:   1
     *      ├───┼───┼───┼───┼───┤ filename: A1310B1310C1310
     * EOF  │ 0 │ 0 │ 0 │ 1 │ 1 │ bytes:    41 0D 0A 42 0D 0A 43 0D 0A
     * FAIL │ 0 │ 0 │ 0 │ 1 │ 1 │ content:  A<CR><LF>B<CR><LF>C<CR><LF>
     *      └───┴───┴───┴───┴───┘
     *
     *    or, because I couldn't get the box drawing to work...
     *
     * >>'s   0   1   2   3   4
     *
     * EOF    0   0   0  -1- -1-  filename: A1310B1310C1310 
     * FAIL   0   0   0  -1- -1-  bytes:    41 0D 0A 42 0D 0A 43 0D 0A
     *
     * In this example, the top row indicates the number of
     * extraction operations performed before ifstream.eof() and
     * .fail() were called. This means that the first column shows
     * the status of .eof() and .fail() before the first extraction.
     * The "bytes" field is the entire file in hex, and the "content"
     * field displays the ASCII value of each byte. */

    for (string filename : files) {



        /* This section opens the file and reads the relevant data
         * into the variables above. */

        // increment file counter
        counter++;

        // open file as text to test ifstream.eof() and .fail()
        textfile.open("files/" + filename);

        // open file as bytes to display contents
        bytefile.open("files/" + filename, ios::binary);

        // record .eof/.fail before and after each >> extraction
        for (int i = 0; i < ntests; i++) {
            if (i != 0) textfile >> line;
            eof[i] = textfile.eof();
            fail[i] = textfile.fail();
        }

        // store the bytes of the file in an array
        filesize = 0;
        while (bytefile.get(byte)) {
            bytes[filesize] = byte;
            filesize++; 
        }

        // close files
        textfile.close();
        bytefile.close();



        /* This section displays the relevant data from the files
         * by reading the variables above. */

        // display the header line
        if (counter == 1) {
            cout << endl << endl << ">>'s";
            for (int i = 0; i < ntests; i++) cout << "   " << i;
            cout << endl << endl;
        }

        // display the first line
        cout << "EOF  "; 
        for (int e : eof) cout << (e ? " -1-" : "  0 ");
        cout << "  filename: " << filename;
        cout << endl;

        // display the second line
        cout << "FAIL ";
        for (int f : fail) cout << (f ? " -1-" : "  0 ");
        cout << "  bytes:    ";
        for (int i = 0; i < filesize; i++) cout << setw(2) << (int)(unsigned char)bytes[i] << ' ';
        cout << endl << endl;



        /* Maybe one day I'll figure out box drawing.
         * This section would be a more aesthetically pleasing
         * but less portable alternative to the display method
         * used above, if someone could get the encoding to work.

        // display the first line
        cout << endl << endl << "     ┌";
        for (int i = 0; i < ntests-1; i++) cout << "───┬";
        //cout << "───┐" << endl;
        cout << (char)180 + (char)180 << endl;

        // display the second line
        cout << ">>'s │";
        for (int i = 0; i < ntests; i++) cout << " " << i << " │";
        cout << " number:   " << counter << endl;

        // display the third line
        cout << "     ├";
        for (int i = 0; i < ntests-1; i++) cout << "───┼";
        cout << "───┤ filename: " << filename << endl;

        // display the fourth line
        cout << "EOF  │";
        for (int i = 0; i < ntests; i++) cout << " " << eof[i] << " │";
        cout << " bytes:    ";

        cout << hex << uppercase << setfill('0');
        for (int i = 0; i < filesize; i++) cout << setw(2) << (int)(unsigned char)bytes[i] << ' ';
        cout << endl;

        // display the fifth line
        cout << "FAIL │";
        for (int i = 0; i < ntests; i++) cout << " " << fail[i] << " │";
        cout << " content:  ";

        for (int i = 0; i < filesize; i++) cout << bytes[i]; // unfinished

        // display the sixth line
        cout << "└───┴───┴───┴───┴───┘";
        cout << "     └";
        for (int i = 0; i < ntests-1; i++) cout << "───┴";
        cout << "───┘" << endl << endl;

        */

    }
    cin.ignore();
    return 0;
}
