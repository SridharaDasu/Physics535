/*

   Your first step is to set up access to login.hep.wisc.edu conveniently. 
   We will use VNC to port linux desktop of login.hep.wisc.edu to your laptop 
   
   You will need to start VNC on the login.hep.wisc.edu. To do that:
        Open a Terminal emulator window on your laptop 
	(you can use putty on a Windows laptop or Terminal.app on a Mac laptop)
              ssh login.hep.wisc.edu
	Note that login.hep.wisc.edu is a pseudonym for several machines - you will
	be logged in to one of login01, login02, ... login06
	After logging in with your HEP password type:
	      vncserver -geometry 1200x800
	The 1200x800 is the screen size in pixel units and can be adjusted to suit your laptop
	The first time you issue the above command, it will prompt for a password twice.
	Use a simple password as it is not super-secure.  You need that to connect to the server.
	The program prints out the name of the machine and number for the display.
	In my case it printed:  login02.hep.wisc.edu and 1
	You can then close the terminal window.  The server can remain active for extended
	period of time across your work sessions.  If there is ever a problem, feel free to
	ssh login02.hep.wisc.edu and then kill the server : vncserver -kill :1
        You can tehn restart it as above.  It is important to go to your specific server
	
   You will need a VNC client on your laptop.
   
        On a Mac laptop, I use Chicken : 
        On Windows laptop, I recommend TightVNC :

   Open up your VNC client program and use server name, display number and password you set above.
   Once connected you should see the login.hep.wisc.edu linux desktop.

   Use the linux Gnome desktop enviornment menu that is displayed: Applications/System Tools/Terminal
   to open a terminal window.  In there you can do:
        cd ~/Physics535
        source environment.sh
	cd Exercise00
	root 
	root prompt> .X DDecayKinematics()

   Try it out right away, and you will get three plots

   Your job is to add code to DDecayKinematics.C which simulates 
   D meson decay Kinematics
   Refer to the problem statement provided on Learn@UW

   Begin by reading the Particle Data Group summary on 
   kinematics.  It also helps if you have tried some
   problems from Griffiths before you begin this exercise.

   I provided a shell in which you can fill in your 
   code that computes two-body and three-body decays

   This program currently has 3 one-dimensional test histograms 
   which just show random number distributions.
   These are examples are given so that you can emulate them
   to make your histograms and to learn how random number engine
   is called.  You can delete this code when you have your 
   histograms defined and filled.

*/

#include "TRandom.h"
#include "TH1F.h"
#include "TLorentzVector.h"

void DDecayKinematics() {

  // Random number engine

  TRandom *random = new TRandom();

  // Define histograms that you want to make here
  // You need provide name of the histogram, title to decorate it with,
  // Number of entries, low end of the histogram bin, high end of the bin
  // for the one-dimensional histogram

  // You need to make plots of energy and momentum (magnitude) of 
  // PK, PPi1, PPi2, the decay products of the D meson

  // You also need to make the Dalitz plot (the three body final state)
  // To make Dalitz plot you need to define two-dimensional histogram
  // Look up the syntax for that in ROOT manual

  // Example histograms of random numbers 
  // (can be removed when you have your own histograms of interest)

  TH1F *poissonDistribution = 
    new TH1F("Poisson", "Poisson Distribution (Mean=50)", 100, 0., 100.);

  TH1F *normalDistribution = 
    new TH1F("Normal", "Normal Distribution (Mean=50, SD=10)", 100, 0., 100.);
				       
  TH1F *uniformDistribution = 
    new TH1F("Uniform", "Uniform Distribution (0->100)", 100, 0., 100.);

  // You are generating single D mesons at rest!  Px=Py=Pz=0; E=MD

  TLorentzVector PD(0, 0, 0, 1869.);

  // These are the quantities that you will create and make plots from

  TLorentzVector KStar;
  TLorentzVector PK;
  TLorentzVector PPi1;
  TLorentzVector PPi2;

  // This is a loop over each D meson
  // For debugging use thousand events of D meson
  // You can increase to a million at the end to get good looking plots

  for(int event = 0; event < 1000000; event++) {

    // Let correct fraction of D-mesons decay to K*,pi i.e., in two-body
    // using uniform distribution and appropriate if statement

    {

      // For K*,pi decay choose 4-momenta, PKStar, PPi1 using random numbers
      // satisfying kinematic constraints such that they come from D-Decay
      
      // Let K* decay to K,pi, Set PK and PPi2 using random numbers satisfying
      // kinematic constraints such that they come from K*-meson
      
    }

    // Let correct fraction of D-mesons decay to K,pi,pi i.e., in three-body
    // using uniform distribution and appropriate if statement
    
    {

      // Fill in three-body decay kinematics code to chose PK, PPi1, PPi2
      // using random numbers respecting the kinematic constraints

    }

    // Smear PK, PPi1, PPi2 by detector resolution
    // Use gaussian smearing 

    // Compute the Dalitz plot quantities
    // Define appropriate variables to put them in

    // Fill plots 

    // Test code to make random number distributions

    poissonDistribution->Fill(random->Poisson(50.));
    normalDistribution->Fill(random->Gaus(50., 10.));
    uniformDistribution->Fill(random->Uniform(100.));
    
  }

  // Plot each histogram
  // Make a new canvas so all the histograms are still visible
  // after the command completes

  TCanvas *poissonCanvas = new TCanvas();
  poissonDistribution->Draw();
  poissonCanvas->SaveAs("poisson.png");
  TCanvas *normalCanvas = new TCanvas();
  normalDistribution->Draw();
  normalCanvas->SaveAs("normal.png");
  TCanvas *uniformCanvas = new TCanvas();
  uniformDistribution->Draw();
  uniformCanvas->SaveAs("uniform.png");

}
