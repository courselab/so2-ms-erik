/*
 *    SPDX-FileCopyrightText: 2024 ms-erik <erikmelges@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "tydos.h"

int main()
{
    char name[100];

    puts("Enter your name: ");
    gets(name);
    puts("Hello ");
    puts(name);
    puts("\n");
}
