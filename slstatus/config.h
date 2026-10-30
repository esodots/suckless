/* See LICENSE file for copyright and license details. */
/* Arch (Eluktronics), in the qtile bar's order: weather, wifi, brightness, volume,
 * date, time, battery, [shutdown]. SIGUSR1 refreshes at once (sound, barvol,
 * barclick and the brightness keys send it). Clicks: ~/.local/bin/barclick. */

/* interval between updates (in ms); the clock shows minutes, so 5 s late at most */
const unsigned int interval = 5000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/* ~/.local/bin/bar prints "weather │ wifi │ b NN% │ v NN% │ " in one process */
static const struct arg args[] = {
	/* function       format          argument */
	{ run_command,    "%s",           "bar" },
	{ datetime,       "%s │ ",        "%a %-m/%-d │ %H:%M" },
	{ battery_state,  "%s",           "BAT0" },
	{ battery_perc,   "%s%% │ [shutdown] ", "BAT0" },
};
