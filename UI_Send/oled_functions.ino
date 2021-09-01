void drawProgressBar(int progress) {

  Heltec.display->clear();
  // draw the progress bar
  Heltec.display->drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 15, String(progress) + "%");
  Heltec.display->display();
}
