# Makefile

INTERPRETE = interprete
SRC = main.c
ITREE = itree
INTERVALO = intervalo
QUEUE = queue
COMP = gcc
ARGSCOMP = -Wall -Wextra -Werror -std=c99 -g

all: $(INTERPRETE)

$(INTERPRETE): $(ITREE).o $(INTERVALO).o $(QUEUE).o $(SRC)
	$(COMP) $(ARGSCOMP) -o $(INTERPRETE) $(SRC) $(ITREE).o $(INTERVALO).o $(QUEUE).o

$(INTERPRETE).o: $(INTERPRETE).c
	$(COMP) $(ARGSCOMP) -c $(INTERPRETE).c

$(ITREE).o: ./ITree/$(ITREE).c
	$(COMP) $(ARGSCOMP) -c ./ITree/$(ITREE).c

$(QUEUE).o: ./queue/$(QUEUE).c
	$(COMP) $(ARGSCOMP) -c ./queue/$(QUEUE).c

$(INTERVALO).o: ./Intervalo/$(INTERVALO).c
	$(COMP) $(ARGSCOMP) -c ./Intervalo/$(INTERVALO).c

clean:
	rm *.o