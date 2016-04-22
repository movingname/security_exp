AFL_PATH=/home/mingyi/Downloads/afl-2.10b
TEST_CASE_DIR=/home/mingyi/Projects/afl_exp/pdf/
FINDING_DIR=/home/mingyi/Projects/afl_exp/pdf_findings/
PROGRAM=/home/mingyi/Downloads/xpdf-3.04/xpdf/xpdf

$AFL_PATH/afl-fuzz -t 200000 -i $TEST_CASE_DIR -o $FINDING_DIR $PROGRAM
 
