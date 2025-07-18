/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#000000",       /* after initialization */
	[INPUT] =  "#007700",       /* during input */
	[INPUT_ALT] = "#229900",    /* during input, second color */
	[FAILED] = "#FF0000",       /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 0;
