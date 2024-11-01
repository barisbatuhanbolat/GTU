#include <stdio.h>
/*I declare functions I use in program*/

void write_file(int a,int b, int c);
int draw_equation(int y,int x);
void draw_graph();
void draw_graph_file();

int main(){
    /*And I declared some variables for program*/
	int a,b,c,a1,b1,c1,choice = 0;
    /*And I started an endless loop so that the program does not close.*/
    do{
        /*I created a menu for easy access for each part of program*/
        printf("------------------------MENU------------------------\n");
        printf("Select an Operation\n");
        printf("1 -> Enter the coefficients.\n"
               "2 -> Draw the graph.\n"
               "3 -> Print the graph into a .txt file.\n"
               "4 -> Exit\n");
        printf("----------------------------------------------------\n");
        printf("Choice: ");
        scanf("%d",&choice);
        /*I used switch case for menu parts*/
        switch(choice){
            case 1:
                printf("Please enter the coefficient for the following equation: x=a*(y*y) + b*y +c\n");
                printf("a: ");
                scanf("%d",&a);
                printf("b: ");
                scanf("%d",&b);
                printf("c: ");
                scanf("%d",&c);

                write_file(a,b,c);
                printf("coefficients.txt file has been created.\n");
                break;

            case 2:
                printf("Coefficients has been read from coefficient.txt file\n");
                FILE *coefficients = fopen("coefficients.txt","r");
                if(coefficients == NULL){
                    printf("\nCoefficients file not found.\n");
                    return 0;
                }
                else{
                    fscanf(coefficients,"%d",&a1);
                    fscanf(coefficients,"%d",&b1);
                    fscanf(coefficients,"%d",&c1);
                }
                fclose(coefficients);
                printf("Printing the graph of x = %d*y*y + %d*y + %d\n",a1,b1,c1);
                draw_graph();
                break;
            case 3:
                printf("Coefficients has been read from coefficient.txt file\n");
                coefficients = fopen("coefficients.txt","r");
                if(coefficients == NULL){
                    printf("\nCoefficients file not found.\n");
                    return 0;
                }
                else{
                    fscanf(coefficients,"%d",&a1);
                    fscanf(coefficients,"%d",&b1);
                    fscanf(coefficients,"%d",&c1);
                }
                fclose(coefficients);
                printf("The graph of x = %d*y*y + %d*y + %d  has been written to graph.txt file.",a1,b1,c1);            
                draw_graph_file();
                break;
            default:
                printf("Invalid choice");
                break;
        }
        printf("\n\n");
    }while(choice != 4);
}
/*There are functions that I use starting from this line.*/
void write_file(int a,int b, int c){
    FILE *coefficients = fopen("coefficients.txt","w");
    fprintf(coefficients,"%d\n%d\n%d\n",a,b,c);
    fclose(coefficients);

}

