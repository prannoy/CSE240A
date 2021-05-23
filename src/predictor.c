//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <math.h>
#include <stdio.h>
#include <inttypes.h>
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
int* BHT_index;     // array to keep track of where addr goes to
int* BHT_global;    // 2^n array to keep track of global t/nt
int* BHT_local;     // 2^n array to keep track of local t/nt
int* chooser;       // keeps track of chooser for each addr
int G_hist;         // keeps track of global history

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
  
  // the 'ghistoryBits' will be used to size the global and choice predictors
  int global_size = pow(2, ghistoryBits);
  G_hist = 0; // index into table
  BHT_global = (int*)malloc(sizeof(int) * global_size);
  chooser = (int*)malloc(sizeof(int) * global_size);
  
  // the 'lhistoryBits' and 'pcIndexBits' will be used to size the local predictor.
  int local_size = pow(2, lhistoryBits);
  int BHT_size = pow(2, pcIndexBits);
  BHT_local = (int*)malloc(sizeof(int) * local_size);
  BHT_index = (int*)malloc(sizeof(int) * BHT_size);
  
  // All 2-bit predictors should be initialized to WN (Weakly Not Taken).
  for (int i = 0; i < global_size; i++){
    BHT_global[i] = WN;
  }

  for (int i = 0; i < local_size; i++){
    BHT_local[i] = WN;
  }


  // all addresses' indexes to BHT set to be 0 initially
  for (int i = 0; i < BHT_size; i++){
    BHT_index[i] = 0;
  }

  // The Choice Predictor used to select which predictor 
  // should be initialized to Weakly select the Global Predictor.
  // [0=SG, 1=WG, 2=WL, 3=SL], since 2-bit predictor
  for (int i = 0; i < global_size; i++){
    chooser[i] = 1;
  }
  
}

uint8_t make_prediction_tournament(uint32_t pc){
  printf("%" PRIu32 "\n", pc);
  printf("in tournament");
  return TAKEN;
  
  // mod out index from pc, for local prediction
  int local_mem_track = pow(2, lhistoryBits);
  uint32_t local_index = pc % local_mem_track;
  int BHT_idx = BHT_index[local_index];
  int local_choice =  BHT_local[BHT_idx];


  // global choice
  int global_choice = BHT_global[G_hist];

  int choose_idx = pc % (int)pow(2, ghistoryBits);
  int choice = chooser[choose_idx];

  if (choice <= 1){
    // choice is SG or WG
    if (global_choice == SN || global_choice == WN){
      // predict not taken, as BHT predicts NT
      return NOTTAKEN;
    } else {
      return TAKEN;
    }
  } else {
    // choice is SL or WL
    if (local_choice == SN || local_choice == WN){
      // predict not taken, as BHT predicts NT
      return NOTTAKEN;
    } else {
      return TAKEN;
    }
  }
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
      //printf("%" PRIu32 "\n", pc);
      return make_prediction_tournament(pc);
      break;
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
