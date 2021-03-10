////////////////////////////////////////////////////////////////////
//
// GENERAL CODE CHANGES
//
////////////////////////////////////////////////////////////////////

// Upon review of the code, the following changes 

* Fix compiler warnings (when compiled with gcc v9.3.2)
* Objects unecessarily allocated on the heap
* Ensure no memory leaks
* Fix conversion of .890 to .ass for Hebrew (see below)
* Validate the code with fuzzing
* Implement the probe function
* Ensure that none of the other files being converted have regressed.
* Write test cases (gtest) for utility functions.

////////////////////////////////////////////////////////////////////
//
// HEBREW .890 CODE CONVERSION PROBLEMS
//
////////////////////////////////////////////////////////////////////

// There are two (2) issues:

//////////////////////////////
// 1. The input sample .ass is different to the output .ass.
//////////////////////////////

* The quotation marks '"' are wrong. The errors are obvious when doing a side-by-side
comparison.
* There are unecessary `\N` at the start of line.

//////////////////////////////
// 2. Fix grammatical errors
//////////////////////////////

// NOTE: The ASS file for Hebrew has been generated using SubtitleEdit (.890 to .ass), but
//       a native Hebrew speaker tells me that the conversion is not quite right.

Here are examples of the most common issues we see when converting 890 to ASS:

In line number 79, the ASS contains the following text
Dialogue: 0,1:01:58.16,1:02:02.88,Default,,0,0,0,,?? ,?? ?? ?????- ?????? 35 ???\N??? ??? ???? ???
It should be:
Dialogue: 0,1:01:58.16,1:02:02.88,Default,,0,0,0,,??, ?? ?? ?????? -????? 35 ???\N??? ??? ???? ???

 
In line number 163, the ASS contains the following text:
Dialogue: 0,1:05:28.80,1:05:30.92,Default,,0,0,0,,.?? ,?? ??\N...?? ,?? ??- .?? ,?? ??-
It should be:
Dialogue: 0,1:05:28.80,1:05:30.92,Default,,0,0,0,,.??, ?? ??\N...??, ?? ??. -??, ?? ??-

The issues are with the punctuation marks, I'll give you some examples if it were in English so you'll understand better what you see above-
The ',' mark should be right after the word, than ' ' and then the next word (Hello, Bob).
In the ASS file it reversed (Hello ,Bob).

NOTE: Once these issues are fixed, the output needs to be reviewed. The above _ONLY_ notes
      the most common observed issues. There may be others not reported above. It will be an
      iterative process.
