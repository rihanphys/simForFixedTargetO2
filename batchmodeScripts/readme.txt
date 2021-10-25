
Steps:

1. In your work directory you should have 'simSource' directory which
contains all source macros and scripts. You should also have
OCDBsim.root file (path given in google doc manual). 
your work directory should also have these 4 bash scripts. if these
scripts are not executable, then change the mode. just type:

chmod u+x *.sh

2. Load AliDPG and AliROOT environment (follow google doc manual).

3. set number of subjobs by opening and editing the
batchrunMCRun2Gen.sh scipt. by default the number of subjob is set to
20 (say for your case, you set it to N). 

4. After #3, just simply run the script:
./batchrunMCRun2Gen.sh

5. You should see N subdirectories created with names sim001, sim002...
You should see Kinematic.root file in each subdirectories.

6. Exit the AliDPG and AliROOT environment.

7. Load o2 environment.

8. open batchrunO2sim.sh and edit the number of directory (default is
20). then run the script: 
./batchrunO2sim.sh
you should see bunch of root files are created now you have to run
next two work flows. 

9. open batchrunO2digit.sh file and edit the number of directory
(default is 20). run the digitization workflow: 
./batchrunO2digit.sh

10. open batchrunO2reco.sh file and edit the number of directory
(default is 20). run the reconstruction workflow: 
./batchrunO2reco.sh

11. If you managed to finish #4 to #10 without any trouble (or
segmentation fault error) then you are lucky. You should have
tpctracks.root file in each subdirectory. You can run the analysis 
macro in batch mode. open batchAnalysisEffi.sh file and edit the
number of directory (default is 20). run the Analysis in batch mode: 
./batchAnalysisEffi.sh


12. After analysis is done in all subdirectories then you should merge
all output files into one file (using hadd command) and then run the
plotting macro. 



