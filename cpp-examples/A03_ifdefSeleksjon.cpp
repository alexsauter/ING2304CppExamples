      // Her kan elevene velge metode:
      #ifdef USE_PULSEIN_METHOD
          unsigned long timeTaken = egenNamespace::measureReactionTime();
      #else
          unsigned long timeTaken = measureReactionTime();  // Manuell versjon
      #endif
