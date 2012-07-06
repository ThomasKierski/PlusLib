/*=Plus=header=begin======================================================
Program: Plus
Copyright (c) Laboratory for Percutaneous Surgery. All rights reserved.
See License.txt for details.
=========================================================Plus=header=end*/

#include "vtkTracker.h"

class vtkTrackerBuffer; 

/*!
\class vtkAscension3DGTrackerBase 
\brief Interface for the Ascension 3DG magnetic tracker 

This class talks with Ascension3DG tracker over the ATC trakSTAR device driver

\ingroup PlusLibTracking
*/
class
  VTK_EXPORT
vtkAscension3DGTrackerBase : public vtkTracker
{
public:

  static vtkAscension3DGTrackerBase *New();
  vtkTypeMacro( vtkAscension3DGTrackerBase,vtkTracker );
  void PrintSelf( ostream& os, vtkIndent indent );

  /*! Connect to device */
  PlusStatus Connect();

  /*! Disconnect from device */
  virtual PlusStatus Disconnect();

  /*! 
  Probe to see if the tracking system is present on the specified serial port.  
  If the SerialPort is set to -1, then all serial ports will be checked.
  */
  PlusStatus Probe();

  /*!
  Get an update from the tracking system and push the new transforms
  to the tools.  This should only be used within vtkTracker.cxx.
  This method is called by the tracker thread.
  */
  PlusStatus InternalUpdate();

  /*! Get number of sensors */
  vtkGetMacro(NumberOfSensors, int);


protected:

  vtkAscension3DGTrackerBase();
  ~vtkAscension3DGTrackerBase();

  /*! 
  Start the tracking system.  The tracking system is brought from its ground state into full tracking mode.
  The device will only be reset if communication cannot be established without a reset.
  */
  PlusStatus InternalStartTracking();

  /*! Stop the tracking system and bring it back to its ground state: Initialized, not tracking, at 9600 Baud. */
  PlusStatus InternalStopTracking();

  vtkTrackerBuffer* LocalTrackerBuffer; 


private:  // Definitions.

  enum {TRANSMITTER_OFF = -1};

private:  // Functions.

  vtkAscension3DGTrackerBase( const vtkAscension3DGTrackerBase& );
  void operator=( const vtkAscension3DGTrackerBase& );  

  /*! Check return status and log in case of error */
  PlusStatus CheckReturnStatus( int status );


private:  // Variables.

  std::vector< bool > SensorSaturated;
  std::vector< bool > SensorAttached;
  std::vector< bool > SensorInMotion;

  void* AscensionRecordBuffer; 

  bool TransmitterAttached;

  unsigned int FrameNumber;
  int NumberOfSensors; 

};