#!/bin/bash

### EDIT PATH ACCORDINGLY
autotester=./Team11/Code11/Release/AutoTester.exe
debug=./Team11/Code11/Debug/AutoTester.exe
outputPath=./out
analysis_path=./Team11/Code11/Tests/analysis.xsl

source_suffix=_source.txt
query_suffix=_queries.txt
test_path=./Team11/Tests11/

adv_spa=ADV_SPA/
basic_spa=BASIC_SPA/

output_suffix=queries-out.xml
log_suffix="log"

timeout=30
# check if the directory exist and make one if not
[ ! -d "$outputPath" ] && mkdir $outputPath
[ ! -d "$outputPath/out" ] && mkdir $outputPath/out

echo Removing All Previous Outputs
# remove all logs
rm $outputPath/*
rm $outputPath/out/*

echo Done Removing Previous Outputs

echo "========== Copy Analysis File ============="
cp $analysis_path $outputPath/out
echo "========== Done Copy Analysis File ============="



basic_spa_types=("uses_s" "uses_p" "modifies_s" "modifies_p" "Sample_deep_nesting" "Sample_follows" "Sample_parent" "Sample_pattern" "Sample" "Sample_uses" "Sample-long-pattern" "Sample_two" "assign_pattern")
adv_spa_types=("calls_clause" "calls_star_clause" "one_modifies_clause" "one_uses_clause" "select_attribute" "select_boolean" "select_tuple" "sample_advpattern" "sample_with" "next_clause" "next_start_clause" "multi_clause" "multiple_clauses" "multiple_fp" "one_affects_clause" "with" "with2" "while_pattern" "if_pattern" "multi_clause_pattern" "one_affects_star_clause" "stress_long_programme" "multiple_with+um")

echo "========= RUNNING BASIC SPA ========="

# run BASIC_SPA tests
for type in "${basic_spa_types[@]}"
do
	 $autotester $test_path$basic_spa$type$source_suffix $test_path$basic_spa$type$query_suffix $outputPath/out/out-$type$output_suffix > $outputPath/release-$type-$log_suffix.txt
	 if grep "AutoTester Completed !" $outputPath/release-$type-$log_suffix.txt; then
	  echo "Done $type"
	 else
		echo "Did not complete $type for Release"
		sleep 5
		exit 1
	 fi
	 echo Done $type
done

echo "========= RUNNING ADVANCED SPA =========="

# run ADV_SPA tests
for type in "${adv_spa_types[@]}"
do
	$autotester $test_path$adv_spa$type$source_suffix $test_path$adv_spa$type$query_suffix $outputPath/out/out-$type$output_suffix > $outputPath/release-$type-$log_suffix.txt
	if grep "AutoTester Completed !" $outputPath/release-$type-$log_suffix.txt; then
		sleep 1
	else
	  echo "Did not complete $type for Release"
		sleep 5
		exit 1
	fi
done

echo '=============== Grep failed testcases'

grep 'Missing' $outputPath/*$log_suffix.txt > $outputPath/all_tests.txt
grep 'Missing' $outputPath/*$log_suffix.txt
echo 'Above are failed tcs, if there is nothing above then all is good.' >> $outputPath/all_tests.txt

if grep 'Missing' $outputPath/*$log_suffix.txt; then
	echo 'Some failed'
	sleep 5
else
	echo 'All passed'
fi

if grep "TIMEOUT" $outputPath/*$log_suffix.txt; then
    echo 'Timeout found'
    sleep 5
else
   echo 'No timeout'
fi

echo '=============== Completed, Testcases listed above'

start http://localhost:8000 &
cd $outputPath/out && python -m http.server 8000
