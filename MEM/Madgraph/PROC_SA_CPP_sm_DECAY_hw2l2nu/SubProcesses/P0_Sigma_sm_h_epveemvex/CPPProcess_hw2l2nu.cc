//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.2.2, 2014-11-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "CPPProcess_hw2l2nu.h"
#include "HelAmps_sm_hw2l2nu.h"

using namespace MG5_sm_hw2l2nu; 

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: h > w+ e- ve~
// *   Decay: w+ > e+ ve WEIGHTED=2
// Process: h > w+ mu- vm~
// *   Decay: w+ > e+ ve WEIGHTED=2
// Process: h > w+ e- ve~
// *   Decay: w+ > mu+ vm WEIGHTED=2
// Process: h > w+ mu- vm~
// *   Decay: w+ > mu+ vm WEIGHTED=2

//--------------------------------------------------------------------------
// Initialize process.

void CPPProcess_hw2l2nu::initProc(string param_card_name) 
{
  // Instantiate the model class and set parameters that stay fixed during run
  pars = Parameters_sm_hw2l2nu::getInstance(); 
  SLHAReader slha(param_card_name); 
  pars->setIndependentParameters(slha); 
  pars->setIndependentCouplings(); 
  pars->printIndependentParameters(); 
  pars->printIndependentCouplings(); 
  // Set external particle masses for this matrix element
  mME.push_back(pars->mdl_MH); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  jamp2[0] = new double[1]; 
}

//--------------------------------------------------------------------------
// Evaluate |M|^2, part independent of incoming flavour.

void CPPProcess_hw2l2nu::sigmaKin() 
{
  // Set the parameters which change event by event
  pars->setDependentParameters(); 
  pars->setDependentCouplings(); 
  static bool firsttime = true; 
  if (firsttime)
  {
    pars->printDependentParameters(); 
    pars->printDependentCouplings(); 
    firsttime = false; 
  }

  // Reset color flows
  for(int i = 0; i < 1; i++ )
    jamp2[0][i] = 0.; 

  // Local variables and constants
  const int ncomb = 16; 
  static bool goodhel[ncomb] = {ncomb * false}; 
  static int ntry = 0, sum_hel = 0, ngood = 0; 
  static int igood[ncomb]; 
  static int jhel; 
  std::complex<double> * * wfs; 
  double t[nprocesses]; 
  // Helicities for the process
  static const int helicities[ncomb][nexternal] = {{0, -1, -1, -1, -1}, {0, -1,
      -1, -1, 1}, {0, -1, -1, 1, -1}, {0, -1, -1, 1, 1}, {0, -1, 1, -1, -1},
      {0, -1, 1, -1, 1}, {0, -1, 1, 1, -1}, {0, -1, 1, 1, 1}, {0, 1, -1, -1,
      -1}, {0, 1, -1, -1, 1}, {0, 1, -1, 1, -1}, {0, 1, -1, 1, 1}, {0, 1, 1,
      -1, -1}, {0, 1, 1, -1, 1}, {0, 1, 1, 1, -1}, {0, 1, 1, 1, 1}};
  // Denominators: spins, colors and identical particles
  const int denominators[nprocesses] = {1}; 

  ntry = ntry + 1; 

  // Reset the matrix elements
  for(int i = 0; i < nprocesses; i++ )
  {
    matrix_element[i] = 0.; 
  }
  // Define permutation
  int perm[nexternal]; 
  for(int i = 0; i < nexternal; i++ )
  {
    perm[i] = i; 
  }

  if (sum_hel == 0 || ntry < 10)
  {
    // Calculate the matrix element for all helicities
    for(int ihel = 0; ihel < ncomb; ihel++ )
    {
      if (goodhel[ihel] || ntry < 2)
      {
        calculate_wavefunctions(perm, helicities[ihel]); 
        t[0] = matrix_h_wpemvex_wp_epve(); 

        double tsum = 0; 
        for(int iproc = 0; iproc < nprocesses; iproc++ )
        {
          matrix_element[iproc] += t[iproc]; 
          tsum += t[iproc]; 
        }
        // Store which helicities give non-zero result
        if (tsum != 0. && !goodhel[ihel])
        {
          goodhel[ihel] = true; 
          ngood++; 
          igood[ngood] = ihel; 
        }
      }
    }
    jhel = 0; 
    sum_hel = min(sum_hel, ngood); 
  }
  else
  {
    // Only use the "good" helicities
    for(int j = 0; j < sum_hel; j++ )
    {
      jhel++; 
      if (jhel >= ngood)
        jhel = 0; 
      double hwgt = double(ngood)/double(sum_hel); 
      int ihel = igood[jhel]; 
      calculate_wavefunctions(perm, helicities[ihel]); 
      t[0] = matrix_h_wpemvex_wp_epve(); 

      for(int iproc = 0; iproc < nprocesses; iproc++ )
      {
        matrix_element[iproc] += t[iproc] * hwgt; 
      }
    }
  }

  for (int i = 0; i < nprocesses; i++ )
    matrix_element[i] /= denominators[i]; 



}

//--------------------------------------------------------------------------
// Evaluate |M|^2, including incoming flavour dependence.

double CPPProcess_hw2l2nu::sigmaHat() 
{
  // Select between the different processes
  if(id1 == 25 && id2 == 24)
  {
    // Add matrix elements for processes with beams (25, 24)
    return matrix_element[0] * 4; 
  }
  else
  {
    // Return 0 if not correct initial state assignment
    return 0.; 
  }
}

//==========================================================================
// Private class member functions

//--------------------------------------------------------------------------
// Evaluate |M|^2 for each subprocess

void CPPProcess_hw2l2nu::calculate_wavefunctions(const int perm[], const int hel[])
{
  // Calculate wavefunctions for all processes
  int i, j; 

  // Calculate all wavefunctions
  sxxxxx(p[perm[0]], -1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], -1, w[1]); 
  oxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  FFV2_3(w[1], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[3]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[4]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[5]); 
  FFV2_3(w[5], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[6]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  VVS1_0(w[6], w[3], w[0], pars->GC_72, amp[0]); 

}
double CPPProcess_hw2l2nu::matrix_h_wpemvex_wp_epve() 
{
  int i, j; 
  // Local variables
  const int ngraphs = 1; 
  const int ncolor = 1; 
  std::complex<double> ztemp; 
  std::complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{1}}; 

  // Calculate color flows
  jamp[0] = -amp[0]; 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[0][i] += real(jamp[i] * conj(jamp[i])); 

  return matrix; 
}



