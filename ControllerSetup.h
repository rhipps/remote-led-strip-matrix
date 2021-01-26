//set up
short selection = 1;
const short matrixSize = 16;

enum mode { view, edit };
mode currentMode = view;

//Controller Button Configurations
//Direction
const uint32_t upArrow = 16736925;
const uint32_t downArrow = 16754775;
const uint32_t leftArrow = 16720605;
const uint32_t rightArrow = 16761405;

//ColorChoices
const uint32_t num0 = 16738455;
const uint32_t num1 = 16724175;
const uint32_t num2 = 16718055;
const uint32_t num3 = 16743045;
const uint32_t num4 = 16716015;
const uint32_t num5 = 16726215;
const uint32_t num6 = 16734885;
const uint32_t num7 = 16728765;
const uint32_t num8 = 16730805;
const uint32_t num9 = 16732845;

//misc buttons
const uint32_t toggleMode = 16753245;
const uint32_t okayButton = 16712445;

//These are the ox plow type layout controls
bool isSelectionInEvenRowInMatrix(){
  int row = (selection-1) / matrixSize;
  return row == 0 ? false : row % 2 != 0;
}

bool isEndCap(){
  int endCapCheck = selection % matrixSize;
  return endCapCheck == 0;
}

bool isStartCap(){
  int startCapCheck = selection % matrixSize;
  return startCapCheck == 1;
}

void oxControllerMoveUp(){
  if(selection > matrixSize) {
    selection -= (2*((selection-1)%matrixSize) + 1);
  }
}

void oxControllerMoveDown(){
  if(selection < matrixSize*(matrixSize-1)) {
    selection += 2*matrixSize - 2*((selection-1)%matrixSize) - 1;
  }
}

void oxControllerMoveLeft(){
  if (!isSelectionInEvenRowInMatrix()){
    selection -= isStartCap() ? -(matrixSize-1) : 1;
  } else {
    selection += isEndCap() ? -(matrixSize-1) : 1;
  }
}

void oxControllerMoveRight(){
  if(selection < matrixSize*matrixSize) {
    if (!isSelectionInEvenRowInMatrix()){
      selection += isEndCap() ? -(matrixSize-1) : 1;
    } else {
      selection -= isStartCap() ? -(matrixSize-1) : 1;
    }
  }
}

controllerToggleMode(){
  if(currentMode == view) {
    currentMode = edit;
  } else {
    currentMode = view;
  }
}
