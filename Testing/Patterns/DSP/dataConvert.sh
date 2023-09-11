#! /usr/bin/bash

for i in $(find . -name *.txt); do
	data=$(echo $i | awk -F / '{print $(NF-1)}')"_"
	dataName=../$(echo $i | awk -F / '{print $(NF-1)}')"Data.c"
	type=$(echo $i | awk -F _ '{print $(NF-0)}' | cut -d . -f 1)
	if [ $type == "f32" ]; then
		type="u32"
	elif [ $type == "f64" ]; then
		type="u64"
	fi
	valueName=$(echo $i | awk -F / '{print $(NF-0)}' | cut -d . -f 1)
	valueSize=$(cat $i | sed -n 2p)
	valueReal=$(cat $i | sed '1,2d' | grep -v '//' | tr "\n" ",")
	if [ ! -f "$dataName" ]; then
		echo "#include <stdint.h>" >>$dataName
		echo "" >>$dataName
		echo "typedef int8_t q7;" >>$dataName
		echo "typedef int16_t q15;" >>$dataName
		echo "typedef int32_t q31;" >>$dataName
		echo "typedef int64_t q63;" >>$dataName
		echo "" >>$dataName
		echo "typedef int8_t s8;" >>$dataName
		echo "typedef int16_t s16;" >>$dataName
		echo "typedef int32_t s32;" >>$dataName
		echo "typedef int64_t s64;" >>$dataName
		echo "" >>$dataName
		echo "typedef uint32_t u32;" >>$dataName
		echo "typedef uint64_t u64;" >>$dataName
		echo "" >>$dataName
		echo "typedef float f32;" >>$dataName
		echo "typedef double f64;" >>$dataName
		echo "" >>$dataName
	fi
	echo "const $type $data$valueName[$valueSize]={$valueReal};" >> $dataName
	echo "" >>$dataName
	sed -i s/,}/}/g $dataName
done
