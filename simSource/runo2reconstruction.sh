#/bin/bash

## this command is for TPC reconstruction:
(o2-tpc-reco-workflow -b --tpc-digit-reader '--infile tpcdigits.root' --input-type digits --output-type clusters,tracks --tpc-track-writer "--treename events --track-branch-name Tracks --trackmc-branch-name TracksMCTruth" --configKeyValues "GPU_rec_tpc.searchWindowDZDR=7" --shm-segment-size 10000000000)

## this following command is for FT0 reconstruction:
(o2-ft0-reco-workflow -b)
