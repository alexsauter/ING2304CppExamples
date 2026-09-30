      // Her kan elevene velge metode:
      #ifdef USE_PULSEIN_METHOD
          unsigned long timeTaken = egenNamespace::measureReactionTime(); //pulsIn() versjon
      #else
          unsigned long timeTaken = measureReactionTime();  // Manuell versjon
      #endif
