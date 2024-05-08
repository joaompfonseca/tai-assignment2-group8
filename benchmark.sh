FOLDS="0" #1 2 3 4 5 6 7 8 9"
DATASET="datasets/out/wiki"

cd bin
make
rm -rf ../$DATASET/run
mkdir ../$DATASET/run

for fold in $FOLDS; do
    touch ../$DATASET/run/run$fold.txt
    cat ../$DATASET/val/0/val$fold.txt ../$DATASET/val/1/val$fold.txt > ../$DATASET/run/run$fold.txt

    #K
    for ((i=3; i<=10; i++)); do
        mkdir ../$DATASET/run-k"$i"
        ./was_chatted -n ../$DATASET/train/0/train$fold.txt -r ../$DATASET/train/1/train$fold.txt -t ../$DATASET/run/run$fold.txt -l ../$DATASET/run-k"$i"/out$fold.csv -a ../example/alphabet.txt -k "$i" -s 1.0 -d 1.0
    done

    #S
    for ((i=1; i<=10; i++)); do
        val=$(bc <<< "scale=1; $i / 10")
        mkdir ../$DATASET/run-s"$val"
        ./was_chatted -n ../$DATASET/train/0/train$fold.txt -r ../$DATASET/train/1/train$fold.txt -t ../$DATASET/run/run$fold.txt -l ../$DATASET/run-s"$val"/out$fold.csv -a ../example/alphabet.txt -k 6 -s "$val" -d 1.0
    done

done
