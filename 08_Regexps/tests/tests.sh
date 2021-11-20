#!/bin/bash

build_dir=$1

if [[ ! -f "${build_dir}/esub" ]]
then
    echo "Build esub for tests running"
    exit 2
fi

esub_tmp=${build_dir}/esub_tmp
sed_tmp=${build_dir}/sed_tmp

set -x -e

function reg_test() {
    in_string=$1
    reg_expr=$2
    subst=$3
    echo "${in_string}" | sed -E "s/${reg_expr}/${subst}/" &> ${sed_tmp}
    ./esub ${reg_expr} ${subst} ${in_string} &> ${esub_tmp}
    cat ${sed_tmp} && cat ${esub_tmp}
    cmp ${sed_tmp} ${esub_tmp}
    return $?
}

reg_test 'abcstringabc' '([a-z])' '\0\1'
reg_test 'dcestringdce' 'st([a-z]*)ng' '===\0==\1=='
reg_test 'xystringxy' 'st([a-z]*)(n)g' '===\0==\1=\2='
reg_test 'zstringabz' 'st([a-z]*)(n)g' '=\\\\\\=\=\0==\1=\2='
reg_test 'string' 'st([a-z]*)(n)g' '\\\\'
reg_test 'stringstringstring' 'st([a-z]*)(n)g' '==\\1\\==\='
reg_test 'stringstringstring' 'st([a-z]*)(n)g' '==\\1\\==\=\2'
reg_test 'zstringabz' 'st(.*)(n)g' '=\\\\\\=\=\0==\1=\2='
reg_test 'zabz' 'st(.*)(n)g' '=\\\\\\=\=\0==\1=\2='

echo 'invalid reference \5' &> ${sed_tmp}
./esub 'str([a-z]*)ng' '==\0==\5==' 'abcstringabc' &> ${esub_tmp}
cat ${sed_tmp} && cat ${esub_tmp}
cmp ${sed_tmp} ${esub_tmp}

echo 'unterminated command' &> ${sed_tmp}
./esub 'str([a-z]*)ng' '==\0==\' 'abcstringabc' &> ${esub_tmp}
cat ${sed_tmp} && cat ${esub_tmp}
cmp ${sed_tmp} ${esub_tmp}

rm ${sed_tmp} ${esub_tmp}

set +x

echo "All test passed"
