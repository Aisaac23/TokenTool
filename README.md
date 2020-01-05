# TokenTool
- To execute please follow one of the following two formats:
  - TokenTool.exe outputFile.txt string123 k
  - TokenTool.exe string123 k
-Where:
    - string123: is the base string and should be all different characters, for example: abcdefghijklm...
    - k: is the size of the token, it should be up to 5 when base string is 26 (alphabet) and up to 6 characters when the base string is 10 (0-9 digits).
  
- It generates a csv file or stores them in memory with no more than 412MB.
- This is the first version of this tool so there are some improvements to be made and some validations to code.
- It's written in pure C Standard so it should run properly both Windows and Unix archs.
- If you have any doubts about the base string and token sizes just use this equation: # n!/(n-r)! Where n is the base string size and r is the token size. Anything greater than 20,971,529 will result in more than 400MB in memory or file size.
- Maybe some day I'll update it for a more flexible version.

