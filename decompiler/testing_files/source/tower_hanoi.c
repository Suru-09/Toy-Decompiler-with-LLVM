#include<stdio.h>

typedef struct caramida1{

      unsigned position;

}caramida;

 int x = 25;
 int y  = 200 ;

void svg_body(FILE * out , int n , caramida caramida[] );

void initializeaza_caramida(caramida caramida[] , int n){

        for(int i = 0 ; i < n ; i++){
          caramida[i].position = 0;
        }
}
void tower_hanoi(int n ,int copy_n , int from , int to , int aux , caramida caramida[] ,FILE * out){

  if (n == 1)
   {
       printf("Disk 1 from %d to %d\n" , from , to);
       svg_body(out , copy_n , caramida);
       caramida[0].position = to;
       return;
   }

   tower_hanoi(n - 1, copy_n ,from , aux, to , caramida ,out);
   printf("Disk %d from %d to %d\n" ,n , from , to);
   svg_body(out , copy_n , caramida);
   caramida[n - 1].position = to;
   tower_hanoi(n - 1, copy_n ,  aux, to ,from , caramida ,  out);
}
void svg_first_thing(FILE * out){

      fprintf(out , "<svg width =\"1920\" height =\"2300\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" overflow =\"auto\" > \n\n");
}

void svg_body(FILE * out , int n , caramida caramida[] ){


    static int nr;

    fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"50\" height=\"200\" fill=\"lightcoral\" stroke-width=\"4\" stroke=\"pink\" />\n" , x + 25 , y - 125);
    fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"50\" height=\"200\" fill=\"lightcoral\" stroke-width=\"4\" stroke=\"pink\" />\n" , x + 175 , y - 125);
    fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"50\" height=\"200\" fill=\"lightcoral\" stroke-width=\"4\" stroke=\"pink\" />\n" , x + 310, y - 125 );
    fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"400\" height=\"40\" fill=\"saddlebrown\" stroke-width=\"4\" stroke=\"pink\" />\n\n" , x , y + 50 );

    int copy1_y = y;
    int copy2_y = y;
    int copy3_y = y;

    int centrare = 0;                //Ajuta la centrarea pieselor(cele mai mici sa fie pe centrrul lu' alea mai mari)
    for(int i = (n - 1) ; i >= 0 ; --i){            //Am inceput invers ca sa modific dimensiunea(width) discurilor sa fie direct
      if(caramida[i].position == 0){                //proportionala cu i-ul
        fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"35\" fill=\"lightseagreen\" stroke-width=\"4\" stroke=\"pink\" />\n" , x + 3 + centrare , copy1_y + 12 , i * 10 + 50);
        copy1_y -= 35;
      }
      else if(caramida[i] .position == 1){
        fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"35\" fill=\"lightseagreen\" stroke-width=\"4\" stroke=\"pink\" />\n" , x + 153 + centrare , copy2_y + 12 , i * 10 + 50);
        copy2_y -= 35;
      }
      else if(caramida[i].position == 2){
        fprintf(out , "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"35\" fill=\"lightseagreen\" stroke-width=\"4\" stroke=\"pink\" />\n" , x + 288 + centrare , copy3_y + 12 , i * 10 + 50);
        copy3_y -= 35;
      }
      centrare += 5;
    }

    ++nr;
    if(nr == 4){

        x = 25;
        y += 275;
        nr = 0;
    }
    else{
      x += 495;
    }

}

void svg_final(FILE * out){

  fprintf(out , "\n\n</svg>");
}
int main(){

  FILE * out;
  out = fopen("out.svg" , "w");
  if(!out){
    printf("I couldn't open the file :( \n");
    return 0;
  }

  int n ;
  printf("Enter the number of disks you want , it is not recommended to go for more than 5 tho' : ");
  scanf("%d" , &n);
  printf("\n");

  int copy_n = n;
  caramida caramida[n];

  initializeaza_caramida(caramida , n);   //Setez toate pozitiile pe 0 initial

  svg_first_thing(out);   //imi deschid <svg chestie ...

  tower_hanoi(n , n ,  0 , 2 , 1 , caramida , out);   //Aplic hanoi si afisez la fiecare pas
  svg_body(out , copy_n , caramida);      //La final afisez cand discurile sunt pe ultima pozitie
  svg_final(out);   //inchid cu </svg>

  return 0;
}
