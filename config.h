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
 *y battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 *n battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 *n battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 *m cat                 read arbitrary file             path
 *n cpu_freq            cpu frequency in MHz            NULL
 *y cpu_perc            cpu usage in percent            NULL
 *y datetime            date and time                   format string (%F %T)
 *n entropy             available entropy               NULL
 *n hostname            hostname                        NULL
 *n ipv4                IPv4 address                    interface name (eth0)
 *n ipv6                IPv6 address                    interface name (eth0)
 *y kanji               current day of week kanji       NULL
 *n kernel_release      `uname -r`                      NULL
 *n load_avg            load average                    NULL
 *n netspeed_rx         receive network speed           interface name (wlan0)
 *n netspeed_tx         transfer network speed          interface name (wlan0)
 *n num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 *n ram_free            free memory in GB               NULL
 *y ram_perc            memory usage in percent         NULL
 *n ram_total           total memory size in GB         NULL
 *n ram_used            used memory in GB               NULL
 *y run_command         custom shell command            command (echo foo)
 *n swap_free           free swap in GB                 NULL
 *n swap_perc           swap usage in percent           NULL
 *n swap_total          total swap size in GB           NULL
 *n swap_used           used swap in GB                 NULL
 *y temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 *n vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 *n wifi_essid          WiFi ESSID                      interface name (wlan0)
 *y wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

/* vol and mic modules stolen from github.com/brookiestein */
static const char vol[] =
    "muted=`wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $3;}'`; \
                            volume=`wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $2;}'`; \
                            if [ -z ${muted} ]; then \
                                printf \"${volume}\"; \
                            else printf \"离开\"; \
                            fi";

static const char mic[] =
    "muted=`wpctl get-volume @DEFAULT_AUDIO_SOURCE@ | awk '{print $3;}'`; \
                            volume=`wpctl get-volume @DEFAULT_AUDIO_SOURCE@ | awk '{print $2;}'`; \
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
    {run_command, "^fg(458588) %s ^fg()", mic},

    {datetime, "^fg(b16286)%s^fg()", "%Y年%m月%d日"},
    {kanji, "^fg(b16286) %s ^fg()", NULL},
    {datetime, "^fg(b16286)%s ^fg()", "%H:%M:%S"},
};
