#include <TimeLib.h>
#include "command.h"
int a = 0;
bool valide = true;

void setup() {
   Serial.begin(9600);
   setTime(8, 27, 0, 14, 12, 2015);
   a = 0;
   Serial.println("entrez la date actuelle sous le format 'HH:MM:SS DD:MM:YYYY' :");
}

void loop() {
   temps temps;
   prog prog;
   
   while (Serial.available() > 0 ){
         prog.jeux = Serial.read();
         prog.phrase[a] = prog.jeux;
         a++;
   }
   if (a != 0){
      temps.annee = 0;
      settime(prog.phrase, &temps, &prog);
      if (temps.annee != 0){
         if (valide == true){
            setTime(temps.heure, temps.minu, temps.seconde, temps.jour, temps.mois, temps.annee);
            valide = false;
         }
         Serial.print("il est ");
         print2digits(hour());
         Serial.print(":");
         print2digits(minute());
         Serial.print(":");
         print2digits(second());
         Serial.print(" ");
         print2digits(day());
         Serial.print(":");
         print2digits(month());
         Serial.print(":");
         Serial.println(year());
      }
   }  
  delay(1000);
}

void settime(char* phrase, temps *temps, prog *prog)
{
   if (phrase[1] == ':'){
      temps->heure = phrase[0] - 48 ;
      prog->index = 2;        
   } else {
      temps->heure = (phrase[0] - 48) * 10 + (phrase[1] - 48);
      prog->index = 3;
   }
   if (phrase[prog->index + 1] == ':'){
      temps->minu = phrase[prog->index] - 48;
      prog->index += 2;
   } else {
      temps->minu = (phrase[prog->index] - 48) * 10 + (phrase[prog->index + 1] - 48);
      prog->index += 3;
   }
   if (phrase[prog->index + 1] == ':'){
      temps->seconde = phrase[prog->index] - 48;
      prog->index += 2; 
   } else {
      temps->seconde = (phrase[prog->index] - 48) * 10 + (phrase[prog->index + 1] - 48);
      prog->index += 3;
   }
   temps->jour = (phrase[prog->index] - 48) * 10 + (phrase[prog->index + 1] - 48);
   prog->index +=3;
   temps->mois = (phrase[prog->index] - 48) * 10 + (phrase[prog->index + 1] - 48);
   prog->index+=3;
   temps->annee = (phrase[prog->index] - 48) * 1000 + (phrase[prog->index + 1] - 48) * 100 + 
   (phrase[prog->index + 2] - 48) * 10 + (phrase[prog->index + 3] - 48); 
}

void print2digits(int number) 
{
  if (number >= 0 && number < 10)
      Serial.print(0);
  Serial.print(number);
}

// Copyright Saad Berrada Epitech
