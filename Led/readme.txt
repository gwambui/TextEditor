 Prepared by:  Kinyanjui, Wambui J
 ID: 		 24600878
 CONCORDIA UNIVERSITY 

LED command menu

		HERE ARE THE COMMAND EXAMPLES" 

	A single address or adress range can be included with each command

Command example single line:	1c

Command example current line:	.,.c

Command example for range:	2,4c 

Command example full buffer:	1,$c


		HERE ARE THE COMMAND OPTIONS

a - Appends new line after requested address or by default at end of buffer 

i - Inserts new line before requested address or by default at top of buffer

r - Removes specific line or line range

p - Prints the current line or indicated range

n - Prints the current line or indicated range with line numbers

c - Replaces specific text in the buffer lines with supplied text

u - Offsets current address up by given value and not above first line

d - Offsets current address down by given value and not below last line 

w - Writes buffer to associated text file of creates a  new text file and exports buffer to file

= - Prints the address of the current line

e - Exits Led

h - The trusted help menu, you can return here as many times as you like!!

Enter - Same as 1d. Moves current line down by one.

m - Clears the screen

v - Preview items in the buffer