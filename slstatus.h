/* See LICENSE file for copyright and license details. */

/* battery */
const char *battery_perc(const char *);

/* cpu */
const char *cpu_perc(const char *unused);

/* datetime */
const char *datetime(const char *fmt);

/* kanji */
const char *kanji(const char *unused);

/* ram */
const char *ram_perc(const char *unused);

/* run_command */
const char *run_command(const char *cmd);

/* temperature */
const char *temp(const char *);

/* wifi */
const char *wifi_perc(const char *interface);
