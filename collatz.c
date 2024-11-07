#include <stdio.h>
//Βιβλιοθηκη stdlib.h ειναι αναγκαια επειδη για π.δ μετατρεπουμε μεταβλητη απο char σε long long 
#include <stdlib.h>
//Συναρτηση με ονομα collatz η οποια θα παιρνει εναν αριθμο και θα επιστρεφει το μηκος της ακολουθιας του
int collatz(long long n){
    int sum=0;  
    while (n != 1){
        if (n % 2 == 0){
            n=n/2;
            sum++;
        }
        else{
            n = ((3 * n) + 1) / 2;
            sum+=2;
        }
    }
return sum;
}
int main(int argc, char *argv[]) {
   //Υπαρχει αυτη η συνθηκη ελεγχου γιατι input θεωρειτε το ονομα της ασκησης ενω τα αλλα δυο inputs ειναι τα ορια που βαζει ο χρηστησ 
    if (argc != 3) {
        printf("Usage: %s <lower_limit> <upper_limit>\n", argv[0]);
        printf("%d\n",0);
        return 0;
    }
    //Θετω τον αριθμο του upper limit ως τον τριτο αριθμο του πινακα argv(πρωτος ειναι το ονομα του αρχειου)
    long long uplimit = atoll(argv[2]);
    //θετω τον αριθμο του lower limit ως τον δευτερο αριθμο του πινακα argv
    long long lowlimit = atoll(argv[1]);
    //Ελεγχος των τιμων που βαζει ο χρηστης
    if (lowlimit < 1 || uplimit < 1 || uplimit > 100000000) {
        printf("%d\n",0);
        return 0;
    }
    //Ευρεση μεγαλυτερης ακολουθιας μεταξυ των αριθμων στα ορια με την βοηθεια της συναρτησης
    long long maxl = 0;
    for (long long i=lowlimit;i<=uplimit;i++) {
        int l=collatz(i);
        if (l> maxl) {
            maxl = l;
        }
    }
    printf("%lld\n", maxl+1);
return 0;
}
