# EXEC : nom final de l'application
EXEC = programme_qcm

# SRC : liste de tous les fichiers sources (fichiers.c)
SRC = main.c etudiant.c enseignant.c

# CC = C Compiler (compilateur "gcc").
CC = gcc

# CFLAGS (C Flags) : les options de compilation. 
# -Wall et -Wextra : activent les avertissements de securite.
CFLAGS = -Wall -Wextra -std=c11

# Demande a fabriquer l'executable final.
all: $(EXEC)

# Créer le programme final ($(EXEC)) a partir des fichiers sources.
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# "rm -f" : supprime (remove)
clean:
	rm -f $(EXEC)

# "re" : lance le nettoyage (clean) puis la compilation (all)
re: clean all
