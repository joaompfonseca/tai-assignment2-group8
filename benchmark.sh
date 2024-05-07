FOLDS="0" #1 2 3 4 5 6 7 8 9"
DATASET="datasets/out/wiki"

cd bin
make
rm -rf ../$DATASET/run
mkdir ../$DATASET/run

for fold in $FOLDS; do
    touch ../$DATASET/run/run$fold.txt
    cat ../$DATASET/val/0/val$fold.txt ../$DATASET/val/1/val$fold.txt > ../$DATASET/run/run$fold.txt

    ./was_chatted -n ../$DATASET/train/0/train$fold.txt -r ../$DATASET/train/1/train$fold.txt -t ../$DATASET/run/run$fold.txt -l ../$DATASET/run/out$fold.csv -a ../example/alphabet.txt -k 6 -s 0.1
done
