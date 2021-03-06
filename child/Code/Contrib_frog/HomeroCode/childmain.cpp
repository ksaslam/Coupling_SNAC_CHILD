/**************************************************************************/
/**
**                            C H I L D
**
**       CHANNEL-HILLSLOPE INTEGRATED LANDSCAPE DEVELOPMENT MODEL
**
**                        OXFORD VERSION 2003
**
**  Designed and created by Gregory E. Tucker, Stephen T. Lancaster,
**      Nicole M. Gasparini, and Rafael L. Bras
**
**
**  @file   childmain.cpp
**  @brief  This file contains the main() routine that handles
**          top-level initialization and implements the main
**          time-loop.
**
**  NOTE: This source code is copyrighted material. It is distributed
**        solely for noncommercial research and educational purposes
**        only. Use in whole or in part for commercial purposes without
**        a written license from the copyright holder(s) is expressly
**        prohibited. Copies of this source code or any of its components
**        may not be transferred to any other individuals or organizations
**        without written consent. Copyright (C) Massachusetts Institute
**        of Technology, 1997-2000. All rights reserved.
**
**  For information regarding this program, please contact Greg Tucker at:
**
**     Cooperative Institute for Research in Environmental Sciences (CIRES)
**     and Department of Geological Sciences
**     University of Colorado
**     2200 Colorado Avenue, Campus Box 399
**     Boulder, CO 80309-0399
**
**  $Id: childmain.cpp,v 1.28 2005/03/15 17:17:29 childcvs Exp $
*/
/**************************************************************************/

/* set traps for some floating point exceptions on Linux */
#include "trapfpe.h"
#include "Inclusions.h"
#include "tFloodplain/tFloodplain.h"
#include "tStratGrid/tStratGrid.h"
#include "tEolian/tEolian.h"
#include "tOption/tOption.h"

#include "tMeshList/tMeshList.h"

Predicates predicate;

