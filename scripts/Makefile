build_dir ?= build


tt: tt.o nob.h

%.tt.h: %.h.tt tt
	./tt -o $@ $<

make_pandoc_sh.o: make_pandoc_sh.c make_pandoc.tt.h
	$(CC) -c -o $@ make_pandoc_sh.c

make_pandoc_sh: make_pandoc_sh.o

pandoc.sh: make_pandoc_sh
	 ./make_pandoc_sh

.PHONY: clean
clean:
	rm -f *.o *.tt.h make_pandoc_sh tt


