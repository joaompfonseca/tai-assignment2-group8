FOLDS="0" #1 2 3 4 5 6 7 8 9"
# K_VALUES="6"
# SMOOTHING_VALUES="0.1"
DATASET="datasets/out/daigt"

cd bin
make
rm -rf ../$DATASET/run
mkdir ../$DATASET/run

for fold in $FOLDS; do
    rm ../$DATASET/train/0/train$fold.txt.order6.cache
    rm ../$DATASET/train/1/train$fold.txt.order6.cache

    touch ../$DATASET/run/run$fold.txt
    cat ../$DATASET/val/0/val$fold.txt ../$DATASET/val/1/val$fold.txt > ../$DATASET/run/run$fold.txt

    ./was_chatted -n ../$DATASET/train/0/train$fold.txt -r ../$DATASET/train/1/train$fold.txt -t ../$DATASET/run/run$fold.txt -l ../$DATASET/run/out$fold.csv -a ../example/alphabet.txt -k 6 -s 1.0 -d 1.0
done
