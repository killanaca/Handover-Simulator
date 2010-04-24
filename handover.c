#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "record.h"
#include "simtime.h"
#include <math.h>
//code event
#define CALL 1
#define HANDOVER 2
#define END_CALL 3
//global constant

//global variables
long seme1 = 14123451,
     seme2 =57645805;
	 
Time current_time;
FILE *file;
double lambdaLoad,stayMeanTime;

 void schedule(int type, Time time,int station,int cell, int channell){
   Event *ev;
   ev=new_event();
   ev->type=type;
   ev->time=time;
   ev->cell=cell;
   ev->channell=channell;
   insert_event(&event_list,ev);
   return;
}

void get_input(char *format,void *variable){
    static char linebuffer[255];
    char *pin;

    fgets(linebuffer, 255, stdin);	/*  Gets a data from stdin without  */
    pin = strrchr (linebuffer, '\n');	/*  flushing problems		    */
    if (pin!=NULL) *pin = '\0';

    sscanf(linebuffer,format,variable);	/* Read only the beginning of the   */
					/* line, letting the user to write  */
					/* all the garbage he prefer on the */
					/* input line.			    */
}

void risultati(void){
	exit(0);
}



int main(){

Event *ev;
Time maximum,last_event_time;

printf("Insert the lambda value for the traffic load\n");
get_input("%lf",&lambdaLoad);
printf("Insert the mean time value for cell's stay\n");
get_input("%lf",&stayMeanTime);
printf("Insert the simulation's max time \n");
get_input("%lf",&maximum);
printf("The lambda value for the traffic load is %f\n",lambdaLoad);
printf("The mean time value for cell's stay is %f\n",stayMeanTime);
printf("The simulation's max time is %f\n",maximum);

file = fopen("simulationData.csv","w");
//fprintf(file,"# %s","Time,\tArrivo_Pkt,\tEnd_Tx,\tArrivo_token,\tDropped_Pkt\n");



while (current_time<maximum){
	//remove the event from the event_list
    ev = get_event(&event_list);
    last_event_time = current_time;
    current_time = ev->time;
    //"Time,Arrivo_Pkt,End_Tx,Arrivo_token"
    switch (ev->type){
       case CALL:
              //fprintf(file,"%f\t 1 \t\t NaN \t NaN \t NaN \t NaN\n",ev->time);
              call(ev->cell,0);
		      break;
       case HANDOVER:
              //fprintf(file,"%f\t NaN \t NaN \t 0.5 \t NaN \t NaN\n",ev->time);
              handover(ev->cell,0);
		      break;
		case END_CALL:
            //fprintf(file,"%f\t NaN \t 3 \t\t NaN \t NaN \t NaN\n",ev->time);
		    end_call(ev->cell,e->ch);
			break;
       default:       printf("Orrore!!!\n");
		      exit(1);
     }
	 //destroy the event removed from the event_list
    release_event(ev);
  } //end event loop
   risultati();
   fclose(file);
return 0;
}