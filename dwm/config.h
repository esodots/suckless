/* Arch (Eluktronics) dwm config, copied from the ThinkPad one 2026-10-26.
 * Bar at the bottom like qtile (Super+B hides it); its text is slstatus, and
 * clicks on it go to ~/.local/bin/barclick (see statuscmd below). */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:pixelsize=20" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:pixelsize=20";
static const char col_bg[]          = "#000000";
static const char col_fg[]          = "#ffffff";
static const char col_dim[]         = "#91959e";
static const char col_focus[]       = "#555555";
static const char col_normal[]      = "#14161b";
static const char *colors[][3]      = {
	/*               fg       bg         border   */
	[SchemeNorm] = { col_dim, col_bg,    col_normal },
	[SchemeSel]  = { col_fg,  col_focus, col_focus  },
};

/* Clicks on the status text (slstatus) run statuscmd with the mouse button
 * and the clicked part, the parts being split by statussep. */
static const char statussep[] = "│";
static const char statuscmd[] = "barclick";

/* tagging: 10 tags, Super+0 is the tenth like in qtile */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 0: no gaps around st in tiles */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 240;  /* the panel is 240 Hz */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_dim, "-sb", col_focus, "-sf", col_fg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[]  = { "i3lock", "-c", "14161b", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_q,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("thunar || nautilus") },
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	/* machine-specific keys, not in the repo (gitignored) */
#if __has_include("keys.local.h")
#include "keys.local.h"
#endif
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	/* focus: k / Down = next, Up = previous; j / ; = master narrower / wider */
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_semicolon, setmfact,    {.f = +0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("roll") },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	/* layouts: Tab flips between the last two, F monocle, T tile */
	{ MODKEY,                       XK_Tab,    setlayout,      {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_v,      togglefloating, {0} },
	{ MODKEY,                       XK_grave,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_grave,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	/* screenshots, as in qtile (~/.local/bin/screenshot-clip) */
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("screenshot-clip file") },
	{ MODKEY|ControlMask|ShiftMask, XK_s,      spawn,          SHCMD("screenshot-clip clip") },
	{ 0,                            XK_Print,  spawn,          SHCMD("screenshot-clip full") },
	{ MODKEY,                       XK_Print,  spawn,          SHCMD("sleep 5; screenshot-clip full") },
	/* hardware keys */
	{ 0, XF86XK_AudioRaiseVolume,  spawn, SHCMD("barvol +5") },
	{ 0, XF86XK_AudioLowerVolume,  spawn, SHCMD("barvol -5") },
	{ 0, XF86XK_AudioMute,         spawn, SHCMD("barvol mute") },
	{ 0, XF86XK_AudioMicMute,      spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_MonBrightnessUp,   spawn, SHCMD("bl +5; pkill -USR1 -x slstatus") },
	{ 0, XF86XK_MonBrightnessDown, spawn, SHCMD("bl -5; pkill -USR1 -x slstatus") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button3,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button4,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button5,        statusclick,    {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
