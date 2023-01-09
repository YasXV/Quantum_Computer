SFML_PATH=../../SFML-2.5.1/
ENTETE_PATH=../Fichiers_h
CFLAGS=-I$(SFML_PATH)include
CFLAGS2=-I$(ENTETE_PATH)

%.o : %.cpp
	g++ -o $@ -c $< $(CFLAGS) $(CFLAGS2)

ordi: afficheprob.o qbit.o circuitchoix.o portes.o surchargeop.o etatquantique.o ordiquant.o NOT2.o normalisation.o
	g++ afficheprob.o qbit.o circuitchoix.o portes.o surchargeop.o etatquantique.o ordiquant.o NOT2.o normalisation.o -o ordi -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio
	rm *.o
	./ordi
