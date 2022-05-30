#include <EloquentTinyML.h>
//#include "EloquentTinyML.h"
#include <eloquent_tinyml/tensorflow.h>
// Import TensorFlow stuff
#include <math.h>
#include"model.h"
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "CME >>>";   // your network SSID (name) 
const char* password = "99669963";   // your network password


WiFiClient  client;

unsigned long myChannelNumber = 4;
const char * myWriteAPIKey = "J9JHLMG5IDESGFDM";

#define N_INPUTS 3 
#define N_OUTPUTS 1 
#define TENSOR_ARENA_SIZE 3*1024

Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;
//Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml(model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  delay(4000);
  tf.begin(model);
    
  // check if model loaded fine
  if (!tf.isOk()) {
     Serial.print("ERROR: ");
     Serial.println(tf.getErrorMessage());
        
     while (true) delay(1000);
  }
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    
      float Temp_val1[] = {24.6,
24.34,
24.37,
24.47,
25.2,
27.4,
29.84,
29.94,
31.14,
31.23,
31.86,
32.21,
31.88,
31.98,
31.43,
30.39,
29.04,
28.28,
27.83,
27.44,
27.24,
26.84,
26.64,
26.22,
26.03,
25.98,
25.85,
25.72,
26.64,
28.98,
30.87,
31.46,
31.92,
31.55,
32.58,
33.69,
35.07,
33.2,
33.94,
31.02,
29.19,
28.26,
27.72,
27.43,
26.91,
26.57,
26.3,
26.19,
25.84,
25.98,
25.75,
25.53,
26.44,
28.13,
30.35,
31.42,
32.44,
32.69,
33.67,
33.06,
33.73,
33.28,
32.8,
30,
29.21,
28.92,
28.74,
28.62,
28.42,
28.37,
28.12,
27.63,
27.45,
26.92,
25.97,
26.17,
26.68,
27.49,
26.02,
25.72,
25.84,
25.73,
25.93,
26.42,
27.04,
28.4,
26.65,
26.7,
26.83,
26.71,
26.78,
26.87,
26.95,
27.42,
29.25,
26.99,
27.01,
26.97,
26.83

};
       float Pressure_val1[] = {1002.60217,
1002.98547,
1002.96069,
1003.47375,
1004.00299,
1004.4953,
1004.97034,
1004.73499,
1004.60211,
1003.88422,
1003.13025,
1002.42908,
1002.36462,
1002.53607,
1002.52545,
1003.62189,
1003.98437,
1004.25751,
1005.19733,
1005.25189,
1004.91693,
1004.3811,
1003.565,
1003.08392,
1002.86304,
1003.15356,
1003.48901,
1003.82617,
1004.35889,
1005.1156,
1005.59406,
1005.37799,
1004.95721,
1004.30389,
1003.54565,
1002.99127,
1002.86273,
1002.89203,
1003.14532,
1003.72516,
1004.16827,
1004.48157,
1005.26013,
1005.94861,
1005.52533,
1005.02655,
1004.64288,
1004.35516,
1004.31641,
1004.50549,
1004.68768,
1004.98499,
1005.49292,
1006.01813,
1006.47986,
1006.24377,
1006.08704,
1005.26672,
1004.41284,
1003.75922,
1002.92249,
1002.86157,
1003.20795,
1004.1145,
1004.59296,
1005.27893,
1005.77875,
1006.47906,
1006.21594,
1005.55377,
1004.9472,
1003.79523,
1003.42224,
1003.39453,
1004.10297,
1004.3446,
1004.79138,
1005.97516,
1005.55664,
1004.85687,
1004.46594,
1004.10858,
1004.34076,
1004.79517,
1005.57349,
1006.51263,
1006.07782,
1005.55487,
1005.20544,
1004.67737,
1004.77783,
1004.76727,
1005.31641,
1005.85205,
1006.77856,
1006.39594,
1006.14032,
1005.45782,
1005.20898

};
        float Humidity_val1[] = {100,
100,
100,
100,
100,
100,
84.18164,
84.94727,
74.58691,
72.03711,
69.03613,
69.76855,
68.15723,
67.49121,
69.08789,
77.2334,
85.8291,
90.6875,
95.64551,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
97.40625,
78.87891,
74.27832,
69.65039,
69.2334,
63.63867,
59.19531,
57.0127,
62.45605,
60.13867,
71.16699,
88.35742,
98.44434,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
84.64453,
74.70703,
69.8252,
67.74609,
64.0459,
67.35352,
65.09082,
62.95605,
67.10059,
82.95508,
90.80664,
96.01172,
96.98633,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
100,
98.23145,
100,
100,
100,
100,
100,
100,
100,
100,
95.71191,
100,
100,
100,
100
};
    float max_temp = 54.92; float min_temp = 21.9;  float range_temp = 33.02;
    float max_humid = 100;float min_humid = 12.92393;float range_humid = 87.07607;
    float max_pressure = 1011.01471;float min_pressure = 1000.72107;float range_pressure = 10.29364;
   // float max_predict_temp = 29.896961; float min_predict_temp = 21.767612; float range_predict_temp = 8.129349;
    float max_predict_temp = 30.403557; float min_predict_temp = 20.619833 ; float range_predict_temp = 11.783724;

    
 for ( int i =0; i <101 ; i = i+1){

    float temp_std = ((Temp_val1[i] - min_temp)/range_temp); 
    float Temperature_val = temp_std*(+1); 
   
    float humid_std = ((Humidity_val1[i] - min_humid)/range_humid);
    float Humidity_val = humid_std*(+1); 
    
    float pressure_std = (Pressure_val1[i] - min_pressure)/range_pressure;
    float Pressure_val = pressure_std*(+1);

    
    float input[N_INPUTS] = {Temperature_val, Humidity_val,Pressure_val}; //create input with is a float array 
    float output = tf.predict(input); //predict the output by giving to the model input
    

    //float output = (output_1 - min_predict_temp)/range_predict_temp;
    float x_std = ((output+1 )/2);
    float x_scaled_proper = (x_std*range_predict_temp) + min_predict_temp; 
     

    //Results :
    Serial.print("Temperature : ");
    Serial.print(Temp_val1[i]);
    Serial.print("Humidity : ");
    Serial.print(Humidity_val1[i]);
    Serial.print("Pressure : ");
    Serial.print(Pressure_val1[i]);
    //Serial.print(" predicted Temperature: ");
    //Serial.println(output); //predicted y
    Serial.print("Predicted Temperature: ");
    Serial.println(x_scaled_proper); 
    delay(15000);
    
    ThingSpeak.setField(1, Temp_val1[i]);
    ThingSpeak.setField(2, Humidity_val1[i]);
    ThingSpeak.setField(3, Pressure_val1[i]);
    ThingSpeak.setField(4, x_scaled_proper);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
 }
}
