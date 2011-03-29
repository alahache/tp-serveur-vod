SRC_DIR=src
INC_DIR=include
CC=g++
EXEC_NAME=serveur_vod
INCLUDES=-I $(INC_DIR)
LIBS=-lpthread
OBJ_FILES=DataTransfertTCP.o DataTransfertTCPPull.o DataTransfertTCPPush.o DataTransfertUDP.o DataTransfertUDPPull.o DataTransfertUDPPush.o IOControl.o ActionConnection.o ActionClient.o ActionCommand.o Stream.o ActionHTTPConnection.o ActionHTTPClient.o Server.o Main.o
OPT_CMP=-c -ggdb
OPT_EDL=-o

# Lancement de la chaîne de compilation :
all: $(EXEC_NAME)

# Nettoyage des fichiers .o ainsi que de l'exécutable :
mrproper: clean
	rm $(EXEC_NAME)

# Nettoyage des fichiers .o :
clean:
	rm $(OBJ_FILES)

# Edition des liens :
$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OPT_EDL) $(EXEC_NAME) $(OBJ_FILES) $(LIBS)
	
Main.o: $(SRC_DIR)/Main.cpp
	$(CC) $(OPT_CMP) $(INCLUDES) $(SRC_DIR)/Main.cpp

# Pattern de compilation des modules :
%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CC) $(OPT_CMP) $(INCLUDES) $<
