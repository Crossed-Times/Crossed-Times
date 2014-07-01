##########################################################
#	MAKEFILE POUR LES LISTES							 #
#	MODE DEBUG UNIQUEMENT								 #
#	CREE PAR KAILASDEV									 #
##########################################################

#Compilateur
CC=g++
#compilation flags
CFLAGS=
#dossiers inlude(bibliotheque)
IFLAGS=-ILib\Ogre_1-8-1\include\OGRE -ILib\Ogre_1-8-1\include\OIS -ILib\Ogre_1-8-1\boost
#dossiers lib(bibliotheque)
LFLAGS=-LLib\Ogre_1-8-1\lib\Debug -Llib\Ogre_1-8-1\boost\lib
#link
LINK=-lOgreMain_d -lOIS_d -lboost_system-mgw47-mt-1_51
#nom de l'executable
EXEC=exec/CrossedTimes.exe
#recupere tous les .cpp
SRC=src/main.cpp \
	src/Window.cpp
OBJ=$(SRC:.cpp=.o)
CLEAN=rm $(OBJ)

#executable a creer
all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS) $(IFLAGS) $(LINK)

%.o: %.cpp
	@$(CC) -o $@ -c $< $(CFLAGS) $(LFLAGS) $(IFLAGS) $(LINK)

clean:
	$(CLEAN)