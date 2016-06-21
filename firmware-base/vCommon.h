// vCommon 0.5.0a

#define ANALOG_SAMPLES_DEF_SAMPLES 20
#define ANALOG_SAMPLES_DEF_DELAY 20

// Takes multiple sample from AnalogRead and average them

struct analogSampleResult {
  int minValue;
  int maxValue;
  int errorRange;
  float avgValue;
};


analogSampleResult analogSampleRaw(int PIN, int samples=ANALOG_SAMPLES_DEF_SAMPLES,int sampleDelay=ANALOG_SAMPLES_DEF_DELAY){
  int firstVal=analogRead(PIN); // discarding first reading

  int valSum=0;
  int currVal=0;
  float valAvg=0;

  float errorRange=0;  
  
  int minVal=1023;
  int maxVal=-1;
  
  for(int i=0;i<samples;i++){
      delay(sampleDelay);
      currVal=analogRead(PIN);
      valSum+=currVal;
      minVal = currVal < minVal ? currVal : minVal;
      maxVal = currVal > maxVal ? currVal : maxVal;      
  }
  valAvg=valSum/samples;
  errorRange = maxVal-minVal;
  
  analogSampleResult result;
  result.minValue=minVal;
  result.maxValue=maxVal;
  result.errorRange=errorRange;
  result.avgValue=valAvg;
  
  return result;
}
float analogSample(int PIN, int samples=ANALOG_SAMPLES_DEF_SAMPLES,int sampleDelay=ANALOG_SAMPLES_DEF_DELAY){
  analogSampleResult result=analogSampleRaw(PIN,samples,sampleDelay);
  return result.avgValue;
}
