//randomly simulate 10^4 events -> I distinguish when generating random angles (?)

#include <iostream>

// ROOT header files: Lorentz vector, random numbers, plotting, file storage

#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"

using std::cout;
using std::endl;

int main() {

  // Open TFile for output
  TString rootfname("./output.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
    std::cout << "problems creating root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

  // Create B meson, pion and kaon
  TLorentzVector B; //particle object w position X(), Y(), Z(), T(), momentum Px(), Py(), Pz(), E()
  double m_B = 5.279; // GeV
  TLorentzVector Pi;
  double m_Pi = 0.140; // GeV
  TLorentzVector K;
  double m_K = 0.500; //GeV
  
  // square masses of convenience
  double m_B_2 = m_B*m_B;
  double m_Pi_2 = m_Pi*m_Pi;
  double m_K_2 = m_K*m_K;
  
  // 4-momentum of B meson in the LAB rest frame
  double p_B = 0.300; // GeV
  // Flat metric, (+ - - -) signature: m^2 = E^2 - p^2
  //B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B_2));
  
  // Start up a new random generator(we will need a delete!)
  TRandom*  gen = new TRandom();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);
  // # events
  int nsig = 10;//per ora 10
  
  // 4-momentum of the pion in the B rest frame (center of mass of the B meson)
  double p_Pi = sqrt((m_B_2*m_B_2 + m_Pi_2*m_Pi_2 + m_K_2*m_K_2 -2*m_B_2*m_Pi_2 -2*m_B_2*m_K_2 -2*m_Pi_2*m_K_2)/(2*m_B_2));
  
  // 4-momentum of the kaon in the B rest frame (equal to the pion)
  double p_K = p_Pi;
  
  // Once I have the module of the momentum, I generate the random directions for te two particles
  double point_Pi, point_K, theta_Pi, phi_Pi, theta_K, phi_K;;
  Double_t x, y, z, r=1; 
  
  // Loop on the 10000 events
  for(int i=0; i<nsig; ++i) {

    // Genarate random point in spherical coordinates for pion
    point_Pi = gen.Sphere(x,y,z,r); //vedere che raggio mettere
    theta_Pi = atan(y / x);
    phi_Pi = acos(z / r);
    cout<<""<<theta_Pi<<""<<phi_Pi<<endl;//per ora
    // Generate random point in spherical coordinates for kaon
    point_K = gen.Sphere(x,y,z,r);
    theta_K = atan(y / x);
    phi_K = (z / r);
    cout<<""<<theta_K<<""<<phi_K<<endl;//per ora

    //save values in a file
    
  }
  
  
  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;
  
  /*
     Print to screen 4-momenta as we have them
     As a reminder:
     * Hadron colliders measure physical momenta in terms of momentum transverse
       to the beam axis (z-axis); the TRANSVERSE MOMENTUM is denoted by p_T
     * p_x = p_T * cos(phi) 
       p_y = p_T * sin(phi) 
       p_z = m_T * sinh(eta) 
       E = m_T * cosh(eta) 
       where m_T = sqrt(p_T^2 + m^2) is the TRANSVERSE MASS
     * eta is the PSEUDORAPIDITY: eta = -ln[tan(theta/2)]; differences in eta
       are Lorentz invariants under boosts along the longitudinal axis
  */


  // Exit
  return 0;
}
