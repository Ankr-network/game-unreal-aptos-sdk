@echo %cd%
RD /S /Q "Binaries/"
#RD /S /Q "Build/"
RD /S /Q ".vs/"
RD /S /Q "Intermediate/"
RD /S /Q "Saved/"
RD /S /Q "Plugins/AptosSDK/Binaries/"
RD /S /Q "Plugins/AptosSDK/Intermediate/"
Del symbols.zip
Del UnrealAptosSDK.sln
exit