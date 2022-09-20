#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include "ns3/nr-helper.h"
#include "ns3/log.h"
#include "ns3/nr-point-to-point-epc-helper.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/nr-mac-scheduler-tdma-rr.h"
#include "ns3/nr-module.h"
#include <ns3/buildings-module.h>
#include "ns3/antenna-module.h"
#include <ns3/string.h>
#include <fstream>

using namespace ns3;

int
main (int argc, char *argv[])
{
  std::string remMode = "CoverageArea";
  std::string simTag = "";

  std::string scenario = "InH-OfficeOpen_LoS"; //scenario
  std::string beamforming = "search-omni"; //beamforming at gNB and UE, the first is gNB and the second is UE
  enum BandwidthPartInfo::Scenario scenarioEnum = BandwidthPartInfo::UMa;

  uint16_t gNbNum = 1;
  uint16_t ueNumPergNb = 1;
  std::string deploymentScenario = "3_Sector";
  std::string typeOfRem = "DlRem";
  std::string errorModel = "ns3::NrEesmCcT1";
  std::string outputDir = "./";

  std::string lambda = "0.25";
  uint32_t packetSize = 125;
  double appStartTime = 0.01;
  bool useDl = true;
  bool useUl = false;

  double gNB1x;
  double gNB1y;
  double gNB2x;
  double gNB2y;
  double gNB3x;
  double gNB3y;

  double ue1x = 35;
  double ue1y = 25;
  double ue2x = 35.01;
  double ue2y = 25.01;
  double ue3x = 35.02;
  double ue3y = 25.02;

  double offset = 0.01;
  double offset2 = 1;
  double offset3 = 1;


  double frequency = 24.3e9;//28e9
  double bandwidth = 200e6; //100e6
  uint16_t numerology = 2;
  double txPower = 5; //4

  //Antenna Parameters
  double hBS;   //Depend on the scenario (no input parameters)
  double hUT;
  uint32_t numRowsUe = 1; //2
  uint32_t numColumnsUe = 1; //2
  uint32_t numRowsGnb = 1; //4
  uint32_t numColumnsGnb = 1; //4
  bool isoUe = true;
  bool isoGnb = false; //false

  double simTime = 1; // in seconds
  bool logging = false;
  bool enableTraces = false;

  //building parameters in case of buildings addition
  bool enableBuildings = false; //Depends on the scenario (no input parameter)
  uint32_t numOfBuildings = 1;
  uint32_t apartmentsX = 2;
  uint32_t nFloors = 1;

  //Rem parameters
  double xMin = 0;
  double xMax = 70;
  uint16_t xRes = 210;
  double yMin = 0;
  double yMax = 50.0;
  uint16_t yRes = 150;
  double z = 3;
  
  CommandLine cmd;
  cmd.AddValue ("outputDir",
                "Output directory",
                outputDir);  
  cmd.AddValue ("remMode",
                "What type of REM map to use: BeamShape, CoverageArea, UeCoverage."
                "BeamShape shows beams that are configured in a user's script. "
                "Coverage area is used to show worst-case SINR and best-case SNR maps "
                "considering that at each point of the map the best beam is used "
                "towards that point from the serving gNB and also of all the interfering"
                "gNBs in the case of worst-case SINR."
                "UeCoverage is similar to the previous, just that it is showing the "
                "uplink coverage.",
                remMode);
  cmd.AddValue ("simTag",
                "Simulation string tag that will be concatenated to output file names",
                simTag);
  cmd.AddValue ("scenario",
                "The scenario for the simulation. Choose among 'RMa', 'UMa', "
                "'UMi-StreetCanyon', 'InH-OfficeMixed', 'InH-OfficeOpen'"
                "'UMa-Buildings', 'UMi-Buildings'.",
                scenario);
  cmd.AddValue ("gNbNum",
                "The number of gNbs in multiple-ue topology",
                gNbNum);
  cmd.AddValue ("ueNumPergNb",
                "The number of UE per gNb in multiple-ue topology",
                ueNumPergNb);
  cmd.AddValue ("gNB1x",
                "gNb 1 x position",
                gNB1x);
  cmd.AddValue ("gNB1y",
                "gNb 1 y position",
                gNB1y);
  cmd.AddValue ("gNB2x",
                "gNb 2 x position",
                gNB2x);
  cmd.AddValue ("gNB2y",
                "gNb 2 y position",
                gNB2y);
  cmd.AddValue ("gNB3x",
                "gNb 3 x position",
                gNB3x);
  cmd.AddValue ("gNB3y",
                "gNb 3 y position",
                gNB3y);
  cmd.AddValue ("ue1x",
                "ue 1 x position",
                ue1x);
  cmd.AddValue ("ue1y",
                "ue 1 y position",
                ue1y);
  cmd.AddValue ("ue2x",
                "ue 2 x position",
                ue2x);
  cmd.AddValue ("ue2y",
                "ue 2 y position",
                ue2y);
  cmd.AddValue ("ue3x",
                  "ue 3 x position",
                  ue3x);
  cmd.AddValue ("ue3y",
                  "ue 3 y position",
                  ue3y);
  cmd.AddValue ("deploymentScenario",
                "The deployment scenario for the simulation. Choose among "
                "'SingleGnb', 'TwoGnbs'.",
                deploymentScenario);
  cmd.AddValue ("typeOfRem",
                "The type of Rem to generate (DL or UL) in the case of BeamShape option. Choose among "
                "'DlRem', 'UlRem'.",
                typeOfRem);
  cmd.AddValue ("frequency",
                "The central carrier frequency in Hz.",
                frequency);
  cmd.AddValue ("bandwidth",
                "The system bandwidth to be used",
                bandwidth);
  cmd.AddValue ("numerology",
                "The numerology to be used",
                numerology);
  cmd.AddValue ("txPower",
                "total tx power that will be proportionally assigned to"
                " bands, CCs and bandwidth parts depending on each BWP bandwidth ",
                txPower);
  cmd.AddValue ("numRowsUe",
                "Number of rows for the UE antenna",
                numRowsUe);
  cmd.AddValue ("numColumnsUe",
                "Number of columns for the UE antenna",
                numColumnsUe);
  cmd.AddValue ("isoUe",
                "If true (set to 1), use an isotropic radiation pattern in the Ue ",
                isoUe);
  cmd.AddValue ("numRowsGnb",
                "Number of rows for the gNB antenna",
                numRowsGnb);
  cmd.AddValue ("numColumnsGnb",
                "Number of columns for the gNB antenna",
                numColumnsGnb);
  cmd.AddValue ("isoGnb",
                "If true (set to 1), use an isotropic radiation pattern in the gNB ",
                isoGnb);
  cmd.AddValue ("numOfBuildings",
                "The number of Buildings to deploy in the scenario",
                numOfBuildings);
  cmd.AddValue ("apartmentsX",
                "The number of apartments inside a building",
                apartmentsX);
  cmd.AddValue ("nFloors",
                "The number of floors of a building",
                nFloors);
  cmd.AddValue ("beamforming",
                "If dir-dir configure direct-path at both gNB and UE; "
                "if dir-omni configure direct-path at gNB and quasi-omni at UE;"
                "if omni-dir configure quasi-omni at gNB and direct-path at UE;",
                beamforming);
  cmd.AddValue ("logging",
                "Enable logging"
                "another option is by exporting the NS_LOG environment variable",
                logging);
  cmd.AddValue ("xMin",
                "The min x coordinate of the rem map",
                xMin);
  cmd.AddValue ("xMax",
                "The max x coordinate of the rem map",
                xMax);
  cmd.AddValue ("xRes",
                "The resolution on the x axis of the rem map",
                xRes);
  cmd.AddValue ("yMin",
                "The min y coordinate of the rem map",
                yMin);
  cmd.AddValue ("yMax",
                "The max y coordinate of the rem map",
                yMax);
  cmd.AddValue ("yRes",
                "The resolution on the y axis of the rem map",
                yRes);
  cmd.AddValue ("z",
                "The z coordinate of the rem map",
                z);

  cmd.Parse (argc, argv);

  // enable logging
  if (logging)
    {
      //LogComponentEnable ("ThreeGppSpectrumPropagationLossModel", LOG_LEVEL_ALL);
      LogComponentEnable ("ThreeGppPropagationLossModel", LOG_LEVEL_ALL);
      //LogComponentEnable ("ThreeGppChannelModel", LOG_LEVEL_ALL);
      //LogComponentEnable ("ChannelConditionModel", LOG_LEVEL_ALL);
      //LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
      //LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);
      //LogComponentEnable ("LteRlcUm", LOG_LEVEL_LOGIC);
      //LogComponentEnable ("LtePdcp", LOG_LEVEL_INFO);
    }

  /*
   * Default values for the simulation. We are progressively removing all
   * the instances of SetDefault, but we need it for legacy code (LTE)
   */
  Config::SetDefault ("ns3::LteRlcUm::MaxTxBufferSize", UintegerValue (999999999));

  // set mobile device and base station antenna heights in meters, according to the chosen scenario
  if (scenario.compare ("RMa") == 0)
    {
      hBS = 35;
      hUT = 1.5;
      scenarioEnum = BandwidthPartInfo::RMa;
    }
  else if (scenario.compare ("UMa") == 0)
    {
      //hBS = 25;
      hBS = 1.5;
      hUT = 1.5;
      scenarioEnum = BandwidthPartInfo::UMa;
    }
  else if (scenario.compare ("UMa-Buildings") == 0)
    {
      hBS = 1.5; // 25
      hUT = 1.5;
      scenarioEnum = BandwidthPartInfo::UMa_Buildings;
      enableBuildings = true;
    }
  else if (scenario.compare ("UMi-StreetCanyon") == 0)
    {
      hBS = 10;
      hUT = 1.5;
      scenarioEnum = BandwidthPartInfo::UMi_StreetCanyon;
    }
  else if (scenario.compare ("UMi-Buildings") == 0)
    {
      hBS = 10;
      hUT = 1.5;
      scenarioEnum = BandwidthPartInfo::UMi_Buildings;
      enableBuildings = true;
    }
  else if (scenario.compare ("InH-OfficeMixed") == 0)
    {
      hBS = 3;
      hUT = 1;
      scenarioEnum = BandwidthPartInfo::InH_OfficeMixed;
    }
  else if (scenario.compare ("InH-OfficeOpen") == 0)
    {
      hBS = 3;
      hUT = 1;
      scenarioEnum = BandwidthPartInfo::InH_OfficeOpen;
    }   
  else if (scenario.compare ("InH-OfficeOpen_LoS") == 0)
    {
      hBS = 3;
      hUT = 1;
      scenarioEnum = BandwidthPartInfo::InH_OfficeOpen_LoS;
    }
  else if (scenario.compare ("InH-OfficeOpen_nLoS") == 0)
    {
      hBS = 3;
      hUT = 1;
      scenarioEnum = BandwidthPartInfo::InH_OfficeOpen_nLoS;
    }  
  else
    {
      NS_ABORT_MSG ("Scenario not supported. Choose among 'RMa', 'UMa', "
                    "'UMi-StreetCanyon', 'InH-OfficeMixed', 'InH-OfficeOpen',"
                    "'UMa-Buildings', and 'UMi-Buildings'.");
    }
  
  if (deploymentScenario.compare ("3_OmniLine") == 0)
    {
      gNbNum = 3;
      ueNumPergNb = 1;
    }
  else if (deploymentScenario.compare ("3_Sector") == 0)
    {
      gNbNum = 3;
      ueNumPergNb = 1;
    }
  else if (deploymentScenario.compare ("4_OmniLine") == 0)
    {
      gNbNum = 4;
      ueNumPergNb = 1;
    }  
  else if (deploymentScenario.compare ("SquareInside") == 0)
    {
      gNbNum = 4;
      ueNumPergNb = 1;
    }  
  else if (deploymentScenario.compare ("AllCorners") == 0)
    {
      gNbNum = 4;
      ueNumPergNb = 1;
    } 

  else
    {
      NS_ABORT_MSG ("Deployment scenario not supported. "
                    "Choose among 'SingleGnb', 'TwoGnbs'.");
    }

  // create base stations and mobile terminals
  NodeContainer gnbNodes;
  NodeContainer ueNodes;
  gnbNodes.Create (gNbNum);
  ueNodes.Create (ueNumPergNb * gNbNum);

  // position the base stations
  Ptr<ListPositionAllocator> gnbPositionAlloc = CreateObject<ListPositionAllocator> ();
  if (deploymentScenario.compare ("3_OmniLine") == 0){
	  isoGnb = true;
	  gNB1x = 17.5;
	  gNB1y = 25.0;
	  gNB2x = 35.0;
	  gNB2y = 25.0;
      gNB3x = 52.5;
  	  gNB3y = 25.0;

   	  // position the base stations
   	  gnbPositionAlloc->Add (Vector (gNB1x, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x, gNB2y, hBS));
      gnbPositionAlloc->Add (Vector (gNB3x, gNB3y, hBS));
    }
  else if (deploymentScenario.compare ("3_Sector") == 0){
  	  gNB1x = 35.0;
  	  gNB1y = 25.0;
  	  gNB2x = 35.0;
  	  gNB2y = 25.0;
  	  gNB3x = 35.0;
  	  gNB3y = 25.0;

  	  offset2 = 0.01;
  	  offset3 = 0.02;

  	  // position the base stations
  	  gnbPositionAlloc->Add (Vector (gNB1x, gNB1y, hBS));
  	  gnbPositionAlloc->Add (Vector (gNB2x+offset2, gNB2y, hBS));
  	  gnbPositionAlloc->Add (Vector (gNB3x+offset3, gNB3y, hBS));
    }
  else if (deploymentScenario.compare ("4_OmniLine") == 0){
	  isoGnb = true;
      gNB1x = 14.0;
      gNB1y = 25.0;
      gNB2x = 28.0;
      gNB2y = 25.0;

      offset = 28.0;

      // position the base stations
   	  gnbPositionAlloc->Add (Vector (gNB1x, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x, gNB2y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB1x+offset, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x+offset, gNB2y, hBS));
    }
  else if (deploymentScenario.compare ("SquareInside") == 0){
	  isoGnb = true;
      gNB1x = 23.33;
      gNB1y = 16.66;
      gNB2x = 23.66;
      gNB2y = 33.33;

      offset = 23.33;

      // position the base stations
   	  gnbPositionAlloc->Add (Vector (gNB1x, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x, gNB2y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB1x+offset, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x+offset, gNB2y, hBS));
    }
  else if (deploymentScenario.compare ("AllCorners") == 0){
	  gNB1x = 0.1;
      gNB1y = 0.1;
      gNB2x = 0.1;
      gNB2y = 49.9;

      offset = 68.8;

      // position the base stations
   	  gnbPositionAlloc->Add (Vector (gNB1x, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x, gNB2y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB1x+offset, gNB1y, hBS));
   	  gnbPositionAlloc->Add (Vector (gNB2x+offset, gNB2y, hBS));
    }

  MobilityHelper gnbMobility;
  gnbMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  gnbMobility.SetPositionAllocator (gnbPositionAlloc);
  gnbMobility.Install (gnbNodes);

  // position the mobile terminals
  MobilityHelper ueMobility;
  ueMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  ueMobility.Install (ueNodes);

  ueNodes.Get (0)->GetObject<MobilityModel> ()->SetPosition (Vector (ue1x, ue1y, hUT));
  if ((deploymentScenario.compare ("3_OmniLine") == 0) or (deploymentScenario.compare ("3_Sector") == 0))
    {
      ueNodes.Get (1)->GetObject<MobilityModel> ()->SetPosition (Vector (ue2x, ue2y, hUT));
      ueNodes.Get (2)->GetObject<MobilityModel> ()->SetPosition (Vector (ue1x + offset, ue1y, hUT));
    }
  if ((deploymentScenario.compare ("4_OmniLine") == 0) or (deploymentScenario.compare ("SquareInside") == 0) or (deploymentScenario.compare ("AllCorners") == 0))
    {
      ueNodes.Get (1)->GetObject<MobilityModel> ()->SetPosition (Vector (ue2x, ue2y, hUT));
      ueNodes.Get (2)->GetObject<MobilityModel> ()->SetPosition (Vector (ue1x + offset, ue1y, hUT));
	  ueNodes.Get (3)->GetObject<MobilityModel> ()->SetPosition (Vector (ue2x + offset, ue2y, hUT));
    }

  if (enableBuildings)
    {
      Ptr<GridBuildingAllocator> gridBuildingAllocator;
      gridBuildingAllocator = CreateObject<GridBuildingAllocator> ();
      gridBuildingAllocator->SetAttribute ("GridWidth", UintegerValue (numOfBuildings));
      gridBuildingAllocator->SetAttribute ("LengthX", DoubleValue (2 * apartmentsX));
      gridBuildingAllocator->SetAttribute ("LengthY", DoubleValue (10));
      gridBuildingAllocator->SetAttribute ("DeltaX", DoubleValue (10));
      gridBuildingAllocator->SetAttribute ("DeltaY", DoubleValue (10));
      gridBuildingAllocator->SetAttribute ("Height", DoubleValue (3 * nFloors));
      gridBuildingAllocator->SetBuildingAttribute ("NRoomsX", UintegerValue (apartmentsX));
      gridBuildingAllocator->SetBuildingAttribute ("NRoomsY", UintegerValue (2));
      gridBuildingAllocator->SetBuildingAttribute ("NFloors", UintegerValue (nFloors));
      gridBuildingAllocator->SetAttribute ("MinX", DoubleValue (10));
      gridBuildingAllocator->SetAttribute ("MinY", DoubleValue (10));
      gridBuildingAllocator->Create (numOfBuildings);

      BuildingsHelper::Install (gnbNodes);
      BuildingsHelper::Install (ueNodes);
    }

  /*
   * Create NR simulation helpers
   */
  Ptr<NrPointToPointEpcHelper> epcHelper = CreateObject<NrPointToPointEpcHelper> ();
  Ptr<IdealBeamformingHelper> idealBeamformingHelper = CreateObject <IdealBeamformingHelper> ();
  Ptr<NrHelper> nrHelper = CreateObject<NrHelper> ();

  nrHelper->SetBeamformingHelper (idealBeamformingHelper);
  nrHelper->SetEpcHelper (epcHelper);

  /*
   * Spectrum configuration:
   * We create a single operational band with 1 CC and 1 BWP.
   *
   * |---------------Band---------------|
   * |---------------CC-----------------|
   * |---------------BWP----------------|
   */
  BandwidthPartInfoPtrVector allBwps;
  CcBwpCreator ccBwpCreator;
  const uint8_t numCcPerBand = 1;


  CcBwpCreator::SimpleOperationBandConf bandConf (frequency, bandwidth, numCcPerBand, scenarioEnum);
  OperationBandInfo band = ccBwpCreator.CreateOperationBandContiguousCc (bandConf);

  //Initialize channel and pathloss, plus other things inside band.
  Config::SetDefault ("ns3::ThreeGppChannelModel::UpdatePeriod",TimeValue (MilliSeconds (0)));
  nrHelper->SetChannelConditionModelAttribute ("UpdatePeriod", TimeValue (MilliSeconds (0)));
  nrHelper->SetPathlossAttribute ("ShadowingEnabled", BooleanValue (false));
  nrHelper->SetDlErrorModel(errorModel);
  nrHelper->SetUlErrorModel(errorModel);

  nrHelper->InitializeOperationBand (&band);
  allBwps = CcBwpCreator::GetAllBwps ({band});

  // Configure beamforming method
  if (beamforming.compare ("dir-dir") == 0)
    {
      idealBeamformingHelper->SetAttribute ("BeamformingMethod", TypeIdValue (DirectPathBeamforming::GetTypeId ())); // dir at gNB, dir at UE
    }
  else if (beamforming.compare ("dir-omni") == 0)
    {
      idealBeamformingHelper->SetAttribute ("BeamformingMethod", TypeIdValue (DirectPathQuasiOmniBeamforming::GetTypeId ())); // dir at gNB, q-omni at UE
    }
  else if (beamforming.compare ("omni-dir") == 0)
    {
      idealBeamformingHelper->SetAttribute ("BeamformingMethod", TypeIdValue (QuasiOmniDirectPathBeamforming::GetTypeId ())); // q-omni at gNB, dir at UE
    }
  else if (beamforming.compare ("search-omni") == 0)
    {
      idealBeamformingHelper->SetAttribute ("BeamformingMethod", TypeIdValue (CellScanQuasiOmniBeamforming::GetTypeId ())); // q-omni at gNB, dir at UE
    }
  else
    {
      NS_FATAL_ERROR ("Beamforming does not exist:" << beamforming);
    }

  epcHelper->SetAttribute ("S1uLinkDelay", TimeValue (MilliSeconds (0)));

  // Antennas for the UEs
  nrHelper->SetUeAntennaAttribute ("NumRows", UintegerValue (numRowsUe));
  nrHelper->SetUeAntennaAttribute ("NumColumns", UintegerValue (numColumnsUe));
  //Antenna element type for UEs
  if (isoUe)
    {
      nrHelper->SetUeAntennaAttribute ("AntennaElement", PointerValue (CreateObject<IsotropicAntennaModel> ()));
    }
  else
    {
      nrHelper->SetUeAntennaAttribute ("AntennaElement", PointerValue (CreateObject<ThreeGppAntennaModel> ()));
    }

  // Antennas for the gNbs
  nrHelper->SetGnbAntennaAttribute ("NumRows", UintegerValue (numRowsGnb));
  nrHelper->SetGnbAntennaAttribute ("NumColumns", UintegerValue (numColumnsGnb));
  //Antenna element type for gNBs
  if (isoGnb)
    {
      nrHelper->SetGnbAntennaAttribute ("AntennaElement", PointerValue (CreateObject<IsotropicAntennaModel> ()));
    }
  else
    {
      nrHelper->SetGnbAntennaAttribute ("AntennaElement", PointerValue (CreateObject<ThreeGppAntennaModel> ()));
    }


  // install nr net devices
  NetDeviceContainer gnbNetDev = nrHelper->InstallGnbDevice (gnbNodes, allBwps);
  NetDeviceContainer ueNetDev = nrHelper->InstallUeDevice (ueNodes, allBwps);

  int64_t randomStream = 1;
  randomStream += nrHelper->AssignStreams (gnbNetDev, randomStream);
  randomStream += nrHelper->AssignStreams (ueNetDev, randomStream);

  for (uint32_t i = 0; i < gNbNum; ++i)
    {
    if ((deploymentScenario.compare ("AllCorners") == 0))
	  {
		  if (i==0)
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(45))); //30
		  }
		  else if (i==1)
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(-45))); //150
		  }
		  else if (i==2)
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(135))); //-90
		  }
		  else
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(-135))); //-90
		  }
	  }
	  if (deploymentScenario.compare ("3_Sector") == 0)
	  {
		  if (i%3==0)
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(0))); //30
		  }
		  else if (i%3==1)
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(120))); //150
		  }
		  else
		  {
			  Ptr<NrGnbPhy> phy0 = nrHelper->GetGnbPhy (gnbNetDev.Get(i),0);
			  Ptr<UniformPlanarArray> antenna0 =
			  DynamicCast<UniformPlanarArray> (phy0->GetSpectrumPhy ()->GetAntenna ());
			  antenna0->SetAttribute ("BearingAngle", DoubleValue (DegreesToRadians(-120))); //-90
		  }
	  }

      nrHelper->GetGnbPhy (gnbNetDev.Get (i), 0)->SetTxPower (txPower);
      nrHelper->GetGnbPhy (gnbNetDev.Get (i), 0)->SetAttribute ("Numerology", UintegerValue (numerology));
    }

  // When all the configuration is done, explicitly call UpdateConfig ()
  for (auto it = gnbNetDev.Begin (); it != gnbNetDev.End (); ++it)
    {
      DynamicCast<NrGnbNetDevice> (*it)->UpdateConfig ();
    }

  for (auto it = ueNetDev.Begin (); it != ueNetDev.End (); ++it)
    {
      DynamicCast<NrUeNetDevice> (*it)->UpdateConfig ();
    }

  // create the internet and install the IP stack on the UEs
  // get SGW/PGW and create a single RemoteHost
  Ptr<Node> pgw = epcHelper->GetPgwNode ();
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // connect a remoteHost to pgw. Setup routing too
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (2500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);

  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  // interface 0 is localhost, 1 is the p2p device
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);

  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);
  internet.Install (ueNodes);

  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueNetDev));

  // assign IP address to UEs, and install UDP downlink applications
  uint16_t dlPort = 1100;
  uint16_t ulPort = 2000;
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;
  for (uint32_t u = 0; u < ueNodes.GetN(); ++u) {
	  if (useDl) {
		  PacketSinkHelper dlPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(ueIpIface.GetAddress(u), dlPort));
		  serverApps.Add(dlPacketSinkHelper.Install(ueNodes.Get(u)));

		  OnOffHelper dlClient("ns3::UdpSocketFactory", InetSocketAddress(ueIpIface.GetAddress(u), dlPort));
		  dlClient.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=0.001]"));
		  dlClient.SetAttribute("OffTime", StringValue("ns3::ExponentialRandomVariable[Mean=" + lambda + "]"));
		  dlClient.SetAttribute("PacketSize", UintegerValue(packetSize));
		  dlClient.SetAttribute("StartTime", TimeValue(MilliSeconds(100)));
		  dlClient.SetAttribute("StopTime", TimeValue(Seconds(simTime)));
		  clientApps.Add(dlClient.Install(remoteHost));
	  }
	  if (useUl) {
		  ++ulPort;
		  PacketSinkHelper ulPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(remoteHostAddr, ulPort));
		  serverApps.Add(ulPacketSinkHelper.Install(remoteHost));

		  OnOffHelper ulClient("ns3::UdpSocketFactory", InetSocketAddress(remoteHostAddr, ulPort));
		  ulClient.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=0.001]"));
		  ulClient.SetAttribute("OffTime", StringValue("ns3::ExponentialRandomVariable[Mean=" + lambda + "]"));
		  ulClient.SetAttribute("PacketSize", UintegerValue(packetSize));
		  ulClient.SetAttribute("StartTime", TimeValue(MilliSeconds(100)));
		  ulClient.SetAttribute("StopTime", TimeValue(Seconds(simTime)));
		  clientApps.Add(ulClient.Install(ueNodes.Get(u)));
	  }
  }
  // attach UEs to the closest gNB
  nrHelper->AttachToEnb (ueNetDev.Get (0), gnbNetDev.Get (0));
  if ((deploymentScenario.compare ("3_OmniLine") == 0) or (deploymentScenario.compare ("3_Sector") == 0))
    {
      nrHelper->AttachToEnb (ueNetDev.Get (1), gnbNetDev.Get (1));
      nrHelper->AttachToEnb (ueNetDev.Get (2), gnbNetDev.Get (2));
    }
  if ((deploymentScenario.compare ("4_OmniLine") == 0) or (deploymentScenario.compare ("SquareInside") == 0) or (deploymentScenario.compare ("AllCorners") == 0))
    {
      nrHelper->AttachToEnb (ueNetDev.Get (1), gnbNetDev.Get (1));
      nrHelper->AttachToEnb (ueNetDev.Get (2), gnbNetDev.Get (2));
      nrHelper->AttachToEnb (ueNetDev.Get (3), gnbNetDev.Get (3));
    }

  // start server and client apps
  serverApps.Start(MilliSeconds(appStartTime));
  clientApps.Start(MilliSeconds(appStartTime));
  serverApps.Stop (Seconds (simTime));
  clientApps.Stop (Seconds (simTime - 0.2));

  // enable the traces provided by the nr module
  if (enableTraces)
    {
      nrHelper->EnableTraces ();
    }

  //LogComponentEnable("NrRadioEnvironmentMapHelper",LOG_INFO);
  
  uint16_t remBwpId = 0;
  //Radio Environment Map Generation for ccId 0
  Ptr<NrRadioEnvironmentMapHelper> remHelper = CreateObject<NrRadioEnvironmentMapHelper> ();
  remHelper->SetMinX (xMin);
  remHelper->SetMaxX (xMax);
  remHelper->SetResX (xRes);
  remHelper->SetMinY (yMin);
  remHelper->SetMaxY (yMax);
  remHelper->SetResY (yRes);
  remHelper->SetZ (z);
  remHelper->SetSimTag (simTag);

  gnbNetDev.Get (0)->GetObject<NrGnbNetDevice> ()->GetPhy (remBwpId)->GetSpectrumPhy(0)->GetBeamManager ()->ChangeBeamformingVector (ueNetDev.Get (0));
  if ((deploymentScenario.compare ("3_OmniLine") == 0) or (deploymentScenario.compare ("3_Sector") == 0))
    {
	  gnbNetDev.Get (1)->GetObject<NrGnbNetDevice> ()->GetPhy (remBwpId)->GetSpectrumPhy(0)->GetBeamManager ()->ChangeBeamformingVector (ueNetDev.Get (1));
	  gnbNetDev.Get (2)->GetObject<NrGnbNetDevice> ()->GetPhy (remBwpId)->GetSpectrumPhy(0)->GetBeamManager ()->ChangeBeamformingVector (ueNetDev.Get (2));
    }
  if ((deploymentScenario.compare ("4_OmniLine") == 0) or (deploymentScenario.compare ("SquareInside") == 0) or (deploymentScenario.compare ("AllCorners") == 0))
    {
	  gnbNetDev.Get (1)->GetObject<NrGnbNetDevice> ()->GetPhy (remBwpId)->GetSpectrumPhy(0)->GetBeamManager ()->ChangeBeamformingVector (ueNetDev.Get (1));
	  gnbNetDev.Get (2)->GetObject<NrGnbNetDevice> ()->GetPhy (remBwpId)->GetSpectrumPhy(0)->GetBeamManager ()->ChangeBeamformingVector (ueNetDev.Get (2));
	  gnbNetDev.Get (3)->GetObject<NrGnbNetDevice> ()->GetPhy (remBwpId)->GetSpectrumPhy(0)->GetBeamManager ()->ChangeBeamformingVector (ueNetDev.Get (3));
    }

  if (remMode == "BeamShape")
    {
      remHelper->SetRemMode (NrRadioEnvironmentMapHelper::BEAM_SHAPE);

      if (typeOfRem.compare ("DlRem") == 0)
        {
          remHelper->CreateRem (gnbNetDev, ueNetDev.Get (0), remBwpId);
        }
      else if (typeOfRem.compare ("UlRem") == 0)
        {
          remHelper->CreateRem (ueNetDev, gnbNetDev.Get (0), remBwpId);
        }
      else
        {
          NS_ABORT_MSG ("typeOfRem not supported. "
                        "Choose among 'DlRem', 'UlRem'.");
        }
    }
  else if (remMode == "CoverageArea")
    {
      remHelper->SetRemMode (NrRadioEnvironmentMapHelper::COVERAGE_AREA);
      remHelper->CreateRem (gnbNetDev, ueNetDev.Get (0), remBwpId);
    }
  else if (remMode == "UeCoverage")
    {
      remHelper->SetRemMode (NrRadioEnvironmentMapHelper::UE_COVERAGE);
      remHelper->CreateRem (ueNetDev, gnbNetDev.Get (0), remBwpId);
    }
  else
    {
      NS_ABORT_MSG ("Not supported remMode.");
    }

  Simulator::Stop (Seconds (simTime));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


