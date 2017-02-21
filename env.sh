#!/bin/bash
echo "start cp commit id message ....................."
scp -p -P 29418 name@10.10.100.102:hooks/commit-msg .git/hooks/
scp -p -P 29418 name@10.10.100.102:bin/gerrit-cherry-pick ~/bin/
echo "cp done  commit id message ....................."                                           
