#pragma once
#include <sys/time.h>
#include <time.h>
#include <string.h>
#ifndef NDEBUG

#define dbg \
    fprintf(stderr, "%s(line %d): %s()\t$$$$$$$$$$$$$$$$$$$$\n", basename(__FILE__), __LINE__, __FUNCTION__);

#define outHex(buff, len) \
for(int i = 0; i < len; i++) \
{\
    fprintf(stderr, "0x%02x, ", buff[i]); \
} \
fprintf(stderr, "\t%s:%d\n", basename(__FILE__), __LINE__)

#define outDec(buff, len) \
for(int i = 0; i < len; i++) \
{\
    fprintf(stderr, "%d, ", buff[i]); \
} \
fprintf(stderr, "\t%s:%d\n", basename(__FILE__), __LINE__)


// 捕捉段错误等, 自动打印函数栈
void catchFatalError(void);
void deleteErrorCatch(void);

#define D_UNUSED(x) (void)x;
#define DELETE_PTR(ptr) 			\
    do { 							\
        if (NULL != ptr) 			\
        {							\
            delete ptr; 			\
            ptr = NULL;				\
        }							\
    }while(0)

#define   SETCOLOR(color, fd)   dprintf(fd, "\033[0;"#color"m")
#define   RESETCOLOR(fd)      dprintf(fd, "\033[0;58m")
#define   MOVETOXY(x,y,fd)     dprintf(fd, "\033["#x";"#y"H")

#define PR(fd)    dprintf(fd,"\n");
#define PP(fd)    { SETCOLOR(33, fd);dprintf(fd, "%-15s() ",__func__); \
                SETCOLOR(37,fd);dprintf(fd,"%-10s:%-5d ", __FILE__, __LINE__); \
              }

#define PD(X) { SETCOLOR(32,0);dprintf(0, #X" = %-5d ",(X)); \
                PP(0);PR(0); \
                RESETCOLOR(0); \
              }

#define PADDR(X) { SETCOLOR(32,0);dprintf(0, #X"'s address = %p ",(X)); \
                PP(0);PR(0); \
                RESETCOLOR(0); \
              }

#define PS(X) do{  \
                SETCOLOR(31,0);dprintf(0,"Str is < "); \
                SETCOLOR(35,0);dprintf(0, X);SETCOLOR(31,0); \
                dprintf(0, " > "); \
                PP(0);PR(0); \
                RESETCOLOR(0); \
              }while(0)

#define PF(X) { SETCOLOR(31,0);dprintf(0, #X" = %-9f ",(X)); \
                PP(0);PR(0); \
                RESETCOLOR(0); \
              }
//打出当前时间 -- 精确到微秒
#define PTIME {  struct timeval tp; \
                struct tm t_m;\
                gettimeofday (&tp, NULL);\
                t_m = *localtime( &tp );\
                printf("TIME -- %d:%d:%d  [%d ms:%d us]\n",\
                    t_m.tm_hour,t_m.tm_min, t_m.tm_sec, tp.tv_usec/1000,tp.tv_usec%1000); \
              }

#define TIME_WORK_INIT struct timeval tp_start;struct timeval tp_end;int timeuse;
#define TIME_WORK_START gettimeofday (&tp_start, NULL);
#define TIME_WORK_END(SS) {gettimeofday (&tp_end, NULL); \
                timeuse = 1000000 * (tp_end.tv_sec - tp_start.tv_sec) + tp_end.tv_usec - tp_start.tv_usec; \
                printf (SS" -  spend time - %12d usecs\n", timeuse); \
                }

#define IMPOSSIBLE_ERROR fprintf(stderr, "\n[[[[[[[[--ERROR!!! %s %d--]]]]]]]]\n", __func__, __LINE__);

#define STDIN (0)
#define STDOUT (1)
#define STDERROR (2)

#define unix_error()  do{ \
    int fd = STDERROR; \
    SETCOLOR(31,fd);\
    dprintf(fd, "<%s>\t", strerror(errno));\
    PP(fd);PR(fd); \
    RESETCOLOR(fd);\
}while(0)

#else
#define PT(X)
#define ERRX(X)
#define ERR(X)
#endif
