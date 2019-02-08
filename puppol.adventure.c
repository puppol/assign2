#include <stdio.h>
#include <string.h>

enum ROOM_TYPE{ START_ROOM, END_ROOM, MID_ROOM};

struct Room {
  char roomName[9];
  int numConnections;
  struct Room * outboundConnections[6];
  enum ROOM_TYPE room_type;
};

struct Room rooms[7];

void rebuildRoomsArray(){
  //Read most recent room files
  int i;
  char
  //for (i = 0; i < 7; i++) {
    FILE *fptr;
    char buff[255];
    char data[11];
    fptr = fopen("puppol.rooms.15322/bb_room.txt","r");
    fgets(buff, 255, (FILE*)fptr);
    char * pch;
    pch=strrchr(str,' ');




   printf("%s", buff );
   fclose(fptr);

  //}


}

void displayRoomConnections(struct Room* currRoom){

}


struct Room* getStartRoom(){

}




int main(void) {
  rebuildRoomsArray();



}
