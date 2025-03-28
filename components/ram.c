/* See LICENSE file for copyright and license details. */
#include <stdio.h>

#include "../slstatus.h"
#include "../util.h"

#include <stdint.h>

const char *ram_perc(const char *unused) {
  uintmax_t total, free, buffers, cached;
  int percent;

  if (pscanf("/proc/meminfo",
             "MemTotal: %ju kB\n"
             "MemFree: %ju kB\n"
             "MemAvailable: %ju kB\n"
             "Buffers: %ju kB\n"
             "Cached: %ju kB\n",
             &total, &free, &buffers, &buffers, &cached) != 5)
    return NULL;

  if (total == 0)
    return NULL;

  percent = 100 * ((total - free) - (buffers + cached)) / total;
  return bprintf("%d", percent);
}
