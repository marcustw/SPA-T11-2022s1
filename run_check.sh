#!/bin/bash

### EDIT PATH ACCORDINGLY
autotester=./Team11/Code11/Release/AutoTester.exe
debug=./Team11/Code11/Debug/AutoTester.exe
outputPath=./out

source_suffix=_source.txt
query_suffix=_queries.txt
test_path=./Team11/Tests11/
analysis_path=./Team11/Code11/Tests/analysis.xsl

adv_spa=ADV_SPA/
basic_spa=BASIC_SPA/

output_suffix=queries-out.xml
log_suffix="log"

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
adv_spa_types=("calls_clause" "calls_star_clause" "one_modifies_clause" "one_uses_clause" "select_attribute" "select_boolean" "select_tuple" "sample_advpattern" "sample_with" "next_clause" "next_start_clause" "multi_clause" "multiple_clauses" "multiple_fp" "one_affects_clause" "with" "with2" "while_pattern" "if_pattern" "multi_clause_pattern" "one_affects_star_clause" )
stress_test_types=("stress_long_programme" "multiple_with+um")

# Just for stress testing
#basic_spa_types=("Sample")
#adv_spa_types=("sample_with")
#stress_test_types=("stress_long_programme")


echo "========= RUNNING BASIC SPA ========="

# run BASIC_SPA tests
for type in "${basic_spa_types[@]}"
do
  echo "------------- Start $type for $1 -------------"
  if [[ "$1" != "Debug" ]]; then
	  $autotester $test_path$basic_spa$type$source_suffix $test_path$basic_spa$type$query_suffix $outputPath/out/release-basic-$type$output_suffix > $outputPath/release-basic-$type-$log_suffix.txt
	  if grep "AutoTester Completed !" $outputPath/release-basic-$type-$log_suffix.txt; then
		sleep 1
	  else
		echo "Did not complete $type for Release"
		sleep 5
		exit 1
	  fi
	  echo "------------- Done $type for Release -------------"
  else
    $debug $test_path$basic_spa$type$source_suffix $test_path$basic_spa$type$query_suffix $outputPath/out/debug-basic-$type$output_suffix > $outputPath/debug-basic-$type-$log_suffix.txt
	if grep "AutoTester Completed !" $outputPath/debug-basic-$type-$log_suffix.txt; then
	  sleep 1
	else
	  echo "Did not complete $type for Debug"
	  sleep 5
	  exit 1
	fi
	echo "------------- Done $type for Debug -------------"
  fi
  echo ""
done

echo "========= RUNNING ADVANCED SPA =========="

# run ADV_SPA tests
for type in "${adv_spa_types[@]}"
do
    echo "------------- Start $type for $1 -------------"
    if [[ "$1" != "Debug" ]]; then
	  $autotester $test_path$adv_spa$type$source_suffix $test_path$adv_spa$type$query_suffix $outputPath/out/release-adv-$type$output_suffix > $outputPath/release-adv-$type-$log_suffix.txt
	  if grep "TIMEOUT" $outputPath/release-adv-$type-$log_suffix.txt; then
		echo "Time out for $type for Release"
		cat $outputPath/out/release-adv-$type$output_suffix
		sleep 10
		exit 1
	  elif grep "AutoTester Completed !" $outputPath/release-adv-$type-$log_suffix.txt; then
		sleep 1
	  else
		echo "Did not complete $type for Release"
		sleep 5
		exit 1
	  fi
	  echo "------------- Done $type for Release -------------"
	else
	  $debug $test_path$adv_spa$type$source_suffix $test_path$adv_spa$type$query_suffix $outputPath/out/debug-adv-$type$output_suffix > $outputPath/debug-adv-$type-$log_suffix.txt
	  if grep "TIMEOUT" $outputPath/debug-adv-$type-$log_suffix.txt; then
		echo "Time out for $type for Debug"
		cat $outputPath/out/debug-adv-$type$output_suffix
		sleep 10
		exit 1
	  elif grep "AutoTester Completed !" $outputPath/debug-adv-$type-$log_suffix.txt; then
		sleep 1
	  else
		echo "Did not complete $type for Debug"
		sleep 5
		exit 1
	  fi
	  echo "------------- Done $type for Debug -------------"
	fi
	echo ""
done

echo "========= RUNNING STRESS TEST =========="

# run STRESS TESTs
for type in "${stress_test_types[@]}"
do
    echo "------------- Start $type for $1 -------------"
    if [[ "$1" != "Debug" ]]; then
	  $autotester $test_path$adv_spa$type$source_suffix $test_path$adv_spa$type$query_suffix $outputPath/out/release-adv-$type$output_suffix > $outputPath/release-adv-$type-$log_suffix.txt
	  if grep "TIMEOUT" $outputPath/release-adv-$type-$log_suffix.txt; then
		echo "Time out for $type for Release"
		cat $outputPath/out/release-adv-$type$output_suffix
		sleep 10
		exit 1
	  elif grep "AutoTester Completed !" $outputPath/release-adv-$type-$log_suffix.txt; then
		sleep 1
	  else
		echo "Did not complete $type for Release"
		sleep 5
		exit 1
	  fi
	  cat $outputPath/out/release-adv-$type$output_suffix
	  echo "------------- Done $type for Release -------------"
	else
	  $debug $test_path$adv_spa$type$source_suffix $test_path$adv_spa$type$query_suffix $outputPath/out/debug-adv-$type$output_suffix > $outputPath/debug-adv-$type-$log_suffix.txt
	  if grep "TIMEOUT" $outputPath/debug-adv-$type-$log_suffix.txt; then
		echo "Time out for $type for Debug"
		cat $outputPath/out/debug-adv-$type$output_suffix
		sleep 10
		exit 1
	  elif grep "AutoTester Completed !" $outputPath/debug-adv-$type-$log_suffix.txt; then
		sleep 1
	  else
		echo "Did not complete $type for Debug"
		sleep 5
		exit 1
	  fi
	  cat $outputPath/out/debug-adv-$type$output_suffix
	  echo "------------- Done $type for Debug -------------"
	fi
	echo ""
done

echo '=============== Grep failed testcases'

grep 'Missing' $outputPath/*$log_suffix.txt > $outputPath/all_tests.txt
echo 'Above are failed tcs, if there is nothing above then all is good.' >> $outputPath/all_tests.txt

if grep 'Missing' $outputPath/*$log_suffix.txt; then
  echo 'Some failed'
	sleep 5
	exit 1
else
	echo 'All passed'
  sleep 5
fi

echo '=============== Completed, Testcases listed above'
