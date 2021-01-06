#include <TimeLib.h>
#include "command.h" // initialisation des structures
int a = 0;
bool valide = true;
bool ok = false;

void setup() //initialisation
{
   Serial.begin(9600); //on demarre le Sérial sur un signal de 9600 baud
   setTime(8, 27, 0, 14, 12, 2015); // temps aléatoire 
   a = 0; // initalise a = 0 pour plus tard
   Serial.println("entrez la date actuelle sous le format 'HH:MM':"); // print des instructions
}

void loop() // loop
{
   temps temps; // declaration structure temps
   prog prog; // declaration structure prog
   
   while (Serial.available() > 0) { //
      prog.jeux = Serial.read();    //  Lecture de l'entrée Série et copie du buffer dans un string
      prog.phrase[a] = prog.jeux;   //
      a++;      
   }
   if (a != 0) { // quand le string est pas vide
      temps.annee = 0; // juste pour debug
      settime(prog.phrase, &temps, &prog); // on appelle la fonction settime avec comme argument , le string et les adresses des 2 structures
      if (ok == true) { // une fois que settime c'est bien deroulé
         if (valide == true) { // boolean anti doublon
            setTime(temps.heure, temps.minu, temps.seconde, temps.jour, temps.mois, temps.annee); // settime
            valide = false;
         }
         Serial.print("il est "); //
         print2digits(hour());    //
         Serial.print(":");       // Affichage de l'heure
         print2digits(minute());  //
         Serial.println("");      //
      }
   }  
   delay(1000); // delay
}

void settime(char* phrase, temps *temps, prog *prog) // on remarque l'utilisation de pointeurs sur structures pour rendre le tout plus propore
{
   if ( a < 5 || a >= 7) { // debug verrif error gestion
      Serial.println("Syntax Error");
      delay(1000); 
      exit(84);
   }
   if (phrase[1] == ':') { // test si l'heure est composée de 2 nombres si "non" alors:
      temps->heure = phrase[0] - 48 ; // l'heure est égal au premiers caractére de notre string - 48  48 etant la valeur ascii de '0'
      prog->index = 2; // on l'index et donc egal a 2 soit le troisieme caractére de la string
   } else { // sinon
      temps->heure = (phrase[0] - 48) * 10 + (phrase[1] - 48); // heure est égal au caractére 0 * 10 + le caractére 1 - 48 pour passer de l'ascii au int
      prog->index = 3; // index egal a 3
   }
   if (phrase[prog->index + 1] >= 48 && phrase[prog->index + 1] <= 57) {// meme fonctionnement que pour l'heure mais cette fois inversé 
      temps->minu = (phrase[prog->index] - 48) * 10 + (phrase[prog->index + 1] - 48);
      prog->index += 3;
   } else {
      temps->minu = phrase[prog->index] - 48;
      prog->index += 2;
   }
   temps->jour = 1; // jour a 1 par defaut
   temps->mois = 1; // mois a 1 par defaut
   temps->annee = 2020; // année a 1 par deffaut
   ok = true; // on valide le fait que tout c'est bien passer
}

void print2digits(int number) 
{
  if (number >= 0 && number < 10)
      Serial.print(0);
   Serial.print(number);
}

// Copyright Saad Berrada Epitech