      // Her kan elevene velge metode:
      #ifdef USE_PULSEIN_METHOD
          unsigned long timeTaken = measureReactionTime_pulseIn();
      #else
          unsigned long timeTaken = measureReactionTime();  // Manuell versjon
      #endif
