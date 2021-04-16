/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps	     = 1;	    /* 1 means gaps are used by default */
static const unsigned int gappx     = 20;       /* default gap between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const double defaultopacity  = 0.75;     
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_blue[]        = "#072f75";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_blue  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

  ///  typedef struct {
  ///	const char *class;
  ///	const char *instance;
  ///	const char *title;
  ///	unsigned int tags;
  ///	int isfloating;
  ///    double opacity; // 0 means left it to the compositor configurations.
  ///	int monitor;
  ///  } Rule;

  { "Gimp",      NULL,       NULL,       0,            1,           0.0,		-1 },
///  { "firefox",   NULL,       NULL,       0,            0,           0.0,		-1 },
///  { "Alacritty", NULL,       NULL,       0,            0,           0.0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },

/// centeredmaster_begin
  { "|CM|", centeredmaster },
  { ">CFM>", centeredfloatingmaster },
/// centeredmaster_end

/// bottomstack_begin
	{ "BSTACK",      bstack },
	{ "BSHORIZ",      bstackhoriz },
/// bottomstack_end

/// grid_begin
	{ "GRID",      grid },
/// grid_end

/// cyclelayouts_begin
  { NULL, NULL }, /// should be the last
/// cyclelayouts_end
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
static void rotatestack(const  Arg *arg);
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "/bin/sh", "-c", "~/.dwm/bin/terminal", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_f,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Escape,     killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
/// centeredmaster_begin
//	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
//	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
/// centeredmaster_end
/// cyclelayouts_begin
	{ MODKEY,		    XK_Down,  cyclelayout,    {.i = -1 } },
	{ MODKEY,           XK_Up,    cyclelayout,    {.i = +1 } },
/// cyclelayouts_end
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
/// actualfullscreen_begin
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
/// actualfullscreen_end
/// alwaysontop_begin
	{ ALTKEY|ShiftMask,             XK_t,  togglealwaysontop, {0} },
    { ALTKEY|ShiftMask|ControlMask,             XK_t, unalwaysontop_all, {0} },
/// alwaysontop_end
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
/// clientopacity_begin
//    { MODKEY|ShiftMask,             XK_KP_Add, changeopacity,  {.f = +0.1}},
//    { MODKEY|ShiftMask,             XK_KP_Subtract, changeopacity,  {.f = -0.1}},
/// clientopacity_end
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
/// functionalgap_begin
	{ MODKEY|ShiftMask,             XK_KP_Add,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_KP_Subtract,  setgaps,         {.i = +5 } },
	{ MODKEY|ShiftMask,                       XK_KP_Equal,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
/// functionalgap_end
/// shiftview_begin
	{ MODKEY,              XK_Right,           shiftview,  { .i = +1 } },
	{ MODKEY,              XK_Left,           shiftview,  { .i = -1 } },
	{ MODKEY|ShiftMask, XK_Left, rotatestack, {0} },
/// shiftview_end
/// maximize_begin
	{ MODKEY|ControlMask|ShiftMask, XK_h,           togglehorizontalmax, {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,           togglehorizontalmax, {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,           toggleverticalmax,   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,           toggleverticalmax,   {0} },
	{ MODKEY|ControlMask,           XK_m,           togglemaximize,      {0} },
/// maximize_end
/// defaultopacity_begin
//	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   SHCMD("transset-df -a --dec .1") },
//	{ MODKEY|ShiftMask,		XK_d,	   spawn,	   SHCMD("transset-df -a --inc .1") },
//	{ MODKEY|ShiftMask,		XK_f,	   spawn,	   SHCMD("transset-df -a .75") },
/// defaultopacity_end
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
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

