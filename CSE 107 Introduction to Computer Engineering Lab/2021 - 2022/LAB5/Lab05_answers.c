#include <stdio.h>

int main ()
{
  int n1, n2, n3, temp, i, factorial = 1;
  printf ("Part1:\n");
  printf ("Lütfen 3 adet sayı girin:\n");
  scanf ("%d", &n1);
  scanf ("%d", &n2);
  scanf ("%d", &n3);
  if (n2 < n1)
    {
      temp = n2;
      n2 = n1;
      n1 = temp;
    }
  if (n3 < n2)
    {
      temp = n3;
      n3 = n2;
      n2 = temp;
    }
  if (n2 < n1)
    {
      temp = n2;
      n2 = n1;
      n1 = temp;
    }
  printf ("Küçükten büyüğe : %d %d %d\n", n1, n2, n3);
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  printf ("Part2:\n");
  printf ("Lütfen ilk sayıyı girin: ");
  scanf ("%d", &n1);
  printf ("Lütfen ikinci sayıyı girin: ");
  scanf ("%d", &n2);
  printf ("Değişmeden önce:\nx = %d\ny=%d\n", n1, n2);
  temp = n2;
  n2 = n1;
  n1 = temp;
  printf ("Değiştikten sonra:\nx = %d\ny=%d\n", n1, n2);
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  printf ("Part3:\n");
  for (i = 4; i <= 100; i = i + 3)
    {
      printf ("%d ", i);
    }
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  printf ("Part4:\n");
  printf ("Lütfen faktoriyeli alınacak sayıyı girin: ");
  scanf ("%d", &n1);
  for (i = 2; i <= n1; i++)
    {
      if (n1 == 2)
	factorial = 1;
      else
	factorial *= i;
    }
  printf ("%d! = %d", n1, factorial);
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");


  printf ("Quiz Answers:\n");
  printf ("Part1:\n");
  printf ("Lütfen kaç terim yazdirmak istediğinizi girin:");
  scanf("%d", &n3);
  n1 = 0;
  n2 = 1;
  printf ("\nİlk %d terim :%d %d ", n3, n1, n2);
  for (i = 2; i < n3; i++)
    {
      temp = n2;
      n2 = n2 + n1;
      n1 = temp;
      printf ("%d ", n2);
    }
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  printf ("Part2:\n");
  printf ("Lütfen kontrol edilecek sayıyı girin:");
  scanf("%d", &n1);
  n2 = 1;
  for (i = 2; i < n1; i++)
  {
      if (n1 % i == 0)
      {
          n2 = 0;
          break;
      }
  }
  if (n2 == 1) printf("%d asaldır.\n", n1);
  else printf("%d asal değildir.\n", n1);
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  printf ("Part3:\n");
  printf ("Lütfen kontrol edilecek sayıyı girin:");
  scanf("%d", &n1);
  n2 = 0;
  for (i = 1; i < n1; i++)
  {
      if (n1 % i == 0)
      {
          n2 += i;
      }
  }
  if (n2 == n1) printf("%d mükemmel sayıdır.\n", n1);
  else printf("%d mükemmel sayı değildir.\n", n1);
  printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  return 0;



}
