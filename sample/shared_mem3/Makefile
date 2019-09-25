CFLAGS=-lrt

main.x: shmmem_parent.c child1.x child2.x
	gcc shmmem_parent.c -o main.x $(CFLAGS)

child1.x: shmmem_child1.c
	gcc shmmem_child1.c -o child1.x $(CFLAGS)

child2.x: shmmem_child2.c
	gcc shmmem_child2.c -o child2.x $(CFLAGS)

clean:
	rm -rvf *.x
