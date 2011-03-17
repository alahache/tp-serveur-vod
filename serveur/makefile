CC=g++
EXEC_NAME=serveur_vod
INCLUDES=
LIBS=
OBJ_FILES=IOControl.o ActionConnection.o ActionClient.o ActionCommand.o Stream.o ActionHTTPConnection.o ActionHTTPClient.o Server.o Main.o
SRC_DIR=src/
OPT_CMP=-c
OPT_EDL=-o

# Lancement de la chaîne de compilation :
all: $(EXEC_NAME)

# Nettoyage des fichiers .o ainsi que de l'exécutable :
clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

# Edition des liens :
$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OPT_EDL) $(EXEC_NAME) $(OBJ_FILES) $(LIBS)
	
Main.o: $(SRC_DIR)Main.cpp
	$(CC) $(OPT_CMP) $(INCLUDES) $(SRC_DIR)Main.cpp

# Pattern de compilation des modules :
%.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.h
	$(CC) $(OPT_CMP) $(INCLUDES) $<
