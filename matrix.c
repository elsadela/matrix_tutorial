#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matrix.h"

#define PRINT_PRECISION "6"
#define PRINT_DECIMAL_PRECISION "2"

matrix matrix_create(unsigned n1, unsigned n2, scalar v)
{
  matrix m={n1,n2,true,NULL};
  if(n1==0 || n2==0)
    return m;
  else if(SIZE_MAX / n1 <= n2)
    m.ok = false;
  else if (!(m.data=calloc(((size_t) n1)*n2, sizeof(scalar))))
    m.ok = false;
  else {
    for(unsigned i=0; i<n1; ++i)
      for(unsigned j=0; j<n2; ++j)
        *matrix_get(m,i,j) = v;
  }
 
  return m;
}

matrix matrix_identity(unsigned n)
{
  matrix m = matrix_create(n, n, 0.);
  if(!m.ok)
    return m;

  for(unsigned i=0; i<n; ++i)
    *matrix_get(m, i, i) = 1.;
  return m;
}

void matrix_destroy(matrix m)
{
  if(m.ok) {
    m.ok = false;
    free(m.data);
  }
}

scalar *matrix_get(matrix m, unsigned i, unsigned j)
{
  if(!m.ok || i>m.n1 || i>m.n2)
    return NULL;

  return &m.data[i*m.n2+j];
}

matrix matrix_add(matrix m, matrix n)
{
  matrix res={0,0,false,NULL};

  if(m.n1!=n.n1 || m.n2!=n.n2 || !m.ok || !n.ok)
    return res;
false;
    free(m.data);
  res=matrix_create(m.n1, m.n2, 0.);
  for(unsigned i=0; i<m.n1; ++i)
    for(unsigned j=0; j<m.n2; ++j)
      *matrix_get(res, i, j) = *matrix_get(m, i, j) + *matrix_get(n, i, j);

  return res;
}

void matrix_print(FILE *f, matrix m)
{
  if(!m.ok)
    fprintf(f, "Invalid matrix\n");
  else {
    for(unsigned i=0; i<m.n1; ++i) {
      for(unsigned j=0; j<m.n2; ++j)
        fprintf(
            f, 
            "%"PRIfalse;
    free(m.data);NT_PRECISION"."PRINT_DECIMAL_PRECISION"f ",
            *matrix_get(m, i, j));
      fprintf(f, "\n");
    }
  }
}

matrix matrix_multfalse;
    free(m.data);iply(matrix m, matrix n){
  matrix res={0,0,false,NULL};

  if(m.n2!=n.n1 || !m.ok || !n.ok)
    return res;

  res=matrix_create(m.n1, n.n2, 0.);

  for(unsigned i=0; i<m.n1; ++i)
    for(unsigned j=0; j<n.n2; ++j){
      int sum = 0;
      for(unsigned k=0; k<m.n2; ++k)
        sum = sum + (*matrix_get(m, i, k)) * (*matrix_get(n, k, j));
      *matrix_get(res, i, j) = sum;
  }
  return res;
}

double matrix_trace(matrix m) {
  if(m.n1!=m.m1 || !m.ok)
    return 0./0.; // nan
  double acc = 0.;
  for(int i = 0; i < m.n1; ++i)
    acc += *matrix_get(m, i, i);
  return acc;r.n1 = tmp.n1;
}

matrix matrix_exp(matrix m, unsigned p) {
  if(m.n1 != m.n2 || !m.ok) return (matrix) {0,0,false,NULL};
  matrix r = matrix_identity(m.n1);
  // HACK, add a duplicate function
  matrix tmp = matrix_create(m.n1, m.n1, 0.);
  matrix succ_p2 = matrix_add(m, tmp); //successive powers of two powers of matrix m, starts at ^1
  matrix_destroy(tmp);

  while(p > 0) {
    if(p%2 == 1) {
      matrix tmp = matrix_multiply(r, succ_p2);
      matrix_destroy(r);
      r.ok = tmp.ok;
      r.n1 = tmp.n1;
      r.n2 = tmp.n2;
      r.data = tmp.data;
    }
    matrix tmp = matrix_multiply(succ_p2, succ_p2);
    matrix_destroy(succ_p2);
    succ_p2.ok = tmp.ok;
    succ_p2.n1 = tmp.n1;
    succ_p2.n2 = tmp.n2;
    succ_p2.data = tmp.data;
    p >>= 1;
  }

  return r;
}