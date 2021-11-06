#!/bin/bash

set -e

rhasher_dir=$1
use_readline=$2

if [[ ! -f "${rhasher_dir}/rhasher" ]]
then
    echo "rhasher does not exist"
    exit 2
fi

current_dir=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)

sha1sum ${current_dir}/test_1.txt | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "SHA1 ${current_dir}/test_1.txt" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test 1. sha1sum test_1.txt vs rhasher SHA1 test_1.txt: passed"

sha256sum ${current_dir}/test_1.txt | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "SHA256 ${current_dir}/test_1.txt" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test 1. sha256sum test_1.txt vs rhasher SHA256 test_1.txt: passed"

md5sum ${current_dir}/test_1.txt | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "MD5 ${current_dir}/test_1.txt" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test 1. md5sum test_1.txt vs rhasher MD5 test_1.txt: passed"

sha1sum ${current_dir}/test_2.txt | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "SHA1 ${current_dir}/test_2.txt" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test 2. sha1sum test_2.txt vs rhasher SHA1 test_2.txt: passed"

sha256sum ${current_dir}/test_2.txt | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "SHA256 ${current_dir}/test_2.txt" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test 2. sha256sum test_2.txt vs rhasher SHA256 test_2.txt: passed"

md5sum ${current_dir}/test_2.txt | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "MD5 ${current_dir}/test_2.txt" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test 2. md5sum test_2.txt vs rhasher MD5 test_2.txt: passed"

TEXT=fslbflevwf3682snflskbfw844
echo "TEXT=${TEXT}"
echo -n "${TEXT}" | sha1sum - | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "SHA1 \"${TEXT}" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test for TEXT. sha1sum vs rhasher SHA1: passed"

echo -n "${TEXT}" | sha256sum - | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "SHA256 \"${TEXT}" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test for TEXT. sha256sum vs rhasher SHA256: passed"

echo -n "${TEXT}" | md5sum - | sed -e 's/\s.*$//' 1> ${rhasher_dir}/tmp_1
echo "MD5 \"${TEXT}" | ${rhasher_dir}/rhasher 1> ${rhasher_dir}/tmp_2
if [[ ${use_readline} == "1" ]]
then
    sed '1d' ${rhasher_dir}/tmp_2 1> ${rhasher_dir}/tmp_3 && mv ${rhasher_dir}/tmp_3 ${rhasher_dir}/tmp_2
fi
cmp ${rhasher_dir}/tmp_1 ${rhasher_dir}/tmp_2
echo "Test for TEXT. md5sum vs rhasher MD5: passed"
