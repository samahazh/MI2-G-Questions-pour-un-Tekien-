# Nom de l'exécutable final :
EXEC = programme_qcm

# Liste des fichiers sources à compiler :
SRC = main.c etudiant.c enseignant.c

# Compilateur ("gcc") :
CC = gcc

# Options de compilation (avertissements de sécurité) :
CFLAGS = -Wall -Wextra -std=c11

# Crée l'exécutable final :
all: $(EXEC)

# Compile les fichiers sources en un seul programme :
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# Supprime l'exécutable généré :
clean:
	rm -f $(EXEC)

# Nettoie tout et recompile : 
re: clean all
