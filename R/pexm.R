#' @title pexm: Loading a Just Another Gibbs Sampling Module for the Piecewise Exponential Distribution
#'
#' @description
#' Load the Just Another Gibbs Sampling (JAGS) module "pexm". 
#' The module provides the tools to work with the Piecewise Exponential (PE) distribution in a Bayesian model with 
#' the corresponding Markov Chain Monte Carlo algorithm (Gibbs Sampling) implemented via JAGS.
#' 
#' @details 
#' The current version contains the main function \code{loadpexm} to load the proposed JAGS module. 
#' Details about JAGS can be found in the \href{https://sourceforge.net/projects/mcmc-jags/files/Manuals/3.x/jags_user_manual.pdf}{JAGS User Manual}.
#' Download instructions are presented in the home page given by this \href{https://mcmc-jags.sourceforge.io}{link}. 
#' Details about \pkg{pexm} and the piecewise exponential model can be found in \emph{Mayrink et al. (2020)}.
#' 
#' @author Vinicius D. Mayrink, Joao D. N. Duarte and Fabio N. Demarqui. 
#' 
#' Departamento de Estatistica, ICEx, Universidade Federal de Minas Gerais, Av. Antonio Carlos, 6627, Belo Horizonte, MG, Brazil, 31270-901.
#' 
#' @docType package
#' @name pexm
#' @useDynLib pexm
#' 
#' @references
#' arXiv:2004.12359 (\href{https://arxiv.org/abs/2004.12359}{Mayrink et al.; 2020})
#' 
#' @seealso
#' \code{\link{loadpexm}}
#' 
#' @import rjags coda msm 
NULL