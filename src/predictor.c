//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <math.h>
#include <stdio.h>
#include "predictor.h"


//
// TODO:Student Information
//
const char *studentName = "NAME";
const char *studentID   = "PID";
const char *email       = "EMAIL";

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *bpName[4] = { "Static", "Gshare",
                          "Tournament", "Custom" };

int ghistoryBits; // Number of bits used for Global History
int lhistoryBits; // Number of bits used for Local History
int pcIndexBits;  // Number of bits used for PC index
int bpType;       // Branch Prediction Type
int verbose;

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

//
//TODO: Add your own Branch Predictor data structures here
//
int* BHR_tour;      // array to keep track of global t/nt
int* BHT_global;    // 2^n array to keep track of global t/nt
int* BHT_local;     // 2^n array to keep track of local t/nt
int* chooser_tour;  // keeps track of chooser for each addr

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void
init_predictor()
{ 
  //
  //TODO: Initialize Branch Predictor Data Structures
  //
  int global_size = pow(2, ghistoryBits);
  int local_size = pow(2, lhistoryBits);
  BHT_global = (int*)malloc(sizeof(int) * global_size);
  BHT_local = (int*)malloc(sizeof(int) * local_size);

  int mem_size = pow(2, ghistoryBits);
  chooser_tour = (int*)malloc(sizeof(int) * mem_size);
  printf("%d", ghistoryBits);

  // BHR, branch history register, keeps track of global branch 
  // taken or not.
  // all initialized to N/not taken/0
  int BHR_size = ghistoryBits;
  BHR_tour = (int*)malloc(sizeof(int) * BHR_size);//  [ghistoryBits];
  
  for (int idx = 0; idx < BHR_size; idx++){
    BHR_tour[idx] = WN;
  } 

  printf("k%dk\n", BHR_tour[0]);
  // BHT/PHT, for local history
  // all initialized to 0/NT
  //[pcIndexBits][lhistoryBits];
  int BHT_size = pow(2, pcIndexBits);
  int loc_size = lhistoryBits;
  BHT_tour = (int*)malloc(sizeof(int) * BHT_size); 
  for (int idx = 0; idx < pcIndexBits; idx++){
    BHT[idx] = malloc(sizeof(int) * loc_size);
  }
  
  
}

uint8_t make_prediction_tournament(uint32_t pc){
  printf("%d", pc);
  return TAKEN;
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t
make_prediction(uint32_t pc)
{
  //
  //TODO: Implement prediction scheme
  //

  // Make a prediction based on the bpType
  switch (bpType) {
    case STATIC:
      return TAKEN;
    case GSHARE:
    case TOURNAMENT:
      //printf("tournament\n");
      return make_prediction_tournament(pc);
    case CUSTOM:
    default:
      break;
  }

  // If there is not a compatable bpType then return NOTTAKEN
  return NOTTAKEN;
}



// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void
train_predictor(uint32_t pc, uint8_t outcome)
{
  //
  //TODO: Implement Predictor training
  //
}
