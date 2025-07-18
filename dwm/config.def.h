/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systraypadding = 140;  /* systray padding */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono:size=15:weight=bold", "FontAwesome:size=15:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono:size=15:weight=bold";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#00ffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

#define HOME "/home/username"

static const char *const autostart[] = {
	"bash", "-c", HOME"/.config/dwm/bash_scripts/autostart.sh", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/* class                instance    title           tags mask     isfloating   monitor   scratch key */
	{ NULL,                 NULL,       "spterm",       0,            1,           -1,       't' },
	{ NULL,                 NULL,       "spcalc",       0,            1,           -1,       'c' },
	{ NULL,                 NULL,       "spvifm",       0,            1,           -1,       'f' },
	{ NULL,                 NULL,       "spmus",        0,            1,           -1,       'm' },
	{ NULL,                 NULL,       "passphrase",   0,            1,           -1,        0  },
	{ "Thunar",             NULL,       NULL,           0,            1,           -1,       'h' },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	{ "[]=",      tile },
	{ "[0]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
#define BROWSER "firefox-esr"
#define TERMINAL "st"
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-p", "Launch: ", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
	{ "~/.config/dwm/dunst/mode_switcher.sh", 1 },
	{ "~/.config/dwm/dunst/mic_mute.sh", 2 },
	{ "st -e pulsemixer", 3 },
	{ "", 4 },
	{ "~/.config/dwm/dunst/calendar.sh", 5 },
};
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"t", TERMINAL, "-T", "spterm", "-g", "60x16+570+0", NULL};
static const char *calccmd[] = {"c", TERMINAL, "-T", "spcalc", "-g", "60x16+570+0", "-e", "python3", "-i", HOME"/.config/dwm/others/import.py", NULL};
static const char *thunarcmd[] = {"h", "thunar", NULL};
static const char *vifmcmd[] = {"f", TERMINAL, "-T", "spvifm", "-g", "135x36+80+0", "-e", "vifm", NULL};
static const char *muscmd[] = {"m", TERMINAL, "-T", "spmus", "-g", "60x16+570+0", "-e", "vifm", HOME"/Music", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
    // monitor
	{ 0,                       XF86XK_Display, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/bash_scripts/monitor.sh", NULL } } },

    // screenshot
	{ 0,                            XK_Print,  spawn,          {.v = (const char*[]){ "bash", "-c", "FILE=Pictures/screenshots/screenshot_$(date +%Y%m%d_%H%M%S).png; import $FILE; xclip -selection clipboard -t image/png -i $FILE", NULL } } },
	{ MODKEY,                       XK_Print,  spawn,          {.v = (const char*[]){ "bash", "-c", "FILE=~/Pictures/screenshots/screenshot_$(date +%Y%m%d_%H%M%S).png; import -window root $FILE; xclip -selection clipboard -t image/png -i $FILE", NULL } } },

    // play-pause
	{ Mod1Mask,                     XK_space,  spawn,          {.v = (const char*[]){ "sh", "-c", "playerctl play-pause || playerctl -p mpv play-pause", NULL } } },

    // volume control
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/dunst/volume_decrease.sh", NULL } } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/dunst/volume_increase.sh", NULL } } },
	{ 0,                     XF86XK_AudioMute, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/dunst/volume_mute.sh", NULL } } },
	{ 0,                  XF86XK_AudioMicMute, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/dunst/mic_mute.sh", NULL } } },

    // brightness control
	{ 0,               XF86XK_MonBrightnessUp, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/dunst/brightness_increase.sh", NULL } } },
	{ 0,             XF86XK_MonBrightnessDown, spawn,          {.v = (const char*[]){ HOME"/.config/dwm/dunst/brightness_decrease.sh", NULL } } },

    // Poweroff
	{ ControlMask|Mod1Mask, 	    XK_Delete, spawn,          {.v = (const char*[]){ "systemctl", "poweroff", NULL } } },

    // appfinder
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_slash,  spawn,          {.v = (const char*[]){ "bash", "-ic", "$(dmenu -p 'Run: ' < /dev/null)", NULL } } },
	{ MODKEY|ShiftMask,    XF86XK_TouchpadOff, spawn,          {.v = dmenucmd } },

    // launch programme
	{ MODKEY,                       XK_s,      spawn,          {.v = (const char*[]){ HOME"/.config/dwm/bash_scripts/spanish.sh", NULL } } },
	{ MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ HOME"/.config/dwm/bash_scripts/mount.sh", NULL } } },
	{ MODKEY,                       XK_b,      spawn,          {.v = (const char*[]){ HOME"/.config/dwm/bash_scripts/bookmarks.sh", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_f,	   spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_t,	   spawn,          {.v = termcmd } },
	{ ControlMask|Mod1Mask, 	    XK_g,	   spawn,          {.v = (const char*[]){ "gnome-boxes", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_k,	   spawn,          {.v = (const char*[]){ "kdeconnect-app", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_o,	   spawn,          {.v = (const char*[]){ "obs", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_y,	   spawn,          {.v = (const char*[]){ BROWSER, "--private-window", "youtube.com", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_p,	   spawn,          {.v = (const char*[]){ BROWSER, "--private-window", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_w,	   spawn,          {.v = (const char*[]){ "ffplay", "-f", "v4l2", "-i", "/dev/video0", NULL } } },
	{ ControlMask|Mod1Mask, 	    XK_j,	   spawn,          {.v = (const char*[]){ HOME"/.config/dwm/bash_scripts/jupyter.sh", NULL } } },
	{ ControlMask|Mod1Mask,         XK_v,      spawn,          {.v = (const char*[]){ HOME"/.config/dwm/bash_scripts/vpn.sh", NULL } } },

    // scratchpad
	{ MODKEY,                       XK_Return, togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                    XK_semicolon, togglescratch,  {.v = vifmcmd } },
	{ MODKEY,                       XK_ntilde, togglescratch,  {.v = vifmcmd } },
	{ MODKEY,                       XK_e,      togglescratch,  {.v = thunarcmd } },
	{ ControlMask|Mod1Mask,         XK_c,      togglescratch,  {.v = calccmd } },
	{ ControlMask|Mod1Mask,         XK_m,      togglescratch,  {.v = muscmd } },

    // window manager control
	{ MODKEY,                       XK_f,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_comma,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_period, incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_n,      setmfact,       {.f = 1.5} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m,      zoom,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_Tab,    setlayout,      {0} },
	{ MODKEY,                       XK_t,      togglefloating, {0} },
	{ MODKEY,                       XK_a,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_a,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_i,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_d,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_d,      tagmon,         {.i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_w,	   spawn,          {.v = (const char*[]){ "systemctl", "suspend", NULL }}},
	{ MODKEY|ShiftMask,             XK_r,	   spawn,          {.v = (const char*[]){ "sh", "-c", "kill $(pgrep -f ~/.config/dwm/bash_scripts/status_bar.sh); ~/.config/dwm/bash_scripts/status_bar.sh &", NULL }}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

