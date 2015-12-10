#define RGB(R, G, B)	(R | G << 5 | B << 10)
#define Red(Color)		((Color) & 31)
#define Green(Color)	((Color >> 5) & 31)
#define Blue(Color)		((Color >> 10) & 31)

