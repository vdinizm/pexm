#include <stdlib.h>
#include <R_ext/Rdynload.h>
#include <Rinternals.h>

void
R_init_pexm(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, NULL, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
