##########################################################
#	MAKEFILE              								 #
#	MODE DEBUG UNIQUEMENT								 #
#	CREE PAR KAILASDEV									 #
##########################################################

#Compilateur
CC=g++
#compilation flags
CFLAGS=
#dossiers inlude(bibliotheque)
IFLAGS=-ILib\Ogre_1-8-1\include\OGRE -ILib\Ogre_1-8-1\include\OIS -ILib\Ogre_1-8-1\boost -Ilib\CEGUI-0-7-9\cegui\include
#dossiers lib(bibliotheque)
LFLAGS=-LLib\Ogre_1-8-1\lib\Debug -Llib\Ogre_1-8-1\boost\lib -Llib\CEGUI-0-7-9\bin
#link
LINK=-lOgreMain_d -lOIS_d -lboost_system-mgw47-mt-1_51 -lCEGUIBase_d -lCEGUIOgreRenderer_d
#nom de l'executable
EXEC=exec/CrossedTimes.exe
#recupere tous les .cpp
SRC=src/main.cpp \
	src/Graphic/Window.cpp
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