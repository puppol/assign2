#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>


struct Room {
  char roomName[9];
  char roomType[12];
  char outboundConnections[6][3];
  int numConnections;
};

struct Room rooms[7];

void rebuildRoomsArray(){
  //Read most recent room files
  int i;
  int j;
  struct dirent *de;
  struct dirent *mostRecentDir;
  struct stat currStat;
  int lastestChangeTime;
  DIR *dr = opendir(".");
  char fileName[80];

  if (dr == NULL) {   // opendir returns NULL if couldn't open directory{
        printf("Could not open current directory\n" );
  }
  if( de = readdir(dr) != NULL) {
    mostRecentDir = de;
    stat(de->d_name, &currStat);
    lastestChangeTime = currStat.st_mtime;
  }
  while ((de = readdir(dr)) != NULL) {
    stat(de->d_name, &currStat);
    if ( (currStat.st_mode & S_IFDIR) && currStat.st_mtime > lastestChangeTime ) {
      mostRecentDir = de;
      lastestChangeTime = currStat.st_mtime;
    }
  }

  //printf("%s was last modified\n", mostRecentDir->d_name);
  closedir(dr);

  //Now at the correct dir, and about to filter through rooms
  dr = opendir(mostRecentDir->d_name);
  if (dr == NULL) {   // opendir returns NULL if couldn't open directory{
        printf("Could not open current directory" );
  }

  //Going through each room file, building structs as we go
  char buffer[100];
  memset(fileName, '\0', sizeof(fileName));
  i = 0;
  while ((de = readdir(dr)) != NULL) {
    if(!strstr(de->d_name, ".txt")){
      continue;
    }
    memset(fileName, '\0', sizeof(fileName));
    strcpy(fileName, mostRecentDir->d_name);

    //Get file NAME
    strcat(fileName, "/");
    strcat(fileName, de->d_name);

    //Open file
    //printf("Opening file: %s\n", fileName);
    FILE *fp = fopen(fileName, "r");

    if(fp == NULL)
      continue;
    //printf("Opened file: %s\n", fileName);
    memset(buffer, '\0', sizeof(buffer));
    j = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
      buffer[strlen(buffer)-1]='\0';
      if( strstr(buffer, "NAME") ){
        strcpy(rooms[i].roomName, &buffer[11]);
        printf("RoomName: %s\n", rooms[i].roomName);
      }
      else if( strstr(buffer, "CONNECTION") ){
        strcpy(rooms[i].outboundConnections[j], &buffer[14]);
        rooms[i].numConnections += 1;
        j+=1;
      }
      else if( strstr(buffer, "TYPE") ){
        strcpy(rooms[i].roomType, &buffer[11]);
        printf("RoomType: %s\n", rooms[i].roomType);
      }
      // printf("Buffer was: %s\n", buffer);
      memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    i+=1;
  }
  closedir(dr);
}

char * getStartRoom(){
  int i;
  for (i = 0; i < 7; i++){
    if (strstr(rooms[i].roomType, "START")){
      printf("roomType found: %s\n",rooms[i].roomType);
      return rooms[i].roomName;
    }
  }
}


int main() {
  rebuildRoomsArray();
  printf("Start room: %s\n",getStartRoom());
}
