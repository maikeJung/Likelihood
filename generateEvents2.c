/* 
*Author: Maike Jung
*Date: 26.01.2017

*Purpose: Draw random events from a certain mass spectrum

SN - Model: Lawrence-Livermore
    time spectrum is convoluted with the first hit distribution, to account for not knowing the absolute arrival times

UNITS: mass: eV
       energy: MeV
       distance: Mpc
       time: s

BINNING: defined in header-file (spectrum.h)
*/

#include "spectrum.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void createEventsArray(double events, double *spectrum, double max, int *timeArray, int *energyArray){
    
    /*creates events and writes them in a time and energy array*/
    int eventsGenerated = 0;
    int randE, randT;
    double randCheck;
    while(eventsGenerated < events){
        randE = rand() % (RESE-1);
        randT = rand() % (REST);
        randCheck = rand()*max/RAND_MAX;
        if (spectrum[randT*(RESE-1)+randE] >= randCheck){
            timeArray[eventsGenerated] = randT;
            energyArray[eventsGenerated] = randE;
            eventsGenerated ++;
        }
    }
}

void getSeed(double distance, double mass, double events, double noise){
    unsigned seed = time(NULL);
    FILE *f = fopen("seeds.txt", "a");
    fprintf(f, "%f %f %.0f %f %d\n", distance, mass, events, noise, seed);
    srand( seed );
}


double findSpectrumMax(double *spectrum){
    /* find the maximum value in the spectrum - needed to draw random events */
    double max = 0.0;
    int i;
    for(i=0; i<((RESE-1)*REST); i++){
        if(spectrum[i]>max) max = spectrum[i];
    }
    return max;
}
