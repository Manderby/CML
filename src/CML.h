
// Color Machine Library (CML)
//
// CML is a self-contained implementation of color transformations used in
// color science and standards, based on informations from the literature and
// reference material from standartization institutes.
//
// This is the full version of CML and has been made available to you, your
// company or institute by a separate contract. If not stated otherwise, you
// are permitted by this contract to use this software for internal software
// engineering and to get future version upgrades for free (See changelog for
// more information). If not explicitly stated in the contract, you are NOT
// allowed to use this version for a product. Further restrictions/terms are
// stated in the contract.
//
// Please contact cml@manderim.ch for requests, bugs, hints, clarification and
// similar things. Note that German is the preferred choice of correspondance
// but English is offered as a common language of inter-communication.
// Requests which can be answered by yourself with the given documentation will
// be answered with a reference to the documentation.
//
// If you consider incorporating CML into a bigger project and need (paid) help
// in engineering, feel free to contact.
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.
//
// Designed and implemented by Tobias Stamm, Manderim GmbH

#ifndef CML_INCLUDED
#define CML_INCLUDED

#ifdef __cplusplus 
  extern "C"{
#endif



// Some typedefs and math operators.
#include "CMLDefinitions.h"

// Enumerations and color types used in CML.
#include "CMLTypes.h"

// CMLFunctions define response curves, spectra and other various 1D-functions.
#include "CMLFunctions.h"
#include "CMLIllumination.h"
#include "CMLObserver.h"
#include "CMLResponseCurve.h"

// Definition of the most basic color API
#include "CMLBaseAPI.h"

// Color Machines and their API
#include "CMLColorMachine.h"

// The defaults used in CML.
#include "CMLConstants.h"



#ifdef __cplusplus 
  } // extern "C"
#endif

#endif // CML_INCLUDED
