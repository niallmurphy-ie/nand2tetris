// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.
	@R0
	D=M
	@x
	M=D
	@R1
	D=M
	@y
	M=D
	@R2 // SUM
	M=0
	@i
	M=0

	(LOOP)
		// Compare i to y (max)
		@i
		D=M
		@y
		D=D-M
		// Jump to END if D == 0
		@END
		D;JEQ
		// Sum
		@x
		D=M
		@R2
		M=M+D
		// Iterate i
		@i
		M=M+1
		// Loop
		@LOOP
		0;JEQ
	(END)
		@END
		0;JEQ

