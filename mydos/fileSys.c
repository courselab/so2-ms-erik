/*
 *    SPDX-FileCopyrightText: 2024 ms-erik <erikmelges@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fileSys.h"
#include "kaux.h"

struct fs_header_t *get_fs_header() {
  return (struct fs_header_t *)0x7c00;
}

void load_disk_into_memory(int block_coordinate, int sectors_to_read, void *target_addres) {
  int sector_coordinate = (block_coordinate - 1) % MAX_SECTORS + 1;
  int head_coordinate = ((block_coordinate - 1) / MAX_SECTORS) % MAX_HEADS;
  int cylinder_coordinate = (block_coordinate - 1) / (MAX_HEADS * MAX_SECTORS);

  __asm__ volatile(
      "pusha \n"
      "mov boot_drive, %%dl \n"    /* Select the boot drive (from rt0.o). */
      "mov $0x2, %%ah \n"          /* BIOS disk service: op. read sector. */
      "mov %[sectToRead], %%al \n" /* How many sectors to read          */
      "mov %[cylCoord], %%ch \n"          /* Cylinder coordinate (starts at 0).  */
      "mov %[sectCoord], %%cl \n"  /* Sector coordinate   (starts at 1).  */
      "mov %[headCoord], %%dh \n"  /* Head coordinate     (starts at 0).      */
      "mov %[targetAddr], %%bx \n" /* Where to load the file system (rt0.o).   */
      "int $0x13 \n"               /* Call BIOS disk service 0x13.        */
      "popa \n" ::
      [headCoord] "g"(head_coordinate),
      [sectCoord] "g"(sector_coordinate),
      [cylCoord] "g"(cylinder_coordinate),
      [sectToRead] "g"(sectors_to_read),
      [targetAddr] "g"(target_addres));
}
