# apache_icu
Little C++/QT widget to calculate APACHE II ("Acute Physiology And Chronic Health Evaluation II"), which  is a severity-of-disease classification system (Knaus et al., 1985), one of several ICU scoring systems. It is applied within 24 hours of admission of a patient to an intensive care unit (ICU): an integer score from 0 to 71 is computed based on several measurements; higher scores correspond to more severe disease and a higher risk of death. The first APACHE model was presented by Knaus et al. in 1981.

# Requirements
C++14

Qt 5

# Instructions to compile and Run
1. Linux:
 * qmake-qt5
 * make
 * ./apache

2. Windows:
 * qmake
 * make -f Makefile.Release
