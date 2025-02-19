# C++ <code>ifstream.eof()</code> Cheatsheet
This C++ script opens multiple text files with various end-of-line byte combinations and compares the values of <code>infile.eof()</code> and <code>infile.fail()</code> at the end of each file.

A detailed description of the displayed information can be found in the in-code documentation. In summary, each column of `1's` and `0's` is a snapshot of the values of <code>.eof()</code> and <code>.fail()</code> after a specified number of <code>ifstream >> string</code> extractions. The number at the top of the column indicates the number of extractions the occurred before the snapshot; for example, the first column shows the values returned by <code>.eof()</code> and <code>.fail()</code> before any extractions take place, the second column shows the values after the first extraction, and so forth.

*The default output is shown below:*
```
>>'s   0   1   2   3   4

EOF    0   0   0   0  -1-  filename: A1310B1310C1310
FAIL   0   0   0   0  -1-  bytes:    41 0D 0A 42 0D 0A 43 0D 0A

EOF    0   0   0   0  -1-  filename: A1310B1310C13
FAIL   0   0   0   0  -1-  bytes:    41 0D 0A 42 0D 0A 43 0D

EOF    0   0   0   0  -1-  filename: A1310B1310C10
FAIL   0   0   0   0  -1-  bytes:    41 0D 0A 42 0D 0A 43 0A

EOF    0   0   0   0  -1-  filename: A13B13C13
FAIL   0   0   0   0  -1-  bytes:    41 0D 42 0D 43 0D

EOF    0   0   0   0  -1-  filename: A10B10C10
FAIL   0   0   0   0  -1-  bytes:    41 0A 42 0A 43 0A

EOF    0   0   0  -1- -1-  filename: A1310B1310C
FAIL   0   0   0   0  -1-  bytes:    41 0D 0A 42 0D 0A 43

EOF    0  -1- -1- -1- -1-  filename: ABC
FAIL   0   0  -1- -1- -1-  bytes:    41 42 43
```
## *Important conclusions from the above test:*

The function <code>.eof()</code> returns the same values whether the file ends in a <code>carriage return (0x0D)</code>, a <code>line feed (0x0A)</code>, or both in that order. Both function returns `1` following the first extraction attempt that extracts no data.

However, this is not the case if the file ends without a carriage return or a line feed (i.e. the last byte in the file is a character, not a whitespace or control character). In this case, <code>.eof()</code> returns `1` following the last extraction attempt that successfully extracts data.

This is because the extraction operator <code>>></code> ignores only *leading* whitespace when reading out a word. If there are carriage return or line feed characters after the last word in the file, they remain in the file stream after the last word is extracted because <code>>></code> does *not* ignore *trailing* whitespace. The function <code>.eof()</code> returns `1` when there are *no bytes* remaining in the file stream, so the files with trailing whitespace or control characters require one additional extraction after the last word to reach end-of-file.

The function <code>.fail()</code> always returns `1` following the last extraction attempt that extracts no data.

## *Why is this important?*


Different editors save text files in different ways. For example, Notepad does not add any whitespace or control characters at the end of the file, while Vim (by default) adds a carriage return character and a line feed character at the end of each file. Similarly, writing to a file in C++ with the insertion operator <code><<</code> will not add any trailing whitespace bytes unless the file ends with <code>endl</code> or <code>"\n"</code>, each of which add both a carriage return character and a line feed character. This should be taken into consideration when writing C++ programs that read data from files.
> Note:
> The included <code>filereading.exe</code> was compiled in the Visual Studio 2022 Developer Powershell v17.13.0 on Windows 11 using the command <code>cl /EHsc .\filereading.cpp</code>.
