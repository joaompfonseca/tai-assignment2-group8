lenghts="5000000 10000000 15000000 20000000 25000000 30000000 35000000 40000000"

cd bin
make

for lenght in $lenghts; do

    mkdir ../datasets/out/daigt/run-c$lenght

    ./was_chatted -n ../datasets/out/daigt/train/0/train0-"$lenght".txt -r ../datasets/out/daigt/train/1/train0-"$lenght".txt -t ../datasets/out/daigt/run/run0.txt -l ../datasets/out/daigt/run-c"$lenght"/out0.csv -a ../example/alphabet.txt -k 8 -s 0.1 -d 1.0
done
