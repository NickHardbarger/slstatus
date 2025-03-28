/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "零";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * kanji               current day of week kanji       NULL
 * ram_perc            memory usage in percent         NULL
 * run_command         custom shell command            command (echo foo)
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

/* vol module stolen from github.com/brookiestein */
static const char vol[] =
    "muted=`wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $3;}'`; \
                            volume=`wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $2;}'`; \
                            if [ -z ${muted} ]; then \
                                printf \"${volume}\"; \
                            else printf \"离开\"; \
                            fi";

static const struct arg args[] = {
    /* function        format         argument */
    {temp, "^fg(cc241d)  %s°C ^fg()",
     "/sys/class/thermal/thermal_zone1/temp"},
    {cpu_perc, "^fg(d65d0e) %s%% ^fg()", NULL},
    {ram_perc, "^fg(d79921) %s%% ^fg()", NULL},
    {wifi_perc, "^fg(98971a) %s%% ^fg()", "wlp3s0"},
    {battery_perc, "^fg(689d6a) %s%% ^fg()", "BAT0"},
    {run_command, "^fg(458588)  %s ^fg()", vol},
    {datetime, "^fg(b16286)%s^fg()", "%Y年%m月%d日"},
    {kanji, "^fg(b16286) %s ^fg()", NULL},
    {datetime, "^fg(b16286)%s ^fg()", "%H:%M:%S"},
};
