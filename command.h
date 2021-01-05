typedef struct temps temps;
struct temps{   
   int heure;
   int minu;
   int seconde;
   int jour;
   int mois;
   int annee;
};

typedef struct prog prog;
struct prog{   
   int index;
   char jeux;
   char phrase[256];
};

void settime(char* phrase, temps *temps, prog *prog);
void print2digits(int number);
