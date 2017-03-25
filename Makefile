#--------------------------------------- Select target computer
#SYSTYPE="Workstation"
SYSTYPE="Mac"
#SYSTYPE="uv2000"
#--------------------------------------- Adjust settings for target computer
ifeq ($(SYSTYPE),"Workstation")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall 
GSL_INCL =  -I/home/dlcheng/Install/gsl/include
GSL_LIBS =  -L/home/dlcheng/Install/gsl/lib
endif

ifeq ($(SYSTYPE),"Mac")
CC       =   /usr/local/Cellar/gcc/5.2.0/bin/gcc-5  
OPTIMIZE =   -O3 -Wall
GSL_LIBS=   -L/usr/local/Cellar/gsl/1.16/lib 
GSL_INCL =  -I/usr/local/Cellar/gsl/1.16/include
endif

ifeq ($(SYSTYPE),"uv2000")
CC       =   gcc
OPTIMIZE =   -O3 -Wall
GSL_LIBS=   -L/home/dlcheng/lib/gsl-1.6/lib  -Wl
GSL_INCL =  -I/home/dlcheng/lib/gsl-1.6/include
endif

OPTIONS =  $(OPTIMIZE) $(OPT) 

EXEC   = downgrade_j

OBJS   = allvars.o init.o load_jing.o main.o memory_control.o out_put.o warn_end.o

INCL   = allvars.h proto.h define.h Makefile


CFLAGS = $(OPTIONS) $(GSL_INCL)


LIBS   = $(GSL_LIBS) -lgsl -lgslcblas -lm

$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS)   -o  $(EXEC)  

$(OBJS): $(INCL) 


clean:
	rm -f $(OBJS) $(EXEC) *.gch

