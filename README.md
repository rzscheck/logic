# logic
## A digital logic simulation written in C  
This is an attempt to simulate an eight bit computer, starting from the bare logic gates.
It's based off of the NandGame, which in turn is based off of Nand2Tetris.
I've gotten all of the basic components created. The code, while barely commented, should be pretty self explanatory if you know about digital logic and components like multiplexors.
## Help Wanted: ALU/instruction set design
I want to do something pretty simple but that has enough functionality to actually do stuff (run a simple OS???). Coding the logic gates and components was the easy part. Any help would be greatly appreciated with this as I don't have a good idea what's necessary in an instruction set to make it theoretically Turing Complete or computationally universal or whatever (ignoring stuff like memory limits).
## Warning: THIS IS A WORK IN PROGRESS. IT DOESN'T DO ANYTHING COOL RIGHT NOW.
It's set to run the test() function from test.c, which in turn runs test functions for each component (most are commented out right now).
## It's also not working correctly. I'm having some issues with the combined memory (RAM and registers) component.

## Extra Warning: I mean tests in the loosest sense. I'm just visually checking for correct output. I know this isn't best practice, but I'm just an ignorant teenager who hasn't had the time/motivation to learn/teach myself about good testing

To compile just run ```make```. I use gcc so you can change the Makefile if you use clang or something else. Then just run ```./logic```  
## Yet Another Warning: This has only been tested on a Raspberry Pi 3B running the latest 32-bit Rasberry Pi OS. There's nothing that should prevent it from working on other Linux installations as far as I know. As for Mac and Windows, who knows?
