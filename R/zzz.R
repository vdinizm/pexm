#  This file is based on R package JAGSmodule file R/zzz.R
#
#  This file can be used (unmodified) by any R package wishing to implement
#  an inbuilt JAGS module
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License version
#  2 as published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  A copy of the GNU General Public License is available at
#  http://www.r-project.org/Licenses/

#' @importFrom rjags load.pkg.module unload.module list.modules

# Package environment variables:
.jags_pkg_env <- new.env(parent = emptyenv())
.jags_pkg_env$pkgname <- character(0)
.jags_pkg_env$libname <- character(0)
.jags_pkg_env$dyn_loaded <- FALSE
.jags_pkg_env$pkg_compile_flags <- rjags::pkg.compile.flags("ALL")

.onLoad <- function(libname, pkgname){

  # Preserve the name of the package for use in .onUnload etc:
  .jags_pkg_env$pkgname <- pkgname
  .jags_pkg_env$libname <- libname

  # First try to load rjags (this sets paths on Windows etc):
  tryCatch({
    if(!isNamespaceLoaded("rjags")) loadNamespace("rjags")
  }, error = function(e) {
    stop("The following error was obtained when loading rjags:\n\t",
         conditionMessage(e), call.=FALSE)
  })
  # Ensure the version of rjags is compatible with what we need:
  rjags_version <- utils::packageVersion("rjags")
  if(rjags_version >= "5" && rjags_version < "5.4"){
    stop("An incompatible version of rjags (", gsub(".","-",rjags_version,fixed=TRUE), ") is installed\n\tPlease install either rjags 4-18 or rjags >= 5-4", call.=FALSE)
  }

  # Guard against non-present dynlib when running roxygen:
  if(file.exists(
    if(nzchar(.Platform$r_arch)){
      file.path(libname, pkgname, "libs", .Platform$r_arch, paste0(pkgname, .Platform$dynlib.ext))
    }else{
      file.path(libname, pkgname, "libs", paste0(pkgname, .Platform$dynlib.ext))
    }
  )){
    tryCatch({
      # First load the package module, so that rjags can report on any JAGS
      # version incompatibility:
      rjags::load.pkg.module(pkgname, libname, .jags_pkg_env$pkg_compile_flags, quiet=TRUE)

      # Then load the dynamic library:
      library.dynam(pkgname, pkgname, libname)
      # And set the dyn_loaded flag to TRUE:
      .jags_pkg_env$dyn_loaded <- TRUE

    }, error = function(e) {
      if(.jags_pkg_env$pkgname %in% list.modules()){
        unload.module(.jags_pkg_env$pkgname, quiet=TRUE)
      }
      stop("Loading the package module/dynlib failed with the following error:\n\t", conditionMessage(e), call.=FALSE)
    })
  }
}

.onAttach <- function(libname, pkgname){
  # Only attempt to load the package module if the dynlib is loaded:
  if(.jags_pkg_env$dyn_loaded && .jags_pkg_env$pkgname %in% list.modules()){
    packageStartupMessage("module ", pkgname, " loaded")
  }else if(.jags_pkg_env$dyn_loaded){
    packageStartupMessage("The JAGS module ", pkgname, " was unloaded before the package was attached")
  }else{
    packageStartupMessage("The JAGS module and package dynlib for ", pkgname, " failed to load\n(this is expected during roxygenization and with devtools::load_all)")
  }
}

.onUnload <- function(libname){
  # Ignore if the dynlib failed to load at startup:
  if(.jags_pkg_env$dyn_loaded){
    # First unload the JAGS module (silently), if loaded:
    if(.jags_pkg_env$pkgname %in% list.modules()){
      unload.module(.jags_pkg_env$pkgname, quiet = TRUE)
    }
    # Then the dynlib:
    library.dynam.unload(.jags_pkg_env$pkgname, libname)
  }
}
