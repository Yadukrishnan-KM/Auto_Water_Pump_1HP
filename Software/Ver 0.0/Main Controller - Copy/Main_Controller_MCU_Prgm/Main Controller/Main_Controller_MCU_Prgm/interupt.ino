void interupt(){
  for(int i = 0; i <= 3; i++){                           // saving all the received data bits into a temporary locaton
    b[i] = digitalRead((3+i));
  }
  if(b[3] && b[2] && !b[1] && !b[0]) batLow = true;
  else if (b[3] && b[2] && !b[1] && b[0]) batLow = false;
  else if (b[3] && b[2] && b[1] && !b[0]) solarCharg = true;
  
  else{
    for(int j =0; j <= 3; j++){                           // saving all the received data bits into a global variable after confirming it is water level
      d[j] = b[j];
    }
  }
}