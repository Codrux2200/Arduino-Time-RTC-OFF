#include <TimeLib.h>

int a;
char phrase[256];
char jeux;
int heure = 0;
int minu = 0;
int seconde = 0;
int index = 0;
int jour = 0;
int mois = 0;
int annee = 0;
bool valide = true;
void settime(char* phrase);
void print2digits(int number);

void setup() {
   Serial.begin(9600);
   a = 0;
   setTime(8, 27, 0, 14, 12, 2015);
   Serial.println("entrez la date actuelle sous le format 'H:M:S DD:MM:YYYY' :");
}

void loop() {
   while (Serial.available() > 0 ){
         jeux = Serial.read();
         phrase[a] = jeux;
         a++;
   }
   if (a != 0){
      settime(phrase);
      if (annee != 0){
         if (valide == true){
            setTime(heure, minu, seconde, jour, mois, annee);
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

void settime(char* phrase)
{
  if (phrase[0] == '0'){
      Serial.println("ERROR");
      exit(0);     
   } else {
      if (phrase[1] == ':'){
         heure = phrase[0] - 48 ;
         index = 2;        
      } else {
         heure = (phrase[0] - 48) * 10 + (phrase[1] - 48);
         index = 3;
      }
      if (phrase[index + 1] == ':'){
         minu = phrase[index] - 48;
         index += 2;
      } else {
         minu = (phrase[index] - 48) * 10 + (phrase[index + 1] - 48);
         index += 3;
      }
      if (phrase[index + 1] == ':'){
         seconde = phrase[index] - 48;
         index += 2; 
      } else {
         seconde = (phrase[index] - 48) * 10 + (phrase[index + 1] - 48);
         index += 3;
      }
      jour = (phrase[index] - 48) * 10 + (phrase[index + 1] - 48);
      index+=3;
      mois = (phrase[index] - 48) * 10 + (phrase[index + 1] - 48);
      index+=3;
      annee = (phrase[index] - 48) * 1000 + (phrase[index + 1] - 48) * 100 + 
      (phrase[index + 2] - 48) * 10 + (phrase[index + 3] - 48); 
   }
}

void print2digits(int number) 
{
  if (number >= 0 && number < 10)
      Serial.print(0);
  Serial.print(number);
}

// Copyright Saad Berrada Epitech 2020