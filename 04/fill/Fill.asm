// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
(LOOP)
		// Load SCREEN into addr
		@SCREEN
		D=A
		@addr
		M=D // Sets to start
		// Load blocks into i
		@8192
		D=A
		@i
		M=D
		@addr
		M=M+D // Sets to SCREEN + i
		// Get current keyboard
		@KBD
		D=M
		@colour
		M=0
		// If 0 --> GOTO Print White
		@PRINT
		D;JEQ
		// BLACK
		@colour
		M=-1
		// GOTO Print Black
		@PRINT
		D;JEQ

		(PRINT)
			// Load i and check if 0
			@i
			D=M
			@LOOP
			D+1;JEQ // Go back to start if back to SCREEN

			// PrintD
			@colour
			D=M
			// Set colour
			@addr
			A=M
			M=D
			// Decrement
			@i
			M=M-1
			@addr
			M=M-1
			@PRINT
			0;JEQ
	@LOOP
		0;JEQ