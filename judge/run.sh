code=$1
data=$2
Lang=$3
current=`pwd`
CodiDir="$(dirname "$current")"

echo $current
echo $CodiDir


docker run --rm -it -e MARKPATH=/home/mark -e PROBPATH=/home/prob/ -v ${CodiDir}/judge:/home/judge -v ${CodiDir}/volume/mark_no/${code}:/home/mark -v ${CodiDir}/volume/prob_no/${data}:/home/prob --memory="2g" judge:1.0 /bin/bash

#docker run --rm -it -e MARKPATH=/home/mark -e PROBPATH=/home/prob/ -v ${CodiDir}/judge:/home/judge -v ${CodiDir}/volume/mark_no/${code}:/home/mark -v ${CodiDir}/volume/prob_no/${data}:/home/prob judge:1.0 /bin/bash
