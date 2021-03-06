#include "TimingDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

TimingDetectorConstruction::TimingDetectorConstruction()
  : G4VUserDetectorConstruction(),
    fScoringVolume1(0),
    fScoringVolume2(0)
{ 
  DefineMaterials();
}

TimingDetectorConstruction::~TimingDetectorConstruction()
{ }

void TimingDetectorConstruction::DefineMaterials()
{
  G4double a, z, density;
  G4Element*  O = new G4Element("Oxygen",   "O",  z= 8., a= 16.00*g/mole);
  G4Element* Lu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* Si = new G4Element("Silicon",  "Si", z=14., a= 28.09*g/mole);
  G4Element* H  = new G4Element("Hydrogen" ,"H" , 1.,  1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"   ,"C" , 6., 12.00*g/mole);

  G4Material* plastic = 
    new G4Material("plastic", 1.0*g/cm3, 2);
  plastic->AddElement(H, 1);
  plastic->AddElement(C, 1);


  G4Material* LYSO = new G4Material("LYSO", density=7.1*g/cm3,3,kStateSolid);
  LYSO->AddElement(Lu, 2);
  LYSO->AddElement(Si, 1);
  LYSO->AddElement(O,  5);

  
  const G4int nEntries_FAST = 261;

  G4double PhotonEnergy_FAST[nEntries_FAST] = 
    { 1.77169*eV, 1.77266*eV, 1.77558*eV, 1.77851*eV, 1.78145*eV, 1.78539*eV, 1.79033*eV, 1.7963*eV, 1.80231*eV, 1.80836*eV,
      1.81445*eV, 1.82058*eV, 1.82882*eV, 1.83401*eV, 1.84553*eV, 1.85293*eV, 1.86147*eV, 1.869*eV, 1.87769*eV, 1.89308*eV,
      1.90536*eV, 1.92007*eV, 1.93039*eV, 1.94901*eV, 1.95846*eV, 1.9668*eV, 1.97884*eV, 1.99102*eV, 2.00088*eV, 2.01209*eV,
      2.02596*eV, 2.03617*eV, 2.04519*eV, 2.0569*eV, 2.06611*eV, 2.0794*eV, 2.09151*eV, 2.10239*eV, 2.112*eV, 2.1231*eV,
      2.13431*eV, 2.14565*eV, 2.15566*eV, 2.16868*eV, 2.18038*eV, 2.19519*eV, 2.21171*eV, 2.2193*eV, 2.23619*eV, 2.23464*eV,
      2.24395*eV, 2.25806*eV, 2.27234*eV, 2.28358*eV, 2.29493*eV, 2.30475*eV, 2.31631*eV, 2.32463*eV, 2.33134*eV, 2.33809*eV,
      2.34487*eV, 2.35856*eV, 2.36719*eV, 2.37939*eV, 2.38642*eV, 2.40238*eV, 2.41134*eV, 2.424*eV, 2.43312*eV, 2.44047*eV,
      2.44786*eV, 2.46278*eV, 2.47788*eV, 2.48741*eV, 2.49317*eV, 2.49702*eV, 2.50282*eV, 2.50865*eV, 2.5145*eV, 2.52038*eV,
      2.52432*eV, 2.53223*eV, 2.5362*eV, 2.54619*eV, 2.55424*eV, 2.56031*eV, 2.56437*eV, 2.57049*eV, 2.57663*eV, 2.58487*eV,
      2.59317*eV, 2.59734*eV, 2.60571*eV, 2.61414*eV, 2.61414*eV, 2.61837*eV, 2.62262*eV, 2.62475*eV, 2.62902*eV, 2.63331*eV,
      2.63545*eV, 2.63976*eV, 2.64191*eV, 2.64841*eV, 2.65493*eV, 2.6593*eV, 2.66149*eV, 2.66588*eV, 2.67914*eV, 2.67914*eV,
      2.68136*eV, 2.68136*eV, 2.68359*eV, 2.68805*eV, 2.68805*eV, 2.68805*eV, 2.69477*eV, 2.69477*eV, 2.69702*eV, 2.70153*eV,
      2.70605*eV, 2.71286*eV, 2.71742*eV, 2.71971*eV, 2.722*eV, 2.722*eV, 2.72429*eV, 2.72889*eV, 2.72889*eV, 2.73351*eV,
      2.73814*eV, 2.74279*eV, 2.74512*eV, 2.74979*eV, 2.75213*eV, 2.75447*eV, 2.75917*eV, 2.75682*eV, 2.76389*eV, 2.76626*eV,
      2.76389*eV, 2.76626*eV, 2.77338*eV, 2.77576*eV, 2.78533*eV, 2.79255*eV, 2.79738*eV, 2.80223*eV, 2.80466*eV, 2.80709*eV,
      2.80953*eV, 2.80953*eV, 2.81934*eV, 2.8218*eV, 2.82673*eV, 2.83168*eV, 2.84164*eV, 2.84916*eV, 2.85419*eV, 2.8643*eV,
      2.86684*eV, 2.87449*eV, 2.87705*eV, 2.87961*eV, 2.88475*eV, 2.88733*eV, 2.8925*eV, 2.89509*eV, 2.90028*eV, 2.90549*eV,
      2.90811*eV, 2.91073*eV, 2.91335*eV, 2.91335*eV, 2.91335*eV, 2.91861*eV, 2.92125*eV, 2.92125*eV, 2.92389*eV, 2.92654*eV,
      2.92654*eV, 2.92919*eV, 2.92919*eV, 2.93185*eV, 2.93451*eV, 2.93717*eV, 2.93985*eV, 2.94252*eV, 2.9452*eV, 2.94789*eV,
      2.94789*eV, 2.94789*eV, 2.95058*eV, 2.95868*eV, 2.96411*eV, 2.96955*eV, 2.97228*eV, 2.97228*eV, 2.96955*eV, 2.97228*eV,
      2.97502*eV, 2.97776*eV, 2.97502*eV, 2.9805*eV, 2.9805*eV, 2.9805*eV, 2.98601*eV, 2.99154*eV, 2.99431*eV, 2.99431*eV,
      2.99708*eV, 2.99431*eV, 2.99708*eV, 3.00544*eV, 3.00824*eV, 3.00824*eV, 3.00824*eV, 3.00824*eV, 3.01385*eV, 3.0223*eV,
      3.02797*eV, 3.03081*eV, 3.02797*eV, 3.03365*eV, 3.03081*eV, 3.03081*eV, 3.0365*eV, 3.03935*eV, 3.04221*eV, 3.04795*eV,
      3.04795*eV, 3.05083*eV, 3.05371*eV, 3.05949*eV, 3.06239*eV, 3.06529*eV, 3.0682*eV, 3.06529*eV, 3.07112*eV, 3.0682*eV,
      3.07696*eV, 3.08283*eV, 3.0976*eV, 3.09464*eV, 3.09464*eV, 3.10653*eV, 3.11252*eV, 3.11852*eV, 3.12757*eV, 3.13668*eV,
      3.14583*eV, 3.15813*eV, 3.16741*eV, 3.17675*eV, 3.20828*eV, 3.23719*eV, 3.26664*eV, 3.28656*eV, 3.31351*eV, 3.34783*eV,
      3.38287*eV };

  G4double FastComponent[nEntries_FAST] = 
    { 0.011691, 0.011691, 0.011691, 0.0146138, 0.0146138, 0.0146138, 0.011691, 0.011691, 0.00876827, 0.00876827,
      0.00584551, 0.00584551, 0.00584551, 0.00292276, 0.00876827, 0.0146138, 0.0146138, 0.0146138, 0.0204593, 0.023382,
      0.0263048, 0.0204593, 0.0204593, 0.023382, 0.0292276, 0.0321503, 0.0350731, 0.0379958, 0.0379958, 0.0379958,
      0.0350731, 0.0379958, 0.0409186, 0.0438413, 0.0526096, 0.0584551, 0.0643006, 0.0730689, 0.0730689, 0.0818372,
      0.0906054, 0.0964509, 0.0993737, 0.105219, 0.111065, 0.122756, 0.125678, 0.146138, 0.146138, 0.160752,
      0.157829, 0.163674, 0.184134, 0.192902, 0.20167, 0.219207, 0.230898, 0.242589, 0.25428, 0.265971,
      0.274739, 0.292276, 0.306889, 0.315658, 0.321503, 0.350731, 0.368267, 0.385804, 0.397495, 0.415031,
      0.432568, 0.458873, 0.482255, 0.496868, 0.514405, 0.529019, 0.549478, 0.564092, 0.581628, 0.593319,
      0.602088, 0.616701, 0.637161, 0.660543, 0.681002, 0.71023, 0.736534, 0.756994, 0.777453, 0.806681,
      0.844676, 0.868058, 0.891441, 0.9119, 0.938205, 0.955741, 0.984969, 1.0142, 1.03173, 1.05511,
      1.07557, 1.11649, 1.13695, 1.15741, 1.17495, 1.19248, 1.21002, 1.22756, 1.27432, 1.2977,
      1.31524, 1.32985, 1.36785, 1.40292, 1.39415, 1.4, 1.41754, 1.44092, 1.47015, 1.48476,
      1.50814, 1.5286, 1.54906, 1.56952, 1.58998, 1.61921, 1.63967, 1.66597, 1.68935, 1.71566,
      1.73904, 1.76242, 1.77996, 1.80042, 1.8238, 1.83549, 1.85303, 1.8618, 1.87933, 1.89979,
      1.91733, 1.92902, 1.95825, 1.98163, 2.01378, 2.03424, 2.0547, 2.07808, 2.09562, 2.11023,
      2.12484, 2.13361, 2.15407, 2.15699, 2.15992, 2.16576, 2.16868, 2.16868, 2.16284, 2.15699,
      2.14823, 2.13946, 2.12484, 2.11023, 2.08977, 2.06639, 2.04593, 2.02839, 2.01086, 1.98455,
      1.96409, 1.94948, 1.93194, 1.91733, 1.90271, 1.87641, 1.86472, 1.8501, 1.83841, 1.82088,
      1.79749, 1.77119, 1.75073, 1.73027, 1.70689, 1.68058, 1.65428, 1.6309, 1.60167, 1.57244,
      1.55491, 1.53152, 1.50522, 1.47891, 1.45261, 1.43215, 1.40877, 1.38831, 1.362, 1.33862,
      1.31232, 1.28601, 1.27432, 1.25678, 1.21587, 1.19541, 1.17203, 1.14864, 1.12234, 1.10772,
      1.08434, 1.06096, 1.0142, 0.987891, 0.967432, 0.938205, 0.9119, 0.879749, 0.853445, 0.82714,
      0.786221, 0.765762, 0.739457, 0.716075, 0.681002, 0.660543, 0.637161, 0.60501, 0.581628, 0.552401,
      0.531942, 0.505637, 0.485177, 0.458873, 0.435491, 0.412109, 0.379958, 0.356576, 0.336117, 0.309812,
      0.280585, 0.25428, 0.207516, 0.175365, 0.157829, 0.13737, 0.119833, 0.0993737, 0.0759916, 0.0613779,
      0.0526096, 0.0350731, 0.0263048, 0.011691, 0.00876827, 0.00876827, 0.011691, 0.011691, 0.011691, 0.00876827,
      0.011691 };
  
  const G4int nEntries_RI = 3;
  G4double PhotonEnergy_RI[nEntries_RI] =
    { 1.0*eV, 1.84*eV, 4.5*eV};
  G4double RefractiveIndex[nEntries_RI] =
    { 1.82, 1.82, 1.82};
  
  const G4int nEntries_ABS = 9;
  G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 1.00*eV , 2.82*eV , 2.88*eV , 2.95*eV , 3.02*eV  , 3.10*eV  , 3.18*eV  , 3.26*eV , 4.08*eV };
  G4double Absorption[nEntries_ABS] =
    { 438.*mm , 438.*mm , 413.*mm , 375.*mm , 263.*mm  , 87.5*mm  , 11.5*mm  , 1.0*mm  , 1.0*mm  };
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("FASTCOMPONENT", PhotonEnergy_FAST, FastComponent,  nEntries_FAST);
  myMPT->AddProperty("RINDEX",        PhotonEnergy_RI,   RefractiveIndex, nEntries_RI);
  myMPT->AddProperty("ABSLENGTH",     PhotonEnergy_ABS,  Absorption,      nEntries_ABS);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",40000./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",3.4);
  myMPT->AddConstProperty("FASTTIMECONSTANT",40.*ns);
  myMPT->AddConstProperty("YIELDRATIO",1.0);
  myMPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.1*ns);
  
  LYSO->SetMaterialPropertiesTable(myMPT);
}