int draw_equation(int y,int x){
    /*In this function I read coefficients from the file and I took coordinates from cartesian plane .*/
    /*And I checked the coordinates.*/
    int result,a,b,c;
    FILE *coefficients = fopen("coefficients.txt","r");
    if(coefficients == NULL){
        printf("\nCoefficients file not found.\n");
    }
    else{
        fscanf(coefficients,"%d",&a);
        fscanf(coefficients,"%d",&b);
        fscanf(coefficients,"%d",&c);

    }
    fclose(coefficients);

    result = (x-(a*y*y)-(b*y)-c);
    
    if(result == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void draw_graph(){
    /*In this function I create a nested loop for draw cartesian plane*/
    printf("\n\n");
    int result,i,j,y,x;
    /*In this loop I create an extra loop for the signs I forgot*/
    for(y = 0;y<=55;y++){
        if(y!=55){
            printf(" ");
        }
        else{
            printf("^");
        }
    }
    /*From this part I create an nested loop */
    printf("\n");
	for(i = 15; i >= -15; i--){
        if(i != 0){
            for(j = -55; j <= 56; j++){
                if(j== -1 && i%5 == 0 && i>0){
                    printf("\b");
                    if(i>0 && i>5){
                        printf("\b");
                    }
                    printf("\033[0;33m");                     
                    printf("%d",i);
                    printf("\033[0;37m");

                }
                if(draw_equation(i,j) == 1 && j == 0){
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0;37m");                    
                }
                if(draw_equation(i,j) == 0 && j>0 && j%10 == 0 && i == -1){
                        printf("\b\b");
                        printf("\033[0;33m");                     
                        printf("%d",j);
                        printf("\033[0;37m");
                }    
                else if(i==-1 && j%10 == 0 && j<0){
                    printf("\b\b\b");
                    printf("\033[0;33m");                     
                    printf("%d",j);
                    printf("\033[0;37m");
                }                        
                else if(draw_equation(i,j) == 1){
                    printf("\b");

                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0;37m"); 
                }      
                else if(j==-1 && i%5 == 0 && i<0){
                    printf("\b\b");
                    if(i<0 && i<-5){
                        printf("\b");
                    }
                    printf("\033[0;33m"); 
                    printf("%d",i);
                    printf("\033[0;37m");
                }
                else if(i==-1 && j==-1){
                    printf("\b");
                    printf("\033[0;33m"); 
                    printf("0");
                    printf(" ");
                    printf("\b");
                    printf("\033[0;37m");
                }

                else if((j == 0)){
                        printf("|");
                }
                printf(" ");
            }
        }

        else{
            for(j = -55; j <= 56; j++){
                if(j==0 && i==0 && draw_equation(0,0) == 0 ){
                    printf("|");
                }
                if(j==56){
                    printf(">");
                }

                else if(draw_equation(0,0) == 1 && i==0 && j==0){
                    //printf("\b");
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0;37m"); 
                }
                else if(draw_equation(i,j) == 1 && i==0){
                    if(j>0){
                        printf("\b");
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0;37m");
                    }
                    else{
                        //printf("-");
                        printf("\b");                        
                        printf("\033[0;34m");
                        printf("#");
                        printf("\033[0;37m");
                        printf("-");
                    }
                    
                }
                else if(draw_equation(i,0)==1 && j == 0){
                    printf("\b");
                    printf("\033[0;34m");
                    printf("#");
                    printf("\033[0;37m");                     
                }
                else if(draw_equation(0,j)==0){
                    printf("-");                    
                }
            }
        }
		printf("\n");
	}
}

void draw_graph_file(){
    /*In this function I transfered the graph to the file*/
    FILE *graph = fopen("graph.txt","w");
    fputc('\n',graph);
    fputc('\n',graph);
    int result,i,j,y,x;
    for(y = 0;y<=55;y++){
        if(y!=55){
            fputc(' ',graph);
        }
        else{
            fputc('^',graph);
        }
    }
    fputc('\n',graph);
	for(i = 15; i >= -15; i--){
        if(i != 0){
            for(j = -55; j <= 56; j++){
                if(j== -1 && i%5 == 0 && i>0){
                    fseek(graph, -1, SEEK_CUR);
                    if(i>0 && i>5){
                        fseek(graph, -1, SEEK_CUR);
                    }                   
                    fprintf(graph,"%d",i);

                }
                if(draw_equation(i,j) == 1 && j == 0){
                        //fseek(graph, -1, SEEK_CUR);
                        fputc('#',graph);
                }
                if(draw_equation(i,j) == 0 && j>0 && j%10 == 0 && i == -1){
                        fseek(graph, -2, SEEK_CUR);
                     
                        fprintf(graph,"%d",j);

                }            
                else if(draw_equation(i,j) == 1){
                    fseek(graph, -1, SEEK_CUR);
                    fputc('#',graph);
                }      
                else if(j==-1 && i%5 == 0 && i<0){
                    fseek(graph, -2, SEEK_CUR);
                    if(i<0 && i<-5){
                        fseek(graph, -1, SEEK_CUR);
                    } 
                    fprintf(graph,"%d",i);
                }
                else if(i==-1 && j%10 == 0 && j<0){
                    fseek(graph, -3, SEEK_CUR);                   
                    fprintf(graph,"%d",j);
                }
                
                else if(i==-1 && j==-1){
                    fseek(graph, -1, SEEK_CUR);
                    fputc('0',graph);
                    fputc(' ',graph);
                    fseek(graph, -1, SEEK_CUR);
                }

                else if((j == 0)){
                        fputc('|',graph);
                }
                fputc(' ',graph);
            }
        }

        else{
            for(j = -55; j <= 56; j++){
                if(j==0 && i==0 && draw_equation(0,0) == 0 ){
                    fputc('|',graph);
                }
                if(j==56){
                    fputc('>',graph);
                }
                else if(draw_equation(0,0) == 1 && i==0 && j==0){
                    //fseek(graph, -1, SEEK_CUR);
                    fputc('#',graph);
                }
                else if(draw_equation(i,j) == 1 && i==0){
                    if(j>0){
                        fseek(graph, -1, SEEK_CUR);
                        fputc('#',graph);
                    }
                    else{
                        //fputc('-',graph);
                        fseek(graph, -1, SEEK_CUR);                        
                        fputc('#',graph);
                        fputc('-',graph);
                    }
                    
                }
                else if(draw_equation(i,0)==1 && j == 0){
                    fseek(graph, -1, SEEK_CUR);
                    fputc('#',graph);                    
                }
                else if(draw_equation(0,j)==0){
                    fputc('-',graph);                    
                }
            }
        }
		fputc('\n',graph);
	}
    fclose(graph);
}

