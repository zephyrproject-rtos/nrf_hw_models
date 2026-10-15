/*
 * Copyright (c) 2018 Oticon A/S
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bs_oswrap.h"
#include "bs_tracing.h"

void hwu_reverse_byte_order(const unsigned char *in_data, unsigned char *out_data, size_t len)
{
    unsigned int i;
    in_data += len - 1;
    for (i = 0; i < len; i++)
    {
        *out_data++ = *in_data--;
    }
}

/**
 * Bitwise reverse 1 byte,
 * Based on code in the public domain as claimed by the author in this page:
 * http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64Bits
 */
uint8_t hwu_rev_byte(uint8_t input)
{
  return ((input * 0x80200802ULL) & 0x0884422110ULL)
          * 0x0101010101ULL >> 32;
}

/**
 * Reverse the bits order in a 32 bit word
 */
uint32_t hwu_rev_32(uint32_t input)
{
  uint32_t ret;
  ret = (uint32_t)hwu_rev_byte((input >> 0) & 0xff) << 24
      | (uint32_t)hwu_rev_byte((input >> 8) & 0xff) << 16
      | (uint32_t)hwu_rev_byte((input >> 16) & 0xff) << 8
      | (uint32_t)hwu_rev_byte((input >> 24) & 0xff);
  return ret;
}

/**
 * Reverse the bits order in a 24 bit word
 */
uint32_t hwu_rev_24(uint32_t input)
{
  uint32_t ret;
  ret = (uint32_t)hwu_rev_byte((input >> 0) & 0xff) << 16
      | (uint32_t)hwu_rev_byte((input >> 8) & 0xff) << 8
      | (uint32_t)hwu_rev_byte((input >> 16) & 0xff);
  return ret;
}

/**
 * Reverse the bits order in a 16 bit word
 */
uint16_t hwu_rev_16(uint16_t input)
{
  uint16_t ret;
  ret = (uint16_t)hwu_rev_byte((input >> 0) & 0xff) << 8
      | (uint16_t)hwu_rev_byte((input >> 8) & 0xff) << 0;
  return ret;
}

/*
 * Read a line from a file into a buffer (s), while
 * skipping duplicate spaces (unless they are quoted), comments (#...),
 * empty lines, and spaces before comments or end of lines.
 * The string will be null terminated (even if nothing is copied in).
 * All isspace() characters (outside of quoted strings) will be normalized to be plain spaces.
 *
 * Return: The number of characters copied into s (apart from the termination 0 byte)
 */
int hwu_readline(char *s, int size, FILE *stream)
{
  int c = 0, i = 0;
  bool was_a_space = true;
  bool in_a_string = false;

  while ((i == 0) && (c != EOF)) {
    while ((i < size - 1) && ((c = getc(stream)) != EOF) && c != '\n') {
      if ((c == '#') && (!in_a_string)) {
        bs_skipline(stream);
        break;
      }
      if (isspace(c) && (!in_a_string)) {
        if (was_a_space) {
          continue;
        }
        was_a_space = true;
        s[i++] = ' ';
        continue;
      } else {
        was_a_space = false;
      }
      if (c == '"') {
        in_a_string = !in_a_string;
      }
      s[i++] = c;
    }
  }

  if (i >= size - 1) {
    bs_trace_warning_line("Truncated line while reading from file after %i chars\n",
              size - 1);
  }

  if ((i > 0) && was_a_space) { /* Remove a possible space at the end */
    i--;
  }
  s[i] = 0;

  return i;
}
