# TokenTool
- To execute please use one of the following two options:
  - TokenTool.exe -s outputFile.txt string123 k
  - TokenTool.exe -p string123 k
- Where:
    - string123: is the base string and should be all different characters, for example: abcdefghijklm...
    - k: is the size of the token, it shouldn't be greater than the length of the base string.
- With option -p:
	- It generates a csv file with a size of 100 tokens per record.
- With option -s:
	- It prints the tokens in blocks of 100 tokens.

- It's written in pure C Standard so it should run properly both Windows and Unix archs.
- If you have any doubts about the base string and token sizes just use this equation: 
# n!/(n-r)! 

Where n is the base string size and r is the token size. Then the result should be multiplied by r and that's an aproximate file size in Bytes. 


