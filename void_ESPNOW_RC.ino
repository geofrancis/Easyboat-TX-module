void ESPNOW(){
  // Set values to send
  RC_CHANNELS.eh1 = ch1;
  RC_CHANNELS.eh2 = ch2;
  RC_CHANNELS.eh3 = ch3;
  RC_CHANNELS.eh1 = ch1;
  RC_CHANNELS.eh2 = ch2;
  RC_CHANNELS.eh3 = ch3;
  RC_CHANNELS.eh1 = ch1;
  RC_CHANNELS.eh2 = ch2;
  RC_CHANNELS.eh3 = ch3;
  RC_CHANNELS.eh1 = ch1;
  RC_CHANNELS.eh2 = ch2;
  RC_CHANNELS.eh3 = ch3;
  RC_CHANNELS.eh1 = ch1;
  RC_CHANNELS.eh2 = ch2;
  RC_CHANNELS.eh3 = ch3;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &RC_CHANNELS, sizeof(RC_CHANNELS));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
