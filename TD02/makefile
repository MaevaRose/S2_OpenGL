CC			= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 02

# Fichiers exercice 01
OBJ_TD02_EX01= ex01/td02_ex01.o
EXEC_TD02_EX01= td02_ex01.out

# Fichiers exercice 02
OBJ_TD02_EX02= ex02/td02_ex02.o
EXEC_TD02_EX02= td02_ex02.out

# Fichiers exercice 03
OBJ_TD02_EX03= ex03/td02_ex03.o
EXEC_TD02_EX03= td02_ex03.out


# Regles compilation TD 02

all :

ex01 : $(OBJDIR)$(OBJ_TD02_EX01)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD02_EX01) -o $(BINDIR)$(EXEC_TD02_EX01) $(LDFLAGS)

ex02 : $(OBJDIR)$(OBJ_TD02_EX02)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD02_EX02) -o $(BINDIR)$(EXEC_TD02_EX02) $(LDFLAGS)

ex03 : $(OBJDIR)$(OBJ_TD02_EX03)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD02_EX03) -o $(BINDIR)$(EXEC_TD02_EX03) $(LDFLAGS)


clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
