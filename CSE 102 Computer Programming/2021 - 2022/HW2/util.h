#ifndef _UTIL_H_
#define _UTIL_H_

#define CLOSE_ENOUGH 0.001

int dt0(int t, double p, double h, int s, int w);

char dt1a(double PL, double PW, double SL, double SW);
char dt1b(double PL, double PW, double SL, double SW);

int compare_P1(char res1, char res2);
double compare_P2(double res3, double res4);

double dt2a(double x1, double x2, double x3, int x4, int x5);
double dt2b(double x1, double x2, double x3, int x4, int x5);

char dt3a(int TEMPERATURE,double MASS,double RADIUS,int COLOR,int LUMINOSITY,int HYDROGEN);
char dt3b(int TEMPERATURE,double MASS,double RADIUS,int COLOR,int LUMINOSITY,int HYDROGEN);

#endif /* _UTIL_H_ */