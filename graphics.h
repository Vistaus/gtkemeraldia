/*                                */
/* xemeraldia   ------ graphics.h */
/*                                */

#include <stdio.h>

//#define GTK_DISABLE_DEPRECATED
//#define GDK_PIXBUF_DISABLE_DEPRECATED
//#define G_DISABLE_DEPRECATED

#include <gtk/gtk.h>
#include <unistd.h>
#include <gettext.h>

#define _(x) gettext(x)

typedef enum {
	EMPTY = 0,
	COLOR_1 = 1,
	COLOR_2 = 2,
	COLOR_3 = 3,
	COLOR_4 = 4,
	COLOR_5 = 5,
	COLOR_6 = 6,
	CHECKED = 10,
	OBSTACLE = 32,
	STAR = 44
} cellstatus_t;

typedef enum {
	EMPTY_SUB = 0,
	CRACKED = 1,
	DELETE = 2,
	NEW_CRACKED = 5
} cellsubstatus_t;

#define BLOCK_VARIETY  6
#define BLOCK_WIDTH  32
#define BLOCK_HEIGHT 32
#define CRUSH_ANIME_FRAMES  5

#define BOARD_WIDTH  7
#define BOARD_HEIGHT 14

#define WIN_WIDTH   (BLOCK_WIDTH * (BOARD_WIDTH + 1))
#define WIN_HEIGHT  (BLOCK_HEIGHT * (BOARD_HEIGHT + 1))
#define DIFF_X       (BLOCK_WIDTH / 2)
#define DIFF_Y       (BLOCK_HEIGHT / 2)

#define MAX_DELAY   920


extern GdkGC   *draw_gc, *delete_gc;
extern GdkPixmap  *board_pix, *block[BLOCK_VARIETY * 2 + 1], *saved_screen, *background;
extern GdkPixmap  *crush[CRUSH_ANIME_FRAMES];
extern GdkPixmap  *star;
extern GtkWidget  *board_w, *quit, *start, *scores, *nextItem_w, *score_disp, *level_disp, *about;
extern GtkWidget  *score_frame, *score_text, *high_sc_w, *topLevel;
extern int     colored;
extern guint timer;
extern PangoFontDescription *animated_score_font;
extern PangoFontDescription *game_over_font;
extern PangoFontDescription *pause_font;
extern FILE *f_scores;
extern int errno_scores;


typedef struct {
  gboolean  usescorefile;
  const char *scorefile;
  GdkColor    block1pixel;
  GdkColor    block2pixel;
  GdkColor    block3pixel;
  GdkColor    block4pixel;
  GdkColor    block5pixel;
  GdkColor    block6pixel;
  GdkColor    starpixel;
} AppData, *AppDataPtr;

extern AppData app_data;

/* In graphics.c */
gboolean expose_board(GtkWidget *widget, GdkEventExpose *event, gpointer data);
void RedrawNextItem(void);
void deleteCell(int xcoord, int ycoord);
void delete_1_block(int x, int y);
void printNextItem(void);
void drawCell(int xcoord, int ycoord, cellstatus_t color, cellsubstatus_t sub);
void printBlock(int x, int y, cellstatus_t color);
void crack_1_block(int x, int y);
void crushAnimate(int x, int y, int num);
void printScore(void);
void printItem(void);
void printLevel(void);
void clearScreen(void);
void clearNextItem(void);
void startTimer(void);
void stopTimer(void);
void showTmpScore(long tmp_sc, int sc_x, int sc_y, long ch_s);
void Done(void);

/* In move.c */
void Rotation(void);
void CCRotation(void);
void MoveLeft(void);
void MoveRight(void);
void MoveDown(void);
void moveItem(int vx, int vy);
gboolean CanItemMove(int vx, int vy, int vrot) /* G_GNUC_PURE */ ;
gboolean CanStarMove(int vx, int vy) G_GNUC_PURE;

/* In games.c */
void StartGame(void);
void addScore(int sc_x, int sc_y);
void makeNext(void);

/* In crack.c */
gboolean canMoveDown(void) G_GNUC_PURE;
gboolean DropItem(void);

void Quit(void);

/* In score.c */
void update_highscore_table(void);
void open_high_scores_file(void);
void read_high_scores(void);
void write_high_scores(void);
void PrintHighScores(void);

/* In init-graphics */
void  initGTK (GtkWidget *w);
void  initXlib (void);

#ifndef HIGH_SCORE_TABLE
#define HIGH_SCORE_TABLE ".xemeraldia.scores"
#endif

#ifndef HAVE_USLEEP
void usleep(unsigned);
#endif
