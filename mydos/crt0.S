#    SPDX-FileCopyrightText: 2024 ms-erik <erikmelges@usp.br>
#   
#    SPDX-License-Identifier: GPL-3.0-or-later
	.code16gcc		/* Select 16-bit code.                    */
	.global _start		/* This will be the program entry point.  */
	.text

	jmp _start
_start:
    call main
        ret


