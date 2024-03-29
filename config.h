/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int baralpha        = OPAQUE;
// static const unsigned int baralpha        = 0xff;
static const unsigned int borderalpha     = OPAQUE;
static const char *fonts[]          = {"FantasqueSansM Nerd Font Mono:size=15:antialias=true","noto color emoji:size=13:antialias=true",};
static const char dmenufont[]       =  "FantasqueSansM Nerd Font Mono:size=15:antialias=true";
static const char col_gray1[]       = "#050505";
static const char col_gray2[]       = "#bbbbbb";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#333333";
static const char col_cyan[]        = "#00ffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray3, col_gray1,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     	instance  title           tags mask 	iscentered	isfloating	monitor */
	{ "Gimp",				NULL,     NULL,           0,        	0,					1,          	-1 },
	{ "Brave",		NULL,     NULL,							0,					0,					0,          	-1 },
	{ "Alacritty",  NULL,     NULL,           0,         	0,					0,            -1 },
	{ "Alacritty",  "float",  NULL,           0,         	1,					1,            -1 },
	{ "Xmessage",		NULL, "xmessage",      0,          1,					1,            -1 },
	{ "mpv",				NULL,     "mpvfloat",     0,         	1,					1,            -1 },
	{ "mpv",				NULL,     "mpvwebcam",   ~0,          0,					1,            -1 },
	{ NULL,					NULL,     "Event Tester", 0,        	0,					1,          	-1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.77; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask // start/windows key
#define AltMask Mod1Mask // Altkey
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray2, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,          					    XK_t, 		 spawn,          {.v = termcmd } },
	{ AltMask|MODKEY,               XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,     0,                Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,     0,                Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,                Button2,        zoom,           {0} },
	{ ClkStatusText,   0,                Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,   0,                Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,   0,                Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,   0,                Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,   0,                Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,   MODKEY,           Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,   AltMask,          Button1,        sigdwmblocks,   {.i = 7} },
	{ ClkClientWin,    MODKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,           Button3,        togglefloating, {0} },
	{ ClkClientWin,    AltMask|ShiftMask,Button1,        resizemouse,    {0} },
	{ ClkTagBar,       0,                Button1,        view,           {0} },
	{ ClkTagBar,       0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,           Button1,        tag,            {0} },
	// { ClkTagBar,       MODKEY,           Button3,        toggletag,      {0} },
};

