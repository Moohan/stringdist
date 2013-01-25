/* Hamming distance function
 */

#include <R.h>
#include <Rdefines.h>

int hamming(const char *a, const char *b, int maxDistance){
   int i=0, h=0;
   while(a[i]){
      h += (a[i] == b[i]) ? 0 : 1;
      if ( maxDistance > 0 && maxDistance < h ){
         return -1;
      }
      ++i;
   }
   return h;
}


// -- R interface

SEXP R_hm(SEXP a, SEXP b, SEXP ncharA, SEXP ncharB, SEXP maxDistance){
   PROTECT(a);
   PROTECT(b);
   PROTECT(ncharA);
   PROTECT(ncharB);
   PROTECT(maxDistance);

   int *nchar_a = INTEGER(ncharA);
   int *nchar_b = INTEGER(ncharB);

   int na = length(a);
   int nb = length(b);
   int nt = ( na > nb) ? na : nb;
   SEXP yy;
   PROTECT(yy = allocVector(INTSXP,nt));
   int *y = INTEGER(yy);
   int i,j,k;
   int maxDist = INTEGER(maxDistance)[0];

   for ( k=0; k<nt; ++k){
      i = k % na;
      j = k % nb;
      if ( STRING_ELT(a,i) == NA_STRING || STRING_ELT(b,j) == NA_STRING ){
         y[k] = NA_INTEGER;
         continue;         
      }
      if ( nchar_a[i] != nchar_b[j] ){
         error("Charater strings %s and %s not of equal length",
            CHAR(STRING_ELT(a,i)), CHAR(STRING_ELT(b,j))
         );
      }
      y[k] = hamming(
         CHAR(STRING_ELT(a,i)),
         CHAR(STRING_ELT(b,j)),
         maxDist
      );
   }
   UNPROTECT(6);
   return yy;

}
/*
#include <stdio.h>
void main(){
   int h = hamming("aa","ab",0);
   printf("h = %d\n",h);
}

*/
