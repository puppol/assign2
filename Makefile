build:
	gcc -o puppol.buildrooms puppol.buildrooms.c
	gcc -o puppol.adventure puppol.adventure.c 
clean:
	rm -rf puppol.buildrooms puppol.rooms.*
