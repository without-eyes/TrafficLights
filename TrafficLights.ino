// Constants
const short trafficLightSize = 3;
const int redAndGreenLightDuration = 10000;
const int yellowLightDuration = 3000;

// State variables
bool isGoingUp = false;
int currentLight = 2;

// Pin configuration for the two traffic lights (red, yellow, green)
const short firstTrafficLights[trafficLightSize] = {10, 9, 8};
const short secondTrafficLights[trafficLightSize] = {7, 6, 5};

void setup() {
  initializeTrafficLights();
  changeLightState(currentLight, HIGH);
}

void loop() {
  waitBeforeTurningOff(currentLight);
  changeLightState(currentLight, LOW);
  updateLightDirection(); 
  changeLightState(currentLight, HIGH);
}

void initializeTrafficLights() {
  for (int i = 0; i < trafficLightSize; i++) {
    pinMode(firstTrafficLights[i], OUTPUT);
    pinMode(secondTrafficLights[i], OUTPUT);
  }
}

void changeLightState(int trafficLightPosition, int state) {
  digitalWrite(firstTrafficLights[trafficLightPosition], state);
  digitalWrite(secondTrafficLights[getOppositeLightPosition(trafficLightPosition)], state);
}

int getOppositeLightPosition(int position) {
  return abs(trafficLightSize - position - 1);
}

void waitBeforeTurningOff(int trafficLightPosition) {
  int waitTime = (trafficLightPosition == 1) ? yellowLightDuration : redAndGreenLightDuration;
  delay(waitTime);
}

void updateLightDirection() {
  if (isGoingUp) {
    currentLight++;
    if (currentLight >= trafficLightSize - 1) {
      isGoingUp = false;
    }
  } else {
    currentLight--;
    if (currentLight <= 0) {
      isGoingUp = true;
    }
  }
}
