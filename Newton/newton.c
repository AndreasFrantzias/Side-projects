
#include<stdio.h>
#include<stdlib.h>
//Χρησιμοποιώ την βιβλιοθήκη math.h γιατί χρησιποιώ την εντολή pow
#include<math.h>
//Συνάρτηση fun υπάρχει για να δημιουργήσει το πολυώνυμο 5ου βαθμού
double fun(double A0,double A1,double A2,double A3,double A4,double A5,double X0){
    return A0+A1*X0+A2*pow(X0,2)+A3*pow(X0,3)+A4*pow(X0,4)+A5*pow(X0,5);
}
//Συνάρτηση der είναι η παράγωγος του πολυωνύμου 5ου βαθμού
double  der(double A0,double A1,double A2,double A3,double A4,double A5,double X0){
    return A0*0+A1+A2*2*X0+A3*3*pow(X0,2)+A4*4*pow(X0,3)+A5*5*pow(X0,4);
}
int main(int argc,char **argv){
//Έλεγχος αν οι εισόδοι που δόθηκαν είναι σωστοί
     if(argc != 8){
     printf("Wrong input\n");
     return 1;
    }
//Μετατροπή μεταβλητών απο argument σε double
    double A0 = atof(argv[1]);
    double A1 = atof(argv[2]);
    double A2 = atof(argv[3]);
    double A3 = atof(argv[4]);
    double A4 = atof(argv[5]);
    double A5 = atof(argv[6]);
    double X0 = atof(argv[7]);

    int j=0;
    double x=X0;
    double fx;
    double dfx;
    double x2=2;
    double x1=1;
    while(j<=1000){
     fx=fun(A0,A1,A2,A3,A4,A5,x);
     dfx=der(A0,A1,A2,A3,A4,A5,x);
//Έλεγχος αν οι ρίζες συγκλίνουν
     if(fabs(x2-x1)<pow(10,-6)){
      printf("%.2f\n",x);
      return 0;
     }
//Έλεγχος αν ο αλγόριθμος συγκλίνει
     if(fabs(dfx)==0){
      printf("nan\n");
      return 0;
     }
     x=x-fx/dfx;
     j++;
     x1=x2;
     x2=x;
    }
//Έλεγχος επαναλήψεων αλγόριθμου
    if(j>1000){
     printf("incomplete\n");
     return 0;
    }else{
        printf("%.2f",x);
    }
    return 0;
}
