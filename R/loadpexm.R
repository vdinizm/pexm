#############################################################################################
#' @title loadpexm
#' @description Function to load the Just Another Gibbs Sampling (JAGS) module \code{pexm} into the \code{R} environment.
#' @param f.path This is an optional argument. If having difficulties to find the main file "\code{pexm.so}" (unix) or "\code{pexm.dll}" (windows), the user 
#' may choose to manually include here the corresponding quoted path to the target directory.
#' @return Indication of whether the JAGS module \pkg{pexm} was correctly loaded in the \code{R} environment.
#' @details The main purpose of the present function is to load the target JAGS module \pkg{pexm} into the R environment. 
#' The pexm module allows the application of the Piecewise Exponential (PE) distribution in any Bayesian model implemented through JAGS.  
#' In order to apply this loading routine, it is necessary to have \href{https://mcmc-jags.sourceforge.io}{JAGS} installed in the computer.
#' The supporting package \pkg{rjags} is also required and it should have been automatically installed together with \pkg{pexm}. 
#' Important remark for Windows users: the JAGS version 4.3.0 is the one considered in the present implementation of \pkg{pexm}. 
#' If working with another version, one must download the source code of \pkg{pexm} and then modify the file "Makevars.win" (directory \code{src}). 
#' In this case, simply adapt the path in \code{JAGS_ROOT} with the correct version number. 
#' In order to build the present package, the source code of \pkg{runjags} (\emph{Denwood; 2016}) was used as an example. Details about \pkg{pexm} and 
#' the piecewise exponential model can be found in \emph{Mayrink et al. (2021)}.   
#' 
#' @references
#' DOI:10.18637/jss.v071.i09 (\href{https://www.jstatsoft.org/article/view/v071i09}{Denwood; 2016})
#' 
#' DOI:10.18637/jss.v100.i08 (\href{https://www.jstatsoft.org/article/view/v100i08}{Mayrink et al.; 2021})  
#'
#' @seealso
#' \code{\link{pexm}}
#'
#' @examples
#' # Load the new module with the command below:
#' \donttest{ loadpexm() }
#' 
#' @export
#' @importFrom rjags load.module
#' 
loadpexm = function(f.path = NULL){
  if(any(.packages(TRUE)=="rjags")==FALSE){ stop("Error: the required package rjags is not installed. Please, install it and try again.") }
  # find the path to the file pexm.so (unix) or pexm.dll (windows).
  if(is.null(f.path)==TRUE){
    aux = paste0(Sys.getenv("R_LIBS_USER"),"/pexm/libs",Sys.getenv("R_ARCH"))
    if(dir.exists(aux)==FALSE){ aux = pexmprivate$lib.loc }
    out = try(load.module('pexm', path = aux))
  }else{ 
    if(grepl("pexm.so",f.path)==TRUE){ f.path = dirname(f.path) } 
    if(grepl("pexm.dll",f.path)==TRUE){ f.path = dirname(f.path) }     
    out = try(load.module('pexm',path = f.path)) }
  #
  if(inherits(out,"try-error")){ message("Error: module pexm cannot be loaded. Verify the path to the files pexm.so (unix) or pexm.dll (windows).") }
}

pexmprivate <- new.env()

.onLoad <- function(libname, pkgname){ 
  # Get and save the library location, getting rid of any trailing / caused by r_arch being empty:
  loc.lib <- gsub('/$','', file.path(libname, pkgname, 'libs', if(.Platform$r_arch!="") .Platform$r_arch else ""))
  if(!file.exists(file.path(loc.lib, paste('pexm', .Platform$dynlib.ext, sep=''))))
    loc.lib <- ''
  pexmprivate$lib.loc <- loc.lib
} 

.onAttach <- function(libname, pkgname){ 
  # Get and save the library location, getting rid of any trailing / caused by r_arch being empty:
  loc.lib <- gsub('/$','', file.path(libname, pkgname, 'libs', if(.Platform$r_arch!="") .Platform$r_arch else ""))
  if(!file.exists(file.path(loc.lib, paste('pexm', .Platform$dynlib.ext, sep=''))))
    loc.lib <- ''
  pexmprivate$lib.loc <- loc.lib
} 
