#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
//#include <allegro5/allegro.h>


const int MAXINT = 2147483647; // "plus nieskoñczonoœæ"

// Zmienne globalne

int tab[5][13], tab_2[5][13]; // Macierze kosztów oraz poprzedników
int n, m;     // Liczba wierzcho³ków i krawêdzi

// Funkcja wyznaczania kosztów dojœcia oraz
// minimalnych œcie¿ek w grafie wa¿onym
//------------------------------------------


int FloydWarshall( )
{
  int i, j, k, w;

  for( k = 0; k < n; k++ )
    for( i = 0; i < n; i++ )
      for( j = 0; j < n; j++ )
      {
        if( ( tab [ i ][ k ] == MAXINT ) || ( tab [ k ][ j ] == MAXINT ) ) continue;
        w = tab [ i ][ k ] + tab [ k ][ j ];
        if( tab [ i ][ j ] > w )
        {
          tab [ i ][ j ] = w;
          tab_2 [ i ][ j ] = tab_2 [ k ][ j ];
        }
      }
  for( i = 0; i < n; i++ )
    if( tab [ i ][ i ] < 0 ) return 0; // Ujemny cykl
  return 1;
}

// Rekurencyjna procedura odtwarzania minimalnej
// œcie¿ki z macierzy poprzedników p
//----------------------------------------------
void FWPath ( int i, int j )
{
  if( i == j ) printf("%d ",i);
  else if( tab_2 [ i ][ j ] == -1 ) printf( "NO PATH");
  else
  {
    FWPath ( i, tab_2 [ i ][ j ] );
    printf("%d ", j);
  }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************
int main( )
{
  int i, j, x, y, w;

  scanf("%d %d", &n,&m);
//-----------------------------------------------------------------------------------
/*                       !!! tablica dynamiczna !!!
    int wier, col;
    int **tab;

    // Pobranie danych
    printf("Wiersze: ");
    scanf("%d", &wier);
    printf("\nKolumny: ");
    scanf("%d", &col);

    // Alokacja pamięci dla tablicy dwuwymiarowej
    tab=(int**)malloc(wier*sizeof(int*)); // alokacja pamięci dla wierszy
    for(int i=0; i<wier; i++)
        tab[i]=(int*)malloc(col*sizeof(int)); // alokacja pamięci dla kolumn
 */
//------------------------------------------------------------------------------------



  for( i = 0; i < n; i++ )
  {

    for( j = 0; j < n; j++ )
    {
      tab [ i ][ j ] = MAXINT; // Wiersz d wype³niamy najwiêksz¹ liczb¹ dodatni¹
      tab_2 [ i ][ j ] = -1;     // Wiersz p wype³niamy liczbami -1 ( brak poprzednika )
    }
    tab [ i ][ i ] = 0;        // Jednak¿e na przek¹tnej d wpisujemy 0
  }

  for( i = 0; i < m; i++ )
  {
    scanf("%d %d %d", &x,&y, &w);// Czytamy definicjê krawêdzi

//-----------------------------------------------------------------------------------
/*                       !!! sprawszanie cykli ujemnych !!!
    if(x==y && w<0) printf("graf nie może zawierac cykli ujemnych");
 */
//------------------------------------------------------------------------------------

    tab [ x ][ y ] = w;        // Wagê krawêdzi umieszczamy w macierzy d
    tab_2 [ x ][ y ] = x;        // Poprzednikiem y jest x
  }

  // Wywo³ujemy procedurê Floyda-Warshalla


  if( FloydWarshall( ) )
  {
    // Wyœwietlamy wyniki
    for( i = 0; i < n; i++ )
      for( j = 0; j < n; j++ )
      {
        printf("tab{%d ; %d] ", i, j);
        printf("droga { ");
        FWPath ( i, j );
        printf("}");
        if( tab[ i ][ j ] < MAXINT )  printf ("\n koszt %d",tab [ i ][ j ]);
        printf("\n");
      }
  }
printf ( "Negative cycle found" );

  return 0;
}