int main( int argc, char **argv )
{
   bool optDetachLim,      // Option for detachment-limited erosion only
        optFloodplainDep,  // Option for floodplain (overbank) deposition
        optLoessDep,       // Option for eolian deposition
        optVegetation,     // Option for dynamic vegetation cover
        optSM,             // Option for soil moisture
        optRad,            //  Option for radiation
        optVegLink,        // Option for linking vegetation to moisture losses
        optBRockWeathering,// Option for bedrock weathering
        optMeander,        // Option for stream meandering
        optDiffuseDepo,    // Option for deposition / no deposition by diff'n
        optStratGrid,      // Option to enable stratigraphy grid
        optBLrain;         // Option for Barlett-Lewis rainfall
   tVegetation *vegetation(0);  // -> vegetation object
   tRadiation *radiation(0);    // -> vegetation object
   tSoilMoisture *soilmoist(0); // -> soil moisture object
   tFloodplain *floodplain(0);  // -> floodplain object
   tStratGrid *stratGrid(0);    // -> Stratigraphy Grid object
   tEolian *loess(0);           // -> eolian deposition object
   tStreamMeander *strmMeander(0); // -> stream meander object

   /****************** INITIALIZATION *************************************\
   **  ALGORITHM
   **    Get command-line arguments (name of input file + any other opts)
   **    Set silent_mode flag
   **    Open main input file
   **    Create and initialize objects for...
   **      Mesh
   **      Output files
   **      Storm
   **      Stream network
   **      Erosion
   **      Uplift (or baselevel change)
   **      Run timer
   **    Write output for initial state
   **    Get options for erosion type, meandering, etc.
   \**********************************************************************/

   // Check command-line arguments
   tOption option( argc, argv );

   // Say hello
   option.version();

   // Open main input file
   tInputFile inputFile( option.inputFile );

   // Create a random number generator for the simulation itself
   tRand rand( inputFile );

   // Create and initialize objects:
   std::cout << "Creating mesh...\n";
   tMesh<tLNode> mesh( inputFile, option.checkMeshConsistency );

   std::cout << "Creating output files...\n";
   tLOutput<tLNode> output( &mesh, inputFile, &rand );

   tStorm storm( inputFile, &rand );
   std::cout << "Creating stream network...\n";
   tStreamNet strmNet( mesh, storm, inputFile );
   tErosion erosion( &mesh, inputFile );
   tUplift uplift( inputFile );

   // Get various options
   optDetachLim = inputFile.ReadBool( "OPTDETACHLIM" );
   optDiffuseDepo = inputFile.ReadBool( "OPTDIFFDEP" );
   optVegetation = inputFile.ReadBool( "OPTVEG" );
   optSM = inputFile.ReadBool( "OPTSM" );
   optRad = inputFile.ReadBool( "OPTRAD" );
   optVegLink = inputFile.ReadBool( "OPTVEGLINK" );
   optBRockWeathering= inputFile.ReadBool( "OPTBEDROCKWEATHERING" );
   optFloodplainDep = inputFile.ReadBool( "OPTFLOODPLAIN" );
   optLoessDep = inputFile.ReadBool( "OPTLOESSDEP" );
   optMeander = inputFile.ReadBool( "OPTMEANDER" );
   optStratGrid = inputFile.ReadBool( "OPTSTRATGRID" ,false);
   optBLrain = inputFile.ReadBool( "OPTBL" );

   // If applicable, create Vegetation object
   if( optVegetation )
       vegetation = new tVegetation( &mesh, inputFile );
   std::cout << "vegetation finished..." << std::endl;
   //If applicable, create Radiation object
   if( optRad )
   radiation = new tRadiation( &mesh, inputFile );

   // If applicable, create SoilMoisture object
   if( optSM) 
     {
       std::cout << "making new soil moisture" << std::endl;
       soilmoist = new tSoilMoisture( &mesh, inputFile);
     }

   // If applicable, create floodplain object
   if( optFloodplainDep )
       floodplain = new tFloodplain( inputFile, &mesh );

   // If applicable, create eolian deposition object
   if( optLoessDep )
       loess = new tEolian( inputFile );

   // If applicable, create Stream Meander object
   if( optMeander )
     strmMeander = new tStreamMeander( strmNet, mesh, inputFile, &rand );

   // If applicable, create Stratigraphy Grid object
   // and pass it to output
   if( optStratGrid ) {
     if (!optFloodplainDep)
       ReportFatalError("OPTFLOODPLAIN must be enabled.");
     stratGrid = new tStratGrid (inputFile, &mesh);
     output.SetStratGrid( stratGrid, &strmNet );
   }

   std::cout << "Writing data for time zero...\n";
   tRunTimer time( inputFile, !option.silent_mode );
   output.WriteOutput( 0. );
   std::cout << "Initialization done.\n";

   // Option for time series output (IN PROGRESS)
   /*   switch( optTSOutput ){
   case 1:   // Volume output each N years.
     if( time.CheckTSOutputTime() )
       output.WriteVolOutput();
     break;
   case 2:   // Volume and vegetation cover output each N years.
     std::cout << "here" << std::endl;
     if( time.CheckTSOutputTime() ){
       std::cout << "there" << std::endl;
       output.WriteVolVegOutput();}
     break;
   case 3:   // All data at each storm.
     output.WriteTSOutput();
     break;
   case 0:   // No additional timeseries output.
     break;
   default:  // Invalid option.
     ReportFatalError( "The input file contains an invalid value for
OptTSOutput." );
   }   */

   /**************** MAIN LOOP ******************************************\
   **  ALGORITHM
   **    Generate storm
   **    Do storm...
   **      Update network (flow directions, drainage area, runoff)
   **      Water erosion/deposition (vertical)
   **      Meandering (if applicable)
   **      Floodplain deposition (if applicable)
   **    Do interstorm...
   **      Hillslope transport
   **      Vegetation (if applicable)
   **      Exposure history
   **      Mesh densification (if applicable)
   **      Eolian (loess) deposition (if applicable)
   **      Uplift (or baselevel change)
   **********************************************************************/
   while( !time.IsFinished() )
   {
      if(0) //debug
      	std::cout << "         " << std::endl;
      time.ReportTimeStatus();

      /********************Applying the BL rain***********************/
      if(optBLrain)
	{
	  strmNet.ResetDischRain(); //reseting total storm infilt. and disch.
	  storm.GenerateStormBL( time.getCurrentTime()); //new function (hf 06)
	  //std::cout << "# pulses in storm: " << storm.getPulsesBL() << std::endl;

	  for ( int i = 0; i < storm.getPulsesBL(); i++)
	   {
	     if (storm.getIthPulseRate(i) != 0) //to skip "empty" pulses
	       {
		 //std::cout << "do we get in the loop " << std::endl;
		 //std::cout << "(storm.getIthzPulsedur(i)=: " << storm.getIthPulseDur(i) << std::endl;
		 storm.setDurationRainrate(storm.getIthPulseDur( i ), storm.getIthPulseRate( i ));
		 //std::cout << "do we pass storm in the loop? " << std::endl;
		 strmNet.UpdateNet( time.getCurrentTime(), storm );
		 if(0) //DEBUG
		   std::cout << "UpdateNet::Done.." << std::endl;
	     
	     
		 if( optDetachLim )
		   erosion.ErodeDetachLim( storm.getStormDuration(), &strmNet,
				       vegetation );
		 else
		   erosion.DetachErode( storm.getStormDuration(), &strmNet,
				    time.getCurrentTime(), vegetation );
		 if(0) //DEBUG
		   std::cout << "Erosion::Done.." << std::endl;
	       }
	   }
	  storm.setDurationRainrate(-1.0, -1.0);
      if(0) //DEBUG
	     std::cout<< "Storm: "<< storm.getRainrate() << " " << storm.getStormDuration() << " "
	          << storm.interstormDur() << std::endl;
	}

      /***************************************************************/
      else
	{  //beginning of non-Barlett Lewis stuff



      // Do storm...
      strmNet.ResetDischRain(); //reseting total storm infilt. and disch.
      storm.GenerateStorm( time.getCurrentTime(),
                           strmNet.getInfilt(), strmNet.getSoilStore() );
      if(1) //DEBUG
	     std::cout<< "Storm: "<< storm.getRainrate() << " " << storm.getStormDuration() << " "
	          << storm.interstormDur() << std::endl;

      strmNet.UpdateNet( time.getCurrentTime(), storm );
      if(1) //DEBUG
	     std::cout << "UpdateNet::Done.." << std::endl;

      if(0) //DEBUG
	  {
         tMesh< tLNode >::nodeListIter_t mli( mesh.getNodeList() );  // gets nodes from the list
		 tLNode * cn;
		 for( cn=mli.FirstP(); mli.IsActive(); cn=mli.NextP() )
		 {
		    if( cn->getID()==8121 || cn->getID()==8122 ) 
			{
				tEdge * debugedg = cn->getFlowEdg();
				tLNode * nbr = static_cast<tLNode *>(debugedg->getDestinationPtrNC());
				std::cout<<"Childmain 1: node "<<cn->getID()<<" edge "<<debugedg->getID()<<" downstream nbr "<<nbr->getID()<<std::endl;
				std::cout<<"z "<<cn->getZ()<<" dsn z "<<nbr->getZ()<<std::endl;
			}
		 }

	  }

      // Link tLNodes to StratNodes, adjust elevation StratNode to surrounding tLNodes
      if( optStratGrid )
      	  stratGrid->UpdateStratGrid(tStratGrid::k0, time.getCurrentTime());

      if(0) //DEBUG
	  {
         tMesh< tLNode >::nodeListIter_t mli( mesh.getNodeList() );  // gets nodes from the list
		 tLNode * cn;
		 for( cn=mli.FirstP(); mli.IsActive(); cn=mli.NextP() )
		 {
		    if( cn->getID()==8121 || cn->getID()==8122 ) 
			{
				tEdge * debugedg = cn->getFlowEdg();
				tLNode * nbr = static_cast<tLNode *>(debugedg->getDestinationPtrNC());
				std::cout<<"Childmain 2: node "<<cn->getID()<<" edge "<<debugedg->getID()<<" downstream nbr "<<nbr->getID()<<std::endl;
				std::cout<<"z "<<cn->getZ()<<" dsn z "<<nbr->getZ()<<std::endl;
			}
		 }

	  }

      if( optDetachLim )
          erosion.ErodeDetachLim( storm.getStormDuration(), &strmNet,
				  vegetation );
      else
          erosion.DetachErode( storm.getStormDuration(), &strmNet,
                               time.getCurrentTime(), vegetation );
      if(1) //DEBUG
	     std::cout << "Erosion::Done.." << std::endl;

      // Link tLNodes to StratNodes, adjust elevation StratNode to surrounding tLNodes
      if( optStratGrid )
	     stratGrid->UpdateStratGrid(tStratGrid::k1,time.getCurrentTime() );

      if(0) //DEBUG
	  {
         tMesh< tLNode >::nodeListIter_t mli( mesh.getNodeList() );  // gets nodes from the list
		 tLNode * cn;
		 for( cn=mli.FirstP(); mli.IsActive(); cn=mli.NextP() )
		 {
		    if( cn->getID()==8121 || cn->getID()==8122 ) 
			{
				tEdge * debugedg = cn->getFlowEdg();
				tLNode * nbr = static_cast<tLNode *>(debugedg->getDestinationPtrNC());
				std::cout<<"Childmain 3: node "<<cn->getID()<<" edge "<<debugedg->getID()<<" downstream nbr "<<nbr->getID()<<std::endl;
				std::cout<<"z "<<cn->getZ()<<" dsn z "<<nbr->getZ()<<std::endl;
			}
		 }

	  }

      if( optMeander )
	     strmMeander->Migrate( time.getCurrentTime() );

      if(0) //DEBUG
	     std::cout << "Meander-Migrate::Done..\n";

      // Link tLNodes to StratNodes, adjust elevation StratNode to surrounding tLNodes
      if( optStratGrid )
	     stratGrid->UpdateStratGrid(tStratGrid::k2,time.getCurrentTime());

      //----------------FLOODPLAIN---------------------------------
      if( optFloodplainDep )
	  {
	     if( floodplain->OptControlMainChan() )
	        floodplain->UpdateMainChannelHeight( time.getCurrentTime(),
						 strmNet.getInletNodePtrNC() );
	        std::cout << "UpdateChannelHeight::Done..\n";

	     if( optStratGrid ){
	        stratGrid->UpdateStratGrid(tStratGrid::k3,time.getCurrentTime());
	  }

	  floodplain->DepositOverbank( storm.getRainrate(),
				       storm.getStormDuration(),
				       time.getCurrentTime() );
	  std::cout << "tFloodplain::Done..\n";

	  if( optStratGrid )
	    {
	    stratGrid->UpdateStratGrid(tStratGrid::k4,time.getCurrentTime());
	    }

	  } // end of floodplain stuff

	}//end of non-Barlett Lewis stuff-
      if (optRad)
	{
	  radiation->UpdateRadiation(&mesh,time.getCurrentTime());
	}


      // Do interstorm...

      //-----------------MOISTURE & VEGETATION---------------------
      // Loop to compute moisture and vegetation in weekly intervals at the
      // most (could become a function of some class, but to which class
      // would it belong to?)

      if (optVegLink)
	{
	  soilmoist->ResetETLeak( &mesh ); //reseting total storm infilt. and disch.
	  double interstormDuration, stormDuration, week;
	  interstormDuration = storm.interstormDur();
	  //std::cout << "interstorm: " << interstormDuration << std::endl;
	  stormDuration = storm.getStormDuration();
	  //std::cout << "storm: " << stormDuration << std::endl;
	  week = 0.02;
	  while(interstormDuration > week) // loop that makes sure interstorm
	    //intervals are smaller than a week
	    {
	      if (0) //DEBUG
		std::cout << "tSM::..first loop\n";
	      if( optSM ) soilmoist->updateSoilMoisture( &mesh, week, time.getCurrentTime() );
	      if (0) //DEBUG
		std::cout << "tSM::..first loop done\n";
#define NEWVEG 0
	      if( optVegetation ) {
		if( NEWVEG )
		  vegetation->GrowVegetation( &mesh, week, time.getCurrentTime() );
		else
		  vegetation->UpdateVegetation( &mesh, stormDuration,
						week, time.getCurrentTime() );
	      }
#undef NEWVEG
	      interstormDuration = interstormDuration - week;
	      stormDuration = 0.0;
	    }
	  if(interstormDuration <= week) //This happens when the interstorm is 
	    //smaller than a week (0.02 yr), whether the loop above happened or not
	    {
	      if (0) //DEBUG
		std::cout << "tSM::..second loop\n" << interstormDuration;
	      if( optSM ) soilmoist->updateSoilMoisture( &mesh, interstormDuration, time.getCurrentTime() );
	      if (0) //DEBUG
		std::cout << "tSM::..done\n";
#define NEWVEG 0
	      if( optVegetation ) {
		if( NEWVEG )
		  vegetation->GrowVegetation( &mesh, interstormDuration, time.getCurrentTime() );
		else
		  vegetation->UpdateVegetation( &mesh, stormDuration,
						interstormDuration, time.getCurrentTime() );
	      }
#undef NEWVEG
	    }
	}
      else
	{
	  if (0) //DEBUG
	    std::cout << "tSM::..\n";
	  if( optSM )	  soilmoist->ResetETLeak( &mesh ); //reseting total storm infilt. and disch.
	  if( optSM ) soilmoist->updateSoilMoisture( &mesh,  storm.interstormDur(), time.getCurrentTime() );
	  if (0) //DEBUG
	    std::cout << "tSM::..done\n";
#define NEWVEG 0
	  if( optVegetation ) 
	    {

	      if( NEWVEG )
		vegetation->GrowVegetation( &mesh,storm.interstormDur(), time.getCurrentTime() );
	      else
		vegetation->UpdateVegetation( &mesh, storm.getStormDuration(),storm.interstormDur(), time.getCurrentTime() );
	      std::cout << "for some reason got inside this loop" << std::endl;
	    }
	}
      
      if ( optVegLink) soilmoist->updateInfCap( &mesh );
      
      if(optBRockWeathering)
         erosion.WeatherNodes(storm.getStormDuration() + storm.interstormDur( ), time.getCurrentTime());

      erosion.Diffuse( storm.getStormDuration() + storm.interstormDur(),
		       optDiffuseDepo,time.getCurrentTime() );

      erosion.UpdateExposureTime( storm.getStormDuration() +
                                      storm.interstormDur() );

      if( optLoessDep )
          loess->DepositLoess( &mesh,
                               storm.getStormDuration()+storm.interstormDur(),
                               time.getCurrentTime() );

      if( time.getCurrentTime() < uplift.getDuration() )
          uplift.DoUplift( &mesh,
                           storm.getStormDuration() + storm.interstormDur(), 
						   time.getCurrentTime() );

      time.Advance( storm.getStormDuration() + storm.interstormDur() );

      if( time.CheckOutputTime() )
          output.WriteOutput( time.getCurrentTime() );
      if( output.OptTSOutput() ) output.WriteTSOutput(time.getCurrentTime(), storm.getRainrate(), storm.getStormDuration());
      /* IN PROGRESS
      switch( optTSOutput ){
      case 1:   // Volume output each N years.
        if( time.CheckTSOutputTime() )
  output.WriteVolOutput();
break;
      case 2:   // Volume and vegetation cover output each N years.
if( time.CheckTSOutputTime() )
  output.WriteVolVegOutput();
break;
      case 3:   // All data at each storm.
output.WriteTSOutput();
break;
      case 0:   // No additional timeseries output.
break;
      default:  // Invalid option.
ReportFatalError( "The input file contains an invalid value for OptTSOutput."
*/

     /*tMesh< tLNode >::nodeListIter_t ni( mesh.getNodeList() );
      tLNode *cn;
      for( cn=ni.FirstP(); ni.IsActive(); cn=ni.NextP() )
	{
	  if( cn->getY()<25 && cn->getX()>250 && cn->getDrArea()>1000 )
	    cn->TellAll();
	}*/

   } // end of main loop
   delete vegetation;
   delete floodplain;
   delete loess;
   delete strmMeander;
   delete stratGrid;

   return 0;
}

