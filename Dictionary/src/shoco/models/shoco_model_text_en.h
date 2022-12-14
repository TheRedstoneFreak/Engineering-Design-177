#ifndef _SHOCO_INTERNAL
#error This header file is only to be included by 'shoco.c'.
#endif
#pragma once
/*
This file was generated by 'generate_compressor_model.py'
so don't edit this by hand. Also, do not include this file
anywhere. It is internal to 'shoco.c'. Include 'shoco.h'
if you want to use shoco in your project.
*/

#define MIN_CHR 32
#define MAX_CHR 122

static const char chrs_by_chr_id[32] = {
  ' ', 'e', 't', 'a', 'o', 'n', 'i', 'h', 's', 'r', 'd', 'l', 'u', 'm', 'c', 'w', 'y', 'f', 'g', ',', 'p', 'b', '.', 'v', 'k', 'I', '"', '-', 'H', 'M', 'T', '\''
};

static const int8_t chr_ids_by_chr[256] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, 26, -1, -1, -1, -1, 31, -1, -1, -1, -1, 19, 27, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, 25, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, 30, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 21, 14, 10, 1, 17, 18, 7, 6, -1, 24, 11, 13, 5, 4, 20, -1, 9, 8, 2, 12, 23, 15, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

static const int8_t successor_ids_by_chr_id_and_chr_id[32][32] = {
  {12, -1, 0, 1, 5, 13, 6, 2, 4, -1, 11, 14, -1, 7, 10, 3, -1, 9, -1, -1, 15, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 7, 5, -1, 2, 15, -1, 4, 1, 3, 6, -1, 10, 11, -1, 14, -1, -1, 9, -1, -1, 13, 12, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 3, 6, 5, 2, -1, 4, 0, 13, 7, -1, 12, 9, -1, 15, 14, 11, -1, -1, 8, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {6, -1, 1, -1, -1, 0, 7, -1, 2, 3, 5, 4, -1, 10, 12, -1, 8, -1, 13, -1, 14, 11, -1, 9, 15, -1, -1, -1, -1, -1, -1, -1},
  {2, -1, 6, -1, 8, 1, 15, -1, 9, 3, 12, 10, 0, 5, -1, 7, -1, 4, -1, -1, 13, -1, -1, 11, 14, -1, -1, -1, -1, -1, -1, -1},
  {0, 3, 4, 10, 5, 11, 8, -1, 7, -1, 1, 14, -1, -1, 6, -1, 12, -1, 2, 9, -1, -1, 13, -1, 15, -1, -1, -1, -1, -1, -1, -1},
  {-1, 9, 2, 11, 4, 0, -1, -1, 1, 8, 7, 5, -1, 3, 6, -1, -1, 12, 10, -1, -1, 15, -1, 13, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 0, 5, 1, 4, -1, 2, -1, 13, 7, -1, 14, 8, 12, -1, -1, 10, -1, -1, 6, -1, 15, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, 2, 7, 5, -1, 4, 3, 6, -1, -1, 13, 8, 15, 12, 14, -1, -1, -1, 9, 11, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 0, 7, 4, 3, 12, 2, -1, 5, 11, 9, 15, -1, 14, 13, -1, 6, -1, -1, 10, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, -1, 6, 3, -1, 2, -1, 7, 9, 11, 12, 10, -1, -1, -1, 8, -1, 15, 4, -1, -1, 5, -1, -1, -1, -1, 14, -1, -1, -1, -1},
  {3, 0, 11, 7, 6, -1, 2, -1, 12, -1, 5, 1, 9, -1, -1, 15, 4, 8, -1, 10, -1, -1, 14, -1, 13, -1, -1, -1, -1, -1, -1, -1},
  {5, 9, 1, 11, -1, 4, 10, -1, 3, 0, 12, 2, -1, 13, 7, -1, -1, -1, 6, 15, 8, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 0, -1, 2, 3, -1, 4, -1, 8, -1, -1, -1, 5, 12, -1, -1, 7, 14, -1, 9, 6, 11, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {12, 1, 4, 3, 0, -1, 6, 2, 15, 7, -1, 8, 9, -1, 11, -1, 10, -1, -1, -1, -1, -1, 14, -1, 5, -1, -1, -1, -1, -1, -1, -1},
  {5, 3, -1, 0, 4, 6, 1, 2, 9, 7, 12, 10, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, 11, -1, 15, -1, -1, 14, -1, -1, -1, -1},
  {0, 4, 6, -1, 1, -1, 7, -1, 5, -1, 8, 12, -1, -1, -1, -1, -1, -1, -1, 2, -1, 14, 3, -1, -1, -1, -1, 15, -1, -1, -1, 10},
  {0, 2, 8, 4, 1, -1, 5, -1, -1, 3, -1, 9, 7, -1, -1, -1, 13, 6, -1, 10, -1, -1, 11, -1, -1, -1, -1, 12, -1, -1, -1, -1},
  {0, 2, -1, 4, 3, 12, 6, 1, 9, 5, -1, 7, 11, -1, -1, -1, -1, -1, 13, 8, -1, 15, 10, -1, -1, -1, -1, 14, -1, -1, -1, -1},
  {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 3, -1, -1, -1, 2},
  {7, 0, 8, 2, 3, -1, 6, 11, 10, 1, -1, 4, 9, -1, -1, -1, 12, -1, -1, 13, 5, 15, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {12, 0, 10, 5, 2, -1, 7, 15, 8, 6, -1, 1, 3, -1, -1, -1, 4, -1, -1, -1, -1, 11, 14, 13, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, 2, -1, -1, -1, 1, 4, -1, -1, -1, 3},
  {-1, 0, -1, 2, 3, -1, 1, -1, -1, 6, -1, -1, 5, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 0, -1, 13, -1, 2, 3, 5, 4, -1, -1, 8, -1, -1, -1, 14, 10, 9, -1, 6, -1, -1, 7, -1, -1, -1, -1, 11, -1, -1, -1, -1},
  {0, -1, 1, -1, -1, 2, -1, -1, 4, -1, -1, -1, -1, 7, -1, -1, -1, 3, -1, 6, -1, -1, 14, -1, -1, 8, -1, -1, -1, -1, -1, 5},
  {0, -1, 12, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, 1, -1, -1, 7, 6, 4, -1},
  {8, -1, 1, 2, -1, 9, 15, 5, 4, 7, 14, 13, -1, 12, 6, 10, -1, -1, -1, -1, 11, 3, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1},
  {-1, 0, -1, 1, 2, -1, 3, -1, -1, -1, -1, -1, 4, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {8, 4, -1, 3, 5, -1, 1, -1, -1, 0, -1, -1, 6, -1, -1, -1, 2, -1, -1, -1, -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 2, -1, 8, 1, -1, 4, 0, -1, 6, -1, -1, 5, -1, -1, 7, 13, -1, -1, 11, -1, -1, 12, -1, -1, -1, -1, -1, 10, -1, -1, -1},
  {2, 15, 1, 6, -1, -1, -1, -1, 0, 8, 7, 4, -1, 5, 3, -1, -1, -1, -1, 14, -1, -1, -1, 9, -1, -1, 13, -1, -1, -1, 10, -1}
};

static const int8_t chrs_by_chr_and_successor_id[MAX_CHR - MIN_CHR][16] = {
  {'t', 'a', 'h', 'w', 's', 'o', 'i', 'm', 'b', 'f', 'c', 'd', ' ', 'n', 'l', 'p'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {' ', 'I', 'Y', 'W', 'T', 'A', 'M', 'H', 'O', 'B', 'N', 'D', 't', 'S', 'a', ','},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'s', 't', ' ', 'c', 'l', 'm', 'a', 'd', 'r', 'v', 'T', 'A', 'L', '"', ',', 'e'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {' ', '"', '\'', '-', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'-', 't', 'a', 'b', 's', 'h', 'c', 'r', ' ', 'n', 'w', 'p', 'm', 'l', 'd', 'i'},
  {' ', '"', '.', '\'', '-', ',', '?', ';', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'e', 'a', 'o', 'i', 'u', 'A', 'y', 'E', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {' ', 't', 'n', 'f', 's', '\'', ',', 'm', 'I', 'N', '_', 'A', 'E', 'L', '.', 'R'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'r', 'i', 'y', 'a', 'e', 'o', 'u', 'Y', ' ', '.', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'h', 'o', 'e', 'E', 'i', 'u', 'r', 'w', 'a', ' ', 'H', ',', '.', 'y', 'R', 'Z'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'n', 't', 's', 'r', 'l', 'd', ' ', 'i', 'y', 'v', 'm', 'b', 'c', 'g', 'p', 'k'},
  {'e', 'l', 'o', 'u', 'y', 'a', 'r', 'i', 's', 'j', 't', 'b', ' ', 'v', '.', 'h'},
  {'o', 'e', 'h', 'a', 't', 'k', 'i', 'r', 'l', 'u', 'y', 'c', ' ', 'q', '.', 's'},
  {' ', 'e', 'i', 'o', ',', '.', 'a', 's', 'y', 'r', 'u', 'd', 'l', ';', '-', 'g'},
  {' ', 'r', 'n', 'd', 's', 'a', 'l', 't', 'e', ',', 'm', 'c', 'v', '.', 'y', 'i'},
  {' ', 'o', 'e', 'r', 'a', 'i', 'f', 'u', 't', 'l', ',', '.', '-', 'y', ';', '?'},
  {' ', 'h', 'e', 'o', 'a', 'r', 'i', 'l', ',', 's', '.', 'u', 'n', 'g', '-', 'b'},
  {'e', 'a', 'i', ' ', 'o', 't', ',', 'r', 'u', '.', 'y', '!', 'm', 's', 'l', 'b'},
  {'n', 's', 't', 'm', 'o', 'l', 'c', 'd', 'r', 'e', 'g', 'a', 'f', 'v', 'z', 'b'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'e', ' ', 'n', 'i', 's', 'h', ',', '.', 'l', 'f', 'y', '-', ';', 'a', 'w', '!'},
  {'e', 'l', 'i', ' ', 'y', 'd', 'o', 'a', 'f', 'u', ',', 't', 's', 'k', '.', 'w'},
  {'e', ' ', 'a', 'o', 'i', 'u', 'p', 'y', 's', ',', '.', 'b', 'm', ';', 'f', '?'},
  {' ', 'd', 'g', 'e', 't', 'o', 'c', 's', 'i', ',', 'a', 'n', 'y', '.', 'l', 'k'},
  {'u', 'n', ' ', 'r', 'f', 'm', 't', 'w', 'o', 's', 'l', 'v', 'd', 'p', 'k', 'i'},
  {'e', 'r', 'a', 'o', 'l', 'p', 'i', ' ', 't', 'u', 's', 'h', 'y', ',', '.', 'b'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'e', ' ', 'i', 'o', 'a', 's', 'y', 't', '.', 'd', ',', 'r', 'n', 'c', 'm', 'l'},
  {' ', 'e', 't', 'h', 'i', 'o', 's', 'a', 'u', ',', '.', 'p', 'c', 'l', 'w', 'm'},
  {'h', ' ', 'o', 'e', 'i', 'a', 't', 'r', ',', 'u', '.', 'y', 'l', 's', 'w', 'c'},
  {'r', 't', 'l', 's', 'n', ' ', 'g', 'c', 'p', 'e', 'i', 'a', 'd', 'm', 'b', ','},
  {'e', 'i', 'a', 'o', 'y', 'u', 'r', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {'a', 'i', 'h', 'e', 'o', ' ', 'n', 'r', ',', 's', 'l', '.', 'd', ';', '-', 'k'},
  {'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'},
  {' ', 'o', ',', '.', 'e', 's', 't', 'i', 'd', ';', '\'', '?', 'l', '!', 'b', '-'}
};


typedef struct Pack {
  const uint32_t word;
  const unsigned int bytes_packed;
  const unsigned int bytes_unpacked;
  const unsigned int offsets[8];
  const int16_t _ALIGNED masks[8];
  const char header_mask;
  const char header;
} Pack;

#define PACK_COUNT 3
#define MAX_SUCCESSOR_N 7

static const Pack packs[PACK_COUNT] = {
  { 0x80000000, 1, 2, { 26, 24, 24, 24, 24, 24, 24, 24 }, { 15, 3, 0, 0, 0, 0, 0, 0 }, 0xc0, 0x80 },
  { 0xc0000000, 2, 4, { 25, 22, 19, 16, 16, 16, 16, 16 }, { 15, 7, 7, 7, 0, 0, 0, 0 }, 0xe0, 0xc0 },
  { 0xe0000000, 4, 8, { 23, 19, 15, 11, 8, 5, 2, 0 }, { 31, 15, 15, 15, 7, 7, 7, 3 }, 0xf0, 0xe0 }
};
