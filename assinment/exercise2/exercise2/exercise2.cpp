#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char building_name[100];
    int room_number;
    char room_name[100];
} Handong;

int main() {

     Handong room1 = { "Newton", 109, "SSS-LAB" };
     Handong room2 = { "Newton", 118, "Control-Lab" };
     Handong room3 = { "Newton", 119, "SW-LAB" };


   /* 
    Handong room1 = {.building_name = "Newton", .room_number = 109, .room_name = "SSS-LAB"};
    Handong room2 = {.building_name = "Newton", .room_number = 118, .room_name = "Control-Lab" };
    Handong room3 = {.building_name = "Newton", .room_number = 119, .room_name = "SW-LAB" };
    */

    Handong *room1Pt ;
    room1Pt = &room1;

    Handong *room2Pt;
    room2Pt = &room2;

    Handong * room3Pt;
    room3Pt = &room3;
 

    
   
    printf("%s building, room %d is %s\n", room1.building_name, room1.room_number, room1.room_name);
    printf("%s building, room %d is %s\n", room2.building_name, room2.room_number, room2.room_name);
    printf("%s building, room %d is %s\n", room3.building_name, room3.room_number, room3.room_name);

    printf("room1 address=%p , room1Pt = %p\n", &room1, room1Pt);
    printf("room2 address=%p , room2Pt = %p\n", &room2, room2Pt);
    printf("room3 address=%p , room3Pt = %p\n", &room3, room3Pt);

    return 0;
}