#include <stdio.h>
#include "util.h"

/* Example decision tree - see the HW2 description */
int dt0(int t, double p, double h, int s, int w) {
    
    int r = 0;
    if (t>35 && w!=3) r = 1;
    else if (t<=35 && s==0) r = 1;
    return r;
}

char dt1a(double PL, double PW, double SL, double SW) {
    /*I used the given trees for this function.*/
    if(PL<2.45){
        return 'a';
    }

    else{
        if(PW >= 1.75){
            return 'b';
        }
        else{
            if(PL >= 4.95){
                return 'b';
            }
            else{
                if(PW >= 1.65){
                    return 'b';
                }
                else{
                    return 'c';
                }
            }
        }
    }
}

char dt1b(double PL, double PW, double SL, double SW) {
    /*I used the given trees for this function.*/    
    if(PL < 2.55){
        return 'a';
    }
    else{
        if(PW >= 1.69){
            return 'b';
        }
        else{
            if(PL >= 4.85){
                return 'b';
            }
            else{
                return 'c';
            }
        }
    }
}

double dt2a(double x1, double x2, double x3, int x4, int x5){
    /*I used the given trees for this function.*/
    if(x1<31.5){
        if(x2 > -2.5){
            return 5.0;
        }
        else{
            if(x1 >= x2-0.1 && x1 <= x2+0.1){
                return 2.1;
            }
            else{
                return -1.1;
            }
        } 
    }
    else{
        if(x3>= -1 && x3<=2){
            return 1.4;
        }
        else{
            if(x4 && x5){
                return -2.23;
            }
            else{
                return 11.0;
            }
        }
    }
}

double dt2b(double x1, double x2, double x3, int x4, int x5){
    /*I used the given trees for this function.*/    
    if(x1 >= 12 && x1 <= 22){
        if(x3 > (5/3)){
            return -2.0;
        }
        else{
            if(x3 >= x1-0.1 && x3 <= x1+0.1){
                return 1.01;
            }
            else{
                return -8.0;
            }
        }
    }
    else{
        if(x4 && x5){
            return -1.0;
        }
        else{
            if(x2 >= -1 && x2 <= 2){
                return (-1/7);
            }
            else{
                return 0.47;
            }
        }
    }
}


int compare_P1(char res1,char res2){
    /*I created this function to compare two char results */
    if(res1 == res2){
        return 1;
    }
    else{
        return 0;
    }
}

double compare_P2(double res3,double res4){
    /*I created this function to compare two double results*/
    double sub= res3-res4;
    if (sub<0){
        sub= sub*-1;
        if(sub <= CLOSE_ENOUGH){
            return (res3+res4)/2;
        }
        else{
            return 0;
        }
    }
    else{
        if(sub <= CLOSE_ENOUGH){
            return (res3+res4)/2;
        }
        else{
            return 0;
        }
    }
}
char dt3a(int TEMPERATURE,double MASS,double RADIUS,int COLOR,int LUMINOSITY,int HYDROGEN){
    /*In the submitted file for this function, I used the first decision tree I created for Harvard Spectrum Classification.*/
    if(TEMPERATURE >= 30000){
        return 'o';
    }
    else{
        if(HYDROGEN == 0){
            if(MASS < 16){
                if(RADIUS < 6.6){
                    if(LUMINOSITY == 0){
                        return 'b';
                    }
                    if(LUMINOSITY == 1){
                        return 'a';
                    }
                    if(LUMINOSITY == 2){
                        return 'f';
                    }
                    else{
                        return 'x';
                    }
                }
                else{
                    return 'x';
                }
            }
            else{
                return 'x';
            }
        }
        if(HYDROGEN == 1){
            if(MASS < 16){
                if(COLOR == 2){
                    return 'g';
                }
                if(COLOR == 3){
                    return 'k';
                }
                if(COLOR == 4){ 
                    return 'm';
                }
                else{
                    return 'x';
                }
            }
            else{
                return 'x';
            }
        }
        else{
            return 'x';
        }
    }
    
}

char dt3b(int TEMPERATURE,double MASS,double RADIUS,int COLOR,int LUMINOSITY,int HYDROGEN){
    /*In the submitted file for this function, I used the second decision tree I created for Harvard Spectrum Classification.*/
    if(MASS < 1.5){
        if(RADIUS<1.4){
            if(LUMINOSITY == 2){
                if(TEMPERATURE<7500){
                    if(TEMPERATURE >=5200){
                        if(HYDROGEN == 0){
                            return 'f';
                        }
                        if(HYDROGEN == 1){
                            return 'g';
                        }
                    }
                    return 'x';
                }
                else{
                    return 'x';
                }
            }
            if(LUMINOSITY == 3){
                return 'k';
            }
            if(LUMINOSITY == 4){
                return 'm';
            }
            else{
                return 'x';
            }
        }
        else{
            return 'x';
        }
        
    }
    else{
        if(COLOR == 0){
            if(HYDROGEN == 0){
                return 'b';
            }
            if(HYDROGEN == 1){
                return 'o';
            }
            else{
                return 'x';
            }
        }
        if(COLOR == 1){
            return 'a';
        }
        else{
            return 'x';
        }
    }
}