/* Written by Madison Lynch <madi@mxdi.xyz> */
/* Translated to Mandarin by Nick :p */
#include <time.h>

static const char *symbols[] = {
    /*    "日", // Sunday
          "月", // Monday
          "火", // Tuesday
          "水", // Wednesday
          "木", // Thursday
          "金", // Friday
          "土"  // Saturday
     */
    "周日", "周一", "周二", "周三",
    "周四", "周五", "周六"
    // written with zhou, may change to xingqi
};

/**
 * Returns the appropriate Japanese Kanji character correlating with the current
 * day of the week.
 *
 * @param  unused (NULL)
 * @return the appropriate Kanji character (char)
 * @author Madison Lynch
 */
const char *kanji(const char *unused) {
  const time_t current_time = time(NULL);
  const unsigned int weekday = localtime(&current_time)->tm_wday;

  return (weekday < sizeof(symbols) / sizeof(char *)) ? symbols[weekday] : "?";
}
