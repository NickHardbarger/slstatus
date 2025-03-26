/* See LICENSE file for copyright and license details. */
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../slstatus.h"
#include "../util.h"

#define RSSI_TO_PERC(rssi)                                                     \
  rssi >= -50 ? 100 : (rssi <= -100 ? 0 : (2 * (rssi + 100)))

#include <limits.h>
#include <linux/wireless.h>

#define NET_OPERSTATE "/sys/class/net/%s/operstate"

const char *wifi_perc(const char *interface) {
  int cur;
  size_t i;
  char *p, *datastart;
  char path[PATH_MAX];
  char status[5];
  FILE *fp;

  if (esnprintf(path, sizeof(path), NET_OPERSTATE, interface) < 0)
    return NULL;
  if (!(fp = fopen(path, "r"))) {
    warn("fopen '%s':", path);
    return NULL;
  }
  p = fgets(status, 5, fp);
  fclose(fp);
  if (!p || strcmp(status, "up\n") != 0)
    return NULL;

  if (!(fp = fopen("/proc/net/wireless", "r"))) {
    warn("fopen '/proc/net/wireless':");
    return NULL;
  }

  for (i = 0; i < 3; i++)
    if (!(p = fgets(buf, sizeof(buf) - 1, fp)))
      break;

  fclose(fp);
  if (i < 2 || !p)
    return NULL;

  if (!(datastart = strstr(buf, interface)))
    return NULL;

  datastart = (datastart + (strlen(interface) + 1));
  sscanf(datastart + 1,
         " %*d   %d  %*d  %*d\t\t  %*d\t   "
         "%*d\t\t%*d\t\t %*d\t  %*d\t\t %*d",
         &cur);

  /* 70 is the max of /proc/net/wireless */
  return bprintf("%d", (int)((float)cur / 70 * 100));
}
