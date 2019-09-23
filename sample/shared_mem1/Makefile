CFLAGS=-lrt

main.x: shmmem_parent.c child.x
	gcc shmmem_parent.c -o main.x $(CFLAGS)

child.x: shmmem_child.c
	gcc shmmem_child.c -o child.x $(CFLAGS)

clean:
	rm -rvf *.x
