//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file hadronic/Hadr03/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// $Id: DetectorConstruction.cc 70755 2013-06-05 12:17:48Z ihrivnac $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
//#include "DetectorMessenger.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fMaterial(0), fLAbsor(0), fLGround(0), fLGroundp(0), fWorldMat(0),
 // fPWorld(0), fDetectorMessenger(0),
 fPWorld(0), 
 fCheckOverlaps(true)
{
  fRadius = 3.39e3*km; //
  fWorldSize = (fRadius+150.*km); 
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{

  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Si");
  GroundMars = G4Material::GetMaterial("G4_Si");
  GroundMars->SetName("GroundMars");
  
  // example of vacuum
  fWorldMat = new G4Material("Galactic", 1, 1.01*g/mole, universe_mean_density,
                 kStateGas, 2.73*kelvin, 3.e-18*pascal);
                   
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::MaterialWithSingleIsotope( G4String name,
                           G4String symbol, G4double density, G4int Z, G4int A)
{
 // define a material from an isotope
 //
 G4int ncomponents;
 G4double abundance, massfraction;

 G4Isotope* isotope = new G4Isotope(symbol, Z, A);
 
 G4Element* element  = new G4Element(name, symbol, ncomponents=1);
 element->AddIsotope(isotope, abundance= 100.*perCent);
 
 G4Material* material = new G4Material(name, density, ncomponents=1);
 material->AddElement(element, massfraction=100.*perCent);

 return material;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  // World
  //
  G4Box*
  sWorld = new G4Box("World",                           //name
                   fWorldSize/2.,fWorldSize/2.,fWorldSize);   //dimensions
                   
  G4LogicalVolume*
  lWorld = new G4LogicalVolume(sWorld,                  //shape
                             fWorldMat,                 //material
                             "WorldLV");                  //name

  fPWorld = new G4PVPlacement(0,                        //no rotation
			    G4ThreeVector(),  //at (0,0,0)
                            lWorld,                     //logical volume
                            "WorldPV",                    //name
                            0,                          //mother volume
                            false,                      //no boolean operation
			      0);                         //copy number
                           
  lWorld->SetVisAttributes (G4VisAttributes::Invisible);
  
  // AirMars
  //
  
  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);

  G4Material* elAr = man->FindOrBuildMaterial("G4_Ar");
  G4Material* gasCO2 = man->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  G4Material* gasO2 = man->FindOrBuildMaterial("G4_O");
  G4Material* gasN2 = man->FindOrBuildMaterial("G4_N");
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  
  G4int nLayers=150;
  G4double altStep = 150.*km/nLayers;
  G4double alt1, alt2;
  G4int ncomponents;
  G4String name, nameLV, namePV, sLayer;
  double fractionmass;
  G4double density = 1.290*mg/cm3*0.01;  // air scaled by 0.01(?)
  G4double temperature = 280*kelvin; // ??
  G4double pressure = 0.006*bar; // ?? currently not used
  G4Material *AirMars[150];
  G4Sphere *sAirMars[150];
  G4LogicalVolume *AirMarsLV[150];
  G4VisAttributes *airMars[150];
  
  for (int layerN=0; layerN<nLayers; layerN++) { // volumes with changing density
  
  sLayer = G4UIcommand::ConvertToString(layerN);
  name="AirMars"+sLayer;
  nameLV="AirMarsLV"+sLayer;
  namePV="AirMarsPV"+sLayer;

  alt1 = layerN*altStep;
  alt2 += altStep;
  AirMars[layerN] = new G4Material(name,density*exp(-alt1/km*0.1),ncomponents=4,kStateGas,temperature);
  // *** density and temperature to be correct functions of altitude !
  AirMars[layerN]->AddMaterial(gasN2, fractionmass=2.7*perCent);
  AirMars[layerN]->AddMaterial(gasO2, fractionmass=0.13*perCent);
  AirMars[layerN]->AddMaterial(elAr, fractionmass=1.85*perCent);
  AirMars[layerN]->AddMaterial(gasCO2, fractionmass=95.32*perCent);
  // *** % to correct !

  G4cout<<layerN<<": "<<alt1/km<<"-"<<alt2/km<<" km  dens="<<density*exp(-alt1/km*0.1)/(mg/cm3)<<" mg/cm3"<<G4endl;
  
  sAirMars[layerN] = new G4Sphere(name,                     //name
		     fRadius+alt1, fRadius+alt2, 0., twopi, 0., pi/8.);   //dimensions

  AirMarsLV[layerN] = new G4LogicalVolume(
			     sAirMars[layerN],                  //shape
                             AirMars[layerN],                 //material
                             nameLV);     //name
                               
           new G4PVPlacement(0,                         //no rotation
                            G4ThreeVector(),  //at (0,0,0)
                           AirMarsLV[layerN],                     //logical volume
			   namePV,        //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
			       0);                          //copy number
                             
  airMars[layerN]= new G4VisAttributes( // reducing brightnees with altitude
	 G4Colour(0.4*exp(-alt1/km*0.015),0.1*exp(-alt1/km*0.015),1.0*exp(-alt1/km*0.015))); 
  airMars[layerN]->SetVisibility(true);
  AirMarsLV[layerN]->SetVisAttributes(airMars[layerN]);
  
  } // end of volume density cycle
  
  // Ground
  //
  G4Sphere* 
  sGround = new G4Sphere("GroundMars",                     //name
            fRadius-1.*km, fRadius, 0., twopi, 0., pi/10.);   //dimensions
  // 1m thickness for Mars ground:
  // non-zero to prevent passing protons through
  // but not thick to prevent CPU waist for simulation underground

  fLGround = new G4LogicalVolume(sGround,                  //shape
                             GroundMars,                 //material
                             "GroundMarsLV");     //name
                               
           new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(),             //at (0,0,0)
                           fLGround,                     //logical volume
			     "GroundMarsPV",        //name
			     //lWorld,                      //mother  volume
			     //fLAbsor,                      //mother  volume
			     AirMarsLV[0],                      //mother  volume
                           false,                       //no boolean operation
			       0);                          //copy number
	   //0,                // copy number
	       //fCheckOverlaps);  // checking overlaps

  // Visualization attributes
  //
  
  G4VisAttributes* groundMars= new G4VisAttributes(G4Colour(0.9,0.2,0.2)); //redish
  groundMars->SetVisibility(true);
  fLGround->SetVisAttributes(groundMars);
  
  //always return the root volume
  //

  return fPWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetRadius(G4double value)
{
  fRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

