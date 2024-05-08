lenghts="50 100 150 200 250 300 350 400 450 500 550 600 650 700 750 800 850 900 950 1000"

cd bin
make

for lenght in $lenghts; do

    mkdir ../datasets/out/daigt/run-l$lenght

    ./was_chatted -n ../datasets/out/daigt/train/0/train0.txt -r ../datasets/out/daigt/train/1/train0.txt -t ../datasets/out/daigt/run/run0-"$lenght".txt -l ../datasets/out/daigt/run-l"$lenght"/out0.csv -a ../example/alphabet.txt -k 8 -s 0.1 -d 1.0
done
