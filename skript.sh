#!/bin/bash

path=$1
N=$2
stat=$3

title=$(grep "Sample Description:" $path | sed "s/^#\s*Sample Description\s*:\s*//")
expTime=$(grep "Referrence Time Stamp - UNIX:" $path | sed "s/^#\s*Referrence Time Stamp - UNIX\s*:\s*//" | sed "s/\sus.*$//")
expTime=$(($expTime / 1000000))
expTime=$(date +%d.%m.20%y_%T%Y -d @$expTime | sed "s/_/ /")
stamp=$(($(grep "Initial Time Stamp:" $path | sed "s/^#\s*Initial Time Stamp\s*:\s*//" | sed "s/\ssamples.*$//") * 1000))
freq=$(grep "Sampling Freq.\s*:\s*" $path | sed "s/\sHz.*$//" | sed "s/^#\s*Sampling Freq.\s*:\s*//")
preGain=$(grep "Pre-Amplifier Gain:" $path | sed "s/\sdB.*$//" | sed "s/^#\s*Pre-Amplifier Gain\s*:\s*//")
gain=$(grep "[^-]Amplifier Gain:" $path | sed "s/\sdB.*$//" | sed "s/^#\s*Amplifier Gain\s*:\s*//")
path=$(echo "$path" | sed "s/\.txt.*$/.dat/")

#echo "$path"
#echo "$N"
#echo "$stat"
#echo "$title"
#echo "$expTime"
#echo "$stamp"
#echo "$freq"
#echo "$preGain"
#echo "$gain"
#echo "$0"
#cat $path | ./usr/local/bin/dzachistics $N $stat

gnuplot -p -e "set terminal png enhanced notransparent nointerlace truecolor font 'Liberation, 20' size 2000, 1400;
stat='$stat';
interval='$N';
freq='$freq';
stamp='$stamp';
gain='$gain';
preGain='$preGain';
set out 'graph.png';
set title '$title, Ref.Time: $expTime';
set xlabel 'Time [ms]';
if(stat == '-v') then
{
	statName='Variance [V^2]';
	statData='Variance 1:$N';
	set ylabel '$statName';
	plot '<(cat $path | ./usr/local/bin/dzachistics $N $stat)' using (\$0*$interval*1000/$freq+$stamp):(\$1*((2.048/0x10000)*10**(0-$preGain+$gain)/20)**2) title '$statData' w l;
}
else
{
	statName='Mean [V]';
	statData='Mean 1:$N';
	set ylabel '$statName';
	plot '<(cat $path | ./usr/local/bin/dzachistics $N $stat)' using (\$0*$interval*1000/$freq+$stamp):(\$1*(2.048/0x10000)*10**(0-$preGain+$gain)/20) title '$statData' w l;
};"
    
