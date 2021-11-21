# pexm
<code>R</code> package to load the <code>JAGS</code> module pexm.

<strong>Description</strong>: The Piecewise Exponencial (PE) distribution is not available in <code>JAGS</code>, therefore, many applications in survival analysis assuming a semiparametric modeling based on a piecewise constant hazard must consider a zeros-trick strategy to deal with the MCMC algorithm related to the Bayesian framework. The present <code>R</code> package provides a <code>JAGS</code> module containing distribution and related functions for the random variable <em>T ~ PE(lambda, tau)</em>, where <em>lambda</em> is the vector of failure rates specified for different intervals in the time scale and <em>tau</em> is the vector defining a grid partitioning the time line related to the application. All details about the PE distribution and the proposed <code>pexm</code> module can be found in <a href="https://www.jstatsoft.org/article/view/v100i08"><em>Mayrink et al. (2021)</em></a>.

<hr />
<strong>Authors</strong>: Vinícius D. Mayrink, João D. N. Duarte and Fábio N. Demarqui.

Departamento de Estatística, ICEx, Universidade Federal de Minas Gerais, Av. Antônio Carlos, 6627, Belo Horizonte, MG, Brazil, 31270-901.
<hr />

<li> <a href="https://www.jstatsoft.org/article/view/v100i08"><em>DOI:10.18637/jss.v100.i08</em></a> Mayrink VD, Duarte JDN and Demarqui FN (2021). pexm: a JAGS module for applications involving the piecewise exponential distribution, Journal of Statistical Software, 100, 8, 1-28.</li>
<hr />

<strong>Repositories</strong>: the source code of <code>pexm</code> is open for free access in 
<li>https://CRAN.R-project.org/package=pexm</li>
<li>https://github.com/vdinizm/pexm.git</li>
<li>https://sourceforge.net/projects/jags-pexm</li>
<hr />

In order to build this package, some scripts from the <code>R</code> packages <a href="https://CRAN.R-project.org/package=runjags"><code>runjags</code></a> and <a href="https://CRAN.R-project.org/package=rjags"><code>rjags</code></a> were considered as examples. The source code of <code>pexm</code> may also be used as a template to build other <code>R</code> packages introducing new JAGS modules. Some knowledge of <code>R</code> and <code>C++</code> programming languanges are necessary to work through the details.   

The package can be installed ("Unix or Windows") from CRAN applying the command <code>install.packages("pexm")</code> in the <code>R</code> console. In addition, the installation from GitHub can be done via <code>devtools::install_github("vdinizm/pexm")</code>. Note that the <code>R</code> package <a href="https://CRAN.R-project.org/package=devtools"><code>devtools</code></a> is required for this task.

Alternatively, the <a href="https://sourceforge.net/projects/jags-pexm">Sourceforge</a> repository contains the package sources <code>pexm_1.0.1.tar.gz</code> for both Unix or Windows. The user must download and install it via <code>install.packages(path_to_file, repos = NULL, type="source")</code>, where <code>path_to_file</code> should be replaced by the path pointing to the target <code>tar.gz</code>.

<hr />
<strong>Instructions</strong>: Before installing the package <code>pexm</code>, as indicated above, the user must first install a recent version of <a href="https://sourceforge.net/projects/mcmc-jags"><code>JAGS</code></a> in the computer. For those using the Windows system, the current recommended version is <code>JAGS-4.3.0</code>. If using a different version, the variable <code>JAGS_ROOT</code>, defined in the file <code>Makevars.win</code> (within the directory <code>src</code> of the source code), must be adapted with the correct numerical indication of version. In an Unix system, this modification is supposed to be automatic. The present package has the following dependencies on other <code>R</code> packages: 

<li> <a href="https://CRAN.R-project.org/package=rjags"><code>rjags</code></a> providing tools to load a <code>JAGS</code> module and to compile and run a Bayesian model implemented in <code>JAGS</code>.</li>
<li> <a href="https://CRAN.R-project.org/package=msm"><code>msm</code></a> providing tools to work with the PE distribution in <code>R</code> (important to run some comparison examples).</li> <br />

Assuming that <code>pexm</code> was succesfully installed in <code>R</code>, the user is expected to load the package in the console via <code>libary("pexm")</code> and then load the module using <code>loadpexm()</code>. The message <code>"module pexm loaded"</code> will be displayed when the module is ready to use. Since one might choose a non-standard location to save the <code>pexm</code> package library, an error indication may appear in the console when the function <code>loadpexm()</code> is not able to locate the key files <code>pexm.so</code> (Unix) or <code>pexm.dll</code> (Windows). In this situation, the user can manually set the path to the target directory containing one of these key files by using <code>loadpexm("file_path")</code>, where <code>file_path</code> should be replaced by a quoted path found by the user. 
<hr />