G4VPhysicalVolume* TimingDetectorConstruction::Construct()
{  
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;
  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // -----------------------------------
  // World
  G4double world_sizeXY = 50*cm;
  G4double world_sizeZ  = 50*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
	      0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
  
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     

  // ------------------------------------  
  // Distance source / pixel-bar
  G4double ring  = 2*cm;           

  // ------------------------------------  
  // Crystal
  G4Material* cryst_mat = nist->FindOrBuildMaterial("LYSO");
  G4double cryst_dX = 3*mm, cryst_dY = 3*mm, cryst_dZ = 3*mm; 
  
  G4Box* solidCryst = new G4Box("crystal", cryst_dX/2, cryst_dY/2, cryst_dZ/2);
  G4LogicalVolume* logicCryst = 
    new G4LogicalVolume(solidCryst,          //its solid
                        cryst_mat,           //its material
			"CrystalLV");        //its name
  
  G4RotationMatrix rotmC  = G4RotationMatrix();
  rotmC.rotateY(90*deg); 
  rotmC.rotateZ(0*deg);
  G4ThreeVector uzC = G4ThreeVector(std::cos(0*deg), std::sin(0*deg),0.);     
  G4ThreeVector positionC = (ring+0.5*cryst_dZ)*uzC;
  G4Transform3D transformC = G4Transform3D(rotmC,positionC);
  
  new G4PVPlacement(transformC,             // rotation,position
		    logicCryst,             // its logical volume
		    "crystal",              // its name
		    logicWorld,             // its mother  volume
		    false,                  // no boolean operation
		    0,                      // copy number
		    checkOverlaps);         // checking overlaps 

  // ------------------------------------  
  // Bar
  G4double bar_dX = 5.7*cm, bar_dY = 3.*mm, bar_dZ = 3.*mm;        // chiara

  G4Box* solidBar = new G4Box("bar", bar_dX/2, bar_dY/2, bar_dZ/2);
                     
  G4LogicalVolume* logicBar = new G4LogicalVolume(solidBar, cryst_mat, "BarLV");        
               
  G4RotationMatrix rotmB  = G4RotationMatrix();
  rotmB.rotateY(90*deg); 
  rotmB.rotateZ(180*deg);
  G4ThreeVector uzB = G4ThreeVector(std::cos(180*deg), std::sin(180*deg),0.);     
  G4ThreeVector positionB = (ring+0.5*bar_dZ)*uzB;
  G4Transform3D transformB = G4Transform3D(rotmB,positionB);
                                    
  new G4PVPlacement(transformB, logicBar, "bar", logicWorld, false, 1, checkOverlaps); 

  // ------------------------------------  
  // Source containter
  G4Material* plastic_mat = nist->FindOrBuildMaterial("plastic");
  G4double source_radius = 10*mm,  source_dZ = 3.*mm;        
  G4Tubs* source = new G4Tubs("source", 0, source_radius, source_dZ/2, 0, 2*M_PI);
  G4LogicalVolume* logicSource = new G4LogicalVolume(source, plastic_mat, "SourceLV");        
               
  G4RotationMatrix rotmD  = G4RotationMatrix();
  rotmD.rotateY(90*deg); 
  rotmD.rotateZ(180*deg);
  G4ThreeVector positionD(0,0,0);
  G4Transform3D transformD = G4Transform3D(rotmD,positionD);
                                    
  new G4PVPlacement(transformD, logicSource, "source", logicWorld, false, 1, checkOverlaps); 


  // --------------------------------------------------
  // Set crystals scoring volume
  fScoringVolume1 = logicBar;      
  fScoringVolume2 = logicCryst;      
  
  //always return the physical World
  return physWorld;
}
