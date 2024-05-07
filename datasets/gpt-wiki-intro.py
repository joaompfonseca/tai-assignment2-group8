import pandas as pd
import numpy as np
import os

os.makedirs("out/wiki", exist_ok=True)
os.makedirs("out/wiki/train", exist_ok=True)
os.makedirs("out/wiki/val", exist_ok=True)

os.makedirs("out/wiki/train/0", exist_ok=True)
os.makedirs("out/wiki/train/1", exist_ok=True)
os.makedirs("out/wiki/val/0", exist_ok=True)
os.makedirs("out/wiki/val/1", exist_ok=True)

df = pd.read_parquet("raw/gpt-wiki-intro.parquet")

num_samples = df.shape[0]

for type, data in {"1": df["wiki_intro"], "0": df["generated_intro"]}.items():
    data = data.str.lower()
    data = data.str.replace("\n", " ")

    train_size = int(0.8 * num_samples)
    train_df, test_df = data.iloc[:train_size], data.iloc[train_size:]
    np.savetxt(f"out/wiki/test{type}.txt", test_df.values, fmt="%s")

    # create kfold splits
    splits = np.array_split(train_df.values, 10)

    # iterate over splits, choose 1 split for validation, rest for training
    for i, split in enumerate(splits):
        train_folds = np.concatenate([splits[j] for j in range(10) if j != i])
        np.savetxt(f"out/wiki/train/{type}/train{i}.txt", train_folds, fmt="%s")
        np.savetxt(f"out/wiki/val/{type}/val{i}.txt", split, fmt="%s")
