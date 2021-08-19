#!/bin/bash

CurPath=$(pwd)
ProjectName="/x_platform"
GitPath="/mnt/hgfs/git/Embedded_Software_Architecture/03_Project_Code"


#cd $GitPath/.git || exit
#rsync -av --delete ../.git/ $CurPath/.git
#wait
cd $GitPath$ProjectName || exit
rsync -av --exclude *.si4project/ --delete ./ $CurPath$ProjectName
wait
echo -e "\033[32m rsync from GIT Space Success. \033[0m"



