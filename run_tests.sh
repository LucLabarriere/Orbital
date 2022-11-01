#!/usr/bin/zsh
for test_file in `ls bin/*test*`; do; ./$test_file; done
